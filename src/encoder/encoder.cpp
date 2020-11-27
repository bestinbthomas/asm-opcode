#include<cstdio>
#include<unordered_set>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/algorithm/string/split.hpp>
#include "include/encoder/encoder.h"
#include "converter/converter.h"

Encoder::Encoder(std::string in) :
insn(0) {
	boost::trim_all(in);
	std::vector<std::string> result;
	boost::split(result, in, boost::is_any_of(" "));

	cmd = result[0];
	boost::trim(cmd);

	insn = Mapper::getOpcode(cmd);
	type = Mapper::getInstructionType(cmd);

	if(type == INVALID) {
		insn = 0;
		return;
	}

	std::string argString = in.substr(cmd.size());
	boost::split(args, argString, boost::is_any_of(","));

	for(size_t i=0;i<args.size();i++){
		boost::trim(args[i]);
	}

	std::unordered_set<std::string> bracketList = {"lb", "lh", "lw", "ld", "lbu", "lhu", "lwu","jalr","sb", "sh", "sw", "sd"};

	if(bracketList.find(cmd) != bracketList.end() && args.size() == 2){
		std::vector<std::string> t_args;
		args[1] = args[1].substr(0,args[1].size()-1);
		boost::split(t_args,args[1],boost::is_any_of("("));
		args[1] = t_args[1];
		args.push_back(t_args[0]);
	}

	if(type == R_TYPE || type == I_TYPE || type == U_TYPE || type == J_TYPE) {
		addRd();
	}
	if(type == R_TYPE || type == I_TYPE || type == S_TYPE || type == B_TYPE) {
		addRs1();
	}
	if(type == R_TYPE || type == S_TYPE || type == B_TYPE) {
		addRs2();
	}

	if(type != R_TYPE) {
		addImm();
	}
}

void Encoder::addRd() {
	uint32_t rd = Mapper::getRegNumber(args[0]);
	rd <<= 7;
	insn |= rd;
}

void Encoder::addRs1() {
	uint32_t rs1;
	switch(type){
		case R_TYPE:
		case I_TYPE:
		rs1 = Mapper::getRegNumber(args[1]);
		break;
		case S_TYPE:
		case B_TYPE:
		rs1 = Mapper::getRegNumber(args[0]);
		break;
	}
	rs1 <<=15;
	insn |= rs1;
}

void Encoder::addRs2() {
	uint32_t rs2;
	switch(type){
		case R_TYPE:
		rs2 = Mapper::getRegNumber(args[2]);
		break;
		case S_TYPE:
		case B_TYPE:
		rs2 = Mapper::getRegNumber(args[1]);
		break;
	}
	rs2 <<=20;
	insn |= rs2;
}

void Encoder::addImm() {
	std::string immStr = args[args.size()-1];
	int32_t imm;
	if(immStr[0] == '0' && immStr[1] == 'x') sscanf(immStr.c_str(),"%x",&imm);
	else sscanf(immStr.c_str(),"%d",&imm);

	if(type == I_TYPE) {
		imm <<=20;
		insn |= imm;
	}
	if(type == S_TYPE) {
		uint32_t maskL = 0x1F,
		maskH = 0x7F<<5,
		immL = imm & maskL,
		immH = (imm & maskH)>>5;

		insn |= immL << 7;
		insn |= immH << 25;
	}

	if(type == B_TYPE) {
		uint32_t mask1 = 1<<10,
		mask2 = 0xF<<1,
		mask3 = 0x3F<<5,
		mask4 = 1<<12,
		imm1 = (imm & mask1)>>10,
		imm2 = (imm & mask2)>>1,
		imm3 = (imm & mask3)>>5,
		imm4 = (imm & mask4)>>12;

		insn |= imm1<<7;
		insn |= imm2<<8;
		insn |= imm3<<25;
		insn |= imm4<<31;
	}
	if(type == U_TYPE) {
		uint32_t mask = 0xFFFFF << 12;
		insn |= imm & mask;
	}
	if(type == J_TYPE) {
		uint32_t mask1 = 0xFF<<12,
		mask2 = 1<<11,
		mask3 = 0x3FF<<1,
		mask4 = 1<<20,
		imm1 = (imm & mask1)>>12,
		imm2 = (imm & mask2)>>11,
		imm3 = (imm & mask3)>>1,
		imm4 = (imm & mask4)>>20;

		insn |= imm1<<12;
		insn |= imm2<<20;
		insn |= imm3<<21;
		insn |= imm4<<31;
	}

}

uint32_t Encoder::getFinalOpcode() const{
	return insn;
}

std::string Encoder::getFinalOpcodeString(bool pretty) const{
	return convert::insnToString(insn, type, pretty);
}

std::string Encoder::getArgString() const{
	std::string result;
	for(size_t i=0;i<args.size();i++){
		result += "args[";
		result += i;
		result += "] : ";
		result += args[i];
		result += '\n';
	}
	return result;
}
