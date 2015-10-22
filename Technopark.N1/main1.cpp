#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==1
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif


#ifdef _ACTIVE__FILE
#include <iostream>

void swap(int* arr, int cnt) {
	int mid = cnt / 2;
	for (int i = 0; i < mid; ++i) {
		arr[i] ^= arr[cnt - i - 1];
		arr[cnt - i - 1] ^= arr[i];
		arr[i] ^= arr[cnt - 1 - i];
	}

}

void die(const char* msg){
	std::cout << msg;
}

int main(int argc, char** argv){
	int cnt = 0;
	std::cin >> cnt;
	if (cnt == 0) {
		die("[error]");
		return 1;
	}
	int* arr = new int[cnt];
	for (int i = 0; i < cnt; ++i)
		std::cin>>arr[i];
	swap(arr, cnt);
	for (int i = 0; i < cnt; ++i)
		std::cout << arr[i] << (i<cnt-1?" ":"");

#ifdef _DEBUG
	std::cin.get();
#endif
	delete []arr;
	return 0;
}



#endif