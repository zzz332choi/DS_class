#include <iostream>

using namespace std;

double divide(double dividend, double divisor) {
	if (divisor == 0) throw divisor;
	return dividend / divisor;
}

int main() {

	double dividend, divisor;
	cin >> dividend >>  divisor;

	try {
		double quotient = divide(dividend, divisor);
		cout << "Quorient is : " << quotient << endl;
	}
	catch (double& error) {
		cout << "Error 100: divisor is 0" << endl;
		exit(100);
	}

}