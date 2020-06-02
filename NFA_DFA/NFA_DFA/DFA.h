#pragma once
#ifndef DFA_H
#define DFA_H
#include"head.h"
#include"NFA.h"



class DFA :public NFA {
public:
	int get_index(set<int> x);	//找到x集合对应的DFA状态编码
	bool is_equal(int x, int y);	//判断xy是否为等价状态

	void create_dfa(NFA nfa);	//实现NFA到DFA转换
	void minimize();	//DFA最小化

	bool judge(string text);
	
private:
	vector<set<int>> Dstate;	//生成DFA时储存的BFA状态集
	int equal_list[MAXN];	//等价状态表
	int unionsearch(int root);	//并查集
	void join(int root1, int root2);	//合并等价状态
};
#endif // !DFA_H
