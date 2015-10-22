#ifdef _DEBUG
#include "ProjectSettings.h"
#if defined(_ACTIVE_PROJECT_ALGO) && _ACTIVE_PROJECT_ALGO==4
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
	void pop() {
		//pop last element
		delete this->_arr[--this->_s];
		//if number of remaining elements is lower by one compared to resize threshold
		if (this->_alloc / (this->_s + 1) >= stack::multiplyer) {
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

template <typename T>
class Queue {
	stack<T> ls, rs;

public:
	void shift(const T &val) {
		if (rs.empty())
			rs.push(val);
		else
			ls.push(val);

	};

	T unshift(){
		T val = rs.top();
		rs.pop();
		if (rs.empty())
			while (!ls.empty()) {
				rs.push(ls.top());
				ls.pop();
			}
		return val;
	};
	bool empty(){
		return rs.empty();
	};
};


int main(void){
	Queue<int> q;
	int nc = 0;
	std::cin >> nc;
	bool yes = true;
	for (int cmd = 0, val = 0; nc > 0; --nc){
		std::cin >> cmd;
		std::cin >> val;
		switch (cmd){
		case 3:
			//push
			q.shift(val);
			break;
		case 2:{
			int v = q.empty()? -1 : q.unshift();
			if (!(yes = v == val))
				goto FINAL; //olololo! Haters gonna hate
			break;

		}
		default:
			std::cout << "[error]";
			return 1;
			break;
		}
	}
	
FINAL:
	std::cout << (yes ? "YES" : "NO");
	return 0;
}



#endif
