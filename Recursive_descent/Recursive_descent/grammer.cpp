




/*
#include"head.h"

void Grammer::initial() {
	index = 0;
}


void Grammer::next() {
	if (!is_end()) {
		index++;
	}
}

bool Grammer::is_end() {
	if (index >= words_list.size()) {
		return true;
	}
	else return false;
}

void Grammer::E() {
	T();
	E1();
}

void Grammer::E1() {
	A();
	T();
	E1();
}

void Grammer::T() {
	F();
	T1();
}

void Grammer::T1() {
	M();
	F();
	T1();
}

void Grammer::F() {
	if (words_list[index]->return_name == "(") {
		next();
		E();
		if (words_list[index]->return_name == ")") {
			next;
			return;
		}
		else {
			cout << "illegal arithmetic expression !" << endl;
			exit(0);
		}
	}
	else if (words_list[index]->return_name == "id") {
		return;
	}
	else {
		cout << "illegal arithmetic expression !" << endl;
		exit(0);
	}
}

void Grammer::A() {
	if (words_list[index]->return_name == "+") {
		next();
		return;
	}
	else if (words_list[index]->return_name == "-") {
		next();
		return;
	}
	else {
		cout << "illegal arithmetic expression !" << endl;
		exit(0);
	}
}

void Grammer::M() {
	if (words_list[index]->return_name == "*") {
		next();
		return;
	}
	else if (words_list[index]->return_name == "/") {
		next();
		return;
	}
	else {
		cout << "illegal arithmetic expression !" << endl;
		exit(0);
	}
}

void Grammer::output_grammer() {
	cout << "E::TE'" << endl;
	cout << "E'::ATE'" << endl;
	cout << "E'::epsilon" << endl;
	cout << "T::FT'" << endl;
	cout << "T'::MFT'" << endl;
	cout << "T'::epsilon" << endl;
	cout << "F::(E)" << endl;
	cout << "A::+" << endl;
	cout << "A::-" << endl;
	cout << "M::*" << endl;
	cout << "M::/" << endl;
}
*/
