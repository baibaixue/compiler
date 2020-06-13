#pragma once
#ifndef SLR_GRAMMER_H
#define SLR_GRAMMER_H
#include"head.h"
#include"quaternion.h"
#define MAXN 50

class Production {	//����ʽ
public:
	Production() {	//���캯��
		right.clear();
		left = '\0';
	}

	Production(char l, string r) {	//���ƹ��캯��
		left = l;
		right = r;
	}

	void change(char l, string r) {	//�ı䵱ǰ����ʽ
		left = l;
		right = r;
	}

	bool is_equal(Production pro) {	//��������ʽ�Ƿ����
		if (left == pro.left && right == pro.right) {
			return true;
		}
		else {
			return false;
		}
	}
	bool is_equal(char l, string r) {	//����ʽ�Ƿ����
		if (left == l && right == r) {
			return true;
		}
		else {
			return false;
		}
	}

	bool is_empty() {	//�Ƿ�Ϊ��
		if (left == '\0' && right.empty()) {
			return true;
		}
		else {
			return false;
		}
	}
	char left;	//����ʽ��
	string right;	//����ʽ�Ҳ�
};


class Project {	//LR0��Ŀ
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
	void output();	//���LR0��Ŀ
	bool equal(Project p);

	bool is_Start(char s);	//�Ƿ�ʼ��Ŀ
	bool is_Acc(char s);	//�Ƿ������Ŀ
	bool is_MoveIn(vector<char> vt);	//�Ƿ��ƽ���Ŀ����Ŀ����һ��״̬ʱ�ս����
	bool To_Be_Reduction(vector<char> vn);	//�Ƿ����Լ��Ŀ,��Ŀ����һ��״̬�Ƿ��ս����
	bool is_Reduction();	//�Ƿ��Լ��Ŀ
	bool is_first();	//�Ƿ�A->��a״̬����հ�

	Production prod;
	int index;

};

class SLR_Grammer {	//�ķ�
public:
	SLR_Grammer();	//���캯��
	void initial(string filename);	//����txt�ļ���ʼ��

	void output_grammer();	//����ķ�
	void output_projects();	//�����Ŀ��
	void output_DFA();	//���DFA
	void output_analysis_table();	//���������

	unsigned int get_prod_index(Production p);	//��ȡ����ʽ���±�
	unsigned int get_prod_index(Project p);	//����Ϊ��Ŀ����ȡ����ʽ�±�
	unsigned int get_prod_index(int p);	//����Ϊ��Ŀ��ţ���ȡ����ʽ�±�
	unsigned int get_vn_index(char c);	//��ȡ���ս���ŵ��±�
	unsigned int get_vt_index(char c);	//��ȡ�ս�����±�
	int get_i_index(set<int> i);	//�����Ŀ�����
	int get_proj_index(Project p);	//�����Ŀ���

	bool is_vn(char c);	//�Ƿ��ս����
	bool is_vt(char c);	//�Ƿ���ս����

	//void Inditect_left_recursion();	//��������ݹ��Ǳ����ݹ�
	//void remove_left_Recursive();	//������ݹ�
	//void remove_left_CommonFactor();	//��ȡ��������

	void get_first(char c);	//�õ���������FIRST��
	void get_allfirst();	//�õ��ķ����з��ս����FIRST��
	void output_first();	//���FIRST��

	void get_follow(char c);	//�õ���������FOLLOW��
	void get_allfollow();	//�õ��ķ����з��ս����FOLLOW��
	void output_follow();	//���FOLLOW��

	set<int> get_closure(set<int> i);	//����Ŀ���հ�
	set<int> get_closure(Project p);	//����Ŀ�հ�

	set<int> go(Project p, char c);	//��Ŀת�ƺ���
	set<int> go(set<int> p, char c);	//��Ŀ��ת�ƺ���

	bool is_start(set<int> i);	//��Ŀ�����п�ʼ��Ŀ
	bool is_acc(set<int> i);	//��Ŀ�����н�����Ŀ
	bool is_MoveIn(set<int> i);	//��Ŀ�������ƽ���Ŀ�����Լ��Ŀ
	bool is_Reduction(set<int> i);	//��Ŀ�����й�Լ��Ŀ

	//bool has_intersection(char a, char b);	//���ս����a,b��FOLLOW���Ƿ��н���

	bool judge();	//�ж��Ƿ�SLR(1)�ķ�

	bool analysis(vector<WORD*> words);	//������Ԫ������

	vector<quatern> get_analysis(vector<WORD*> words);	//���������Ԫʽ

	void output_3_address_code(vector<quatern> q);	//������Ԫʽ�������ַ����

private:
	vector<char> Vt;	//�ս���ż�,epsilon��Ϊ@
	vector<char> Vn;	//���ս���ż�
	char S;	//��ʼ����
	vector<Production> production;	//����ʽ����
	vector<Project> projects;	//LR0��Ŀ��
	vector<set<int>> I;	//LR1�淶��Ŀ��
	vector<char> DFA[MAXN][MAXN];	//����DFA
	pair<char, int> Action[MAXN][MAXN] ;	//ACTION��
	int Goto[MAXN][MAXN] ;	//GOTO��
	set<char> First[MAXN];	//FIRST��
	set<char> Follow[MAXN];	//FOLLOW��
	bool is_SLR = true;

	void create_projects();	//����LR0��Ŀ��
	void get_DFA();	//����DFA
	void get_analysis_table();	//���������

	//vector<quatern> Semantic_rules;	//�������
	vector<var> variable;	//���ɱ����б�
	int has_var(string name);	//�Ƿ�����name����,�����򷵻��±�
	string creat_new_id(char c,string name);	//�����ս���ŵı���
	string creat_new_id(char c);	//���ɷ��ս���ŵı���
	quatern Definition_rule(var arg1, var arg2,char res,int n);	//����������򣬷�����Ԫ��	E->E+T|E-T T->T*F|T/F
	void Definition_rule(var& arg1, char res, int n);	//�����������,ֱ�Ӹ�ֵ���		E->T E->F F->i F->(E)
	//quatern Definition_rule(var arg1, char res);	//F->(E)
	quatern Definition_rule(var arg1, var& res);	//S->i:=E
};

#endif // !SLR_GRAMMER_H


