#pragma once
#include<string>
#include<unordered_map>
#include<unordered_set>
#include"instructionType.h"
#define RISCV_LAST_FP_REGNUM 64

class Mapper {
	const static std::unordered_set<std::string> RType;
	const static std::unordered_set<std::string> IType;
	const static std::unordered_set<std::string> SType;
	const static std::unordered_set<std::string> BType;
	const static std::unordered_set<std::string> UType;
	const static std::unordered_set<std::string> JType;


public:
	Mapper();
	const static std::unordered_map<std::string,uint32_t> matchMap;
	const static std::unordered_map<std::string,uint8_t> regNames;
	const static std::unordered_map<std::string,uint8_t> regAliases;

	static InstructionType getInstructionType(std::string command);
	static uint32_t getOpcode(std::string command);
	static uint8_t getRegNumber(std::string regName);
};

