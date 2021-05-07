#ifndef WEKTOR_H
#define WEKTOR_H

#include <iostream>
#include <array>
#include <iomanip>
#include <string>

template<std::size_t SIZE>
class Wektor
{
	std::array<double, SIZE> tab;
	
public:
	Wektor(): tab{}										    {;}
	Wektor(std::array<double, SIZE> pkt) : tab{ pkt }		{;}
	Wektor(const Wektor<SIZE>& temp) : tab{ temp.tab }		{;}

	const double& operator[](unsigned int n) const;
	double& operator[](unsigned int n);

	Wektor<SIZE> operator+(const Wektor<SIZE>&) const;
	Wektor<SIZE> operator-(const Wektor<SIZE>&) const;
	Wektor<SIZE> operator*(double) const;
    
    Wektor<SIZE>& operator=(const Wektor<SIZE>& drugi);
	
	double Length();

};

template <size_t SIZE>
std::istream& operator >> (std::istream&, Wektor<SIZE>&);

template <size_t SIZE>
std::ostream& operator << (std::ostream&, const Wektor<SIZE>&);

#include "Wektor.tpp"

#endif
