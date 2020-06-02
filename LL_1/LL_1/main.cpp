#include"grammer.h"

int line = 1;
vector<pair<string, int>> error_list;
string input;
Point p_input(&input);

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

int main() {
	string text = "data3.txt";
	string grammerfile = "grammer1.txt";

	Grammer grammer;

	grammer.show_detials_run(grammerfile, text);
}