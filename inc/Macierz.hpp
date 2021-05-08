#ifndef MACIERZ_H
#define MACIERZ_H

/**
 * @file
 * @brief Definicja klasy MacierzRot
 */

#include <iostream>
#include <Wektor.hpp>

/**
 * @brief Modeluje pojęcie macierzy rotacji
 *
 * Macierz rotacji zawsze jest intepretowana jako macierz kwadratowa SIZExSIZE
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji
 */
template<size_t SIZE>
class MacierzRot
{
    /**
     * @brief Tablica przechowująca wartości wszystkich pól macierzy
     *
     * Składa się ona z wektorów
     */
    std::array<Wektor<SIZE>, SIZE> tab;

public:
    /**
     * @brief Określa rodzaj osi wokół której wykonywany będzie obrót
     *
     * Obrót może być wykonany wokół jednej z 3 osi układu współrzędnych
     */
    enum class Axis
    {
        OX /** Oś OX układu współrzędnych */,
        OY /** Oś OY układu współrzędnych */,
        OZ /** Oś OZ układu współrzędnych */
    };
    
    /**
     * @brief Inicjalizacja macierzy rotacji
     */
    MacierzRot();
    
    /**
     * @brief Inicjalizuje macierz rotacji na podstawie kąta obotu i osi wokół której ma być wykonany obrót
     */
    MacierzRot(double alpha, Axis o);
    
    /**
     * @brief Konstruktor kopiujący
     */
    MacierzRot(const MacierzRot<SIZE>& druga);
    
    /**
    * \brief Operator dostępowy do wierszów macierzy
    */
    const Wektor<SIZE>& operator[](unsigned int n) const;
    
    /**
    * \brief Operator dostępowy do wierszów macierzy
    */
    Wektor<SIZE>& operator[](unsigned int n);

    /**
     * @brief Modeluje pojęcie mnożenia macierzy przez wektor
     */
    Wektor<SIZE> operator*(const Wektor<SIZE>&) const;
    
    /**
     * @brief Modeluje pojęcie mnozenia macierzy przez inną macierz
     */
    MacierzRot<SIZE> operator*(const MacierzRot<SIZE>&) const;
    
    /**
     * @brief Kopiujący operator przypisania
     */
    MacierzRot<SIZE>& operator=(const MacierzRot<SIZE>& drugi);
    
};

/**
 * @brief  Wpisuje macierz rotacji do strumienia.
 */
template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const MacierzRot<SIZE>& mac);

#include "Macierz.tpp"

#endif
