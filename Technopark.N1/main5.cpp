#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==5
#define _ACTIVE__FILE
#else 
#undef _ACTIVE_FILE
#endif
#else
#define _ACTIVE__FILE
#endif

#ifdef _ACTIVE__FILE
#include <iostream>
#include <cstdlib>
#include <cstring>

#define CUSTOMSTACK
#ifdef CUSTOMSTACK


template <typename T>
class stack {
protected:
	const static size_t multiplyer = 2;

	T**					_arr;
	size_t				_s, _alloc;

public:
	stack() :_arr(0), _s(0), _alloc(1) {
		this->_arr = new T*[this->_alloc];

	};

	void push(const T& val) {
		if (this->_s == this->_alloc)
		{
			this->_alloc *= stack::multiplyer;
			T** narr = new T*[this->_alloc];
			if (narr == NULL)
				throw std::logic_error("OUT OF MEMORY");
			//raw copy pointers
			memcpy(narr, this->_arr, this->_s*sizeof(T*));
			delete[] this->_arr;
			this->_arr = narr;
		}
		//add element
		this->_arr[this->_s++] = new T(val);

	}

	T& top() {
		return *this->_arr[this->_s - 1];
	}

	const T& top() const {

		return *this->_arr[this->_s - 1];
	}
	void pop(){
		//pop last element
		delete this->_arr[--this->_s];
		//if number of remaining elements is lower by one compared to resize threshold
		if (this->_alloc / (this->_s+1) >= stack::multiplyer) {
			//try to shrink
			size_t al = this->_alloc / stack::multiplyer;
			T** narr = new T*[al];
			if (narr != NULL) {
				//shrink successfull
				//copy pointers
				memcpy(narr, this->_arr, this->_s*sizeof(T*));
				//delete old array
				delete[] this->_arr;
				this->_arr = narr;
				//update allocation size
				this->_alloc = al;
			}
		}
	}

	~stack() {
		for (size_t i = 0; i < this->_s; ++i)
			delete this->_arr[i];
		delete[] this->_arr;
	}

	size_t size() {
		return this->_s;
	}

	bool empty() {
		return this->_s == 0;

	}

};

#else
#include <stack>
using namespace std;
#endif
enum TagType  { OPENING , CLOSING, UNKNOWN };

static const char CTS[] = {')',']','}'}, OTS[] = {'(','[','{'}, ck = 3;

TagType tag_type(const char c) {
	int i = 0;
	for (; i < ck; ++i) {
		if (CTS[i] == c)
			return CLOSING;
	}
	for (i = 0; i < ck; ++i) {
		if (OTS[i] == c)
			return OPENING;
	}
	return UNKNOWN;

}

int tag_kind(const char c) {
	int i = 0;
	for (; i < ck; ++i) {
		if (CTS[i] == c)
			return i;
	}
	for (i = 0; i < ck; ++i) {
		if (OTS[i] == c)
			return i;
	}
	return -1;
}

char tag_opposite(const char c) {
	int i = 0;
	for (; i < ck; ++i)
		if (CTS[i] == c)
			return OTS[i];
	
	for (i = 0; i < ck; ++i)
		if (OTS[i] == c)
			return CTS[i];
	return '\0';
}


char* in() {
	const size_t step = 5;
	size_t size = 1,b;
	char* str = (char*)calloc(1,sizeof(char));
	char buf[step];
	do {
		str = (char*) realloc(str,(size+=step-1)*sizeof(char));
		std::cin.get(buf, step);
		b = strlen(buf);
		memcpy(str+size-step, buf, b+1);

	} while (b);
	return str;
}


int main() {
	char* str = in();
	stack<char> lch, opt, rch;
	
	for (int i = 0, s = strlen(str); i < s; ++i)
	{
		char ch = str[i];
		TagType tt = tag_type(ch);
		int pk = tag_kind(ch);
		if (tt == CLOSING) {
			if (opt.empty())
				lch.push(tag_opposite(ch));
			else if (pk != tag_kind(opt.top())) {
				std::cout << "IMPOSSIBLE";
				return 0;
			}
			else
				opt.pop();

		}
		if (tt == OPENING)
			opt.push(ch);
	}
	while (!opt.empty()) {
		rch.push(tag_opposite(opt.top()));
		opt.pop();
	}
	
	while (!lch.empty()) {
		std::cout << lch.top();
		lch.pop();
	}
	std::cout << str;
	while (!opt.empty()) {
		std::cout << tag_opposite(opt.top());
		opt.pop();
	}
	free(str);
	
	return 0;
}

#endif