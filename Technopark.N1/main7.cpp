#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==7
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif


#ifdef _ACTIVE__FILE
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


/**
У каждого атлета есть сила и масса
m1 > m2 <=> f1 < f2


**/
template <typename T1, typename T2>
class pair {
public:
	T1 first;
	T2 second;
	pair(const T1& a, const T2& b) : first(a), second(b) {

	}
};

typedef pair<int, int> ipair;

class OptimizationList {
	std::vector<ipair> initial;

	static bool sort(const ipair& left,const ipair& right) {
		if (left.first != right.first)
			return left.first < right.first;
		else
			return left.second < right.second;
	}
public:
	
	void in() {
		int n = 0;
		int m = 0, f = 0;
		while(!std::cin.eof()) {
			std::cin >> m >> f;
			initial.push_back(ipair(m, f));
		}

		//sort by descendance
		std::sort(this->initial.begin(), this->initial.end(),&sort);

	}
	std::vector<ipair> algo_alt() {
		size_t s = initial.size();
		size_t supporting_weight = s? initial[0].first : 0;
		std::vector<ipair> tower;
		if (s)
			tower.push_back(initial[0]);
		for (int i = 1; i < s; ++i)
			if (initial[i].second >= supporting_weight) {
				supporting_weight += initial[i].first;
				tower.push_back(initial[i]);
			}
		return tower;
	}

	static void print_tower(std::vector<ipair>& tower) {
		std::cout << "Tower: " << std::endl;
		std::cout << "M:\tF:\t" << std::endl;
		for (int i = 0, s = tower.size(); i < s; ++i)
			std::cout << tower[i].first  <<"\t" << tower[i].second << std::endl;

	}
};




int main() {
	OptimizationList ol;
	ol.in();

	std::vector<ipair> mtower = ol.algo_alt();
	std::cout << mtower.size();
	return 0;
}

#endif