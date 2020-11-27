#include<iostream>
#include<string>
#include<cstring>
#include"encoder/encoder.h"
#include"decoder/decoder.h"

#define find_set(set,key) set.find(key) != set.end()

int main(int argc,char* argv[]){
	std::string in;
	std::unordered_set<std::string> args;
	for(int i=0;i<argc;i++){
	    args.insert(std::string(argv[i]));
	}

	while(std::getline(std::cin,in)) {
		if(find_set(args,"-p")) std::cout<<in<<'\n';
		if(find_set(args,"-d")){
			Decoder d(in,find_set(args,"-h"));
			std::cout<<d.getInstruction()<<"\n\n";
		}
		else {
			Encoder e(in);
			if(find_set(args,"-a")) std::cout<<e.getArgString();
			if(find_set(args,"-od")) std::cout<<e.getFinalOpcode()<<'\n';
			else if(find_set(args,"-x")) std::cout<<std::hex<<std::uppercase<<e.getFinalOpcode()<<'\n';
			else std::cout<<e.getFinalOpcodeString(find_set(args,"-h"))<<"\n\n";
		}
	}
}
