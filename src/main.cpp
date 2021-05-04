#include <iostream>
#include <iomanip>
#include <fstream>
#include "Wektor.hpp"
#include "Macierz.hpp"


using namespace std;

//void GNUPlotInicjalizacja(string, PzG::LaczeDoGNUPlota&);
//void Rysuj(const Prostokat&, PzG::LaczeDoGNUPlota&);


int main(int argc, char* argv[])
{
    try
    {
        MacierzRot<3> xD(90, MacierzRot<3>::OS::OX);

        cout << xD << endl << endl;
        cout << xD * Wektor<3>({1,2,3}) << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Out of range exception: " << e.what() << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Runtime error exception: " << e.what() << endl;
    }
    return 0;

    /*if (argc < 2)
    {
        cout << "Brak nazwy pliku z prostokatem jako argument wywolania!" << endl;
        exit(0);
    }

    try
    {

        char znak;
        Prostokat prostokat(argv[1]);
        PzG::LaczeDoGNUPlota lacze;


        GNUPlotInicjalizacja(argv[1], lacze);
        Rysuj(prostokat, lacze);

        cout << "o - obrot prostokata o zadany kat" << endl
            << "p - przesuniecie prostokata o zadany wektor" << endl
            << "w - wyswietlenie wspolrzednych wierzcholkow" << endl
            << "m - wyswietl menu" << endl
            << "k - koniec dzialania programu" << endl
            << "c - czysci ekran" << endl;

        while (true)
        {

            cout << "Twoj wybor? (m - menu): ";
            cin >> znak;

            switch (znak)
            {

            case 'w':
                cout << prostokat << endl;

                break;

            case 'o':
                double alpha; int ip;
                cin >> alpha;
                cin >> ip;

                if (!cin.good())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<int>::max(), '\n');
                    cout << "Blednie podany kat obrotu lub ilosc powtorzen!" << endl;
                    break;
                }
                for (int i = 0; i < ip; ++i)
                    prostokat.Rotacja(alpha);

                prostokat.CzyProstokat();

                Rysuj(prostokat, lacze);

                break;

            case 'p':
                try
                {
                    Wektor2D w;
                    cin >> w;
                    prostokat.Translacja(w);
                    Rysuj(prostokat, lacze);
                }
                catch (std::runtime_error& e)
                {
                    cout << "Blednie podany wektor translacji!" << endl;
                }
                catch (...)
                {
                    throw;
                }
                break;


            case 'm':
                cout << "o - obrot prostokata o zadany kat" << endl
                    << "p - przesuniecie prostokata o zadany wektor" << endl
                    << "w - wyswietlenie wspolrzednych wierzcholkow" << endl
                    << "m - wyswietl menu" << endl
                    << "k - koniec dzialania programu" << endl
                    << "c - czysci ekran" << endl;
                break;

            case 'c':
                system("clear");
                break;

            case 'k':
                return 0;

            case ' ': case '\t': case '\n':
                break;
            default:
                cout << "Nie rozpoznana opcja!" << endl;
                cin.ignore(std::numeric_limits<int>::max(), '\n');

            }

        }
    }

    catch (std::runtime_error& e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Wystapil nie rozpoznany blad!" << endl;
    }


    return 0;*/

  //Prostopadloscian   Pr;   
  //PzG::LaczeDoGNUPlota  Lacze;  

  //Lacze.DodajNazwePliku("prostopadloscian.dat",PzG::RR_Ciagly,2);
  //Lacze.ZmienTrybRys(PzG::TR_3D);

  //Lacze.UstawZakresY(-155,155);
  //Lacze.UstawZakresX(-155,155);
  //Lacze.UstawZakresZ(-155,155);

  //
  //PrzykladZapisuWspolrzednychDoStrumienia(cout,0);
  //if (!PrzykladZapisuWspolrzednychDoPliku("prostopadloscian.dat",0)) return 1;
  //Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  //cout << "Naciśnij ENTER, aby kontynuowac" << endl;
  //cin.ignore(10000,'\n');

  // //----------------------------------------------------------
  // // Ponownie wypisuje wspolrzedne i rysuje prostokąt w innym miejscu.
  // //
  //PrzykladZapisuWspolrzednychDoStrumienia(cout,50);
  //if (!PrzykladZapisuWspolrzednychDoPliku("prostopadloscian.dat",50)) return 1;
  //Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  //cout << "Naciśnij ENTER, aby kontynuowac" << endl;
  //cin.ignore(10000,'\n');
}


//void GNUPlotInicjalizacja(string nazwaPliku, PzG::LaczeDoGNUPlota& lacze)
//{
//    system(("cp " + nazwaPliku + " temp.dat").c_str());
//
//    lacze.DodajNazwePliku("temp.dat", PzG::RR_Ciagly, 2);
//    lacze.DodajNazwePliku("temp.dat", PzG::RR_Punktowy, 2);
//    lacze.ZmienTrybRys(PzG::TR_2D);
//}
//
//
//void Rysuj(const Prostokat& prostokat, PzG::LaczeDoGNUPlota& lacze)
//{
//    std::fstream  plik;
//
//    plik.open("temp.dat", std::ios::out);
//    if (!plik.is_open()) {
//        throw std::runtime_error("Nastapil problem podczas zapisu pliku!");
//    }
//
//    plik << prostokat << prostokat[0] << std::endl;
//
//    plik.close();
//    lacze.Rysuj();
//
//}



//
//void PrzykladZapisuWspolrzednychDoStrumienia(ostream& StrmWy, double Przesuniecie)
//{
//
//    double  x1, y1, z1;
//
//    x1 = y1 = z1 = Przesuniecie;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1
//        << setw(16) << fixed << setprecision(10) << y1
//        << setw(16) << fixed << setprecision(10) << z1
//        << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << y1
//        << setw(16) << fixed << setprecision(10) << z1
//        << endl;
//
//    StrmWy << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1
//        << setw(16) << fixed << setprecision(10) << y1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << z1
//        << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << y1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << z1
//        << endl;
//
//    StrmWy << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1
//        << setw(16) << fixed << setprecision(10) << y1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << z1 + DL_BOKU
//        << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << y1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << z1 + DL_BOKU
//        << endl;
//
//    StrmWy << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1
//        << setw(16) << fixed << setprecision(10) << y1
//        << setw(16) << fixed << setprecision(10) << z1 + DL_BOKU
//        << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << y1
//        << setw(16) << fixed << setprecision(10) << z1 + DL_BOKU
//        << endl;
//
//    StrmWy << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1
//        << setw(16) << fixed << setprecision(10) << y1
//        << setw(16) << fixed << setprecision(10) << z1
//        << endl;
//
//    StrmWy << setw(16) << fixed << setprecision(10) << x1 + DL_BOKU
//        << setw(16) << fixed << setprecision(10) << y1
//        << setw(16) << fixed << setprecision(10) << z1
//        << endl;
//    // Jeszcze raz zapisujemy pierwsze dwa wierzcholki,
//    // aby gnuplot narysowal zamkniętą powierzchnie.
//}
//
//
//bool PrzykladZapisuWspolrzednychDoPliku(const char* sNazwaPliku, double Przesuniecie)
//{
//    ofstream  StrmPlikowy;
//
//    StrmPlikowy.open(sNazwaPliku);
//    if (!StrmPlikowy.is_open()) {
//        cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << endl
//            << ":(  nie powiodla sie." << endl;
//        return false;
//    }
//
//    PrzykladZapisuWspolrzednychDoStrumienia(StrmPlikowy, Przesuniecie);
//
//    StrmPlikowy.close();
//    return !StrmPlikowy.fail();
//}