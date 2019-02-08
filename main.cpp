#include <iostream>
#include "Random_vector.h"
#include "limit_def.h"
#include "limit_func.h"
#include "limit_func2.h"
#include <vector>
#include <string>
#include <sstream>


using namespace std;


void generate_idz1() {
	Limit_def l(string{"/home/artem/math/idz1/task6"}, 30);
	l.generate(6);
}

void generate_idz2() {
	Limit_func l(string{"/home/artem/math/idz2"},30);
	l.generate();
}

void generate_idz3() {
	Limit_func2 l(string{"/home/artem/math/idz3"},30);
	l.generate();
}

int main() {
	generate_idz3();
}
