#include <iostream>

using namespace std;

#include "vec.h"

int main() {

	Vec <int>  myvec(3, 5, 8);
	Vec <int> myvec2(4, 6, 9);
	
	Vec<int> res=myvec = myvec2=myvec;
	res.print();


	//Vec <int> result=myvec + myvec2;
	//result.print();

	//Vec <int> result = myvec - myvec2;
	//result.print();

	//myvec += myvec2;
	//myvec.print();

	//myvec -= myvec2;
	//myvec.print();

	//myvec * 9;
	//myvec.print();

	//myvec.reset();
	//myvec.print();


	system("pause");
	return 0;

}