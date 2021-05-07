#include "Macierz.hpp"
#include <cmath>

template<size_t SIZE>
MacierzRot<SIZE>::MacierzRot(const MacierzRot<SIZE> &druga)
{
    for(uint16_t i=0; i<SIZE;++i)
        tab[i] = druga[i];
}

template<size_t SIZE>
MacierzRot<SIZE>::MacierzRot(): tab{}
{
    for(uint16_t i=0;i<SIZE;++i)
        tab[i][i] = 1;
}

template<std::size_t SIZE>
MacierzRot<SIZE> &MacierzRot<SIZE>::operator=(const MacierzRot<SIZE> &drugi)
{
    if(&drugi == this)
        return (*this);
    
    for(uint16_t i = 0;i<SIZE;++i)
        tab[i] = drugi[i];
    
    return (*this);
}

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

	for (uint16_t i = 0; i < SIZE; ++i)
		for (uint16_t j = 0; j < SIZE; ++j)
			temp[i] += v[j] * tab[i][j];

	return temp;
}

template<size_t SIZE>
MacierzRot<SIZE> MacierzRot<SIZE>::operator*(const MacierzRot<SIZE>& m) const
{
	MacierzRot<SIZE> temp;
    for (uint16_t  w = 0; w < SIZE; ++w)
        temp[w][w] = 0;;
    
	for (uint16_t  i = 0; i < SIZE; ++i)
		for (uint16_t j = 0; j < SIZE; ++j)
			for (uint16_t k = 0; k < SIZE; ++k)
				temp[i][j] += tab[i][k] * m[k][j];

	return temp;
}

template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const MacierzRot<SIZE>& mac)
{
	for (uint16_t i = 0; i < SIZE; ++i)
		std::cout << mac[i] << (i == SIZE-1? " ": "\n");

	return strm;
}
