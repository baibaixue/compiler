#pragma once
#ifndef HEADH
#define HEADH
#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>
#include<list>
#include<vector>
#include<cassert>
#include<fstream>
#include<map>
using namespace std;
extern string input;	//输入内容
extern map<string, int> key_words;	//关键字对照表
extern int line ;	//记录行数
extern vector<pair<string, int>> error_list;	//错误列表


class Point {	//指向文本内容的指针，可识别文本中字符类型
public:
	Point(string* S) {	//构造函数
		s = S;
		ch = '\0';
		index = -1;
	}

	void initial();	//初始化

	bool is_end();	//是否指向结尾
	void next();	//指向下一个
	void back();	//指向上一个

	void remove();	//删去该指针指向的内容
	char get_ch();	//获取当前指针指向的字符

	bool is_letter();	//是否字母
	bool is_digit();	//是否数字
	bool is_underline();	//是否下划线
	bool is_operator();	//是否运算符
	bool is_delimiter();	//是否分界符
	bool is_space();	//是否空白符
	bool is_lf();	//是否回车换行
	bool is_notes();	//是否注释
	
	void line_feed();	//换行
	void rm_space();	//除去空白符
	void move_to();	//跳转到字母数字下划线之后（错误处理时调用）

private:
	string* s;	//指向的文本
	char ch;	//当前字符
	int index;	//当前索引
};
extern Point p_input;

class WORD {	//二元词组

public:
	WORD(const WORD& word) {	//复制构造函数
		name = word.name;
		type = word.type;
	}

	WORD(const string strname) {	//复制构造函数
		name = strname;
		type = key_words[name];
	}

	WORD(const int t,const string s) {
		type = t;
		name = s;
	}

	void assignment(const string strname);	//赋值

	void output();	//输出

	bool is_empty();	//是否为空

	~WORD() {	//析构函数
		if (!is_empty()) {
			delete& name;
			delete& type;
		}
	}
private:
	int type;	
	string name;

};



#endif // !HEADH

