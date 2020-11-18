#pragma once
#include<array>

namespace convert {
	template<int size>
	std::array<bool,size> dtobarray(int num) {
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

	int test(int a);
}
