#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>


/*!
 * \file
 * \brief Ten plik powinien zawierać definicję szablonu Wektor<>
 *
 * Ten plik powinien zawierać definicję szablonu Wektor<>.
 * W tym celu należy przerobić definicję klasy Wektor2D.
 */


/*!
 * \brief Krótki opis czego to jest szablon
 * 
 *  Tutaj trzeba opisac szablon. Jakie pojecie on modeluje
 *  i jakie ma glowne cechy.
 */
template <int Wyniar>
class Wektor {
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich pol i metod prywatnych
   */
  public:
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich metod publicznych
   */    
};


/*!
 * \brief Przeciążenie dla wyjścia musi także być szablonem
 *
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
template <int Wymiar>
inline
std::istream& operator >> (std::istream &Strm, Wektor<Wymiar> &Wek)
{
  /*!
   * Zawartość powinna być przeróbką przeciążenia dla klasy Wektor2D
   */
  return Strm;
}

/*!
 * \brief Przeciążenie dla wejścia musi także być szablonem
 * 
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
template <int Wymiar>
inline
std::ostream& operator << (std::ostream &Strm, const Wektor<Wymiar> &Wek)
{
  /*!
   * Zawartość powinna być przeróbką przeciążenia dla klasy Wektor2D
   */
  return Strm;  
}

#endif
