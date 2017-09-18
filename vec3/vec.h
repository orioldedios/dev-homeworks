#ifndef _VEC_H_

#define uint unsigned int

class Vec {

public:

	uint vec[3];

	Vec(uint x, uint y, uint z) {


		vec[0] = x;
		vec[1] = y;
		vec[2] = z;

	}

	Vec() {
		reset();
	}

	~Vec() {}

	Vec operator + (const Vec &vecaux) const{
		Vec vecaux1;
		for (uint i = 0; i < 3; i++)
		{
			vecaux1.vec[i]=vec[i] + vecaux[i];
		}
		return vecaux1;
	}

	Vec operator -(const Vec &vecaux)const {
		Vec vecaux1;
		for (uint i = 0; i < 3; i++)
		{
			vec[i] -= vecaux[i];
		}
		return vecaux1;

	}

	uint operator+=(uint inc) {
		for (uint i = 0; i < 3; i++)
		{
			vec[i] += inc;
		}
	}

	uint operator-=(uint dec) {
		for (uint i = 0; i < 3; i++)
		{
			vec[i] -= dec;
		}
	}

	uint operator * (uint scalar) {
		for (uint i = 0; i < 3; i++)
		{
			vec[i] = vec[i] * scalar;
		}
	}

	void reset() {
		for (uint i = 0; i < 3; i++)
		{
			vec[i] = 0;
		}
	}

	void print() {
		for (uint i = 0; i < 3; i++)
		{
			cout << vec[i] << endl;
		}
	}

};

#endif // !_VEC_H_
