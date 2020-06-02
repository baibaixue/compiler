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
		for (unsigned int i = 0; i < Dstate.size(); i++) {	//��������״̬����
			for (set<char>::iterator it = nfa.chara.begin(); it != nfa.chara.end(); it++) {	//��������ת���ַ�����
				if ((*it) != '@') {
					sta_list = nfa.move(Dstate[i], (*it));	//״̬ת�ƺ�ļ���
					if (!sta_list.empty()) {	//���ϲ�Ϊ��
						int index = get_index(sta_list);	//�鿴������DFA״̬���е��±�
						if (index == -1) {		//�±�Ϊ1��ʾ������
							Dstate.push_back(set<int>(sta_list));	//���뵽״̬������
							index = get_index(sta_list);	//����µ��±꣬���µ�״̬���
							states.insert(index);	//���뵽״̬��
							if (nfa.is_end(sta_list)) {	//�ж��Ƿ��ս�״̬
								end.insert(index);
							}
						}
						int x = get_index(Dstate[i]);
						state_trans_table[x][index].push_back(*it);	//��¼״̬ת�����
					}
				}
			}
		}
	}
	initial();
}

bool DFA::is_equal(int x, int y) {
	if (x == y) {	//��������ǵȼ�״̬
		return true;
	}
	else if (is_end(x) != is_end(y)) {	//һ��Ϊ����״̬һ�����ǽ���״̬��Ϊ�ȼ�״̬
		return false;
	}
	//ͬΪ����״̬��ͬ��Ϊ����״̬
	for (set<int>::iterator it = states.begin(); it != states.end(); it++) {
		if (state_trans_table[x][*it] != state_trans_table[y][*it]) {	//һ��״̬ת�Ʋ�ͬ����Ϊ�ȼ�״̬
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
		equal_list[*it] = (*it);	//ÿ��״̬�Լ����Լ��ǵȼ�״̬
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
		if (is_join == false) {	//ѭ��û���µĵȼ�״̬����ʱ����ѭ��
			break;
		}
	}

	for (int i = 0; i < states_num; i++) {	//����״̬��
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