#pragma once
#ifndef SCANNERH
#include"head.h"
using namespace std;

class Scanner {
public:
	void get_num();		//获取数字
	void get_id_key();	//获取标识符或关键字
	void get_operator();	//获取运算符
	void get_notes();	//获取注释
	void get_words();	//获取文本中所有词组
	void get_delimiter();	//获取分界符
	void output();	//输出
private:
	list<WORD*> words;
};

#endif // SCANNERH
