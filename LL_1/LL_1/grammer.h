#pragma once
#ifndef GRAMMER_H
#define GRAMMER_H
#include"head.h"
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

bool operator < (const Production& r, const Production& l);	//�ض���<�����(ʹ��map���ݽṹʱ���壬δ����)

class Grammer {	//�ķ�
public:
	Grammer();	//���캯��
	void initial(string filename);	//����txt�ļ���ʼ��
	void output_grammer();	//����ķ�

	unsigned int get_vn_index(char c);	//��ȡ�ս���ŵ��±�
	unsigned int get_vt_index(char c);	//��ȡ���ս�����±�
	bool is_vn(char c);	//�Ƿ��ս����
	bool is_vt(char c);	//�Ƿ���ս����

	void Inditect_left_recursion();	//��������ݹ��Ǳ����ݹ�
	void remove_left_Recursive();	//������ݹ�
	void remove_left_CommonFactor();	//��ȡ��������

	void get_first(char c);	//�õ���������FIRST��
	void get_allfirst();	//�õ��ķ����з��ս����FIRST��
	void output_first();	//���FIRST��

	void get_follow(char c);	//�õ���������FOLLOW��
	void get_allfollow();	//�õ��ķ����з��ս����FOLLOW��
	void output_follow();	//���FOLLOW��

	void get_select();	//�õ�SELECT��
	void output_select();	//���SELECT��

	bool judge();	//�ж��Ƿ�LL_1�ķ�

	void get_AnalysisTable();	//��÷�����
	void output_AnalysisTable();	//���������

	void analysis(vector<WORD*> words);	//����

	void run(string grammerfile, string text);	//���з�����

	void show_detials_run(string grammerfile, string text);	//��ʾϸ��


private:
	vector<char> Vt;	//�ս���ż�
	vector<char> Vn;	//���ս���ż�,epsilon��Ϊ@
	char S;	//��ʼ����
	vector<Production> production;	//����ʽ����
	set<char> First[MAXN];	//FIRST��
	set<char> Follow[MAXN];	//FOLLOW��
	vector<pair<Production, set<char>>> Select;	//SELECT��
	int AnalysisTable[MAXN][MAXN];//������
	bool is_LL1;
};


#endif // !GRAMMER_H


