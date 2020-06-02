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
extern string input;	//��������
extern map<string, int> key_words;	//�ؼ��ֶ��ձ�
extern int line ;	//��¼����
extern vector<pair<string, int>> error_list;	//�����б�


class Point {	//ָ���ı����ݵ�ָ�룬��ʶ���ı����ַ�����
public:
	Point(string* S) {	//���캯��
		s = S;
		ch = '\0';
		index = -1;
	}

	void initial();	//��ʼ��

	bool is_end();	//�Ƿ�ָ���β
	void next();	//ָ����һ��
	void back();	//ָ����һ��

	void remove();	//ɾȥ��ָ��ָ�������
	char get_ch();	//��ȡ��ǰָ��ָ����ַ�

	bool is_letter();	//�Ƿ���ĸ
	bool is_digit();	//�Ƿ�����
	bool is_underline();	//�Ƿ��»���
	bool is_operator();	//�Ƿ������
	bool is_delimiter();	//�Ƿ�ֽ��
	bool is_space();	//�Ƿ�հ׷�
	bool is_lf();	//�Ƿ�س�����
	bool is_notes();	//�Ƿ�ע��
	
	void line_feed();	//����
	void rm_space();	//��ȥ�հ׷�
	void move_to();	//��ת����ĸ�����»���֮�󣨴�����ʱ���ã�

private:
	string* s;	//ָ����ı�
	char ch;	//��ǰ�ַ�
	int index;	//��ǰ����
};
extern Point p_input;

class WORD {	//��Ԫ����

public:
	WORD(const WORD& word) {	//���ƹ��캯��
		name = word.name;
		type = word.type;
	}

	WORD(const string strname) {	//���ƹ��캯��
		name = strname;
		type = key_words[name];
	}

	WORD(const int t,const string s) {
		type = t;
		name = s;
	}

	void assignment(const string strname);	//��ֵ

	void output();	//���

	bool is_empty();	//�Ƿ�Ϊ��

	~WORD() {	//��������
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

