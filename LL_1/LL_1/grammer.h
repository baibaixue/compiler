#pragma once
#ifndef GRAMMER_H
#define GRAMMER_H
#include"head.h"
#define MAXN 50

class Production {	//产生式
public:
	Production() {	//构造函数
		right.clear();
		left = '\0';
	}

	Production(char l, string r) {	//复制构造函数
		left = l;
		right = r;
	}

	void change(char l, string r) {	//改变当前产生式
		left = l;
		right = r;
	}

	bool is_equal(Production pro) {	//两个产生式是否相等
		if (left == pro.left && right == pro.right) {
			return true;
		}
		else {
			return false;
		}
	}
	bool is_equal(char l, string r) {	//产生式是否相等
		if (left == l && right == r) {
			return true;
		}
		else {
			return false;
		}
	}

	bool is_empty() {	//是否为空
		if (left == '\0' && right.empty()) {
			return true;
		}
		else {
			return false;
		}
	}

	char left;	//产生式左部
	string right;	//产生式右部
};

bool operator < (const Production& r, const Production& l);	//重定义<运算符(使用map数据结构时定义，未采用)

class Grammer {	//文法
public:
	Grammer();	//构造函数
	void initial(string filename);	//载入txt文件初始化
	void output_grammer();	//输出文法

	unsigned int get_vn_index(char c);	//获取终结符号的下标
	unsigned int get_vt_index(char c);	//获取非终结符号下标
	bool is_vn(char c);	//是否终结符号
	bool is_vt(char c);	//是否非终结符号

	void Inditect_left_recursion();	//处理间接左递归和潜在左递归
	void remove_left_Recursive();	//消除左递归
	void remove_left_CommonFactor();	//提取最左公因子

	void get_first(char c);	//得到单个符号FIRST集
	void get_allfirst();	//得到文法所有非终结符号FIRST集
	void output_first();	//输出FIRST集

	void get_follow(char c);	//得到单个符号FOLLOW集
	void get_allfollow();	//得到文法所有非终结符号FOLLOW集
	void output_follow();	//输出FOLLOW集

	void get_select();	//得到SELECT集
	void output_select();	//输出SELECT集

	bool judge();	//判断是否LL_1文法

	void get_AnalysisTable();	//获得分析表
	void output_AnalysisTable();	//输出分析表

	void analysis(vector<WORD*> words);	//分析

	void run(string grammerfile, string text);	//运行分析器

	void show_detials_run(string grammerfile, string text);	//显示细节


private:
	vector<char> Vt;	//终结符号集
	vector<char> Vn;	//非终结符号集,epsilon记为@
	char S;	//开始符号
	vector<Production> production;	//产生式集合
	set<char> First[MAXN];	//FIRST集
	set<char> Follow[MAXN];	//FOLLOW集
	vector<pair<Production, set<char>>> Select;	//SELECT集
	int AnalysisTable[MAXN][MAXN];//分析表
	bool is_LL1;
};


#endif // !GRAMMER_H


