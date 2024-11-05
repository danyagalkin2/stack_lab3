#include <iostream>
#include <string>
#include <utility>

using namespace std;

template <class T>
class TStack {
	T* pMem;
	int Maxsize, Num;
public:
	bool isEmpty()const;
	bool isFull() const;
	TStack(int _Maxsize = 10);
	TStack(const TStack& s);
	~TStack();
	TStack& operator=(const TStack& s);
	bool operator==(const TStack& s);
	bool operator!=(const TStack& s);
	T Pop();
	void Push(T value);
	T Top()const;
	void Clear() {Num = -1;}

};

template <class T>
TStack<T>::TStack(int _Maxsize) :Maxsize(_Maxsize) {
	Num = -1;
	pMem = new T[_Maxsize]{};
}

template <class T>
TStack<T>::TStack(const TStack& s) {
	Maxsize = s.Maxsize;
	Num = s.Num;
	pMem = new T[Maxsize];
	for (int i = 0; i <= Num; i++) {
		pMem[i] = s.pMem[i];
	}
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& s) {
	if (this == &s)return *this;
	if (Maxsize != s.Maxsize) {
		delete []pMem;
		Maxsize = s.Maxsize;
		pMem = new T[Maxsize];
	}
	Num = s.Num;
	for (int i = 0; i <= Num; i++) {
		pMem[i] = s.pMem[i];
	}
	return *this;
}

template <class T>
bool TStack<T>::operator==(const TStack& s) {
	if (this == &s)return true;
	if (Num != s.Num)return false;
	for (int i = 0; i <= Num; i++) {
		if (pMem[i] != s.pMem) {
			return false;
		}
	}
	return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack& s) {
	return !(*this == s);
}


template <class T>
bool TStack<T>::isEmpty() const {
	return Num == -1;
}

template <class T>
bool TStack<T>::isFull() const {
	return Maxsize - 1 == Num;
}

template <class T>
T TStack<T>::Pop() {
	if (this->isEmpty())throw - 1;
	T tmp = pMem[Num];
	Num--;
	return tmp;
}

template <class T>
void TStack<T>::Push(T value) {
	if (this->isFull())throw - 1;
	Num++;
	pMem[Num] = value;
}

template <class T>
T TStack<T>::Top()const {
	if (this->isEmpty()) throw - 1;
	return pMem[Num];
}

bool Check(string str)
{
	TStack <char>s;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(' )s.Push('(');
		if (str[i] == ')') {
			if (!s.isEmpty()) {
				s.Pop();
			}
			else {
				return false;
			}
		}

	}
	if (s.isEmpty())return true;
	else return false;
}


template <class T>
TStack<T>::~TStack() {
	delete[]pMem;
}


class TCalc {
	string infix;
	string postfix;
	TStack<double> StNum;
	TStack<char> StChar;
public:
	void setInfix(string input) { infix = input; }
	string getInfix() { return infix; }
	void setPostfix(string input) { postfix = input; }
	string getPostfix() { return postfix; }
	void ToPostfix();
	double CalcPostfix();
	double Calc();
};
int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}
void TCalc::ToPostfix() {
    TStack<char> st;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // If the scanned character is an operand, add it to
        // output string.
        if ('0' <= c && c <= '9')
            postfix += c;

        // If the scanned character is an '(', push it to
        // the stack.
        else if (c == '(')
            st.Push('(');

        // If the scanned character is an ')', pop and to
        // output string from the stack until an '(' is
        // encountered.
        else if (c == ')') {
            while (st.Top() != '(') {
                postfix += st.Top();
                st.Pop();
            }
            st.Pop();
        }

        // If an operator is scanned
        else {
            while (!st.isEmpty() && precedence(c) <= precedence(st.Top())) {
                postfix += st.Top();
                st.Pop();
            }
            st.Push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.isEmpty()) {
        postfix += st.Top();
        st.Pop();
    }

    this->setPostfix(postfix);
}

double TCalc::CalcPostfix() {
	StNum.Clear();
	for (int i = 0; i < postfix.size(); i++) {
		if ('0' <= postfix[i] && postfix[i] <= '9')
			StNum.Push(postfix[i] - '0');
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
			double SecondNum = StNum.Pop();
			double FirstNum = StNum.Pop();
			if (postfix[i] == '+')
				StNum.Push(FirstNum + SecondNum);
			else if (postfix[i] == '-')
				StNum.Push(FirstNum - SecondNum);
			else if (postfix[i] == '*')
				StNum.Push(FirstNum * SecondNum);
			else if (postfix[i] == '/')
				StNum.Push(FirstNum / SecondNum);
		}
	}
	double result = StNum.Pop();
	if (StNum.isEmpty()) {
		return result;
	}
	else {
		throw - 1;
	}
}
