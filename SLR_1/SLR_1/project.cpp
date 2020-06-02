#include"SLR_grammer.h"

void Project::output() {
	cout << prod.left << "->";
	for (unsigned int i = 0; i <= prod.right.size(); i++) {
		if (i == index) {
			cout << "¡¤";
		}
		cout << prod.right[i];
	}
	cout << endl;
}

bool Project::is_Acc(char s) {
	if (prod.left == s && index == prod.right.size()) {
		return true;
	}
	else {
		return false;
	}
}
bool Project::is_Start(char s) {
	if (prod.left == s && index == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Project::is_MoveIn(vector<char> vt){
	if (unsigned int(index) < prod.right.size()) {
		if (find(vt.begin(), vt.end(), prod.right[index]) != vt.end()) {
			return true;
		}
	}
	return false;
}

bool Project::To_Be_Reduction(vector<char> vn) {
	if (unsigned int(index) < prod.right.size()) {
		if (find(vn.begin(), vn.end(), prod.right[index]) != vn.end()) {
			return true;
		}
	}
	return false;
}

bool Project::is_Reduction() {
	if (unsigned int(index) == prod.right.size()) {
		return true;
	}
	else {
		return false;
	}
}

bool Project::is_first()
{
	if (index == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Project::equal(Project p) {
	if (prod.is_equal(p.prod) && index == p.index) {
		return true;
	}
	else {
		return false;
	}
}