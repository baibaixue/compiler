#pragma once
#ifndef SCANNERH
#include"head.h"
using namespace std;

class Scanner {
public:
	void get_num();		//��ȡ����
	void get_id_key();	//��ȡ��ʶ����ؼ���
	void get_operator();	//��ȡ�����
	void get_notes();	//��ȡע��
	void get_words();	//��ȡ�ı������д���
	void get_delimiter();	//��ȡ�ֽ��
	void output();	//���
private:
	list<WORD*> words;
};

#endif // SCANNERH
