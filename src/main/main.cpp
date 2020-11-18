#include<iostream>
#include"converter.h"

int main(){
	std::array a = convert::dtobarray<16>(5);
	for(int i=0;i<a.size();i++) std::cout<<a[i];
	std::cout<<'\n'<<convert::test(3)<<'\n';
	std::cout<<"it works!!!\n";
}
