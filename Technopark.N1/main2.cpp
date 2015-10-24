#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==2
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif

#ifdef _ACTIVE__FILE
#include <iostream>

int* in(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];

	return a;
}

int solve(int*a, int*b, int m, int n, int k) {
	int count = 0;
	for (int diff = 0, j = m - 1, target = 0, i = 0; i < n && j >= 0; ++i)
	{
		target = k - a[i];
		diff = target - b[j];
		if (diff < 0) {
			//find j
			for (; j >= 0; --j)
			{
				diff = target - b[j];
				if (diff > 0)
					break;
				else if (!diff) {
					++count;
					break;
				}
			}
		}
		else if (diff == 0)
			++count;
	}
	return count;
}

void die(const char* msg){
	std::cout << msg;
}

int main(int argc, char** argv) {
	int n = 0, m = 0, k = 0;
	std::cin >> n;
	int* a = in(n);
	std::cin >> m;
	int* b = in(m);
	std::cin >> k;
	if (!m) {
		die("[error]");
		return 1;
	}
	//int *sp = n > m ? a : b;
	//int cn = n > m ? n : m, dl = cn - mn;
	int count = solve(a,b,m,n,k);
	
	std::cout << count;
	delete a;
	delete b;
	return 0;
}



#endif

