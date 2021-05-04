#include "Prostopadloscian.hpp"
#include <fstream>
#include <iomanip>
//
//std::ostream& operator<<(std::ostream& strm, const Prostokat& pr)
//{
//	for (int i = 0; i < 4; ++i)
//		strm << pr[i] << std::endl;
//
//	return strm;
//}
//
//std::istream& operator>>(std::istream& strm, Prostokat& pr)
//{
//	for (int i = 0; i < 4; ++i)
//		strm >> pr[i];
//
//	return strm;
//}
//
//Prostokat::Prostokat(std::string name)
//{
//	std::ifstream plik(name);
//	plik >> (*this);
//	plik.close();
//}
//
//const Wektor2D& Prostokat::operator[](unsigned int n) const
//{
//	if (n < 0 || n > 3)
//		throw std::out_of_range{ "Wektor2D out of range!" };
//	return wierzcholki[n];
//}
//
//Wektor2D& Prostokat::operator[](unsigned int n)
//{
//	if (n < 0 || n > 3)
//		throw std::out_of_range{ "Wektor2D out of range!" };
//	return wierzcholki[n];
//}
//
//void Prostokat::Rotacja(double alpha)
//{
//	Macierz2x2 mRotacji(alpha);
//	for (int i = 0; i < 4; ++i)
//		wierzcholki[i] = mRotacji * wierzcholki[i];
//
//}
//
//void Prostokat::Translacja(Wektor2D wektor)
//{
//	for (int i = 0; i < 4; ++i)
//		wierzcholki[i] = wierzcholki[i] + wektor;
//}
//
//bool Prostokat::CzyProstokat()
//{
//	//3   2
//	// 
//	//0   1
//
//	double epsilon = 0.00000000001;
//	double bok1 = (wierzcholki[0] - wierzcholki[1]).Length(),
//		bok2 = (wierzcholki[0] - wierzcholki[3]).Length(),
//		bok3 = (wierzcholki[2] - wierzcholki[3]).Length(),
//		bok4 = (wierzcholki[1] - wierzcholki[2]).Length();
//
//	if (fabs(bok1 - bok3) > epsilon)
//		std::cout << "Pierwsza para bokow nie jest sobie rowna!!!" << std::endl;
//	else
//		std::cout << "Pierwsza para bokow jest identyczna." << std::endl;
//
//	std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << bok1 << std::endl;
//	std::cout << "\tDlugosc drugiego boku:   " << std::fixed << std::setprecision(10) << bok3 << std::endl << std::endl;
//
//	if (fabs(bok2 - bok4) > epsilon)
//		std::cout << "Druga para bokow nie jest sobie rowna!!!" << std::endl;
//	else
//		std::cout << "Druga para bokow jest identyczna." << std::endl;
//
//	std::cout << "\tDlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << bok2 << std::endl;
//	std::cout << "\tDlugosc drugiego boku:   " << std::fixed << std::setprecision(10) << bok4 << std::endl << std::endl;
//
//	return true;
//}
//
//Prostokat::~Prostokat()
//{
//	system("rm temp.dat");
//}

