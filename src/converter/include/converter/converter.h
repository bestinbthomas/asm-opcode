#pragma once
#include<array>
#include<string>
#include<math.h>
#include"mapping/instructionType.h"

namespace convert {
	template<int size>
	std::array<bool,size> dtobarray(int64_t num) {
		std::array<bool, size> arr;
		int a = size;
		bool neg = num<0?true:false;
		if(neg) num++;
		num = abs(num);
		while(a--){
			arr[a] = num%2;
			if(neg) arr[a] = !arr[a];
			num/=2;
		}
		return arr;
	}

	std::string insnToString(uint32_t insn, InstructionType type, bool pretty);

}
