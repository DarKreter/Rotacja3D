#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

/*!
 * \file
 * \brief Definicja klasy Figura
 *
 *  Plik zawierający definicję klasy Figura.
 */

#include <iostream>
#include <Macierz3x3.hpp>
#include <Wektor3D.hpp>

/**
 * \brief Modeluje pojęcie Prostopadłościanu
 */
class Figure
{
    /**
     * \brief Tablica przechowująca 8 wierzchołków prostopadłościanu
     *
     * Prostopadłościan jest zlokalizowany w przestrzeni 3D
     * Pojedyńczy punkt jest zmodelowany za pomocą klasy Wektor3D
     */
	std::array<Wektor3D, 8> wierzcholki;

public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na podstawie danych z pliku.
     */
    Figure(std::string name);
    
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu
     *
     * Ustawia je wszystkie na zera.
     */
    Figure() : wierzcholki({}) { ; }

    /**
     * \brief Operator dostępowy do wierzchołków prostopadłościanu
     */
	const Wektor3D& operator[](unsigned int n) const;
    /**
    * \brief Operator dostępowy do wierzchołków prostopadłościanu
    */
    Wektor3D& operator[](unsigned int n);
    
    /**
     * \brief  Funkcja składowa wykonująca rotacje bryły.
     */
	void Rotation(MacierzRot3x3 mRotacji);
	
    /**
     * \brief  Funkcja składowa wykonująca translację bryły.
     */
	void Translation(Wektor<3> wektor);
    /**
     * \brief  Funkcja składowa sprawdzająca czy bryła dalej jest poprawnym prostopadłościanem.
     */
	void IsCuboid();
};

/**
 * \brief  Wpisuje prostopadłościan do strumienia.
 */
std::ostream& operator << (std::ostream& strm, const Figure& pr);

/**
 * \brief  Wczytuje prostopadłościan ze strumienia.
 */
std::istream& operator >> (std::istream& strm, Figure& pr);

#endif
