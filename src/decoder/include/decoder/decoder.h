#include <cinttypes>
#include <string>
#include <vector>
#include <unordered_map>
#include "mapping/mapping.h"

class Decoder {
private:
	uint32_t insn;
	std::string cmd;
	InstructionType type;
	std::vector<std::string> args;

	const std::unordered_map<std::string,uint32_t> maskMap;
	bool alias;

	void findCmd();
	void setRegister(uint8_t reg);
	void setImm();

public:
	Decoder(std::string input, bool alias);
	std::string getInstruction() const;
};
