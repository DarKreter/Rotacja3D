#include <iostream>
#include <iomanip>
#include <fstream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "Prostopadloscian.hh"
#include "lacze_do_gnuplota.hh"



using namespace std;

/*
 * Tu definiujemy pozostale funkcje.
 * Lepiej jednak stworzyc dodatkowy modul
 * i tam je umiescic. Ten przyklad pokazuje
 * jedynie absolutne minimum.
 */


#define DL_BOKU   50





/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void PrzykladZapisuWspolrzednychDoStrumienia( ostream&     StrmWy, 
                                              double       Przesuniecie
                                            )
{
   //---------------------------------------------------------------
   // To tylko przyklad !!!
   // W programie nalezy uzywać pojęcia wektora, a nie oddzielnych 
   // zmiennych do reprezentowania wspolrzednych!
   //
  double  x1, y1, z1;

  x1 = y1 = z1 = Przesuniecie;

  StrmWy << setw(16) << fixed << setprecision(10) << x1
         << setw(16) << fixed << setprecision(10) << y1
         << setw(16) << fixed << setprecision(10) << z1 
         << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << y1
         << setw(16) << fixed << setprecision(10) << z1 
         << endl;

  StrmWy << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1
         << setw(16) << fixed << setprecision(10) << y1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << z1 
         << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << y1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << z1 
         << endl;

  StrmWy << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1
         << setw(16) << fixed << setprecision(10) << y1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << z1+DL_BOKU 
         << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << y1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << z1+DL_BOKU 
         << endl;

  StrmWy << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1
         << setw(16) << fixed << setprecision(10) << y1
         << setw(16) << fixed << setprecision(10) << z1+DL_BOKU 
         << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << y1
         << setw(16) << fixed << setprecision(10) << z1+DL_BOKU 
         << endl;

  StrmWy << endl;
 
  StrmWy << setw(16) << fixed << setprecision(10) << x1
         << setw(16) << fixed << setprecision(10) << y1
         << setw(16) << fixed << setprecision(10) << z1 
         << endl;

  StrmWy << setw(16) << fixed << setprecision(10) << x1+DL_BOKU
         << setw(16) << fixed << setprecision(10) << y1
         << setw(16) << fixed << setprecision(10) << z1 
         << endl;
                             // Jeszcze raz zapisujemy pierwsze dwa wierzcholki,
                             // aby gnuplot narysowal zamkniętą powierzchnie.
}



/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool PrzykladZapisuWspolrzednychDoPliku( const char  *sNazwaPliku,
                                         double       Przesuniecie
                                       )
{
  ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  PrzykladZapisuWspolrzednychDoStrumienia(StrmPlikowy,Przesuniecie);

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}



int main()
{
  Prostopadloscian             Pr;   // To tylko przykladowe definicje zmiennej
  PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku("prostopadloscian.dat",PzG::RR_Ciagly,2);
   //
   //  Ustawienie trybu rysowania 3D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy x,y,z.
   //
  Lacze.ZmienTrybRys(PzG::TR_3D);

   // Ustawienie zakresow poszczegolnych osi
  Lacze.UstawZakresY(-155,155);
  Lacze.UstawZakresX(-155,155);
  Lacze.UstawZakresZ(-155,155);

  
  PrzykladZapisuWspolrzednychDoStrumienia(cout,0);
  if (!PrzykladZapisuWspolrzednychDoPliku("prostopadloscian.dat",0)) return 1;
  Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  cout << "Naciśnij ENTER, aby kontynuowac" << endl;
  cin.ignore(10000,'\n');

   //----------------------------------------------------------
   // Ponownie wypisuje wspolrzedne i rysuje prostokąt w innym miejscu.
   //
  PrzykladZapisuWspolrzednychDoStrumienia(cout,50);
  if (!PrzykladZapisuWspolrzednychDoPliku("prostopadloscian.dat",50)) return 1;
  Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  cout << "Naciśnij ENTER, aby kontynuowac" << endl;
  cin.ignore(10000,'\n');
}
