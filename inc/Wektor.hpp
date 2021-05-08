#ifndef WEKTOR_H
#define WEKTOR_H

/**
 * @file
 * @brief Definicja klasy szablonowej Wektor
 */

#include <iostream>
#include <array>
#include <iomanip>
#include <string>

/**
 * @brief Modeluje pojęcie Wektora/Punktu w przestrzeni n-wymiarowej
 *
 * Przechuje wszystkie współrzędne wierzchołka w tablicy
 * oraz pozwala wykonywać na nich podstawowe operacje
 *
 * @tparam SIZE - Określa w ilo wymiarowej przestrzeni przechowujemy nasz wektor
 */
template<std::size_t SIZE>
class Wektor
{
    /**
     * @brief Tablica przechowująca wszystkie współrzędne wektora
     */
	std::array<double, SIZE> tab;
	
public:
    /**
     * @brief Inicjalizuje wektor
     *
     * Ustawia wszystkie współrzędne na zera
     */
	Wektor(): tab{}										    {;}
	
	/**
	 * @brief Inicjalizuje wektor na podstawie wspołrzędnych w tablicy
	 * @param pkt - tablica współrzędnych które zostaną skopiowane do tablicy wektora
	 */
	Wektor(std::array<double, SIZE> pkt) : tab{ pkt }		{;}
	
	/**
	 * @brief Konstruktor kopiujący
	 *
	 * Tworzy wektor na podstawie innego obiektu klasy wektor o tym samym rozmiarze
	 *
	 * @param temp - niemodyfikowalna referencja do obiektu z którego będziemy kopiować
	 */
	Wektor(const Wektor<SIZE>& temp) : tab{ temp.tab }		{;}
    
    /**
    * \brief Operator dostępowy do współrzędnych wektora.
    */
	const double& operator[](unsigned int n) const;
    
    /**
    * \brief Operator dostępowy do współrzędnych wektora.
    */
	double& operator[](unsigned int n);

	/**
	 * @brief Modeluje operacje dodania dwóch wektorów do siebie
	 */
	Wektor<SIZE> operator+(const Wektor<SIZE>&) const;
    
    /**
     * @brief Modeluje operacje odejmowania dwóch wektorów od siebie
     */
	Wektor<SIZE> operator-(const Wektor<SIZE>&) const;
	
	/**
	 * @brief Modeluje pojęcie mnożenia wektora przez stałą
	 */
	Wektor<SIZE> operator*(double) const;
 
	/**
	 * @brief Modeluje pojęcie kopiującego operatora przypisania
	 */
    Wektor<SIZE>& operator=(const Wektor<SIZE>& drugi);
	
    /**
     * @brief Liczy długość wektora
     */
	double Length();

};

/**
 * \brief  Wczytuje wektor ze strumienia.
 */
template <size_t SIZE>
std::istream& operator >> (std::istream&, Wektor<SIZE>&);

/**
 * \brief  Wpisuje wektor do strumienia.
 */
template <size_t SIZE>
std::ostream& operator << (std::ostream&, const Wektor<SIZE>&);

#include "Wektor.tpp"

#endif
