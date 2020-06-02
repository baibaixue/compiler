#pragma once
#ifndef NFA_H
#define NFA_H
#include"head.h"

void get_num_char(string line, int& s, int& e, char& c);

class NFA{
public:
	NFA() = default;	//构造函数
	NFA(NFA& nfa);	//复制构造函数
	
	void copy(const NFA& nfa);

	void initial(string filename);	//初始化
	void initial();	//根据状态转移表初始化状态集和转移符号集合
	bool is_DFA();	//是否DFA
	
	bool is_end(int x);	//是否终结状态
	bool is_end(set<int> x);
	bool is_chara(char c);	//是否转移符号
	bool is_states(int x);	//是否是该NFA状态
	bool is_trans(int s, int e, char c);	//是否存在状态转移
	
	void insert_state(int s, int e, char c);	//插入新的状态转移
	
	set<int> closure(int x);	//求x闭包,从x开始只通过epsilon达到的状态集合
	set<int> closure(set<int> x);
	set<int> move(int x, char c);	//从x状态通过c转移达到的状态集合
	set<int> move(set<int> x, char c);

	void output();	//输出状态转移表


	int states_num = 0;	//状态数量
	int start = 0;
	set<int> end;	//终结状态
	set<int> states;	//状态集
	set<char> chara;	//转移符号集合
protected:
	vector<char> state_trans_table[MAXN][MAXN];	//状态转移表
};
#endif // !NFA_H
