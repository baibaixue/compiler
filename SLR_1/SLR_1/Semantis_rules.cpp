#include"SLR_grammer.h"
/*
void SLR_Grammer::create_var_id(vector<WORD*> w) {
	vector<string> id;
	char a = 'A';
	for (unsigned int i = 0; i < w.size(); i++) {
		if (find(id.begin(), id.end(), w[i]->name) == id.end()) {
			id.push_back(w[i]->name);
			variable.push_back(var{a,1});
			a++;
		}
	}
}

char SLR_Grammer::creat_new_id() {
	char a = 'A';
	while (true) {
		if (has_var(a) == -1) {
			variable.push_back(var{ a,1 });
			return a;
		}
		a++;
	}
}

int SLR_Grammer::has_var(char c) {
	for (unsigned int i = 0; i < variable.size(); i++) {
		if (c == variable[i].name) {
			return i;
		}
	}
	return -1;
}

quatern SLR_Grammer::Definition_rule(char l,string r,int n) {
	quatern res;
	int arg1_num;
	int arg2_num;
	int res_num;
	switch (n) {
		case 1:	//S->i:=E
			res.op = ":=";
			res.arg1 = r[3];
			res.arg2 = '\0';
			res.result = creat_new_id();
			arg1_num = has_var(r[3]);
			assert(arg1_num == -1);
			res_num = has_var(res.result);
			variable[res_num].value = variable[arg1_num].value;
			return res;
		case 2:	//E->E+T
			res.op = '+';
			res.arg1 = r[0];
			res.arg2 = r[2];
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			arg2_num = has_var(r[2]);
			res_num = has_var(res.result);
			assert(arg1_num == -1 || arg2_num == -1);
			variable[res_num].value = variable[arg1_num].value + variable[arg2_num].value;
			return res;
		case 3:	//E->E-F
			res.op = '-';
			res.arg1 = r[0];
			res.arg2 = r[2];
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			arg2_num = has_var(r[2]);
			res_num = has_var(res.result);
			assert(arg1_num == -1 || arg2_num == -1);
			variable[res_num].value = variable[arg1_num].value - variable[arg2_num].value;
			return res;
		case 4:	//E->T
			res.op = "=";
			res.arg1 = r[0];
			res.arg2  = '\0';
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			assert(arg1_num == -1);
			res_num = has_var(res.result);
			variable[res_num].value = variable[arg1_num].value;
			return res;
		case 5:	//T->T*F
			res.op = '*';
			res.arg1 = r[0];
			res.arg2 = r[2];
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			arg2_num = has_var(r[2]);
			res_num = has_var(l);
			assert(arg1_num == -1 || arg2_num == -1);
			variable[res_num].value = variable[arg1_num].value * variable[arg2_num].value;
			return res;
		case 6:	//T->T/F
			res.op = '/';
			res.arg1 = r[0];
			res.arg2 = r[2];
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			arg2_num = has_var(r[2]);
			res_num = has_var(res.result);
			assert(arg1_num == -1 || arg2_num == -1);
			variable[res_num].value = variable[arg1_num].value / variable[arg2_num].value;
			return res;
		case 7:	//T->F
			res.op = "=";
			res.arg1 = r[0];
			res.arg2 = '\0';
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			assert(arg1_num == -1);
			res_num = has_var(l);
			variable[res_num].value = variable[arg1_num].value;
			return res;
		case 8:	//F->(E)
			res.op = "=";
			res.arg1 = r[1];
			res.arg2 = '\0';
			res.result = creat_new_id();
			arg1_num = has_var(r[1]);
			assert(arg1_num == -1);
			res_num = has_var(res.result);
			variable[res_num].value = variable[arg1_num].value;
			return res;
		case 9:	//F->i
			res.op = "=";
			res.arg1 = r[0];
			res.arg2 = '\0';
			res.result = creat_new_id();
			arg1_num = has_var(r[0]);
			assert(arg1_num == -1);
			int res_num = has_var(res.result);
			variable[res_num].value = variable[arg1_num].value;
			return res;
		default:return res;
	}
}
*/

int SLR_Grammer::has_var(string name)
{
	for (unsigned int i = 0; i < variable.size(); i++) {
		if (name == variable[i].name) {
			return i;
		}
	}
	return -1;
}

string SLR_Grammer::creat_new_id(char c, string name)
{
	var v;
	v.i = c;
	v.name = name;
	v.value = 1;
	variable.push_back(v);
	return name;
}
string SLR_Grammer::creat_new_id(char c)
{
	string name ;
	int num = 0;
	while (true) {
		name = "t" + to_string(num);
		if (has_var(name) == -1) {
			var v;
			v.i = c;
			v.name = name;
			v.value = 1;
			variable.push_back(v);
			return name;
		}
		else {
			num++;
		}
	}
}

quatern SLR_Grammer::Definition_rule(var arg1, var arg2, char res, int n)
{
	quatern result;
	int res_num = has_var(creat_new_id(res));
	if (n == 2 || n == 3 || n == 5 || n == 6) {
		result.op = production[n].right[1];
		result.arg1 = arg1.name;
		result.arg2 = arg2.name;
		result.result = variable[res_num].name;
		switch (n)
		{
			case 2:
				variable[res_num].value = arg1.value + arg2.value;
				return quatern(result);
			case 3:
				variable[res_num].value = arg1.value - arg2.value;
				return quatern(result);
			case 5:
				variable[res_num].value = arg1.value * arg2.value;
				return quatern(result);
			case 6:
				variable[res_num].value = arg1.value / arg2.value;
				return quatern(result);
			default:
				break;
		}
	}
	else {
		cout << "error!" << endl;
		exit(0);
	}
}
void SLR_Grammer::Definition_rule(var& arg1, char res, int n)
{
	if (n == 4 || n == 7 || n==9) {
		arg1.i = res;
	}
	else {
		cout << "error!" << endl;
		exit(0);
	}
}
quatern SLR_Grammer::Definition_rule(var arg1, char res)
{
	quatern result;
	int res_num = has_var(creat_new_id(res));
	result.op = "=()";
	result.arg1 = arg1.name;
	result.arg2 = "\0";
	result.result = variable[res_num].name;
	variable[res_num].value = arg1.value;
	
	return quatern(result);
}
quatern SLR_Grammer::Definition_rule(var arg1, var& res)
{
	quatern result;
	result.op = ":=";
	result.arg1 = arg1.name;
	result.arg2 = "\0";
	result.result = res.name;
	res.value = arg1.value;

	return quatern(result);
}
void SLR_Grammer::output_3_address_code(vector<quatern> q) {
	for (unsigned int i = 0; i < q.size(); i++) {
		if (q[i].op == "=()") {
			cout << q[i].result << "=(" << q[i].arg1 << ")" <<endl;
		}
		else if (q[i].arg2 == "\0") {
			cout << q[i].result << q[i].op << q[i].arg1 << endl;
		}
		else {
			cout << q[i].result << "=" << q[i].arg1 << q[i].op << q[i].arg2 << endl;
		}
	}
}

vector<quatern> SLR_Grammer::get_analysis(vector<WORD*> words) {
	vector<quatern> res;
	if (!judge()) {
		exit(0);
	}
	stack<int> states;
	stack<var> chara;
	vector<var> inputstring;
	states.push(0);
	chara.push(var{ "\0",0,'$' });
	for (unsigned int i = 0; i < words.size(); i++) {
		string n = words[i]->name;
		int t = words[i]->type;
		if (t == 27) {
			int num = has_var(words[i]->name);
			if (num == -1) {
				num = has_var(creat_new_id('i', words[i]->name));
			}
			inputstring.push_back(variable[num]);
			continue;
		}
		for (unsigned int y = 0; y < n.size(); y++) {
			inputstring.push_back(var{ "\0",0,n[y] });
		}
	}
	inputstring.push_back(var{ "\0",0,'$' });
	unsigned int cnt = 0;
	while (true) {
		if (cnt >= inputstring.size()) {
			cout << "False!" << endl;
			exit(0);
		}
		int s = states.top();
		char c = inputstring[cnt].i;
		char first;
		int second;
		first = Action[s][get_vt_index(c)].first;
		second = Action[s][get_vt_index(c)].second;
		if (first == 's') {
			states.push(second);
			chara.push(inputstring[cnt]);
			cnt++;
			cout << "Action:	" << first << second << endl;
		}
		else if (first == 'r') {
			int arg1_num = -1;
			int arg2_num = -1;
			for (unsigned int i = 0; i < production[second].right.size(); i++) {
				if (chara.top().name != "\0") {
					if (arg2_num != -1) {
						arg1_num = has_var(chara.top().name);
					}
					else {
						arg2_num = has_var(chara.top().name);
					}
				}
				chara.pop();
				states.pop();
			}
			if (second == 1) {
				quatern q = Definition_rule(variable[arg2_num], variable[arg1_num]);
				res.push_back(q);
				cout << "(" << q.op << "," << q.arg1 << "," << " " << "," << q.result << ")" << endl;
				chara.push(var{"\0", 0, 'S'});
			}
			else if (second == 8) {
				quatern q = Definition_rule(variable[arg2_num], production[second].left);
				cout << "(" << q.op << "," << q.arg1 << "," << " " << "," << q.result << ")" << endl;
				res.push_back(q);
				chara.push(variable[has_var(q.result)]);
			}
			else if (second == 4 || second == 7 || second == 9) {
				Definition_rule(variable[arg2_num], production[second].left,second);
				chara.push(variable[arg2_num]);
			}
			else {
				quatern q = Definition_rule(variable[arg1_num], variable[arg2_num], production[second].left,second);
				cout << "(" << q.op << "," << q.arg1 << "," << q.arg2 << "," << q.result << ")" << endl;
				res.push_back(q);
				chara.push(variable[has_var(q.result)]);
			}
			c = production[second].left;
			s = states.top();
			int go = Goto[s][get_vn_index(c)];
			if (go != -1) {
				states.push(go);
			}
			else {
				cout << "False!" << endl;
				exit(0);
			}
			cout << "Action:	" << first << second << "	GoTo:	" << go << endl;
		}
		else if (first == 'a') {
			cout << "Action:	acc" << endl;
			return res;
		}
		else {
			cout << "False!" << endl;
			exit(0);
		}

	}
	
}
