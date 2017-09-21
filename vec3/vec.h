#ifndef _VEC_H_

template <class TYPE>
class Vec {

public:

	TYPE vec[3];

	Vec(TYPE x, TYPE y, TYPE z) {


		vec[0] = x;
		vec[1] = y;
		vec[2] = z;

	}

	Vec() {
		reset();
	}

	~Vec() {}

	Vec operator=(const Vec &vecaux){

		Vec aux;

		for (TYPE i = 0; i < 3; i++)
		{
			aux.vec[i] = vecaux.vec[i];
		};

		return aux;

	}

	Vec operator + (const Vec &vecaux) const{
		//Vec aux;

		//for (TYPE i = 0; i < 3; i++)
		//{
		//	aux.vec[i]=vec[i] + vecaux.vec[i];
		//}
		Vec aux(vec[0] + vecaux.vec[0], vec[1] + vecaux.vec[1], vec[2] + vecaux.vec[2]);
		return aux;
	}

	Vec operator -(const Vec &vecaux)const {
		Vec aux;

		for (TYPE i = 0; i < 3; i++)
		{
			aux.vec[i] = vec[i] - vecaux.vec[i];
		}
		return aux;

	}

	void operator+=(const Vec &aux) {
		for (TYPE i = 0; i < 3; i++)
		{
			vec[i] += aux.vec[i];
		}
	}

	void operator-=(const Vec &aux) {
		for (TYPE i = 0; i < 3; i++)
		{
			vec[i] -= aux.vec[i];
		}
	}

	void operator * (TYPE scalar) {
		for (TYPE i = 0; i < 3; i++)
		{
			vec[i] *= scalar;
		}
	}

	void reset() {
		for (TYPE i = 0; i < 3; i++)
		{
			vec[i] = 0;
		}
	}

	void print() {
		for (TYPE i = 0; i < 3; i++)
		{
			cout << vec[i] << endl;
		}
	}

};

#endif // !_VEC_H_
