#pragma once
#include"head.h"


bool is_key(string str) {
	if (key_words.find(str) != key_words.end())
		return true;
	else return false;
}


void Scanner::get_words() {
	p_input.initial();
	while (true) {
		if (p_input.is_letter() || p_input.is_underline()) {
			get_id_key();
			continue;
		}
		else if (p_input.is_digit()) {
			get_num();
			continue;
		}
		else if (p_input.is_operator()) {
			get_operator();
			continue;
		}
		else if (p_input.is_space()) {
			p_input.rm_space();
			continue;
		}
		else if (p_input.is_lf()) {
			p_input.line_feed();
			continue;
		}
		else if (p_input.is_delimiter()) {
			get_delimiter();
			continue;
		}
		else if (p_input.is_notes()) {
			get_notes();
			continue;
		}

		else if (p_input.is_end()) {
			break;
		}

		else {
			string s1 = "error:Unrecognize symbol:";
			string ss = s1 + p_input.get_ch();
			error_list.push_back(make_pair(ss, line));

			p_input.next();
		}
	}
}


void Scanner::output() {
	vector<WORD*>::iterator itor;
	for (itor = words.begin(); itor != words.end(); itor++) {
		(*itor)->output();
	}
}

void Scanner::get_id_key() {
	string id_key;
	id_key += p_input.get_ch();
	p_input.next();

	while (p_input.is_letter() || p_input.is_digit() || p_input.is_underline()) {
		id_key += p_input.get_ch();
		p_input.next();
	}
	if (is_key(id_key)) {
		words.push_back(new WORD(id_key));
	}
	else
		words.push_back(new WORD(27, id_key));
}

void Scanner::get_num() {
	string num;
	string s1 = "error:Unrecongized identifier:";
	num += p_input.get_ch();
	p_input.next();

	while (p_input.is_digit()) {
		num += p_input.get_ch();
		p_input.next();
	}

	if (p_input.is_underline() || p_input.is_letter()) {
		while (p_input.is_underline() || p_input.is_letter()) {
			num += p_input.get_ch();
			p_input.next();
		}
		string ss = s1 + num;
		error_list.push_back(make_pair(ss, line));
		return;
	}

	words.push_back(new WORD(28, num));
}


void Scanner::get_notes() {
	while (p_input.get_ch() != '\n') {
		p_input.next();
	}
}

void Scanner::get_delimiter() {
	string op;
	op += p_input.get_ch();
	switch (p_input.get_ch()) {
	case '(':
		words.push_back(new WORD(op));
		p_input.next();
		return;
	case ')':
		words.push_back(new WORD(op));
		p_input.next();
		return;
	case ';':
		words.push_back(new WORD(op));
		p_input.next();
		return;
	}
}

void Scanner::get_operator() {
	string op;
	string s1 = "error:Unrecognize operator:";
	op += p_input.get_ch();
	switch (p_input.get_ch()) {
	case '+':
		p_input.next();
		if (p_input.get_ch() == '+') {	//识别++
			op += p_input.get_ch();
			words.push_back(new WORD(op));
			p_input.next();
			return;
		}
		else {	//识别+
			words.push_back(new WORD(op));
			return;
		}
	case '-':
		p_input.next();
		if (p_input.get_ch() == '-') {	//识别--
			op += p_input.get_ch();
			words.push_back(new WORD(op));
			p_input.next();
			return;
		}
		else {	//识别-
			words.push_back(new WORD(op));
			return;
		}
	case '*':
		p_input.next();
		words.push_back(new WORD(op));
		return;
	case '/':
		p_input.next();
		words.push_back(new WORD(op));
		return;
	case '>':
		p_input.next();
		if (p_input.get_ch() == '=') {	//识别>=
			op += p_input.get_ch();
			words.push_back(new WORD(op));
			p_input.next();
			return;
		}
		else {	//识别>
			words.push_back(new WORD(op));
			return;
		}
	case '<':
		p_input.next();
		if (p_input.get_ch() == '=') {	//识别<=
			op += p_input.get_ch();
			words.push_back(new WORD(op));
			p_input.next();
			return;
		}
		else if (p_input.get_ch() == '>') {	//识别<>
			op += p_input.get_ch();
			words.push_back(new WORD(op));
			p_input.next();
			return;
		}
		else {	//识别<
			words.push_back(new WORD(op));
			return;
		}
	case ':':
		p_input.next();
		if (p_input.get_ch() == '=') {	//识别：=
			op += p_input.get_ch();
			words.push_back(new WORD(op));
			p_input.next();
			return;
		}
		else {	//未识别单个：
			error_list.push_back(make_pair(s1 + op, line));
			return;
		}
	case '=':	//识别=
		p_input.next();
		words.push_back(new WORD(op));
		return;
	}
}