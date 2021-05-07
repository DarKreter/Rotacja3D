#ifndef MACIERZ_H
#define MACIERZ_H

#include <iostream>
#include <Wektor.hpp>

template<size_t SIZE>
class MacierzRot
{
    std::array<Wektor<SIZE>, SIZE> tab;

public:
    enum class Axis
    {
        OX, OY, OZ
    };

    MacierzRot();   //Macierz jednostkowa
    MacierzRot(double alpha, Axis o);
    MacierzRot(const MacierzRot<SIZE>& druga);

    const Wektor<SIZE>& operator[](unsigned int n) const;
    Wektor<SIZE>& operator[](unsigned int n);

    Wektor<SIZE> operator*(const Wektor<SIZE>&) const;
    MacierzRot<SIZE> operator*(const MacierzRot<SIZE>&) const;
    
    MacierzRot<SIZE>& operator=(const MacierzRot<SIZE>& drugi);
    
};

template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const MacierzRot<SIZE>& mac);

#include "Macierz.tpp"

#endif
