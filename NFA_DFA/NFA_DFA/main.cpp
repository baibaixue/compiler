#include"head.h"
#include"NFA.h"
#include"DFA.h"
int main() {
	/*DFAʶ��:
	test1:ab|b
	test2:(a|b)*abb
	test3:(a*|b*)* ;��DFA��������СDFA
	test4:(aa|b)*(a|bb)*
	*/
	NFA nfa;
	string filename = "test4.txt";
	nfa.initial(filename);
	nfa.output();

	string text = "aaab";
	cout << nfa.is_DFA() << endl;

	DFA dfa;
	dfa.create_dfa(nfa);
	dfa.output();
	
	dfa.minimize();
	dfa.output();

	if (dfa.judge(text)) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}

}