#include "UI.h"
#include <iostream>

using std::cout;
using std::endl;

void test_all() {
	teste_domain();
	cout << "Au trecut toate testele din domain." << endl;
	teste_repo();
	cout << "Au trecut toate testele din repo." << endl;
	teste_srv();
	cout << "Au trecut toate testele din service." << endl;
}

void start() {

	ActivitateRepository repo;
	ActivitateValidator val;
	ActivitateStore srv{ repo, val };
	Console ui{ srv };

	ui.run();
}

int main() {
	test_all();
	start();
}