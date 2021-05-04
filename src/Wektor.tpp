#include "Wektor.hpp"
#include <cassert>


template<size_t SIZE>
const double& Wektor<SIZE>::operator[](unsigned int n) const
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{"Wektor<" + std::to_string(SIZE) + "> out of range!"};
	return tab[n];
}

template<size_t SIZE>
double& Wektor<SIZE>::operator[](unsigned int n)
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "Wektor<" + std::to_string(SIZE) + "> out of range!" };
	return tab[n];
}

template<size_t SIZE>
Wektor<SIZE> Wektor<SIZE>::operator+(const Wektor<SIZE>& second) const
{
	Wektor<SIZE> temp(*this);
	for (int i = 0; i < SIZE; ++i)
		temp[i] += second[i];

	return temp;
}

template<size_t SIZE>
Wektor<SIZE> Wektor<SIZE>::operator-(const Wektor<SIZE>& second) const
{
	Wektor<SIZE> temp(*this);
	for (int i = 0; i < SIZE; ++i)
		temp[i] -= second[i];

	return temp;
}

template<size_t SIZE>
Wektor<SIZE> Wektor<SIZE>::operator*(double st) const
{
	Wektor<SIZE> temp(*this);
	for (int i = 0; i < SIZE; ++i)
		temp[i] *= st;

	return temp;
}

template<size_t SIZE>
double Wektor<SIZE>::Length()
{
	double sum = 0;
	for (int i = 0; i < SIZE; ++i)
		sum += pow(tab[i], 2);

	return sqrt(sum);
}

template<size_t SIZE>
std::istream& operator >> (std::istream& strm, Wektor<SIZE>& wek)
{
	double x;
	for (int i = 0; i < SIZE; ++i)
	{
		strm >> x;
		if (!strm.good())
		{
			strm.clear();
			strm.ignore(std::numeric_limits<int>::max(), '\n');
			throw std::runtime_error("Nie udalo sie wczytac Wektora<" + std::to_string(SIZE) + ">!");
		}
		wek[i] = x;
	}

	return strm;
}


template <size_t SIZE>
std::ostream& operator << (std::ostream& strm, const Wektor<SIZE>& wek)
{
	for (int i = 0; i < SIZE; ++i)
		strm << std::setw(12) << std::fixed << std::setprecision(8) << wek[i] << (i == SIZE - 1 ? " " : "");

	return strm;
}
