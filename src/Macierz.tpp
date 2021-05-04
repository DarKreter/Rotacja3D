#include "Macierz.hpp"
#define _USE_MATH_DEFINES //Maybe delete
#include <math.h>


template<size_t SIZE>
const Wektor<SIZE>& MacierzRot<SIZE>::operator[](unsigned int n) const
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "MacierzRot<" + std::to_string(SIZE) + "> out of range!" };

	return tab[n];
}

template<size_t SIZE>
Wektor<SIZE>& MacierzRot<SIZE>::operator[](unsigned int n)
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "MacierzRot<" + std::to_string(SIZE) + "> out of range!" };

	return tab[n];
}

template<size_t SIZE>
Wektor<SIZE> MacierzRot<SIZE>::operator*(const Wektor<SIZE>& v) const
{
	Wektor<SIZE> temp;

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			temp[i] += v[j] * tab[i][j];

	return temp;
}

template<size_t SIZE>
MacierzRot<SIZE> MacierzRot<SIZE>::operator*(const MacierzRot<SIZE>& m) const
{
	MacierzRot<SIZE> temp;

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			for (int k = 0; k < SIZE; ++k)
				temp[i][j] += tab[i][k] * m[k][j];

	return temp;
}

template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const MacierzRot<SIZE>& mac)
{
	for (int i = 0; i < SIZE; ++i)
		std::cout << mac[i] << (i == SIZE-1? " ": "\n");

	return strm;
}
