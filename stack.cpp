#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
using namespace std;

template<class T>
//ver1
//void ChageSize1D(T*& a, const int oldsize, const int newsize) {
//	if (newsize < 0) throw "New length must be >= 0";
//
//	T* temp = new T[newsize];
//	int number = min(newsize, oldsize);
//	copy(a, a + number, temp);
//	delete[] a;
//	a = temp;
//}

//ver2
void ChageSize1D(T** a, const int oldsize, const int newsize) {
	if (newsize < 0) throw "New length must be >= 0";

	T* temp = new T[newsize];
	int number = min(newsize, oldsize);
	copy(a, a + number, temp);
	delete[] a;
	*a = temp;
}


template<class T>
class Stack
{
public:
	Stack(int stackCapacity = 10);
	~Stack() { delete[] stack; }
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	void Pop();
private:
	T* stack;
	int top;
	int capacity;
};

template<class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity) {
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template<class T>
inline bool Stack<T>::IsEmpty() const { return top == -1; }

template<class T>
inline T& Stack<T>::Top() const {
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];
}

template<class T>
void Stack<T>::Push(const T& x) {
	if (top == capacity - 1) {
		//ChangeSize1D(stack, capacity, 2 * capacity);

		int old = capacity;
		int new_one = 2 * old;

		T* a = new T[new_one];
		copy(stack, stack + old, a);
		delete[] stack;
		stack = a;


		capacity *= 2;
	}

	stack[++top] = x;
}

template<class T>
void Stack<T>::Pop() {
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	stack[top--].~T();
}

int main() {
	Stack<int> sta(2);

	sta.Push(1);
	sta.Push(2);
	sta.Push(3);
	sta.Push(4);
	sta.Push(5);

	while (1);
}