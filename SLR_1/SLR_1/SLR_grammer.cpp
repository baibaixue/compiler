#include"SLR_grammer.h"

SLR_Grammer::SLR_Grammer() {
	Vt.clear();
	Vn.clear();
	S = '\0';
	production.clear();
	projects.clear();
	First->clear();
	Follow->clear();
	I.clear();
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			Action[i][j] = make_pair('\0', -1);
			Goto[i][j] = -1;
		}
	}
	is_SLR = true;

}

void SLR_Grammer::initial(string filename) {
	ifstream txtfile;
	txtfile.open(filename);
	assert(txtfile.is_open());

	string line;
	int linecnt = 0;
	while (getline(txtfile, line)) {
		linecnt++;
		if (linecnt == 1) {	//终结符号集
			string vn;
			for (unsigned int i = 0; i < line.length(); i++) {
				if (line[i] != ' ') {
					Vt.push_back(char(line[i]));
				}
			}
		}
		else if (linecnt == 2) {
			Vn.push_back('#');	//拓展文法处理
			S = '#';	//开始符号设为#
			char l;
			string r;
			bool is_left = true;
			for (unsigned int i = 0; i < line.length(); i++) {
				if (is_left) {
					if (i + 1 < line.length() && line[i] == '-' && line[i + 1] == '>') {
						i++;
						is_left = false;
					}
					else {
						l = line[i];
						production.push_back(Production(S,string(1, l)));
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
				if (find(Vn.begin(), Vn.end(), l) == Vn.end()) {	//l未在终结符号集中，将符号加入非终结符号集
					Vn.push_back(l);
				}
			}
		}
		else {
			char l;
			string r;
			bool is_left = true;
			for (unsigned int i = 0; i < line.length(); i++) {
				if (is_left) {
					if (i + 1 < line.length() && line[i] == '-' && line[i + 1] == '>') {
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
	create_projects();	//构建LR0项目集
	get_DFA();	//构建DFA
	get_analysis_table();	//构造分析表

}

void SLR_Grammer::output_grammer() {
	cout << "开始符号:" << S << endl;

	vector<char>::iterator itvn;
	vector<char>::iterator itvt;
	vector<Production>::iterator itpro;

	cout << "非终结符号:";
	for (itvn = Vn.begin(); itvn != Vn.end() - 1; itvn++) {
		cout << *itvn << " ,";
	}
	cout << *itvn << endl;

	cout << "终结符号:";
	for (itvt = Vt.begin(); itvt != Vt.end() - 1; itvt++) {
		cout << *itvt << " ,";
	}
	cout << *itvt << endl;

	cout << "产生式:" << endl;
	for (itpro = production.begin(); itpro != production.end(); itpro++) {
		cout << (*itpro).left << "::" << (*itpro).right << endl;
	}
}

void SLR_Grammer::create_projects() {
	for (unsigned int i = 0; i < production.size(); i++) {
		for (unsigned int j = 0; j <= production[i].right.size(); j++) {
			projects.push_back(Project(production[i], j));
		}
	}
}

void SLR_Grammer::output_projects() {
	cout << "输出项目集：" << endl;
	for (unsigned int i = 0; i < projects.size(); i++) {
		projects[i].output();
	}
}

int SLR_Grammer::get_i_index(set<int> i) {
	vector<set<int>>::iterator index = find(I.begin(), I.end(), i);
	if (index == I.end()) {
		return -1;
	}
	else {
		return index - I.begin();
	}
}

unsigned int SLR_Grammer::get_prod_index(Production p) {
	for (unsigned int i = 0; i < production.size(); i++) {
		if (p.is_equal(production[i])) {
			return i;
		}
	}
	return production.size();
}

unsigned int SLR_Grammer::get_prod_index(Project p)
{
	return get_prod_index(p.prod);
}

unsigned int SLR_Grammer::get_prod_index(int p)
{
	return get_prod_index(projects[p]);
}

int SLR_Grammer::get_proj_index(Project p)
{
	for (unsigned int i = 0; i < projects.size(); i++) {
		if (p.equal(projects[i])) {
			return i;
		}
	}
	return -1;
}

set<int> SLR_Grammer::get_closure(set<int> i)
{
	set<int> res;
	queue<int> que;
	for (set<int>::iterator it = i.begin(); it != i.end(); it++) {
		res.insert(*it);
		que.push(*it);
	}
	while (!que.empty()) {
		int x = que.front();
		que.pop();
		if (projects[x].To_Be_Reduction(Vn)) {
			char l = projects[x].prod.right[projects[x].index];
			for (unsigned int y = 0; y < projects.size(); y++) {
				if (l == projects[y].prod.left && projects[y].is_first()) {
					int num = get_proj_index(projects[y]);
					if (find(res.begin(), res.end(), num) == res.end()) {
						res.insert(num);
						que.push(num);
					}
				}
			}
		}
	}
	return set<int>(res);
}

set<int> SLR_Grammer::get_closure(Project p) {
	set<int> res;
	queue<int> que;
	int i = get_proj_index(p);
	if (i != -1) {
		res.insert(i);
		que.push(i);
	}
	while (!que.empty()) {
		i = que.front();
		que.pop();
		if (projects[i].To_Be_Reduction(Vn)) {
			char l = projects[i].prod.right[projects[i].index];
			for (unsigned int i = 0; i < projects.size(); i++) {
				if (l == projects[i].prod.left && projects[i].is_first()) {
					int num = get_proj_index(projects[i]);
					if (find(res.begin(), res.end(), num) == res.end()) {
						res.insert(num);
						que.push(num);
					}
				}
			}
		}
	}
	return set<int>(res);
}

set<int> SLR_Grammer::go(Project p, char c)
{
	set<int> res;
	if (!p.is_Reduction() && p.prod.right[p.index] == c) {
		for (unsigned int i = 0; i < projects.size(); i++) {
			if (p.prod.is_equal(projects[i].prod)) {
				if (!(projects[i].is_first()) && projects[i].prod.right[projects[i].index - 1] == c) {
					int num = get_proj_index(projects[i]);
					if (find(res.begin(), res.end(), num) == res.end()) {
						res.insert(num);
					}
				}
			}
		}
	}
	return get_closure(res);
}

set<int> SLR_Grammer::go(set<int> p, char c)
{
	set<int> res;
	for (set<int>::iterator it = p.begin(); it != p.end(); it++) {
		Project P(projects[*it]);
		if (!(P.is_Reduction()) && P.prod.right[P.index] == c) {
			for (unsigned int i = 0; i < projects.size(); i++) {
				if (P.prod.is_equal(projects[i].prod)) {
					if (!projects[i].is_first() && projects[i].prod.right[projects[i].index - 1] == c) {
						int num = get_proj_index(projects[i]);
						if (find(res.begin(), res.end(), num) == res.end()) {
							res.insert(num);
						}
					}
				}
			}
		}
	}
	return get_closure(res);
}

bool SLR_Grammer::is_start(set<int> i)
{
	for (set<int>::iterator it = i.begin(); it != i.end(); it++) {
		if (projects[*it].is_Start(S)) {
			return true;
		}
	}
	return false;
}

bool SLR_Grammer::is_acc(set<int> i)
{
	for (set<int>::iterator it = i.begin(); it != i.end(); it++) {
		if (projects[*it].is_Acc(S)) {
			return true;
		}
	}
	return false;
}

bool SLR_Grammer::is_MoveIn(set<int> i)
{
	for (set<int>::iterator it = i.begin(); it != i.end(); it++) {
		if (projects[*it].is_MoveIn(Vt)||projects[*it].To_Be_Reduction(Vn)) {
			return true;
		}
	}
	return false;
}

bool SLR_Grammer::is_Reduction(set<int> i)
{
	for (set<int>::iterator it = i.begin(); it != i.end(); it++) {
		if (projects[*it].is_Reduction()) {
			return true;
		}
	}
	return false;
}
/*
bool SLR_Grammer::has_intersection(char a, char b)
{
	set<char> c;
	set_intersection(Follow[get_vn_index(a)].begin(), Follow[get_vn_index(a)].end(), Follow[get_vn_index(b)].begin(), Follow[get_vn_index(b)].end(), back_inserter(c));
	if (!c.empty()) {
		return true;
	}
	return false;
}
*/

void SLR_Grammer::get_DFA()
{
	I.push_back(get_closure(projects[0]));
	
	for (unsigned int i = 0; i < I.size(); i++) {
		for (unsigned int t = 0; t < Vt.size(); t++) {
			set<int> res;
			if (Vt[t] != '@') {
				res = go(I[i], Vt[t]);
				if (!res.empty()) {
					int num = get_i_index(res);
					if (num == -1) {
						I.push_back(set<int>(res));
					}
					num = get_i_index(res);
					DFA[i][num].push_back( Vt[t]);
				}
			}
		}
		for (unsigned int n = 0; n < Vn.size(); n++) {
			set<int> res;
			if (Vn[n] != '#') {
				res = go(I[i], Vn[n]);
				if (!res.empty()) {
					int num = get_i_index(res);
					if (num == -1) {
						I.push_back(set<int>(res));
					}
					num = get_i_index(res);
					DFA[i][num].push_back(Vn[n]);
				}
			}
		}
	}
}

void SLR_Grammer::output_DFA()
{
	cout << "输出DFA:" << endl;
	for (unsigned int i = 0; i < I.size(); i++) {
		for (unsigned int j = 0; j < I.size(); j++) {
			if (!DFA[i][j].empty()) {
				for (unsigned int x = 0; x < DFA[i][j].size(); x++) {
					cout << i << '-' << DFA[i][j][x] << "->" << j << endl;
				}
			}
		}
	}
}

void SLR_Grammer::get_analysis_table()
{
	get_allfirst();
	get_allfollow();
	for (unsigned int i = 0; i < I.size(); i++) {
		if (is_acc(I[i])) {	//如果是接收项目，ACTION置acc
			Action[i][Vt.size()-1].first = 'a';
		}
		if (is_Reduction(I[i])) {	//是归约项目
			for (set<int>::iterator p = I[i].begin(); p != I[i].end(); p++) {	//遍历项目集中所有项目
				if (projects[*p].is_Reduction()) {	//找到归约项目
					char l = projects[*p].prod.left;
					for (set<char>::iterator it = Follow[get_vn_index(l)].begin(); it != Follow[get_vn_index(l)].end(); it++) {
						unsigned int num = get_prod_index(*p);
						if (Action[i][get_vt_index(*it)].first == '\0') {	//归约
							Action[i][get_vt_index(*it)].first = 'r';
							Action[i][get_vt_index(*it)].second = num;
						}
						else {
							if (Action[i][get_vt_index(*it)].first != 'r' || Action[i][get_vt_index(*it)].second != num) {	//冲突处理
								if (!((*it) == '$' && Action[i][get_vt_index(*it)].first == 'a')) {
									is_SLR = false;
									return;
								}
								
							}
						}
					}
				}
				
			}
		}
		if(is_MoveIn(I[i])) {	//移进项目
			for (unsigned int j = 0; j < I.size(); j++) {
				if (!DFA[i][j].empty()) {
					for (unsigned int k = 0; k < DFA[i][j].size(); k++) {
						char c = DFA[i][j][k];
						if (is_vt(c)) {	//移进
							if (Action[i][get_vt_index(c)].first == '\0') {
								Action[i][get_vt_index(c)].first = 's';
								Action[i][get_vt_index(c)].second = j;
							}
							else if (Action[i][get_vt_index(c)].first != 's' || Action[i][get_vt_index(c)].second != j) {
								is_SLR = false;
								return;
							}
						}
						else if (is_vn(c)){
							if(Goto[i][get_vn_index(c)] == -1){
								Goto[i][get_vn_index(c)] = j;
							}
							else if (Goto[i][get_vn_index(c)] != -1) {
								is_SLR = false;
								return;
							}
						}
						
					}
				}
			}
		}
	}
}

void SLR_Grammer::output_analysis_table() {
	if (!judge()) {
		return;
	}
	cout << "分析表：" << endl;
	cout.width(10);
	cout.setf(ios::left);
	cout << " ";
	for (unsigned int i = 0; i < Vt.size(); i++) {
		cout.width(10);
		cout.setf(ios::left);
		cout << Vt[i];
	}
	for (unsigned int i = 1; i < Vn.size(); i++) {
		cout.width(10);
		cout.setf(ios::left);
		cout << Vn[i];
	}
	cout << endl;
	for (unsigned int i = 0; i < I.size(); i++) {
		cout.width(10);
		cout.setf(ios::left);
		cout << i;
		for (unsigned int t = 0; t < Vt.size(); t++) {
			if (Action[i][t].first == 's' || Action[i][t].first == 'r') {
				string a(1, Action[i][t].first);
				string b;
				b = to_string(Action[i][t].second);
				string res = a + b;
				cout.width(10);
				cout.setf(ios::left);
				cout << res ;
			}
			else if (Action[i][t].first == 'a') {
				cout.width(10);
				cout.setf(ios::left);
				cout << "acc";
			}
			else {
				cout.width(10);
				cout.setf(ios::left);
				cout << " ";
			}
		}
		for (unsigned int n = 1; n < Vn.size(); n++) {
			if (Goto[i][n] != -1) {
				cout.width(10);
				cout.setf(ios::left);
				cout << Goto[i][n];
			}
			else {
				cout.width(10);
				cout.setf(ios::left);
				cout << " ";
			}
		}
		cout << endl;
	}
}

bool SLR_Grammer::judge()
{
	if (is_SLR) {
		return true;
	}
	else {
		cout << "This grammer is not SLR(1) Grammer!" << endl;
		return false;
	}
	
}

unsigned int SLR_Grammer::get_vn_index(char c) {
	vector<char>::iterator it;
	it = find(Vn.begin(), Vn.end(), c);
	return it - Vn.begin();
}

unsigned int SLR_Grammer::get_vt_index(char c) {
	vector<char>::iterator it;
	it = find(Vt.begin(), Vt.end(), c);
	return it - Vt.begin();
}

bool SLR_Grammer::is_vn(char c) {
	if (find(Vn.begin(), Vn.end(), c) == Vn.end()) {
		return false;
	}
	else {
		return true;
	}
}

bool SLR_Grammer::is_vt(char c) {
	if (find(Vt.begin(), Vt.end(), c) == Vt.end()) {
		return false;
	}
	else {
		return true;
	}
}
/*
void Grammer::Inditect_left_recursion() {
	char l_list[MAXN] = { 0 };	//记录发生代入的表达式左部
	string r_list[MAXN];	//记录发生代入的表达式右部
	int cnt = 0;
	for (unsigned int i = 0; i < production.size(); i++) {
		char il = production[i].left;
		string ir = production[i].right;
		for (unsigned int j = i + 1; j < production.size(); j++) {
			char jl = production[j].left;
			string jr = production[j].right;
			if (jr[0] == il && il != jl) {
				string new_r = ir + jr.substr(1);
				production.insert(production.begin() + j + 1, Production(jl, new_r));
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
	char new_left[MAXN] = { 0 };	//新产生的非终结符
	int cnt = 0;
	bool is_leftrec[MAXN] = { 0 };	//非终结符是否左递归
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
		for (unsigned int j = i + 1; j < production.size(); j++) {
			char jl = production[j].left;
			string jr = production[j].right;

			if (il == jl && ir[0] == jr[0] && (!production[i].is_equal(production[j]))) {	//两个表达式有左因子且不相等，A->Ba,A->Bc
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
*/
void SLR_Grammer::get_first(char c) {
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
						//get_first(right[j]);
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

void SLR_Grammer::get_allfirst() {
	for (unsigned int i = 0; i < Vn.size(); i++) {
		if (First[i].empty()) {
			get_first(Vn[i]);
		}
	}
}

void SLR_Grammer::output_first() {
	for (unsigned int i = 0; i < Vn.size(); i++) {
		cout << Vn[i] << ":{";
		set<char>::iterator it;
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

void SLR_Grammer::get_follow(char c) {
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
				else if (is_vn(next)) {	//下一个符号是非终结符号
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
						for (set<char>::iterator it = Follow[get_vn_index(il)].begin(); it != Follow[get_vn_index(il)].end(); it++) {
							Follow[index].insert(*it);
						}
					}
				}
			}
			else if (c == ir[x] && x == ir.size() - 1 && c != il) {
				//get_follow(il);
				for (set<char>::iterator it = Follow[get_vn_index(il)].begin(); it != Follow[get_vn_index(il)].end(); it++) {
					Follow[index].insert(*it);
				}
			}
		}
	}
}

void SLR_Grammer::get_allfollow() {
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

void SLR_Grammer::output_follow() {
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
