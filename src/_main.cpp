#include <iostream>
#include <fstream>
#include <gnuplot.hpp>
#include <Figure.hpp>
#include "Macierz3x3.hpp"


using namespace std;

void GNUPlotInicjalizacja(string nazwaPliku, PzG::LaczeDoGNUPlota& lacze, Wektor<3> range);
void Rysuj(const Figure& figure, PzG::LaczeDoGNUPlota& lacze);


int main(int argc, char* argv[])
{
    
    if (argc < 2)
    {
        cout << "Brak nazwy pliku z prostokatem jako argument wywolania!" << endl;
        exit(0);
    }

    try
    {

        char znak;
        Figure figure(argv[1]);
        PzG::LaczeDoGNUPlota lacze;
        MacierzRot3x3 macierzRot;
    
    
        GNUPlotInicjalizacja("prostopadloscian.dat", lacze, Wektor<3>({100,100,100}));
        Rysuj(figure, lacze);

        cout << "o - obrot bryly o zadana sekwencje katow" << endl
             << "t - powtorzenie poprzedniego obrotu" << endl
             << "r - wyswietlenie macierzy rotacji" << endl
             << "p - przesuniecie bryly o zadany wektor" << endl
             << "w - wyswietlenie wspolrzednych wierzcholkow" << endl
             << "s - sprawdzenie dlugosci przeciwleglych bokow" << endl
             << "m - wyswietl menu" << endl
             << "c - czysci ekran" << endl
             << "k - koniec dzialania programu" << endl;

        while (true)
        {

            cout << "Twoj wybor? (m - menu): ";
            cin >> znak;

            switch (znak)
            {

            case 'w':
                cout << figure << endl;
                break;
    
            
            case 'r':
                cout << "\nMacierz rotacji:\n" << macierzRot << "\n\n\n";
                break;
                
            case 'o':
                
                cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach:";
                
                MacierzRot3x3::Axis axis;
                double alpha; int ip;
                macierzRot = MacierzRot<3>();   //Macierz jedynkowa
                
                while(znak != '.')
                {
                    cin >> znak;
                    switch(znak)
                    {
                    case 'x': case 'X':
                        axis = MacierzRot3x3::Axis::OX;
                        break;
        
                    case 'y': case 'Y':
                        axis = MacierzRot3x3::Axis::OY;
                        break;
                        
                    case 'z': case 'Z':
                        axis = MacierzRot3x3::Axis::OZ;
                        break;
                        
                    default:
                        cin.setstate(ios::failbit);
                    }
                    
                    cin >> alpha;
                    
                    
                    if (!cin.good())
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<int>::max(), '\n');
                        
                        if(znak == '.')
                            break;
                        
                        cout << "Blednie podana os obrotu lub kat!" << endl;
                        continue;
                    }
                    
                    macierzRot = MacierzRot<3>(alpha, axis) * macierzRot;
                    
                }
                
                cout << "Podaj ilosc powtorzen podanej powyzej sekwencji: ";
                while(true)
                {
                    cin >> ip;
                    if (!cin.good())
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<int>::max(), '\n');
                        cout << "Blednie podana ilosc powtorzen, sprobuj jeszcze raz:" << endl;
                        continue;
                    }
                    else
                        break;
                }
                [[fallthrough]];
            case 't':
                
                for (int i = 0; i < ip; ++i)
                    figure.Rotation(macierzRot);
        
                Rysuj(figure, lacze);
                break;
                
            case 's':
                figure.IsCuboid();
                cout << endl;
                break;
                
            case 'p':
                try
                {
                    Wektor<3> w;
                    cin >> w;
                    figure.Translation(w);
                    Rysuj(figure, lacze);
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
                cout << "o - obrot bryly o zadana sekwencje katow" << endl
                     << "t - powtorzenie poprzedniego obrotu" << endl
                     << "r - wyswietlenie macierzy rotacji" << endl
                     << "p - przesuniecie bryly o zadany wektor" << endl
                     << "w - wyswietlenie wspolrzednych wierzcholkow" << endl
                     << "s - sprawdzenie dlugosci przeciwleglych bokow" << endl
                     << "m - wyswietl menu" << endl
                     << "c - czysci ekran" << endl
                     << "k - koniec dzialania programu" << endl;
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


    return 0;

    
}



void GNUPlotInicjalizacja(string nazwaPliku, PzG::LaczeDoGNUPlota& lacze, Wektor<3> range)
{
    system(("cp " + nazwaPliku + " temp.dat").c_str());
    
    lacze.DodajNazwePliku("temp.dat",PzG::RR_Ciagly,2);
    //lacze.DodajNazwePliku("temp.dat", PzG::RR_Punktowy, 2);
    
    lacze.ZmienTrybRys(PzG::TR_3D);
    
    lacze.UstawZakresX(-range[0],range[0]);
    lacze.UstawZakresY(-range[1],range[1]);
    lacze.UstawZakresZ(-range[2],range[2]);
    
}


void Rysuj(const Figure& figure, PzG::LaczeDoGNUPlota& lacze)
{
    std::fstream  file;
    
    file.open("temp.dat", std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Nastapil problem podczas zapisu pliku!");
    }
    
    file << figure << std::endl <<  figure[0] << std::endl << figure[1] << std::endl;
    
    file.close();
    
    lacze.Rysuj();
}


