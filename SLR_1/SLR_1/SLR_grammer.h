#pragma once
#ifndef SLR_GRAMMER_H
#define SLR_GRAMMER_H
#include"head.h"
#include"quaternion.h"
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


class Project {	//LR0项目
public:
	Project() = default;
	Project(Production p, int i) {
		prod.left = p.left;
		prod.right = p.right;
		index = i;
	}

	Project(char l, string r, int i) {
		prod.left = l;
		prod.right = r;
		index = i;
	}
	void output();	//输出LR0项目
	bool equal(Project p);

	bool is_Start(char s);	//是否开始项目
	bool is_Acc(char s);	//是否接受项目
	bool is_MoveIn(vector<char> vt);	//是否移进项目，项目的下一个状态时终结符号
	bool To_Be_Reduction(vector<char> vn);	//是否待归约项目,项目的下一个状态是非终结符号
	bool is_Reduction();	//是否归约项目
	bool is_first();	//是否A->·a状态（求闭包

	Production prod;
	int index;

};

class SLR_Grammer {	//文法
public:
	SLR_Grammer();	//构造函数
	void initial(string filename);	//载入txt文件初始化

	void output_grammer();	//输出文法
	void output_projects();	//输出项目集
	void output_DFA();	//输出DFA
	void output_analysis_table();	//输出分析表

	unsigned int get_prod_index(Production p);	//获取产生式的下标
	unsigned int get_prod_index(Project p);	//参数为项目，获取产生式下标
	unsigned int get_prod_index(int p);	//参数为项目编号，获取产生式下标
	unsigned int get_vn_index(char c);	//获取非终结符号的下标
	unsigned int get_vt_index(char c);	//获取终结符号下标
	int get_i_index(set<int> i);	//获得项目集编号
	int get_proj_index(Project p);	//获得项目编号

	bool is_vn(char c);	//是否终结符号
	bool is_vt(char c);	//是否非终结符号

	//void Inditect_left_recursion();	//处理间接左递归和潜在左递归
	//void remove_left_Recursive();	//消除左递归
	//void remove_left_CommonFactor();	//提取最左公因子

	void get_first(char c);	//得到单个符号FIRST集
	void get_allfirst();	//得到文法所有非终结符号FIRST集
	void output_first();	//输出FIRST集

	void get_follow(char c);	//得到单个符号FOLLOW集
	void get_allfollow();	//得到文法所有非终结符号FOLLOW集
	void output_follow();	//输出FOLLOW集

	set<int> get_closure(set<int> i);	//求项目集闭包
	set<int> get_closure(Project p);	//求项目闭包

	set<int> go(Project p, char c);	//项目转移函数
	set<int> go(set<int> p, char c);	//项目集转移函数

	bool is_start(set<int> i);	//项目集中有开始项目
	bool is_acc(set<int> i);	//项目集中有接收项目
	bool is_MoveIn(set<int> i);	//项目集中有移进项目或待归约项目
	bool is_Reduction(set<int> i);	//项目集中有归约项目

	//bool has_intersection(char a, char b);	//非终结符号a,b的FOLLOW集是否有交集

	bool judge();	//判断是否SLR(1)文法

	bool analysis(vector<WORD*> words);	//分析二元单词组

	vector<quatern> get_analysis(vector<WORD*> words);	//分析获得四元式

	void output_3_address_code(vector<quatern> q);	//根据四元式输出三地址代码

private:
	vector<char> Vt;	//终结符号集,epsilon记为@
	vector<char> Vn;	//非终结符号集
	char S;	//开始符号
	vector<Production> production;	//产生式集合
	vector<Project> projects;	//LR0项目集
	vector<set<int>> I;	//LR1规范项目族
	vector<char> DFA[MAXN][MAXN];	//构造DFA
	pair<char, int> Action[MAXN][MAXN] ;	//ACTION表
	int Goto[MAXN][MAXN] ;	//GOTO表
	set<char> First[MAXN];	//FIRST集
	set<char> Follow[MAXN];	//FOLLOW集
	bool is_SLR = true;

	void create_projects();	//构建LR0项目集
	void get_DFA();	//构建DFA
	void get_analysis_table();	//构造分析表

	//vector<quatern> Semantic_rules;	//语义规则
	vector<var> variable;	//生成变量列表
	int has_var(string name);	//是否已有name变量,若有则返回下标
	string creat_new_id(char c,string name);	//生成终结符号的变量
	string creat_new_id(char c);	//生成非终结符号的变量
	quatern Definition_rule(var arg1, var arg2,char res,int n);	//定义语义规则，返回四元组	E->E+T|E-T T->T*F|T/F
	void Definition_rule(var& arg1, char res, int n);	//定义语义规则,直接赋值情况		E->T E->F F->i F->(E)
	//quatern Definition_rule(var arg1, char res);	//F->(E)
	quatern Definition_rule(var arg1, var& res);	//S->i:=E
};

#endif // !SLR_GRAMMER_H


