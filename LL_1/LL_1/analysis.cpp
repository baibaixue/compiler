#include"grammer.h"

void Grammer::analysis(vector<WORD*> words) {
	if (!judge()) {
		exit(0);
	}
	stack<char> character;
	stack<string> input;
	input.push("$");
	character.push('$');
	character.push(S);
	for (int i = words.size()-1; i >= 0; i--) {
		if (words[i]->type == 27) {
			input.push("i");
		}
		else if (words[i]->type == 28) {
			input.push("NUM");
		}
		else {
			input.push(words[i]->name);
		}
	}
	string letter;
	string intop;
	while (character.top() != '$' || input.top() != "$") {
		letter = character.top();
		intop = input.top();
		if (is_vn(letter[0])) {
			unsigned int l = get_vn_index(letter[0]);
			unsigned int r = get_vt_index(intop[0]);
			int pro = AnalysisTable[l][r];
			if (pro == -1) {
				cout << "illegal arithmetic expression!" << endl;
				exit(0);
			}
			else {
				cout << production[pro].left << "->" << production[pro].right << endl;
				char left = production[pro].left;
				string right = production[pro].right;
				if (right == "@") {
					character.pop();
				}
				else {
					character.pop();
					for (int i = right.size()-1; i >= 0; i--) {
						character.push(right[i]);
					}
				}
				
			}
		}
		else if (is_vt(letter[0])) {
			if (letter == intop) {
				character.pop();
				input.pop();
			}
			else {
				cout << "illegal arithmetic expression!" << endl;
				exit(0);
			}
		}
	}
}

void Grammer::run(string grammerfile, string text) {
	initial(grammerfile);
	Inditect_left_recursion();
	Scanner scan;

	ifstream infile(text);
	istreambuf_iterator<char> begin(infile);
	istreambuf_iterator<char> end;
	string contest(begin, end);

	input = contest;

	cout << "Data1:" << endl;
	cout << input << endl;

	scan.get_words();
	scan.output();

	if (!error_list.empty()) {
		vector<pair<string, int>>::iterator itor;
		for (itor = error_list.begin(); itor != error_list.end(); itor++) {
			cout << (*itor).first << " in line: " << (*itor).second << endl;
		}
		exit(0);
	}
	Inditect_left_recursion();
	remove_left_Recursive();
	remove_left_CommonFactor();
	get_allfirst();
	get_allfollow();
	get_select();
	get_AnalysisTable();
	cout << "分析表：" << endl;
	output_AnalysisTable();
	cout << "分析过程：" << endl;
	analysis(scan.words);
}

void Grammer::show_detials_run(string grammerfile, string text) {
	initial(grammerfile);
	Inditect_left_recursion();
	Scanner scan;

	ifstream infile(text);
	istreambuf_iterator<char> begin(infile);
	istreambuf_iterator<char> end;
	string contest(begin, end);

	input = contest;

	cout << "Data1:" << endl;
	cout << input << endl;

	scan.get_words();
	cout << "词法分析：" << endl;
	scan.output();

	if (!error_list.empty()) {
		vector<pair<string, int>>::iterator itor;
		for (itor = error_list.begin(); itor != error_list.end(); itor++) {
			cout << (*itor).first << " in line: " << (*itor).second << endl;
		}
		exit(0);
	}
	cout << "读入文法：" << endl;
	output_grammer();
	cout << "间接左递归和潜在左递归处理：" << endl;
	Inditect_left_recursion();
	output_grammer();
	cout << "消除左递归：" << endl;
	remove_left_Recursive();
	output_grammer();
	cout << "提取左公共因子：" << endl;
	remove_left_CommonFactor();
	output_grammer();
	cout << "获取FIRST集：" << endl;
	get_allfirst();
	output_first();
	cout << "获取FOLLOW集：" << endl;
	get_allfollow();
	output_follow();
	cout << "获取SELECT集：" << endl;
	get_select();
	output_select();
	cout << "分析表：" << endl;
	get_AnalysisTable();
	output_AnalysisTable();
	cout << "分析过程：" << endl;
	analysis(scan.words);
}