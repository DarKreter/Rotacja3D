#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include <iostream>
#include <Macierz.hpp>

class Prostokat {
	std::array<Wektor<3>, 8> wierzcholki;

public:
	/*Prostokat(std::string name);
	Prostokat(std::array<Wektor2D, 4> temp) : wierzcholki{ temp } { ; }
	Prostokat() : Prostokat({ Wektor2D(), Wektor2D(), Wektor2D(), Wektor2D() }) { ; }
	~Prostokat();

	const Wektor2D& operator[](unsigned int n) const;
	Wektor2D& operator[](unsigned int n);

	void Rotacja(double alpha);
	void Translacja(Wektor2D wektor);
	bool CzyProstokat();*/
};

//std::ostream& operator << (std::ostream& strm, const Prostokat& pr);
//std::istream& operator >> (std::istream& strm, Prostokat& pr);

#endif
