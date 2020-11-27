#include <string>
#include <vector>
#include "mapping/mapping.h"

class Encoder {
private:
	uint32_t insn;
	std::string cmd;
	InstructionType type;
	std::vector<std::string> args;

	void addRd();
	void addRs1();
	void addRs2();
	void addImm();

public:
	Encoder(std::string input);
	uint32_t getFinalOpcode() const;
	std::string getFinalOpcodeString(bool pretty) const;
	std::string getArgString() const;

};
