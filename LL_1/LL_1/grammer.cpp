#include"grammer.h"


bool operator < (const Production& r, const Production& l) {
	if (r.left < l.left) {
		return true;
	}
	else if (r.right < l.right) {
		return true;
	}
	else {
		return false;

	}
}

Grammer::Grammer() {
	Vt.clear();
	Vn.clear();
	S = '\0';
	production.clear();
	First->clear();
	Follow->clear();
	Select.clear();
	is_LL1 = true;
	for (unsigned int i = 0; i < Vn.size(); i++) {
		for (unsigned int j = 0; j < Vt.size(); j++) {
			AnalysisTable[i][j] = -1;
		}
	}

}

void Grammer::initial(string filename) {
	ifstream txtfile;
	txtfile.open(filename);
	assert(txtfile.is_open());

	string line;
	int linecnt = 0;
	while (getline(txtfile, line)) {
		linecnt++;
		if (linecnt == 1) {
			S = line[0];
		}
		
		else if (linecnt == 2) {
		/*
			for (unsigned int i = 0; i < line.length(); i++) {
				if (line[i] != ' ' ) {
					Vn.push_back(char(line[i]));
				}
			}
		*/
		}
		
		else if (linecnt == 3) {
			string vn;
			for (unsigned int i = 0; i < line.length(); i++) {
				if (line[i] != ' ') {
					Vt.push_back(char(line[i]));
				}
			}
		}
		else {
			char l;
			string r;
			bool is_left = true;
			for (unsigned int i = 0; i < line.length(); i++) {
				if (is_left) {
					if (i+1 < line.length() && line[i] == '-' && line[i + 1] == '>') {
						i++;
						is_left = false;
					}
					else {
						l = line[i];
					}
				}
				else {
					if (line[i] == '|') {
						production.push_back(Production(l, r));
						r.clear();
					}
					else {
						r += line[i];
					}
					if (i + 1 == line.length()) {
						production.push_back(Production(l, r));
					}
				}
				if (find(Vn.begin(), Vn.end(), l) == Vn.end()) {
					Vn.push_back(l);
				}
			}
		}

	}
	txtfile.close();
}

void Grammer::output_grammer() {
	cout << "开始符号:" << S << endl;
	
	vector<char>::iterator itvn;
	vector<char>::iterator itvt;
	vector<Production>::iterator itpro;

	cout << "非终结符号:";
	for (itvn = Vn.begin(); itvn != Vn.end()-1; itvn++) {
		cout << *itvn << " ,";
	}
	cout << *itvn <<endl;

	cout << "终结符号:";
	for (itvt = Vt.begin(); itvt != Vt.end()-1; itvt++) {
		cout << *itvt << " ,";
	}
	cout <<*itvt<< endl;

	cout << "产生式:" << endl;
	for (itpro = production.begin(); itpro != production.end(); itpro++) {
		cout << (*itpro).left << "::" << (*itpro).right << endl;
	}
}

unsigned int Grammer::get_vn_index(char c) {
	vector<char>::iterator it;
	it = find(Vn.begin(), Vn.end(), c);
	return it - Vn.begin();
}

unsigned int Grammer::get_vt_index(char c) {
	vector<char>::iterator it;
	it = find(Vt.begin(), Vt.end(), c);
	return it - Vt.begin();
}

bool Grammer::is_vn(char c) {
	if (find(Vn.begin(), Vn.end(), c) == Vn.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool Grammer::is_vt(char c) {
	if (find(Vt.begin(), Vt.end(), c) == Vt.end()) {
		return false;
	}
	else {
		return true;
	}
}

void Grammer::Inditect_left_recursion() {
	char l_list[MAXN] = {0};	//记录发生代入的表达式左部
	string r_list[MAXN] ;	//记录发生代入的表达式右部
	int cnt = 0;
	for (unsigned int i = 0; i < production.size(); i++) {
		char il = production[i].left;
		string ir = production[i].right;
		for (unsigned int j = i+1; j < production.size(); j++) {
			char jl = production[j].left;
			string jr = production[j].right;
			if (jr[0] == il && il!=jl) {
				string new_r = ir + jr.substr(1);
				production.insert(production.begin()+j+1, Production(jl, new_r));
				l_list[cnt] = jl;
				r_list[cnt] = jr;
				cnt++;
				j++;
			}
		}
	}
	for (unsigned int i = 0; i < production.size(); i++) {	//将发生代入的原表达式删去
		for (int j = 0; j < cnt; j++) {
			if (production[i].is_equal(l_list[j], r_list[j])) {
				production.erase((production.begin() + i));
			}
		}
	}
}

void Grammer::remove_left_Recursive() {
	char new_left[MAXN] = {0};	//新产生的非终结符
	int cnt = 0;
	bool is_leftrec[MAXN] = {0};	//非终结符是否左递归
	for (unsigned int i = 0; i < production.size(); i++) {
		char l = production[i].left;
		string r = production[i].right;
		unsigned int index = get_vn_index(l);
		if (l == r[0]) {	//A->Aa形式
			char new_l;
			string new_r;
			if (!is_leftrec[index]) {
				is_leftrec[index] = true;	//记录该非终结符左递归

				new_l = 'A' + cnt;
				while (is_vn(new_l) || is_vt(new_l)) {	//生成新的非终结符A'(不在现有终结符号和非终结符号集合中)
					cnt++;
					new_l = 'A' + cnt;
				}
				Vn.push_back(new_l);
				new_left[index] = new_l;
			}
			
			new_r = r.substr(1);	//将A->Aa形式转换为A'->aA'形式
			new_r += new_left[index];
			production[i].change(new_left[index], new_r);
		}
	}
	for (unsigned int j = 0; j < production.size(); j++) {	//A->b ,A左递归情况
		char l = production[j].left;	//将A->b转换为A->bA'形式
		string r = production[j].right;
		unsigned int index = get_vn_index(l);
		if (is_leftrec[index]) {
			string new_r; 
			new_r = r + new_left[index];
			production[j].change(l, new_r);
		}
	}

	for (unsigned int k = 0; k < Vn.size(); k++) {	//新生成的非终结符号产生A'->@表达式
		unsigned int index = get_vn_index(Vn[k]);
		if (is_leftrec[index]) {
			production.push_back(Production(new_left[index], "@"));
			if (!is_vt('@')) {
				Vt.push_back('@');
			}
		}
	}
}

void Grammer::remove_left_CommonFactor() {
	char new_left[MAXN] = { 0 };	//新产生的非终结符
	int cnt = 0;
	bool is_leftfac[MAXN] = { 0 };	//非终结符是否存在左因子

	for (unsigned int i = 0; i < production.size(); i++) {	//遍历产生式集合
		char il = production[i].left;
		string ir = production[i].right;
		unsigned int index = get_vn_index(il);
		for (unsigned int j = i+1; j < production.size(); j++) {
			char jl = production[j].left;
			string jr = production[j].right;
			
			if (il == jl && ir[0] == jr[0]&&(!production[i].is_equal(production[j]))) {	//两个表达式有左因子且不相等，A->Ba,A->Bc
				if (!is_leftfac[index]) {	//未被记录由左因子则进行如下处理
					char new_l;
					is_leftfac[index] = true;	//该非终结符存在左因子
					new_l = 'A' + cnt;
					while (is_vn(new_l) || is_vt(new_l)) {	//生成新的非终结符
						cnt++;
						new_l = 'A' + cnt;
					}
					Vn.push_back(new_l);
					new_left[index] = new_l;
				}
				string new_ir, new_jr;
				if (ir.size() == 1) {	//A->B和A->Bc情况产生A'->@和A'->c
					new_ir = "@";
					if (!is_vt('@')) {
						Vt.push_back('@');
					}
				}
				else {
					new_ir = ir.substr(1);
				}
				if (jr.size() == 1) {
					new_jr = "@";
					if (!is_vt('@')) {
						Vt.push_back('@');
					}
				}
				else {
					new_jr = jr.substr(1);
				}
			production[i].change(new_left[index], new_ir);//在原产生式的基础上进行更改
			production[j].change(new_left[index], new_jr);
			}
		}
		if (is_leftfac[index]) {	//循环后发现有公共左因子，生成A->BA'产生式
			string new_r;
			string a, b;
			a = ir[0];
			b = new_left[index];
			new_r = a + b;
			production.push_back(Production(il, new_r));
			is_leftfac[index] = false;
		}
	}
}

void Grammer::get_first(char c) {
	unsigned int index = get_vn_index(c);
	int cnt = 0;
	for (unsigned int i = 0; i < production.size(); i++) {	//遍历产生式集合
		if (production[i].left == c) {
			string right = production[i].right;
			if (is_vt(right[0])) {	//右部第一个是终结符号
				First[index].insert(right[0]);
			}
			else if (is_vn(right[0])) {	//右部第一个是非终结符号
				
				for (unsigned j = 0; j < right.length(); j++) {	//依次向后查找
					bool has_empty = false;
					if (is_vn(right[j])) {	//非终结符号
						unsigned int num = get_vn_index(right[j]);
						get_first(right[j]);
						for (set<char>::iterator it = First[num].begin(); it != First[num].end(); it++) {
							if ((*it) == '@') {	//该非终结符号可以生成空串
								has_empty = true;
							}
							else {
								First[index].insert(*it);	//加入FIRST集
							}
						}
						if (has_empty == false) {	//不能生成空串，停止循环
							break;
						}
						else {
							cnt++;
						}
					}
					else if (is_vt(right[j])) {		//是终结符号，停止循环
						First[index].insert(right[j]);
						break;
					}
					if (cnt == right.length()) {	//右部可为空的符号个数和字符串长度相等
						First[index].insert('@');
					}
				}
			}
		}
	}
}

void Grammer::get_allfirst() {
	for (unsigned int i = 0; i < Vn.size(); i++) {
		if (First[i].empty()) {
			get_first(Vn[i]);
		}
	}
}

void Grammer::output_first() {
	for (unsigned int i = 0; i < Vn.size(); i++) {
		cout << Vn[i] << ":{";
		set<char>::iterator it ;
		for (it = First[get_vn_index(Vn[i])].begin(); it != First[get_vn_index(Vn[i])].end(); it++) {
			if (it == First[get_vn_index(Vn[i])].begin()) {
				cout << (*it);
			}
			else {
				cout << ',' << (*it);
			}
		}
		cout << "}" << endl;
	}
}

void Grammer::get_follow(char c) {
	unsigned int index = get_vn_index(c);	//非终结符号的索引
	for (unsigned int i = 0; i < production.size(); i++) {	//遍历产生式
		string ir = production[i].right;
		char il = production[i].left;
		for (unsigned int x = 0; x < ir.size(); x++) {	//遍历产生式右部
			if (c == ir[x] && x < ir.size() - 1) {	//找到非终结符号 并且不是右部的最后一个
				char next = production[i].right[x + 1];	//下一个符号
				if (is_vt(next)) {	//下一个符号是终结符号
					Follow[index].insert(next);
				}
				else if(is_vn(next)){	//下一个符号是非终结符号
					unsigned int now = x;
					int cnt = 0;
					while (true) {	//求后面串的First集
						next = production[i].right[now + 1];
						if (is_vt(next)) {
							Follow[index].insert(next);
							break;
						}
						else {
							bool has_empty = false;
							unsigned int num = get_vn_index(next);
							for (set<char>::iterator it = First[num].begin(); it != First[num].end(); it++) {	//遍历first集
								if ((*it) == '@') {
									has_empty = true;
								}
								else {
									Follow[index].insert(*it);
								}
							}
							if (has_empty) {
								cnt++;
								now++;
							}
							else {
								break;
							}
						}
						if (now == ir.size() - 1) {
							break;
						}

					}
					if (cnt == ir.size() - x - 1 && c != il) {
						//get_follow(il);
						for (set<char>::iterator it = Follow[get_vn_index(il)].begin(); it != Follow[get_vn_index(il)].end(); it ++) {
							Follow[index].insert(*it);
						}
					}
				}
			}
			else if (c == ir[x] && x == ir.size() - 1&& c!= il) {
				//get_follow(il);
				for (set<char>::iterator it = Follow[get_vn_index(il)].begin(); it != Follow[get_vn_index(il)].end(); it ++) {
					Follow[index].insert(*it);
				}
			}
		}
	}
}

void Grammer::get_allfollow() {
	unsigned int start = get_vn_index(S);
	Follow[start].insert('$');
	Vt.push_back('$');
	set<char> follow_re[MAXN];
	for (unsigned int i = 0; i < Vn.size(); i++) {
		follow_re[get_vn_index(Vn[i])] = Follow[get_vn_index(Vn[i])];
	}
	bool is_change;
	while (true) {
		is_change = false;
		for (unsigned int i = 0; i < Vn.size(); i++) {
			get_follow(Vn[i]);
		}
		for (unsigned int i = 0; i < Vn.size(); i++) {
			if (follow_re[get_vn_index(Vn[i])] != Follow[get_vn_index(Vn[i])]) {
				is_change = true;
			}
		}
		if (!is_change) {
			break;
		}

		for (unsigned int i = 0; i < Vn.size(); i++) {
			follow_re[get_vn_index(Vn[i])] = Follow[get_vn_index(Vn[i])];
		}
	}
}

void Grammer::output_follow() {
	for (unsigned int i = 0; i < Vn.size(); i++) {
		cout << Vn[i] << ":{";
		set<char>::iterator it;
		for (it = Follow[get_vn_index(Vn[i])].begin(); it != Follow[get_vn_index(Vn[i])].end(); it++) {
			if (it == Follow[get_vn_index(Vn[i])].begin()) {
				cout << (*it);
			}
			else {
				cout << ',' << (*it);
			}
		}
		cout << "}" << endl;
	}
}

void Grammer::get_select() {
	set<char> letter;
	for (unsigned int i = 0; i < production.size(); i++) {
		char il = production[i].left;
		string ir = production[i].right;
		if (is_vt(ir[0])&&ir[0]!='@') {
			letter.insert(ir[0]);
			Select.push_back(make_pair(Production(il,ir),set<char>(letter)));
			letter.clear();
		}
		else if (ir[0] == '@') {
			set<char>::iterator it;
			for (it = Follow[get_vn_index(il)].begin(); it != Follow[get_vn_index(il)].end(); it++) {
				letter.insert(*it);
			}
			Select.push_back(make_pair(Production(il, ir), set<char>(letter)));
			letter.clear();
		}
		else if (is_vn(ir[0])) {
			int cnt = 0;
			for (unsigned int x = 0; x < ir.length(); x++) {
				bool is_empty = false;
				if (is_vt(ir[x])) {
					letter.insert(ir[x]);
					break;
				}
				else {
					for (set<char>::iterator it = First[get_vn_index(ir[x])].begin(); it != First[get_vn_index(ir[x])].end(); it++) {
						if ((*it) == '@') {
							is_empty = true;
						}
						else {
							letter.insert(*it);
						}
					}
					if (is_empty) {
						cnt++;
					}
					else {
						break;
					}
				}
			}
			if (cnt == ir.length() ) {
				set<char>::iterator it;
				for (it = Follow[get_vn_index(il)].begin(); it != Follow[get_vn_index(il)].end(); it++) {
					letter.insert(*it);
				}
			}
			Select.push_back(make_pair(Production(il,ir),set<char>(letter)));
			letter.clear();
		}
	}
}

void Grammer::output_select() {
	vector<pair<Production, set<char>>>::iterator it;
	for (it = Select.begin(); it != Select.end(); it++) {
		cout << "Select(" << (*it).first.left << "->" << (*it).first.right << ")=";

		set<char>::iterator i;
		for (i = (*it).second.begin(); i != (*it).second.end(); i++) {
			if (i == (*it).second.begin()) {
				cout << "{" << (*i);
			}
			else {
				cout << "," << (*i);
			}
		}
		cout << "}" << endl;
	}
}


void Grammer::get_AnalysisTable() {
	for (unsigned int i = 0; i < Vn.size(); i++) {
		for (unsigned int j = 0; j < Vt.size(); j++) {
			AnalysisTable[i][j] = -1;
		}
	}
	for (unsigned int i = 0; i <Select.size(); i++) {
		unsigned int vn = get_vn_index(Select[i].first.left);
		set<char>::iterator it;
		for (it = Select[i].second.begin(); it != Select[i].second.end(); it++) {
			unsigned int vt = get_vt_index(*it);
			if (AnalysisTable[vn][vt] != -1) {
				is_LL1 = false;
				return;
			}
			else {
				AnalysisTable[vn][vt] = i;
			}
		}
	}
}

void Grammer::output_AnalysisTable() {
	cout.width(10);
	cout.setf(ios::left);
	cout << " ";
	for (unsigned int i = 0; i < Vt.size(); i++) {
		cout.width(10);
		cout.setf(ios::left);
		cout << Vt[i];
	}
	cout << endl;
	for (unsigned int x = 0; x < Vn.size(); x++) {
		cout.width(10);
		cout.setf(ios::left);
		cout << Vn[x];
		for (unsigned int y = 0; y < Vt.size(); y++) {
			if (AnalysisTable[x][y] == -1) {
				cout.width(10);
				cout.setf(ios::left);
				cout << " ";
			}
			else {
				string output;
				string l(1,Select[AnalysisTable[x][y]].first.left);
				string r = Select[AnalysisTable[x][y]].first.right;
				string mid = "->";
				output = l + mid + r;
				cout.width(10);
				cout.setf(ios::left);
				cout << output;
			}
		}
		cout << endl;
	}
}

bool Grammer::judge() {
	if (is_LL1) {
		cout << "This grammer is LL1!" << endl;
		return true;
	}
	else {
		cout << "This grammer is not LL1!" << endl;
		return false;
	}
}
