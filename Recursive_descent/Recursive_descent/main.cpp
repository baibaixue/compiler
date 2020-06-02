#include"head.h"
string text1 = "data1.txt";
string text2 = "data2.txt";
string text3 = "data3.txt";
string text4 = "data4.txt";
string text5 = "data5.txt";
int line = 1;
vector<pair<string, int>> error_list;
string input;
Scanner scan;
Point p_input(&input);
unsigned int index = 0;
bool is_expression = false;
void E();
void E1();
void T();
void T1();
void F();
void A();
void M();
map<string, int> key_words = {
	{ "begin",0 }, { "end",1 }, { "if",2 },
	{ "then",3 }, { "else",4 }, { "for",5 },
	{ "while",6 }, { "do",7 }, { "and",8 },
	{ "or",9 }, { "not",10 }, { "+",11 },
	{ "-",12 }, { "*",13 }, { "/",13 },
	{ ">",14 }, { "<",15 }, { "=",16 },
	{ ":=",17 }, { ">=",18 }, { "<=",19 },
	{ "<>",20 }, { "++",21 }, { "--",22 },
	{ "(",23 }, { ")",24 }, { ";",25 },
	{ "#",26 }, { "id",27 }, { "NUM",28 }
};

void E() {
	T();
	if (index >= scan.words.size()) {
		is_expression = true;
		return;
	}
	else if (scan.words[index]->name == "+" || scan.words[index]->name == "-") {
		E1();
	};
}

void E1() {
	A();
	T();
	if (index >= scan.words.size()) {
		is_expression = true;
		return;
	}
	else if (scan.words[index]->name == "+" || scan.words[index]->name == "-") {
		E1();
	}
}


void T() {
	F();
	if (index >= scan.words.size()) {
		is_expression = true;
		return;
	}
	else if (scan.words[index]->name == "*" || scan.words[index]->name == "/") {
		T1();
	}
}

void T1() {
	M();
	F();
	if (index > scan.words.size()) {
		is_expression = true;
		return;
	}
	else if (scan.words[index]->name == "*" || scan.words[index]->name == "/") {
		T1();
	}
}

void F() {
	if (scan.words[index]->name == "(" ) {
		index++;
		E();
		if (scan.words[index]->name == ")") {
			index++;
			return;
		}
		else {
			cout << "illegal arithmetic expression !" << endl;
			exit(0);
		}
	}
	else if(scan.words[index]->type == 27 ){
		index++;
		return;
	}
}

void A() {
	if (scan.words[index]->name == "+" || scan.words[index]->name == "-") {
		index++;
		return;
	}
	else {
		cout << "illegal arithmetic expression !" << endl;
		exit(0);
	}
}

void M() {
	if (scan.words[index]->name == "*" || scan.words[index]->name == "/") {
		index++;
		return;
	}
	else {
		cout << "illegal arithmetic expression !" << endl;
		exit(0);
	}
}

int main(int argc, char** argv) {

	ifstream infile(text4);
	istreambuf_iterator<char> begin(infile);
	istreambuf_iterator<char> end;
	string contest(begin, end);

	input = contest;


	cout << "Data1:" << endl;
	cout << input << endl;

	scan.get_words();
	scan.output();

	if (!error_list.empty()) {
		vector<pair<string, int>>::iterator itor;
		for (itor = error_list.begin(); itor != error_list.end(); itor++) {
			cout << (*itor).first << " in line: " << (*itor).second << endl;
		}
	}
	else {
		E();
		if (is_expression == true) {
			cout << "legal arithmetic expression!" << endl;
		}
		else {
			cout << "illegal arithmetic expression !" << endl;
		}
	}
	


}