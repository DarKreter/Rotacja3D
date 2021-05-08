#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

/*!
 * \file
 * \brief Definicja klasy Figure
 *
 */

#include <iostream>
#include <Macierz3x3.hpp>
#include <Wektor3D.hpp>

/**
 * \brief Modeluje pojęcie Prostopadłościanu
 *
 * Przechowuje 8 wierzchołków prostopadłościanu w tablicy.
 * Dostarcza narzędzia do przesuwania go w przestrzeni o wektor
 * oraz obrót o zadany kąt względem danej osi układu współrzędnych.
 * Pozwala także na wygodne wypisanie i wczytanie go ze strumienia standardowego.
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
     * \brief  Rotacja bryły.
     */
	void Rotation(MacierzRot3x3 mRotacji);
	
    /**
     * \brief  Translacja bryły.
     */
	void Translation(Wektor<3> wektor);
    /**
     * \brief  Sprawdzanie czy bryła dalej jest poprawnym prostopadłościanem.
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
