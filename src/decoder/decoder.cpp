#include "decodeHelper.h"
#include "include/decoder/decoder.h"
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <utility>
#include<cstdio>

Decoder::Decoder(std::string in,bool alias):
maskMap({
	#define DECLARE_INSN(name,match,mask) {#name,mask},
	#include "mapping/instructions.h"
	#undef DECLARE_INSN
}), alias(alias) {
	boost::trim_all(in);
	boost::to_lower(in);
	if(in[0] == '0' && in[1] == 'x') {
		sscanf(in.c_str(),"%x",&insn);
	}
	else {
		sscanf(in.c_str(),"%d",&insn);
	}

	findCmd();

	type = Mapper::getInstructionType(cmd);

	if(type == INVALID) {
		cmd = "NOT LISTED";
		args.push_back("The hex entered did not match any known command");
	}

	insn_t helper(insn);

	if(type == R_TYPE || type == I_TYPE || type == U_TYPE || type == J_TYPE) {
		uint64_t rd = helper.rd();
		setRegister(rd);
	}
	if(type == R_TYPE || type == I_TYPE || type == S_TYPE || type == B_TYPE) {
		uint64_t rs1 = helper.rs1();
		setRegister(rs1);
	}
	if(type == R_TYPE || type == S_TYPE || type == B_TYPE) {
		uint64_t rs2 = helper.rs2();
		setRegister(rs2);
	}

	if(type != R_TYPE) {
		setImm();
	}
}

void Decoder::setRegister(uint8_t reg) {
	if(alias) {
		for (std::pair<std::string,uint8_t> p : Mapper::regAliases) {
			if(reg == p.second){
				args.push_back(p.first);
				return;
			}
		}
	}
	else {
		for (std::pair<std::string,uint8_t> p : Mapper::regNames) {
			if(reg == p.second){
				args.push_back(p.first);
				return;
			}
		}
	}
}

void Decoder::setImm(){
	insn_t helper(insn);
	int64_t imm;
	switch(type) {
		case I_TYPE:
		imm = helper.i_imm();
		break;
		case S_TYPE:
		imm = helper.s_imm();
		break;
		case B_TYPE:
		imm = helper.sb_imm();
		break;
		case U_TYPE:
		imm = helper.u_imm();
		break;
		case J_TYPE:
		imm = helper.uj_imm();
		break;
		default: imm = 0;
	}
	char immc[11];

	sprintf(immc,"%ld",imm);
	args.emplace_back(immc);
}

void Decoder::findCmd() {
	for (std::pair<std::string, uint32_t> p : Mapper::matchMap) {
		uint32_t mask = maskMap.at(p.first);
		if((insn & mask) == p.second) {
			cmd = p.first;
			return;
		}
	}
}

std::string Decoder::getInstruction() const {
	std::string instruction(cmd + " ");
	for(std::string arg : args) {
		instruction += arg + ", ";
	}
	return instruction.substr(0,instruction.size()-2);
}
