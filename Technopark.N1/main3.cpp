#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==3
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif

#ifdef _ACTIVE__FILE
#include <iostream>
#include <cmath>

int* in(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];

	return a;
}


int main(int argc, char** argv) {
	int n = 0, m = 0, k = 0;
	std::cin >> n;
	int* a = in(n);
	int left = 0, right = n - 1, target =-1;
	switch (n) {
	case 0:
		return 1;
		break;
	case 1:
		std::cout << a[left];
		break;
	case 2:
		std::cout << (a[left] > a[right] ? left : right);
		break;
	default:
		do  {
			target = (int)ceil((double)(left + right) / 2);
			if (a[left] > a[target] && a[target] > a[right]) {
				//monotonous start > target > end
				right = target;
			}
			else if (a[right] > a[target] && a[target] > a[left]) {
				//montonous start < target < end
				left = target;
			}
			else {
				//mountain start < target > end
				int lt = (int)floor((double)(left + target) / 2),
					rt = (int)ceil((double)(right + target) / 2);
				if (a[lt] < a[target] && a[rt] < a[target]) {
					// lt < target > rt
					if (left == lt && right == rt)
						break;
					left = lt;
					right = rt;

				}
				else if (a[lt] > a[rt])
					// left < lt > target > rt > right
					right = target;
				
				else 
					// left < lt < target < rt > right
					left = target;
				
					
			}

			
		} while (right - left > 1);
		if (left == target)
			target = right;
		else if (right == target)
			target = left;
		std::cout << target;
		break;
	}
	delete a;
	return 0;
}



#endif

