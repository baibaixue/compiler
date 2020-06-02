#include"SLR_grammer.h"

bool SLR_Grammer::analysis(vector<WORD*> words) {
	bool res = true;
	if (!judge()) {
		return false;
	}
	stack<int> states;
	stack<char> chara;
	string inputstring;
	states.push(0);
	chara.push('$');
	for (unsigned int i = 0; i < words.size(); i++) {
		string n = words[i]->name;
		int t = words[i]->type;
		if (t == 27) {
			inputstring += "i";
			continue;
		}
		for (unsigned int y = 0; y < n.size(); y++) {
			inputstring += string(1, n[y]);
		}
	}
	inputstring += "$";
	unsigned int cnt = 0;
	while (true) {
		if (cnt >= inputstring.size()) {
			return false;
		}
		int s = states.top();
		char c = inputstring[cnt];
		char first;
		int second;
		first = Action[s][get_vt_index(c)].first;
		second = Action[s][get_vt_index(c)].second;
		if (first == 's') {
			states.push(second);
			chara.push(c);
			cnt++;
			cout << "Action:	" << first << second << endl;
		}
		else if (first == 'r') {
			for (unsigned int i = 0; i < production[second].right.size(); i++) {
				chara.pop();
				states.pop();
			}
			chara.push(production[second].left);
			c = production[second].left;
			s = states.top();
			int go = Goto[s][get_vn_index(c)];
			if (go != -1) {
				states.push(go);
			}
			else {
				return false;
			}
			cout << "Action:	" << first << second << "	GoTo:	" << go << endl;
		}
		else if (first == 'a') {
			cout << "Action:	acc" << endl;
			return true;
		}
		else {
			return false;
		}

	}
}