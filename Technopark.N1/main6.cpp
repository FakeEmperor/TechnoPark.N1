#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==6
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif
#include <cstdlib>
#include <iostream>

#ifdef _ACTIVE__FILE
unsigned long long int recursion_partition(int n) {
	if (n == 0)
		return 1;
	unsigned long long int **arr = new unsigned long long int*[n+1];
	int i,j;
	for (i = 0; i <= n; ++i)
		arr[i] = new unsigned long long int[n+1];
	//work
	unsigned int pn = 0;
	for (i = 0; i <= n; ++i)
		for (j = 0; j <= n; ++j) {
			if (i == 0 && j == 0)
				arr[i][j] = 1;
			else if (i < j)
				arr[i][j] = arr[i][i];
			else if (i > 0 && j == 0)
				arr[i][j] = 0;
			else
				arr[i][j] = arr[i][j - 1] + arr[i - j][j];
		}
	pn = arr[n][n];
	//free
	for (i = 0; i <= n; ++i)
		delete[] arr[i];
	delete[] arr;
	return pn;
}

int main() {
	int n;
	std::cin >> n;
	unsigned long long int rn = recursion_partition(n);
	std::cout << rn;
	return 0;
}

#endif