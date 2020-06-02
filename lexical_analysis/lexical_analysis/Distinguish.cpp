#include"head.h"
using namespace std;

void Point::initial() {
	ch = s->at(0);
	index = 0;
}

bool Point::is_end() {
	if (index >= s->length())
		return true;
	else return false;
}

void Point::next() {
	index = index + 1;
	if (!is_end()) {
		
		ch = s->at(index);
	}
	else {
		ch = '\0';
	}
}

void Point::back() {
	if (index >= 1) {
		index = index - 1;
		ch = s->at(index);
	}
}

void Point::remove() {
	s->erase(index, 1);
	initial();
}

char Point::get_ch() {
	return ch;
}


bool Point::is_letter() {
	if (( ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else return false;
}

bool Point::is_digit() {
	if (ch >= '0' && ch <= '9')
		return true;
	else return false;
}

bool Point::is_operator() {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/'
		|| ch == '>' || ch == '<' || ch == '=' || ch == ':')
		return true;
	else return false;
}

bool Point::is_delimiter() {
	if (ch == '(' || ch == ')'|| ch == ';')
		return true;
	else return false;
}

bool Point::is_underline() {
	if (ch == '_')
		return true;
	else return false;
}

bool Point::is_space() {
	if (ch == ' ' || ch == '\t' || ch == '\v'
		|| ch == '\f' || ch == '\r')
		return true;
	else return false;
}

bool Point::is_notes() {
	if (ch == '#')
		return true;
	else return false;
}

void Point::rm_space() {
	while (is_space()) 
		next();		
}

bool Point::is_lf() {
	if (ch == '\n')
		return true;
	else return false;
}

void Point::line_feed() {
	if (is_lf()) {
		line++;
		next();
	}
}

void Point::move_to() {
	while (is_digit() || is_letter() || is_underline()) {
		next();
	}
}






