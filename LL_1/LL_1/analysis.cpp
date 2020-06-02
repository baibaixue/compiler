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
	cout << "������" << endl;
	output_AnalysisTable();
	cout << "�������̣�" << endl;
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
	cout << "�ʷ�������" << endl;
	scan.output();

	if (!error_list.empty()) {
		vector<pair<string, int>>::iterator itor;
		for (itor = error_list.begin(); itor != error_list.end(); itor++) {
			cout << (*itor).first << " in line: " << (*itor).second << endl;
		}
		exit(0);
	}
	cout << "�����ķ���" << endl;
	output_grammer();
	cout << "�����ݹ��Ǳ����ݹ鴦��" << endl;
	Inditect_left_recursion();
	output_grammer();
	cout << "������ݹ飺" << endl;
	remove_left_Recursive();
	output_grammer();
	cout << "��ȡ�󹫹����ӣ�" << endl;
	remove_left_CommonFactor();
	output_grammer();
	cout << "��ȡFIRST����" << endl;
	get_allfirst();
	output_first();
	cout << "��ȡFOLLOW����" << endl;
	get_allfollow();
	output_follow();
	cout << "��ȡSELECT����" << endl;
	get_select();
	output_select();
	cout << "������" << endl;
	get_AnalysisTable();
	output_AnalysisTable();
	cout << "�������̣�" << endl;
	analysis(scan.words);
}