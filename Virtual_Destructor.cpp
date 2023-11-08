#include <iostream>

using namespace std;

// 대충 두 소멸자 앞에 어디든 virtual을 붙이면 해결되는데 그냥 다 붙이는 걸로 합의보자
// virtual 을 붙이지 않은 경우 3000byte의 메모리 누수가 생긴다. 

class Base {
public:
	virtual ~Base() {
		cout << "Base destructor!" << endl;
	}
};

class Derived : public Base {
public: 
	char* largeBuffer;
	Derived() {
		largeBuffer = new char[3000];
	}

	~Derived() {
		cout << "Derived dextructor!" << endl;
		delete[] largeBuffer;
	}
};

int main() {
	cout << "----Derived# der1 = new Derived() ----" << endl;
	Derived* der1 = new Derived();
	delete der1;

	cout << "\n\n---Base* der2 = new Derived() ---" << endl;
	Base* der2 = new Derived();
	delete der2;
}