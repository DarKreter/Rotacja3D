#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

#ifdef __GNUG__
#pragma implementation
#endif

#include "lacze_do_gnuplota.hh"

using namespace std;

#define STDIN        0
#define STDOUT       1

namespace PzG {


 std::list<InfoPlikuDoRysowania>  LaczeDoGNUPlota::_InfoPlikow;



 void LaczeDoGNUPlota::WyswietlajKomunikatyBledow( bool Tryb )
 {
  _WyswietlajKomunikatyOBledach = Tryb;
 }


  LaczeDoGNUPlota::~LaczeDoGNUPlota() 
  {}


 bool LaczeDoGNUPlota::PrzeslijDoGNUPlota(const char *Komunikat)
 {
  int Ilosc = strlen(Komunikat);
  int IloscPrzeslanych;
  
  while (((IloscPrzeslanych = write(_Wejscie_GNUPlota,Komunikat,Ilosc)) != -1)
          && Ilosc > 0) {
    Komunikat += IloscPrzeslanych;
    Ilosc -= IloscPrzeslanych;
  }
  if (Ilosc > 0) {
    KomunikatBledu("!!! Przeslanie polecenia do GNUPlota nie powiodlo sie.");
    return false;
  }
  return true;
 }




 LaczeDoGNUPlota::LaczeDoGNUPlota() 
 { 
   _PokazOs_OX = _PokazOs_OY = _PokazOs_OZ = true;

   _TrybRys = TR_2D;
   WyswietlajKomunikatyBledow();
   _Wyjscie_GNUPlota = _Wejscie_GNUPlota = -1; 
   UstawZakresX(-350,350);
   UstawZakresY(-350,350);
   UstawZakresZ(-200,200);
   UstawRotacjeXZ(60,30);
   UstawSkaleXZ(1,1);
 }




 bool CzyJestPlik(char const *NazwaPliku)
 {
  struct stat buf;

  if (stat(NazwaPliku,&buf)) return false;
  if (!(S_ISREG(buf.st_mode))) return false;
  if (!(buf.st_mode & S_IRUSR)) return false;
  return true;
 }




 //-------------------------------------------------------------------------
 // Powoduje dodanie do listy plikow zawierajacych dane dla gnuplota,
 // nowej nazwy pliku.
 //
 // PRE:  NazwaPliku  - nazwa pliku z danymi dla gnuplota.
 // POST:
 //  Zwraca wartosc:
 //     true - jezeli istnieje plik o nazwie zawartej w zmiennej NazwaPliku.
 //             Zostaje on ponadto dodany do listy plikow z danymi 
 //             dla gnuplota.
 //    fasle - Jezeli nie istnieje plik o nazwie zawartej w zmiennej
 //            NazwaPliku. Zadne dodatkowe dzialanie nie jest realizowane.
 //
 bool LaczeDoGNUPlota::DodajNazwePliku( const char      * NazwaPliku,
                                        RodzajRysowania   RodzRys,
                                        int               Szerokosc
                                      )
 {
  bool rezultat = true;

  if (!CzyJestPlik(NazwaPliku)) {
    string Komunikat = "!!! Ostrzezenie: Brak pliku ";
    Komunikat += NazwaPliku;
    //TMP    KomunikatBledu(Komunikat.c_str());
    rezultat = false;
  }

  _InfoPlikow.push_back(InfoPlikuDoRysowania(NazwaPliku,RodzRys,Szerokosc));
  return rezultat;
 }


 //-------------------------------------------------------------------------
 // Informuje, czy połączenie z programem gnuplot zostało zainicjowane.
 // 
 bool LaczeDoGNUPlota::CzyPolaczenieJestZainicjowane() const
 {
  return _Wejscie_GNUPlota > -1 && _Wyjscie_GNUPlota > -1;
 }


 void LaczeDoGNUPlota::KomunikatBledu(const char *Komunikat) const
 {
  if (!CzyWyswietlacKomunikaty()) return;
  cerr << Komunikat << endl;
 }


#define ROZ_LINII   120



 bool LaczeDoGNUPlota::Inicjalizuj()
 {
  if (CzyPolaczenieJestZainicjowane()) return true;
  if (!UtworzProcesPotomny()) return false;

  return PrzeslijDoGNUPlota("\n");
 }


/*!
 *  Inicjalizuje połączenie z programem \e gnuplot. Realizowane jest to
 *  poprzez rozwidlenie procesu i uruchomienie jako procesu potomnego
 *  programu \e gnuplot. Komunikacja z programem \e gnuplot realizowana jest
 *  poprzez przejęcie jego wejścia i wyjścia standardowego.
 *
 *  \retval true - gdy połączenie z programem \e gnuplot zostało poprawnie
 *               zainicjalizowane lub gdy już wcześniej było 
 *               zainicjalizowane.
 *  \retval false - gdy proces inicjalizacji połączenia zakończył się
 *               niepowodzeniem.
 */
 bool LaczeDoGNUPlota::UtworzProcesPotomny()
 {
  int indesk[2],outdesk[2];

  if (pipe(indesk) == -1 || pipe(outdesk) == -1) {
    KomunikatBledu(
      "### Niemozliwe utworzenie kanalow komunikacyjnych do podprocesow.");
    exit(1);
  }

  switch (fork()) {
    case -1: KomunikatBledu("### Niemozliwe rozwidlenie procesu.");
             exit(1);
    case  0: 
       /* Start potomka */

       if (close(STDIN) == -1) { 
         KomunikatBledu("### Blad przy zamykaniu strumienia wejsciowego.");
         exit(1);
       }
       if (dup(outdesk[STDIN]) == -1) {
         KomunikatBledu("### Blad duplikacji kanalu wejsciowego.");  
         exit(1);
       }
       
       if (close(STDOUT) == -1) { 
         KomunikatBledu(
            "### Blad zamkniecia kanalu standardowego kanalu wyjsciowego."); 
         exit(1);
       }
       if (dup(indesk[STDOUT]) == -1) {
         KomunikatBledu("### Blad duplikacji kanalu wyjsciowego.");  
         exit(1);
       }       
       if (close(outdesk[STDIN]) == -1) {
         KomunikatBledu("### Blad zamkniecia kanalu wejsciowego.");
         exit(1);
       }
       if (close(outdesk[STDOUT]) == -1) {
         KomunikatBledu("### Blad zamkniecia kanalu wyjsciowego.");
         exit(1);
       }
       if (close(indesk[STDIN]) == -1) {
         KomunikatBledu("### Blad zamkniecia duplikatu kanalu wejsciowego.");
         exit(1);
       }
       if (close(indesk[STDOUT]) == -1) {
         KomunikatBledu("### Blad zamkniecia duplikatu kanalu wyjsciowego.");
         exit(1);
       }
       char Tab[3];
       read(STDIN,Tab,1);
       write(STDOUT,"\n",1); 
       const char *Comm;

       execlp(Comm = "gnuplot","gnuplot",NULL);

       KomunikatBledu("!!! Blad:"); 
       KomunikatBledu("!!! W procesie potomnym nie mogl zostac."); 
       KomunikatBledu("!!! uruchomiony program gnuplot."); 
       KomunikatBledu("!!! Nastapilo przerwanie dzialania procesu potomnego."); 
       KomunikatBledu("!!! Jednym z mozliwych powodow problemu moze byc"); 
       KomunikatBledu("!!! Brak programu gnuplot w szukanej sciezce."); 
       KomunikatBledu("!!! Do uruchomienia programu gnuplot bylo uzyte polecenie:");
       KomunikatBledu(Comm);
       exit(1);

    default:
       if (close(outdesk[STDIN]) == -1 || close(indesk[STDOUT]) == -1) { 
         KomunikatBledu(" Blad zamkniecia outpipe[STDIN], inpipe[STDOUT]."); 
       }

       fcntl(indesk[STDIN],F_SETFL,O_NDELAY);
       _Wyjscie_GNUPlota  = indesk[STDIN];
       _Wejscie_GNUPlota =  outdesk[STDOUT];
  }
  return true;
 }




 bool LaczeDoGNUPlota::RysujDoPliku(const char *NazwaPliku)
 {
  if (!CzyPolaczenieJestZainicjowane()) {
    if (!Inicjalizuj()) return false;
  }
  string Polecenie = "\n\n\nset output '";
  Polecenie += NazwaPliku;
  Polecenie += "\n set term png\n";
  if (!PrzeslijDoGNUPlota(Polecenie.c_str())) {
    KomunikatBledu("!!! Rysunek nie moze byc utworzony.");
    return false;
  }

  bool Wynik = Rysuj();
  if (!PrzeslijDoGNUPlota("\n\n\nset output \nset term x11\n")) {
    KomunikatBledu("!!! Wyjscie dla gnuplot'a nie zostalo poprawnie\n"
                   "!!! przestawione na STDOUT.\n");
    return false;
  }
  return Wynik;
 }



/*!
 * Tworzy napis będący parametrami dla polecenie \e plot programu,
 * \e gnuplot. Parametry te pozwalają na rysowanie brył, których
 *  współrzędne wierzchołków zawarte są w plikach.
 *  Nazwy tych plików muszą być wcześniej dołączone do kolejki 
 *  plików poprzez zastosowanie polecenia
 *   \link LaczeDoGNUPlota::DodajNazwe DodajNazwe\endlink.
 *  
 * \param Polecenie - dopisywana jest do niego sekwencja znaków
 *                  tworzących parametry dla polecenia \e plot.
 * \param Sep - zawiera znak separatora między poszczególnymi
 *              parametrami. Jeżeli parametry listy nazw plików
 *              są generowane jako pierwsze, to zmienna ta musi 
 *              być wskaźnikiem do wskaźnika na łańcuch: " ".
 * \retval true - jeśli lista nazw plików nie jest pusta.
 * \retval false - w przypadku przeciwnym.
 * \post Jeżeli  lista nazw plików nie jest pusta, to poprzez
 *              parametr \e Sep zostaje udostępniony łańcuch: ", ".
 */
 bool LaczeDoGNUPlota::DopiszRysowanieZPlikow( std::string  &Polecenie, 
                                                char const **Sep 
                                             )
 {
  if (_InfoPlikow.empty()) return false;
  list<InfoPlikuDoRysowania>::const_iterator Nazwy = _InfoPlikow.begin();

  for (; Nazwy != _InfoPlikow.end(); ++Nazwy ) {
    //       OSStrm.empty();
       ostringstream OSStrm;
       Polecenie += *Sep;
       Polecenie += " \'";
       Polecenie += Nazwy->WezNazwePliku();
       ((Polecenie += '\'') += " notitle ") += 
       (Nazwy->WezRodzRys() == RR_Ciagly ? " w l" : " w p pt 5");
       if  (Nazwy->WezRodzRys() == RR_Ciagly) OSStrm << " lw " << Nazwy->WezSzerokosc();
                                         else OSStrm << " ps " << Nazwy->WezSzerokosc();
       Polecenie += OSStrm.str();
       *Sep = ", ";
  }
  return true;
 }



 //-------------------------------------------------------------------------
 //  Jezeli lista plikow nie jest pusta, to generuje sekwencje polecen
 //  dla programu gnuplot majaca na celu narysowanie plaszczyzn na
 //  na podstawie danych zawartych w plikach z listy. 
 //
 //  PRE:  Na liscie plikow nie powinna byc pusta. Nazwy plikow na niej
 //        mozna umiescic za pomoca metody 'DodajNazwe'.
 //        Metoda nie wymaga wcześniejszego zainicjowania połączenia
 //        z gnuplotem.
 //  POST: true   - gdy zostaja poprawnie wyslane polecenia dla gnuplota.
 //                 Nie oznacza to jednak, ze proces rysowania zakończył
 //                 się pomyślnie.
 //       false   - gdy połączenie z gnuplotem nie moze zostac poprawnie
 //                 zainicjalizowane lub gdy lista plikow jest pusta.
 //
 bool LaczeDoGNUPlota::Rysuj()
 {
  if (!CzyPolaczenieJestZainicjowane()) {
    if (!Inicjalizuj()) return false;
  }

  string Polecenie;

  BudujPreambulePoleceniaRysowania(Polecenie);

  char const *Sep = "";
  bool TrzebaRysowac = DopiszPlikiDoPoleceniaRysowania(Polecenie,&Sep);
  /*

  */
  TrzebaRysowac = DopiszRysowanieZPlikow(Polecenie,&Sep) || TrzebaRysowac;

  if (!TrzebaRysowac) return false;
  Polecenie += "\npause -1\n";
  string Komenda = "/usr/bin/echo \"";
  Komenda += Polecenie;
  Komenda += "\" | gnuplot&";

  return PrzeslijDoGNUPlota(Polecenie.c_str());
 }



 void  LaczeDoGNUPlota::BudujPreambulePoleceniaRysowania(std::string &Preambula) const
 {
  switch (_TrybRys) {
   case TR_2D: BudujPreambule_2D(Preambula); break;
   case TR_3D: BudujPreambule_3D(Preambula); break;
  }
 }



 void  LaczeDoGNUPlota::BudujPreambule_2D(std::string &Preambula) const
 {
  Preambula.clear();
  Preambula.reserve(1000);
  Preambula = "\n\n";

  if (_PokazOs_OX) Preambula += "set xzeroaxis lt 0 lw 1\n";
  if (_PokazOs_OY) Preambula += "set yzeroaxis lt 0 lw 1\n";

  Preambula += ZapiszUstawienieZakresu('x');
  Preambula += ZapiszUstawienieZakresu('y');
  Preambula += "\nplot ";
 }



 void  LaczeDoGNUPlota::BudujPreambule_3D(std::string &Preambula) const
 {
  Preambula.clear();
  Preambula.reserve(1000);
  Preambula = "\n\n"
                       "set parametric\n"
                       "set isosamples 9\n"
                       "set urange [-180:180]\n"
                       "set vrange [-90:90]\n";  

  if (_PokazOs_OX) Preambula += "set xzeroaxis lt 0 lw 1\n";
  if (_PokazOs_OY) Preambula += "set yzeroaxis lt 0 lw 1\n";
  if (_PokazOs_OZ) Preambula += "set zzeroaxis lt 0 lw 1\n";

  Preambula += ZapiszUstawienieZakresu('x');
  Preambula += ZapiszUstawienieZakresu('y');
  Preambula += ZapiszUstawienieZakresu('z');
  Preambula += ZapiszUstawienieRotacjiISkali();
  Preambula += "set hidden3d\nsplot ";
 }



std::string LaczeDoGNUPlota::ZapiszUstawienieZakresu(char Os) const
{
  ostringstream strm;
  float Min, Max;

  switch (Os) {
   case 'x':  Min = Xmin();  Max = Xmax();  break;
   case 'y':  Min = Ymin();  Max = Ymax();  break;
   case 'z':  Min = Zmin();  Max = Zmax();  break;
   default: cerr << "!!! Blad w 'ZapiszUstawienieZakresu' niedozwolony"
                    " znak: " << Os << endl;
            return "";
  }
  strm << "set " << Os << "range [" <<  Min << ":" << Max << "]\n";
  return strm.str();
}



std::string LaczeDoGNUPlota::ZapiszUstawienieRotacjiISkali() const
{
  ostringstream strm;
  strm << "set view " << RotacjaX() << "," << RotacjaZ() 
       << "," << SkalaX() << "," << SkalaZ() << endl;
  return strm.str();
}







 //-------------------------------------------------------------------------
 //  Metda usuwa ostatnia nazwe z listy nazw plikow.
 //
 void LaczeDoGNUPlota::UsunOstatniaNazwe()
 {
   list<InfoPlikuDoRysowania>::iterator Nazwy = _InfoPlikow.end();
   _InfoPlikow.erase(--Nazwy,_InfoPlikow.end());
 }



 //-------------------------------------------------------------------------
 //  Metda calkowicie kasuje zawartosc listy nazw plikow.
 //
 void LaczeDoGNUPlota::UsunWszystkieNazwyPlikow()
 {
  _InfoPlikow.clear();
 }




} //___ Koniec przestrzeni nazw: PzG ____________________________________________
