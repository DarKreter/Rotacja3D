#include "Figure.hpp"
#include <fstream>
#include <iomanip>

Figure::Figure(std::string name)
{
	std::ifstream plik(name);
	plik >> (*this);
	plik.close();
}

const Wektor3D& Figure::operator[](unsigned int n) const
{
	if (n < 0 || n > 7)
		throw std::out_of_range{ "Figure out of range!" };
	
	return wierzcholki[n];
}

Wektor3D& Figure::operator[](unsigned int n)
{
	if (n < 0 || n > 7)
		throw std::out_of_range{ "Figure out of range!" };
	
	return wierzcholki[n];
}

void Figure::Rotation(MacierzRot3x3 mRotacji)
{
	for (int i = 0; i < 8; ++i)
		wierzcholki[i] = mRotacji * wierzcholki[i];

}

void Figure::Translation(Wektor3D wektor)
{
	for (int i = 0; i < 8; ++i)
		wierzcholki[i] = wierzcholki[i] + wektor;
}

bool Figure::IsCuboid()
{

	double epsilon = 0.00000000001;
	double  bok1[4], bok2[4], bok3[4];
	
	for(int i=0;i<4;++i)
	    bok1[i] = (wierzcholki[2*i] - wierzcholki[2*i+1]).Length();
    
    for(int i=0;i<2;++i)
        bok2[i] = (wierzcholki[i] - wierzcholki[i+2]).Length();
    
    for(int i=2;i<4;++i)
        bok2[i] = (wierzcholki[i+2] - wierzcholki[i+4]).Length();
    
    for(int i=0;i<2;++i)
        bok3[i] = (wierzcholki[i] - wierzcholki[i+6]).Length();
    
    for(int i=2;i<4;++i)
        bok3[i] = (wierzcholki[i] - wierzcholki[i+2]).Length();


    for(int i=0;i<3;++i)
        if( std::abs(bok1[i] - bok1[3]) > epsilon )
        {
            std::cout << "Pierwsze cztery boki nie sa sobie rowne!!!" << std::endl;
            goto jeden;
        }
    std::cout << "Pierwsze cztery boki sa identyczne." << std::endl;
    jeden:
    for(int i=0;i<4;++i)
	    std::cout << "\tDlugosc " << i << " boku: "      << std::fixed << std::setprecision(10) << bok1[i] << std::endl;
    std::cout << std::endl;
    
    
    for(int i=0;i<3;++i)
        if( std::abs(bok2[i] - bok2[3]) > epsilon )
        {
            std::cout << "Srodkowe cztery boki nie sa sobie rowne!!!" << std::endl;
            goto dwa;
        }
    std::cout << "Srodkowe cztery boki sa identyczne." << std::endl;
    dwa:
    for(int i=0;i<4;++i)
        std::cout << "\tDlugosc " << i << " boku: "      << std::fixed << std::setprecision(10) << bok2[i] << std::endl;
    std::cout << std::endl;
    
    
    for(int i=0;i<3;++i)
        if( std::abs(bok3[i] - bok3[3]) > epsilon )
        {
            std::cout << "Ostatnie cztery boki nie sa sobie rowne!!!" << std::endl;
            goto trzy;
        }
    std::cout << "Ostatnie cztery boki sa identyczne." << std::endl;
    trzy:
    for(int i=0;i<4;++i)
        std::cout << "\tDlugosc " << i << " boku: "      << std::fixed << std::setprecision(10) << bok3[i] << std::endl;
    std::cout << std::endl;
    
	return true;
}

Figure::~Figure()
{
	system("rm -f temp.dat");
}

std::ostream& operator<<(std::ostream& strm, const Figure& pr)
{
    for (int i = 0; i < 8; ++i)
        strm << pr[i] << (i==7?"":"\n") << (i%2==1?"\n":"");
    
    return strm;
}

std::istream& operator>>(std::istream& strm, Figure& pr)
{
    for (int i = 0; i < 8; ++i)
        strm >> pr[i];
    
    return strm;
}

