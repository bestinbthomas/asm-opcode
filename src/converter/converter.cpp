#include <unordered_set>
#include "include/converter/converter.h"

namespace convert {
	std::string insnToString(uint32_t insn, InstructionType type, bool pretty) {
		if(insn == 0) return "Invalid command";
		std::unordered_set<uint8_t> divset = {19,24};
		switch(type) {
			case I_TYPE:
				divset.insert(16);
				divset.insert(11);
				break;
			case R_TYPE:
			case S_TYPE:
			case B_TYPE:
				divset.insert(16);
				divset.insert(11);
				divset.insert(6);
				break;
			case INVALID:
				return "Cannot determine type";
				break;
		}

		std::array<bool,32> insn_arr = dtobarray<32>(insn);
		std::string result;
		for(size_t i = 0; i < insn_arr.size(); i++)	{
			result += insn_arr[i] ? "1" : "0";
			if(pretty && divset.find(i) != divset.end()) result += " | ";
		}
		return result;
	}
}

