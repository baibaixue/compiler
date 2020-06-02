#pragma once
#ifndef HEADER_H
#define HEADER_H
#include<cstdio>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<list>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<set>
#include<stack>
using namespace std;
extern string input;//输入内容
extern map<string, int> key_words;
extern int line;
extern vector<pair<string, int>> error_list;


class Point {
public:
	Point(string* S) {
		s = S;
		ch = '\0';
		index = -1;
	}

	void initial();

	bool is_end();
	void next();
	void back();

	void remove();
	char get_ch();

	bool is_letter();
	bool is_digit();
	bool is_underline();
	bool is_operator();
	bool is_delimiter();//分界符
	bool is_space();
	bool is_lf();
	bool is_notes();

	void line_feed();
	void rm_space();
	void move_to();

private:
	string* s;
	char ch;
	int index;
};
extern Point p_input;

class WORD {

public:
	WORD(const WORD& word) {
		name = word.name;
		type = word.type;
	}

	WORD(const string strname) {
		name = strname;
		type = key_words[name];
	}

	WORD(const int t, const string s) {
		type = t;
		name = s;
	}

	void assignment(const string strname);

	void output();

	bool is_empty();


	~WORD() {
		if (!is_empty()) {
			delete& name;
			delete& type;
		}
	}
	int type;
	string name;

};

class Scanner {
public:
	void get_num();
	void get_id_key();
	void get_operator();
	void get_notes();
	void get_words();
	void get_delimiter();
	void output();
	vector<WORD*> words;
};

#endif // !HEADER_H
