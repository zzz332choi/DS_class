#include <iostream>
using namespace std;

// classs template declaration part
template <class T>
class Test {
public: 
	Test();
	~Test();
	T Data(T);
};

template<class T>
Test<T>::Test() {
	cout << "C" << endl;
}

template <class T>
Test<T>::~Test() {
	cout << "D" << endl;
}

template <class T>
T Test<T>::Data(T v) {
	return v;
}

int main(void) {
	Test<int> Var1;
	Test<double>Var2;
	Test<char>Var3;

	cout << Var1.Data(100) << endl;
	cout << Var2.Data(1.234) << endl;
	cout << Var3.Data('k') << endl;
}