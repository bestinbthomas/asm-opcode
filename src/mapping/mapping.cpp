#include <string>
#include <unordered_map>
#include "include/mapping/mapping.h"

const std::unordered_set<std::string> Mapper::RType = {"add", "sub", "sll", "slr", "sltu", "xor", "srl", "sra", "or", "and"};
const std::unordered_set<std::string> Mapper::IType = {"lb", "lh", "lw", "ld", "lbu", "lhu", "lwu", "addi", "slli", "xori", "srli", "srai", "ori", "andi", "jalr", "slti""sltiu"};
const std::unordered_set<std::string> Mapper::SType = {"sb", "sh", "sw", "sd"};
const std::unordered_set<std::string> Mapper::BType = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};
const std::unordered_set<std::string> Mapper::UType = {"lui"};
const std::unordered_set<std::string> Mapper::JType = {"jal"};

const std::unordered_map<std::string,uint32_t> Mapper::matchMap = {
	#define DECLARE_INSN(command, match, mask) {#command, match},
	#include"include/mapping/instructions.h"
	#undef DECLARE_INSN
};

const std::unordered_map<std::string,uint8_t> Mapper::regNames = {
	#define DECLARE_REGISTER(name,number) {#name,number},
	#include"registers.h"
	#undef DECLARE_REGISTER
};

const std::unordered_map<std::string,uint8_t> Mapper::regAliases = {
	#define DECLARE_REGISTER_ALIAS(name,number) {#name,number},
	#include"registers.h"
	#undef DECLARE_REGISTER_ALIAS
};

Mapper::Mapper() {}

uint32_t Mapper::getOpcode(std::string command){
	return matchMap.at(command);
}

InstructionType Mapper::getInstructionType(std::string command) {
	if(RType.find(command) != RType.end()) return R_TYPE;
	if(IType.find(command) != IType.end()) return I_TYPE;
	if(SType.find(command) != SType.end()) return S_TYPE;
	if(BType.find(command) != BType.end()) return B_TYPE;
	if(UType.find(command) != UType.end()) return U_TYPE;
	if(JType.find(command) != JType.end()) return J_TYPE;
	return INVALID;
}

uint8_t Mapper::getRegNumber(std::string regName) {
	if(regNames.find(regName) != regNames.end()) return regNames.at(regName);
	if(regAliases.find(regName) != regAliases.end()) return regAliases.at(regName);
	return -1;
}


