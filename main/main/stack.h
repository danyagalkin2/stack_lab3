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
	bool operator==(const TStack& s)const;
	bool operator!=(const TStack& s)const;
	T Pop();
	void Push(T value);
	T Top()const;
	void Clear() { Num = -1; }


};

template <class T>
TStack<T>::TStack(int _Maxsize) :Maxsize(_Maxsize) {
	if (_Maxsize < 1) { throw - 1; }
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
TStack<T>& TStack<T>::operator=(const TStack& s){
	if (this == &s)return *this;
	if (Maxsize != s.Maxsize) {
		delete[]pMem;
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
bool TStack<T>::operator==(const TStack& s)const {
	if (this == &s)return true;
	if (Num != s.Num)return false;
	for (int i = 0; i <= Num; i++) {
		if (pMem[i] != s.pMem[i]) {
			return false;
		}
	}
	return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack& s) const{
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
		if (str[i] == '(')s.Push('(');
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
	bool CurrentCharIsDigit(char c);
	size_t ProcessNumber(const string& str, size_t index);
	void ProcessClosingBracket();
	void ProcessOperator(char oper);
	double ApplyOperation(double num1, double num2, char oper);
	void HandleUnaryMinus(const string& str, size_t& index);
	bool IsOperator(char c);
};
int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	if (op == '^')
		return 3;
	return 0;
}
int str_to_int(string s) {
	int res = 0;
	for (int i = 0; i < s.length(); i++) {
		res = res * 10 + (s[i] - '0');
	}
	return res;
}
void TCalc::ToPostfix() {
	postfix = "";
	string s = "(" + infix + ")";
	StChar.Clear();
	for (int i = 0; i < s.length(); i++) {
		
		// ���� ������ �������� ���������,
		//  ��������� ��� � ������
		if ('0' <= s[i] && s[i] <= '9')
			postfix += s[i];

		// ���� ������ ����� '(',
		//  �������� ��� � ����.
		else if (s[i] == '(')
			StChar.Push('(');

		// ���� �������� �������� ')',
		//  ��������� ������ �� ����� � ��������� 
		// � �������������� ������,
		//  ���� �� ���������� '('
		else if (s[i] == ')') {
			while (StChar.Top() != '(') {
				postfix += " ";
				postfix += StChar.Top();
				StChar.Pop();
				
			}
			StChar.Pop();
		}

		else {
			postfix += " ";
			while (!StChar.isEmpty() && precedence(s[i]) <= precedence(StChar.Top())) {
				postfix += StChar.Top() ;
				StChar.Pop();
				postfix += " ";
			}
			StChar.Push(s[i]);
		}
	}

	//// ��������� ��� �������� �� ����� � ������
	//while (!StChar.isEmpty()) {
	//	postfix += StChar.Top();
	//	StChar.Pop();
	//}

}

double TCalc::CalcPostfix() {
	StNum.Clear();
	for (int i = 0; i < postfix.size(); i++) {
		if ('0' <= postfix[i] && postfix[i] <= '9') {
			string s = "";
			while ('0' <= postfix[i] && postfix[i] <= '9') {
				s += postfix[i];
				i++;
			}
			StNum.Push(str_to_int(s));
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
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
			else 
				StNum.Push(pow(FirstNum,SecondNum));
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
double TCalc::Calc() {
	string str = "(" + infix + ")";
	StNum.Clear();
	StChar.Clear();

	if (!Check(infix)) {
		throw -1;
	}

	for (size_t i = 0; i < str.size(); ++i) {
		char currentChar = str[i];

		if (currentChar == '(') {
			StChar.Push(currentChar);
		}
		else if (CurrentCharIsDigit(currentChar) || currentChar == '.') {
			i = ProcessNumber(str, i);
		}
		else if (currentChar == ')') {
			ProcessClosingBracket();
		}
		else if (IsOperator(currentChar)) {
			ProcessOperator(currentChar);
		}
		else if (currentChar == '-') {
			HandleUnaryMinus(str, i);
		}
	}

	double result = StNum.Pop();
	if (!StNum.isEmpty()) {
		throw -1;
	}
	return result;
}

bool TCalc::CurrentCharIsDigit(char c) {
	return (c >= '0' && c <= '9');
}

size_t TCalc::ProcessNumber(const string& str, size_t index) {
	size_t idx;
	double num = stod(&str[index], &idx);
	StNum.Push(num);
	return index + idx - 1;
}

void TCalc::ProcessClosingBracket() {
	while (StChar.Top() != '(') {
		double Num2 = StNum.Pop();
		double Num1 = StNum.Pop();
		char oper = StChar.Pop();
		StNum.Push(ApplyOperation(Num1, Num2, oper));
	}
	StChar.Pop(); // Remove '('
}

void TCalc::ProcessOperator(char oper) {
	while (!StChar.isEmpty() && precedence(StChar.Top()) >= precedence(oper)) {
		double Num2 = StNum.Pop();
		double Num1 = StNum.Pop();
		char topOper = StChar.Pop();
		StNum.Push(ApplyOperation(Num1, Num2, topOper));
	}
	StChar.Push(oper);
}

double TCalc::ApplyOperation(double num1, double num2, char oper) {
	switch (oper) {
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/':
		if (num2 == 0) throw -1;
		return num1 / num2;
	case '^': return pow(num1, num2);
	}
}

void TCalc::HandleUnaryMinus(const string& str, size_t& index) {
	if (index == 0 || str[index - 1] == '(') {
		index++; // ���������� '-' � ����������
		index = ProcessNumber(str, index); // ������������ ����� ����� ������
		double num = -StNum.Pop(); // ����� ����� � ������ ����

		StNum.Push(num);
	}
}

bool TCalc::IsOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}