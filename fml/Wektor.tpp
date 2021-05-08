#include "Wektor.hpp"
#include <cassert>
#include <cmath>
#include <limits>

/**
 * Możemy za jego pomocą dostać się do poszczególnych współrzędnych wektora.
 * Umożliwa on dostęp do współrzędnych, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;SIZE] zostanie rzucony wyjątek std::out_of_range
 *
 * @tparam SIZE - Określa wymiarowość w jakiej znajduje się wektor
 * @param n - indeks współrzędnej do której chcemy uzyskać dostęp
 * @return Niemodyfikowalna wartość określonej indeksem współrzędnej
 */
template<size_t SIZE>
const double& Wektor<SIZE>::operator[](unsigned int n) const
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{"Wektor<" + std::to_string(SIZE) + "> out of range!"};
	return tab[n];
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych współrzędnych wektora.
 * Umożliwa on dostęp do współrzędnych, z możliwością modyfikacji.
 * Gdy indeks jest spoza zakresu [0;SIZE] zostanie rzucony wyjątek std::out_of_range
 *
 * @tparam SIZE - Określa wymiarowość w jakiej znajduje się wektor
 * @param n - indeks współrzędnej do której chcemy uzyskać dostęp
 * @return Modyfikowalna referencjado  określonej indeksem współrzędnej
 */
template<size_t SIZE>
double& Wektor<SIZE>::operator[](unsigned int n)
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "Wektor<" + std::to_string(SIZE) + "> out of range!" };
	return tab[n];
}

/**
 * Dodaje odpowiednie składowe dwóch wektorów i zwraca wynik.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param second - Wektor który dodajemy
 * @return Zwraca wynik dodawania dwóch wektorów
 */
template<size_t SIZE>
Wektor<SIZE> Wektor<SIZE>::operator+(const Wektor<SIZE>& second) const
{
	Wektor<SIZE> temp(*this);
	for (uint16_t i = 0; i < SIZE; ++i)
		temp[i] += second[i];

	return temp;
}

/**
 * Odejmuje odpowiednie składowe dwóch wektorów i zwraca wynik.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param second - Wektor który odejmujemy
 * @return Zwraca wynik odejmowania dwóch wektorów
 */
template<size_t SIZE>
Wektor<SIZE> Wektor<SIZE>::operator-(const Wektor<SIZE>& second) const
{
	Wektor<SIZE> temp(*this);
	for (uint16_t i = 0; i < SIZE; ++i)
		temp[i] -= second[i];

	return temp;
}

/**
 * Mnoży wszystkie składowe wektora przez przysłaną stałą.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param st - stała przez którą mnożymy
 * @return Zwraca wynik przemnożenia wektora przez stałą.
 */
template<size_t SIZE>
Wektor<SIZE> Wektor<SIZE>::operator*(double st) const
{
	Wektor<SIZE> temp(*this);
	for (uint16_t i = 0; i < SIZE; ++i)
		temp[i] *= st;

	return temp;
}

/**
 *
 * @tparam SIZE - Określa wymiar wektora
 * @return Zwraca długość wektora
 */
template<size_t SIZE>
double Wektor<SIZE>::Length()
{
	double sum = 0;
	for (uint16_t i = 0; i < SIZE; ++i)
		sum += pow(tab[i], 2);

	return sqrt(sum);
}

/**
 * Funkcja kopiująca wartości współrzędnych wektora do innego obiektu tej samej klasy
 * Jeśli spróbujemy wpisać obiekt do samego siebie, funkcja jedynie zwróci referencję do samego siebie.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param drugi - Obiekt z którego kopiujemy wartości współrzędnych
 * @return Zwraca referencję do obiektu do którego wpisywalismy dane
 */
template<std::size_t SIZE>
Wektor<SIZE> &Wektor<SIZE>::operator=(const Wektor<SIZE> &drugi)
{
    if(&drugi == this)
        return (*this);
    
    for(uint16_t i = 0;i<SIZE;++i)
        tab[i] = drugi[i];
    
    return (*this);
}

/**
 * Wczytanie wektora z odpowiedniego strumienia
 *
 * @param strm - strumien z którego ma zostać wczytany wektor
 * @param wek - wektor który ma zostać wczytany
 * @return zwracamy referencję do przysłanego strumienia
 */
template<size_t SIZE>
std::istream& operator >> (std::istream& strm, Wektor<SIZE>& wek)
{
	double x;
	for (uint16_t i = 0; i < SIZE; ++i)
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

/**
 * Wypisanie wektora na odpowiedni strumień
 *
 * @param strm - strumien na który ma zostać wypisany wektor
 * @param wek - wektor który ma zostać wypisany
 * @return zwracamy referencję do przysłanego strumienia
 */
template <size_t SIZE>
std::ostream& operator << (std::ostream& strm, const Wektor<SIZE>& wek)
{
	for (uint16_t i = 0; i < SIZE; ++i)
		strm << std::setw(16) << std::fixed << std::setprecision(8) << wek[i] << (i == SIZE - 1 ? " " : "");

	return strm;
}
