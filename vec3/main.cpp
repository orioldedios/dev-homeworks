#include <iostream>

using namespace std;

#include "vec.h"

int main() {

	uint inc = 1;
	uint dec = 1;
	uint mul = 2;

	Vec  myvec(1, 2, 3);
	Vec  myvec2(10, 9, 8);


	myvec.operator+(myvec2);
	myvec.print();
	myvec.reset();

	myvec.operator-(myvec2);
	myvec.print();
	myvec.reset();

	myvec.operator+=(inc);
	myvec.print();
	myvec.reset();

	myvec.operator-=(dec);
	myvec.print();
	myvec.reset();

	myvec.operator*(mul);
	myvec.print();
	myvec.reset();

	myvec.print();

	system("pause");
	return 0;

}