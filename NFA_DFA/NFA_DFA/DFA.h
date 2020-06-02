#pragma once
#ifndef DFA_H
#define DFA_H
#include"head.h"
#include"NFA.h"



class DFA :public NFA {
public:
	int get_index(set<int> x);	//�ҵ�x���϶�Ӧ��DFA״̬����
	bool is_equal(int x, int y);	//�ж�xy�Ƿ�Ϊ�ȼ�״̬

	void create_dfa(NFA nfa);	//ʵ��NFA��DFAת��
	void minimize();	//DFA��С��

	bool judge(string text);
	
private:
	vector<set<int>> Dstate;	//����DFAʱ�����BFA״̬��
	int equal_list[MAXN];	//�ȼ�״̬��
	int unionsearch(int root);	//���鼯
	void join(int root1, int root2);	//�ϲ��ȼ�״̬
};
#endif // !DFA_H
