#pragma once
#ifndef NFA_H
#define NFA_H
#include"head.h"

void get_num_char(string line, int& s, int& e, char& c);

class NFA{
public:
	NFA() = default;	//���캯��
	NFA(NFA& nfa);	//���ƹ��캯��
	
	void copy(const NFA& nfa);

	void initial(string filename);	//��ʼ��
	void initial();	//����״̬ת�Ʊ��ʼ��״̬����ת�Ʒ��ż���
	bool is_DFA();	//�Ƿ�DFA
	
	bool is_end(int x);	//�Ƿ��ս�״̬
	bool is_end(set<int> x);
	bool is_chara(char c);	//�Ƿ�ת�Ʒ���
	bool is_states(int x);	//�Ƿ��Ǹ�NFA״̬
	bool is_trans(int s, int e, char c);	//�Ƿ����״̬ת��
	
	void insert_state(int s, int e, char c);	//�����µ�״̬ת��
	
	set<int> closure(int x);	//��x�հ�,��x��ʼֻͨ��epsilon�ﵽ��״̬����
	set<int> closure(set<int> x);
	set<int> move(int x, char c);	//��x״̬ͨ��cת�ƴﵽ��״̬����
	set<int> move(set<int> x, char c);

	void output();	//���״̬ת�Ʊ�


	int states_num = 0;	//״̬����
	int start = 0;
	set<int> end;	//�ս�״̬
	set<int> states;	//״̬��
	set<char> chara;	//ת�Ʒ��ż���
protected:
	vector<char> state_trans_table[MAXN][MAXN];	//״̬ת�Ʊ�
};
#endif // !NFA_H
