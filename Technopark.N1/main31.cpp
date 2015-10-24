#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==31
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif

#ifdef _ACTIVE__FILE
//#define _DEBUG_PRINT_ //DEFINE IT TO VIEW DEBUG
#include <iostream>
#include <cmath>

int* in(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];

	return a;
}


void debug_print(int step, size_t pos, int* arr, size_t n, size_t left, size_t right, bool is_more) {
	std::cout << ">step " << step <<":";
	for (size_t i = 0; i < n; ++i)
		std::cout << (i == left?"|":"") << (i==pos?"^":"")<< arr[i] << (i==right?"|":" ");
	
	std::cout << " :: cur < prev (change) ? " << (is_more ? "YES" : "NO");
	std::cout << std::endl;
}


int find_alt(int* arr, size_t n) {
	if (n == 0)
		return -1;
	int cur = arr[0], c;
	size_t step = 1, nn = n, left = 0, right = n-1, p = -1;
#ifdef _DEBUG_PRINT_
	size_t _debug_i =	1;
#endif
	do {
		p = left + step <= right ? left + step : right;
		c = arr[p];
		#ifdef _DEBUG_PRINT_
		debug_print(_debug_i, p, arr, n, left, right, c<cur);
		++_debug_i;

		#endif
		if (c < cur) {
			right = left;
			left -= step >> 1;
			step = 1;
			nn = right + 1 - left;
			cur = arr[left];
		}
		else {
			left += step;
			step <<= 1; 
			cur = c;
			nn >>= 1;
		}
		
	} while (p!=right&&nn);
	return p;
}

int find(int* arr, size_t n) {
#ifdef _DEBUG_PRINT_
	int _i_debug = 1;
	std::cout << "ALTERNATIVE FIND" << std::endl;
#endif
	if (!n)
		return -1;
	size_t nn = n, p = -1, left = 0, right = n-1;
	int cur = arr[left];
	while (nn > 1) {
		p = (left + right +1) / 2;
		
#ifdef _DEBUG_PRINT_
		debug_print(_i_debug, p, arr, n, left, right, arr[p] > cur);
#endif
		if (p + 1 <= right) {
			if (arr[p] < arr[p + 1])
				left = p + 1;
			else
				right = p;
		}
		else if (p - 1 >= left) {
			if (arr[p] > arr[p - 1])
				left = p;
			else
				right = p-1;
		}
		nn = right - left +1;
	}
	return (left + right + 1) / 2;
}

int main() {
	int n;
	std::cin >> n;
	int* arr = in(n);
	std::cout << find(arr, n);
#ifdef _DEBUG_PRINT_
	std::cout << std::endl;
	std::cout << find_alt(arr,n);
#endif
	return 0;
}



#endif