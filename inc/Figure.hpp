#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include <iostream>
#include <Macierz3x3.hpp>
#include <Wektor3D.hpp>

class Figure
{
	std::array<Wektor3D, 8> wierzcholki;

public:
    Figure(std::string name);
    Figure() : wierzcholki({}) { ; }

	const Wektor3D& operator[](unsigned int n) const;
    Wektor3D& operator[](unsigned int n);

	void Rotation(MacierzRot3x3 mRotacji);
	void Translation(Wektor<3> wektor);
	bool IsCuboid();
};

std::ostream& operator << (std::ostream& strm, const Figure& pr);
std::istream& operator >> (std::istream& strm, Figure& pr);

#endif
