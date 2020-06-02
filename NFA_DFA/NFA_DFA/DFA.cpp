#include"DFA.h"

int DFA::get_index(set<int> x) {
	vector<set<int>>::iterator index = find(Dstate.begin(), Dstate.end(), x);
	if (index != Dstate.end()) {
		return index - Dstate.begin();
	}
	else {
		return -1;
	}
}

void DFA::create_dfa(NFA nfa) {
	if (nfa.is_DFA()) {
		copy(nfa);
	}
	else {
		set<int> sta_list;
		start = 0;
		Dstate.push_back(nfa.closure(nfa.start));
		states.insert(0);
		for (unsigned int i = 0; i < Dstate.size(); i++) {	//遍历所有状态集合
			for (set<char>::iterator it = nfa.chara.begin(); it != nfa.chara.end(); it++) {	//遍历所有转移字符集合
				if ((*it) != '@') {
					sta_list = nfa.move(Dstate[i], (*it));	//状态转移后的集合
					if (!sta_list.empty()) {	//集合不为空
						int index = get_index(sta_list);	//查看集合在DFA状态集中的下标
						if (index == -1) {		//下标为1表示不存在
							Dstate.push_back(set<int>(sta_list));	//加入到状态集合中
							index = get_index(sta_list);	//获得新的下标，即新的状态编号
							states.insert(index);	//加入到状态集
							if (nfa.is_end(sta_list)) {	//判断是否终结状态
								end.insert(index);
							}
						}
						int x = get_index(Dstate[i]);
						state_trans_table[x][index].push_back(*it);	//记录状态转移情况
					}
				}
			}
		}
	}
	initial();
}

bool DFA::is_equal(int x, int y) {
	if (x == y) {	//两个相等是等价状态
		return true;
	}
	else if (is_end(x) != is_end(y)) {	//一个为结束状态一个不是结束状态不为等价状态
		return false;
	}
	//同为结束状态或同不为结束状态
	for (set<int>::iterator it = states.begin(); it != states.end(); it++) {
		if (state_trans_table[x][*it] != state_trans_table[y][*it]) {	//一个状态转移不同即不为等价状态
			return false;
		}
	}
	return true;
}

int DFA::unionsearch(int root) {
	while (root != equal_list[root]) {
		return unionsearch(equal_list[root]);
	}
	return root;
}

void DFA::join(int root1, int root2) {
	equal_list[unionsearch(root1)] = unionsearch(root2);

	set<int>::iterator x;
	set<int>::iterator y;
	for (x = states.begin(); x != states.end(); x++) {
		for (y = states.begin(); y!= states.end(); y++) {
			if (equal_list[*x] != (*x) || equal_list[*y] != (*y)) {
				for (unsigned int i = 0; i < state_trans_table[*x][*y].size(); i++) {
					if (find(state_trans_table[equal_list[*x]][equal_list[*y]].begin(),
						state_trans_table[equal_list[*x]][equal_list[*y]].end(),
						state_trans_table[*x][*y][i]) ==
						state_trans_table[equal_list[*x]][equal_list[*y]].end()) {
						state_trans_table[equal_list[*x]][equal_list[*y]].push_back(state_trans_table[*x][*y][i]);
					}
				}
				state_trans_table[*x][*y].clear();
			}
		}
	}
}

void DFA::minimize() {
	set<int>::iterator it;
	set<int>::iterator y;
	for (it = states.begin(); it != states.end();it++) {
		equal_list[*it] = (*it);	//每个状态自己和自己是等价状态
	}
	while (true) {
		bool is_join = false;
		for (it = states.begin(); it != states.end(); it++) {
			for (y = it ; y != states.end(); y++) {
				int p = unionsearch(*it);
				int q = unionsearch(*y);
				if (p != q && is_equal(p, q)) {
					join(q, p);
					is_join = true;
				}
			}
		}
		if (is_join == false) {	//循环没有新的等价状态产生时结束循环
			break;
		}
	}

	for (int i = 0; i < states_num; i++) {	//更新状态集
		if (equal_list[i] != i) {
			states.erase(i);
			if (is_end(i)) {
				end.erase(i);
			}
		}
	}
	states_num = states.size();
}

bool DFA::judge(string text) {
	int now_state = start;
	int next_state;
	for (int i = 0; i < text.size(); i++) {
		bool flag = false;
		for (set<int>::iterator it = states.begin(); it != states.end(); it++) {
			if (find(state_trans_table[now_state][*it].begin(), state_trans_table[now_state][*it].end(),text[i])!= state_trans_table[now_state][*it].end()){
				flag = true;
				next_state = (*it);
			}
		}
		if (!flag) {
			return false;
		}
		now_state = next_state;
		if (i == text.size() - 1 ) {
			if (is_end(now_state)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}