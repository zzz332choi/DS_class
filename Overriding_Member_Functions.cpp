#include <iostream>

using namespace std;

class BaseClass {
private:
	int datum;
public:
	BaseClass(int datumIn) {	datum = datumIn;	}
	void print(void) const {
		cout << "Datum in Base Class is : " << datum << endl;
	}
};

class Derived : public BaseClass {
private:
	int derivedDatum;
public:
	Derived(int baseDataum, int datumIn);
	void print(void) const;
};

Derived::Derived(int baseDatum, int datumIn) :BaseClass(baseDatum) {
	derivedDatum = datumIn;
}

void Derived::print(void)	const {
	BaseClass::print();
	cout << "Datum in Derived Class is : " << derivedDatum << endl;
}

int main() {
	BaseClass baseObj(1);
	Derived	derObj(2, 3);

	baseObj.print();
	derObj.print();
}