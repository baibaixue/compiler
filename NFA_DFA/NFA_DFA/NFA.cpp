#include"NFA.h"

NFA::NFA(NFA& nfa) {
	states_num = nfa.states_num;
	end = nfa.end;
	states = nfa.states;
	chara = nfa.chara;
	for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
		for (set<int>::iterator j = states.begin(); j != states.end(); j++) {
			state_trans_table[*i][*j] = nfa.state_trans_table[*i][*j];
		}
	}
}

void NFA::copy(const NFA& nfa) {
	states_num = nfa.states_num;
	end = nfa.end;
	states = nfa.states;
	chara = nfa.chara;
	for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
		for (set<int>::iterator j = states.begin(); j != states.end(); j++) {
			state_trans_table[*i][*j] = nfa.state_trans_table[*i][*j];
		}
	}
}

void NFA::initial(string filename) {
	ifstream file;
	file.open(filename);
	assert(file.is_open());

	states_num = 0;
	start = 0;
	string line;
	int cnt = 0;
	int m = -1;
	while (getline(file, line)) {
		cnt++;
		if (cnt == 1) {	//文本文件第一行，状态数
			for (unsigned int i = 0; i < line.size(); i++) {
				if (line[i] != ' ') {
					states_num = states_num * 10 + (line[i] - '0');
				}
			}
		}
		else if (cnt == 2) {	//文本文件第二行，开始状态
			for (unsigned int i = 0; i < line.size(); i++) {
				if (line[i] != ' ') {
					start = start * 10 + (line[i] - '0');
				}
			}
		}
		else if (cnt == 3) {	//文本文件第三行，状态转移条数
			m = 0;
			for (unsigned int i = 0; i < line.size(); i++) {
				if (line[i] != ' ') {
					m = m * 10 + (line[i] - '0');
				}
			}
		}
		else if (m == 0) {	//最后一行，结束状态
			int e = 0;
			for (unsigned int i = 0; i < line.size(); i++) {
				if (line[i] != ' ') {
					e = e * 10 + (line[i] - '0');
				}
				else if (line[i] == ' ') {
					end.insert(e);
					e = 0;
				}
				if (i == line.size() - 1) {
					end.insert(e);
				}
			}
			
		}
		else if (m != 0) {	//状态转移
			int s, e;
			char c;
			get_num_char(line, s, e, c);
			state_trans_table[s][e].push_back(c);
			states.insert(s);
			states.insert(e);
			chara.insert(c);
			m--;
		}
	}
	file.close();
}

void NFA::initial() {
	states.clear();
	chara.clear();
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (!state_trans_table[i][j].empty()) {
				states.insert(i);
				states.insert(j);
				for (unsigned int k = 0; k < state_trans_table[i][j].size(); k++) {
					chara.insert(state_trans_table[i][j][k]);
				}
			}
		}
	}
	states_num = states.size();
}

void NFA::insert_state(int s, int e, char c) {
	states.insert(s);
	states.insert(e);
	chara.insert(c);
	state_trans_table[s][e].push_back(c);
}

bool NFA::is_end(int x) {
	if (find(end.begin(), end.end(), x) == end.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool NFA::is_end(set<int> x) {
	for (set<int>::iterator it = end.begin(); it != end.end(); it++) {
		if (find(x.begin(), x.end(), (*it)) != x.end()) {
			return true;
		}
	}
	return false;
}

bool NFA::is_states(int x) {
	if (find(states.begin(), states.end(), x) == states.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool NFA::is_chara(char c) {
	if (find(chara.begin(), chara.end(), c) == chara.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool NFA::is_trans(int s, int e, char c) {
	if (s < MAXN && e < MAXN && !state_trans_table[s][e].empty()) {
		if (find(state_trans_table[s][e].begin(), state_trans_table[s][e].end(), c) != state_trans_table[s][e].end()) {
			return true;
		}
	}
	return false;
}

bool NFA::is_DFA() {
	if (is_chara('@')) {
		return false;
	}
	else {
		for (int i = 0; i < states_num; i++) {
			for (int j = 0; j < states_num; j++) {
				if (state_trans_table[i][j].size() > 1) {
					return false;
				}
			}
			
		}
	}
	return true;
}

void NFA::output() {
	for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
		int s = (*i);
		for (set<int>::iterator j = states.begin(); j != states.end(); j++) {
			int e = (*j);
			if (!state_trans_table[s][e].empty()) {
				for (unsigned int k = 0; k < state_trans_table[s][e].size(); k++) {
					cout << s << '-' << state_trans_table[s][e][k] << "->" << e << endl;
				}
			}
		}
	}
	cout << "Start state:"<<start<< endl;
	cout << "End state:";
	for (set<int>::iterator it = end.begin(); it != end.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
}

set<int> NFA::closure(int x) {
	set<int> res;
	queue<int> sta;
	sta.push(x);
	res.insert(x);
	while (!sta.empty()) {
		int s = sta.front();
		sta.pop();
		for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
			int e = (*i);
			if (is_trans(s, e, '@')) {
				sta.push(e);
				res.insert(e);
			}
		}
	}
	return res;
}

set<int> NFA::closure(set<int> x) {
	set<int> res;
	queue<int> sta;
	for (set<int>::iterator it = x.begin(); it != x.end(); it++) {
		res.insert(*it);
		sta.push(*it);
	}
	while (!sta.empty()) {
		int s = sta.front();
		sta.pop();
		for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
			int e = (*i);
			if (is_trans(s, e, '@')) {
				sta.push(e);
				res.insert(e);
			}
		}
	}
	return res;
}

set<int> NFA::move(int x, char c) {
	set<int> res;
	for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
		int e = (*i);
		if (is_trans(x, e, c)) {
			res.insert(e);
		}
	}
	return closure(res);
}

set<int> NFA::move(set<int> x, char c) {
	set<int> res;
	for (set<int>::iterator it = x.begin(); it != x.end(); it++) {
		int s = (*it);
		for (set<int>::iterator i = states.begin(); i != states.end(); i++) {
			int e = (*i);
			if (is_trans(s, e, c)) {
				res.insert(e);
			}
		}
	}
	return closure(res);
}

void get_num_char(string line, int& s, int& e, char& c){
	s = 0;
	e = 0;
	c = '\0';
	int num = 0;
	for (unsigned int i = 0; i < line.size(); i++) {
		if (num == 0) {
			if (line[i] != ' ') {
				s = s * 10 + (line[i] - '0');
			}
			else {
				num = 1;
			}
		}
		else if(num == 1){
			if (line[i] != ' ') {
				e = e * 10 + (line[i] - '0');
			}
			else {
				num = 2;
			}
		}
		else {
			if (line[i] != ' ') {
				c = line[i];
			}
		}
	}
}
