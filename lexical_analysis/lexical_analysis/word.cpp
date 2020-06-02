#include"head.h"

void WORD::assignment(const string strname) {
	name = strname;
	type = key_words[name];
}

void WORD::output() {
	cout << "[" << name << "," << type << "]" << endl;
}

bool WORD::is_empty() {
	if (name.empty()) {
		return true;
	}
	else return false;
}