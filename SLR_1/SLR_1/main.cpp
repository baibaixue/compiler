#include"head.h"
#include "SLR_grammer.h"


string text = "data11.txt";
string grammerfile = "grammer1.txt";
int line = 1;
vector<pair<string, int>> error_list;
string input;
Point p_input(&input);
SLR_Grammer g;
Scanner s;


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


int main(int argc, char** argv) {

	ifstream infile(text);
	istreambuf_iterator<char> begin(infile);
	istreambuf_iterator<char> end;
	string contest(begin, end);

	input = contest;
	
	cout << "Data:" << endl;
	cout << input << endl;

	s.get_words();
	s.output();

	g.initial(grammerfile);
	g.output_grammer();
	g.output_projects();
	g.output_DFA();
	g.output_analysis_table();
	
	if (!error_list.empty()) {
		vector<pair<string, int>>::iterator itor;
		for (itor = error_list.begin(); itor != error_list.end(); itor++) {
			cout << (*itor).first << " in line: " << (*itor).second << endl;
		}
	}
	else {
		g.output_3_address_code(g.get_analysis(s.words));
	}
	/*
	ifstream infile(text1);
	istreambuf_iterator<char> begin(infile);
	istreambuf_iterator<char> end;
	string contest(begin, end);

	Scanner scan;

	input = contest;


	cout << "Data1:" << endl;
	cout << input << endl;

	scan.get_words();
	scan.output();

	vector<pair<string, int>>::iterator itor;
	for (itor = error_list.begin(); itor != error_list.end(); itor++) {
		cout << (*itor).first << " in line: " << (*itor).second << endl;
	}
	*/
}