#include "Figure.hpp"
#include <fstream>
#include <iomanip>

/**
 * Inicjalizuje wszystkie wierzchołki na podstawie danych z pliku.
 *
 * @param name - nazwa pliku który zostanie otworzony i zostaną z niego
 * wczytane wszystkie wierzchołki
 */
Figure::Figure(std::string name)
{
	std::ifstream plik(name);
	plik >> (*this);
	plik.close();
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych wierzchołków prostopadłościanu.
 * Umożliwa on dostęp do wierzchołków, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;7] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks wierzchołka do którego chcemy uzyskać dostęp
 * @return zwraca odpowiedni niemodyfikowalny wierzchołek prostopadłościanu
 */
const Wektor3D& Figure::operator[](unsigned int n) const
{
	if (n < 0 || n > 7)
		throw std::out_of_range{ "Figure out of range!" };
	
	return wierzcholki[n];
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych wierzchołków prostopadłościanu.
 * Umożliwa on modifikację wierzchołków.
 * Gdy indeks jest spoza zakresu [0;7] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks wierzchołka do którego chcemy uzyskać dostęp
 * @return zwraca referencję do wierzchołka prostopadłościanu który chcemy zmodyfikować
 */
Wektor3D& Figure::operator[](unsigned int n)
{
	if (n < 0 || n > 7)
		throw std::out_of_range{ "Figure out of range!" };
	
	return wierzcholki[n];
}

/**
 * Rotacja jest wykonywana na podstawie macierzy rotacji.
 * Na kolejnych wierzchołkach jest wykonywana operacja mnożenia przez macierz rotacji.
 *
 * @param mRotacji - wyspecjalizowana macierz rotacji zainicjalizowana już odpowiednimi wartości.
 */
void Figure::Rotation(MacierzRot3x3 mRotacji)
{
	for (int i = 0; i < 8; ++i)
		wierzcholki[i] = mRotacji * wierzcholki[i];

}

/**
 * Realizuje translację prostopadłościanu o zadany wektor
 * Do kolejnych wierzchołków jest dodawany wektor translacyjny.
 *
 * @param wektor -  wyspecjalizowany wektor translacji, z zainicjowanymi wartościami.
 */
void Figure::Translation(Wektor3D wektor)
{
	for (int i = 0; i < 8; ++i)
		wierzcholki[i] = wierzcholki[i] + wektor;
}

/**
 * Funckja sprawdza to na podstawie porównywania długości odpowiednich boków.
 * W przypadku braku zgodności długości odpowiednich boków - zostanie wypisany komunikat o niezgodności.
 * Gdyby długości były zgodne - zostanie wypisany komunikat o zgodności
 * Funkcja także wypisze długości wszystkich boków.
 *
 */
void Figure::IsCuboid()
{
    //TODO: może warto by sprawdzać kąty kto wie jakby Ci się kiedyś chciało to zrób
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
    
}

/**
 * Wypisanie Figury na odpowiedni strumień
 *
 * @param strm - strumien na który ma zostać wypisany prostopadłościan
 * @param pr - prostopadłościan który ma zostać wypisany
 * @return zwracamy referencję do przysłanego strumienia
 */
std::ostream& operator<<(std::ostream& strm, const Figure& pr)
{
    for (int i = 0; i < 8; ++i)
        strm << pr[i] << (i==7?"":"\n") << (i%2==1?"\n":"");
    
    return strm;
}

/**
 * Wczytanie Figury z odpowiedniego strumienia
 *
 * @param strm - strumien z którego ma zostać wczytany prostopadłościan
 * @param pr - prostopadłościan który ma zostać wczytany
 * @return zwracamy referencję do przysłanego strumienia
 */
std::istream& operator>>(std::istream& strm, Figure& pr)
{
    for (int i = 0; i < 8; ++i)
        strm >> pr[i];
    
    return strm;
}

