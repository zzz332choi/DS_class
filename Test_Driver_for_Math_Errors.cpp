#include <iostream>

using namespace std;

class Error {
public: 
	virtual void printMessage(void) {
		cout << "Error: type Error" << endl;
	}
};

class Arithmetic :public Error {
public:
	virtual void printMessage(void) {
		cout << "Error: type Arithmetic" << endl;
	}
};

class Divbyzero :public Arithmetic {
public:
	virtual void printMessage(void) {
		cout << "Error: divisor is zero" << endl;
	}
};

class DivbyNeg : public Arithmetic {
public:
	virtual void printMessage(void) {
		cout << "Error: negative divisor" << endl;
	}
};

class BadOperator : public Arithmetic {
public:
	virtual void printMessage(void) {
		cout << "Error: invalid operator" << endl;
	}
};

double math(char oper, double data1, double data2) {
	double result;

	switch(oper) {
	case '+':
		result = data1 + data2;
		break;
	case '-':
		result = data1 - data2;
		break;
	case '*':
		result = data1 * data2;
		break;
	case '/':
		if (data2 == 0) throw Divbyzero();
		if (data2 < 0) throw DivbyNeg();
	
		result = data1 / data2;
		break;
	default: 
		throw BadOperator();
		break;
	}

	return result;
}

int main() {
	double data1, data2;
	char oper;

	cin >> data1 >> data2 >> oper;

	try {
		double result = math(oper, data1, data2);
		cout << result << endl;
	}
	catch (Error& error){
		error.printMessage();
		exit(100);
	}
}