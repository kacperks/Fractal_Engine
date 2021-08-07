#pragma once

template<typename T, unsigned int D>
class Vector
{
public:
	inline T Dot(const Vector<T, D>& r) const {
		T res = T(0);
		for (unsigned int i = 0; i < D; i++)
			res += (*this)[i] * r[i];
		return res;
	}
	inline Vector<T, D> Lerp(const Vector<T, D>& r, T lerpFactor) const { return (r - *this) * lerpFactor + *this; }
};