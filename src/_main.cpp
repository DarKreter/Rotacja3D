#include <iostream>
#include <string>
#include <Figure.hpp>
#include <Scene.hpp>
#include <Macierz3x3.hpp>

/**
 * @file
 * @brief Funkcja main i główna funckjonalność programu
 */

using namespace std;

/**
 * @brief  Funkcja main
 *
 * Zawiera główną funkcjonalność programu
 *
 * @param argc - ilość argumentów przysłanych w linii wywołania
 * @param argv - tablica argumentów wywołania
 * @return - informacja o powodzeniu, bądź nie programu
 */
int main(int argc, char* argv[])
{
    
    if (argc < 2)
    {
        cout << "Brak nazwy pliku z prostokatem jako argument wywolania!" << endl;
        exit(1);
    }

    try
    {

        char znak; int nr;
        Scene scene(Wektor3D({100,100,100}));
        
        for(int i=1; i<argc;++i)
            scene.Add(argv[i]);
        
        scene.Draw();

        cout << "o - obrot bryly o zadana sekwencje katow" << endl
             << "t - powtorzenie poprzedniego obrotu" << endl
             << "r - wyswietlenie macierzy rotacji" << endl
             << "p - przesuniecie bryly o zadany wektor" << endl
             << "w - wyswietlenie wspolrzednych wierzcholkow" << endl
             << "s - sprawdzenie dlugosci przeciwleglych bokow" << endl
             << "e - usuniecie odpowiedniej figury" << endl
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
                
                cin >> nr;
                if (!cin.good())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<int>::max(), '\n');
                    cout << "Blednie podany numer figury do wyswietlenia!" << endl;
                    break;
                }
                try
                {
                    cout << scene[nr-1] << endl;
                }
                catch(std::out_of_range& exp)
                {
                    cout << "Numer figury moze byc tylko liczba naturalna z przedzialu (0;" + to_string(scene.size()) + "]!" << endl;
                }
                break;
                
            case 'e':
    
                cin >> nr;
                if (!cin.good())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<int>::max(), '\n');
                    cout << "Blednie podany numer figury do wyswietlenia!" << endl;
                    break;
                }
                try
                {
                    scene.Remove(nr-1);
                    scene.Draw();
                }
                catch(std::out_of_range& exp)
                {
                    cout << "Numer figury moze byc tylko liczba naturalna z przedzialu (0;" + to_string(scene.size()) + "]!" << endl;
                }
                break;
            
            case 'r':
                cout << "\nMacierz rotacji:\n" << scene() << "\n\n\n";
                break;
                
            case 'o':
                
                cout << "Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach:";

                MacierzRot3x3::Axis axis;
                double alpha; int ip;
                scene() = MacierzRot<3>();   //Macierz jedynkowa

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

                    scene() = MacierzRot<3>(alpha, axis) * scene();

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
//                [[clang::fallthrough]];
            case 't':
                cout << "Podaj numer figury ktora chcesz obrocic:";
                cin >> nr;
                if (!cin.good())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<int>::max(), '\n');
                    cout << "Blednie podany numer figury do wyswietlenia!" << endl;
                    break;
                }
                try
                {
                    for (int i = 0; i < ip; ++i)
                        scene[nr-1].Rotation(scene());
    
                    scene.Draw();
                }
                catch(std::out_of_range& exp)
                {
                    cout << "Numer figury moze byc tylko liczba naturalna z przedzialu (0;" + to_string(scene.size()) + "]!" << endl;
                    break;
                }
                
                break;

            case 's':
                cin >> nr;
                if (!cin.good())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<int>::max(), '\n');
                    cout << "Blednie podany numer figury do sprawdzenia!" << endl;
                    break;
                }
                try
                {
                    scene[nr-1].IsCuboid();
                    cout << endl;
                }
                catch(std::out_of_range& exp)
                {
                    cout << "Numer figury moze byc tylko liczba naturalna z przedzialu (0;" + to_string(scene.size()) + "]!" << endl;
                    break;
                }
                
                break;

            case 'p':


                try
                {
                    Wektor3D w;
                    cin >> w;
    
                    cout << "Podaj numer figury ktora chcesz obrocic:";
                    cin >> nr;
                    if (!cin.good())
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<int>::max(), '\n');
                        cout << "Blednie podany numer figury do przesuniecia!" << endl;
                        break;
                    }
                    
                    scene[nr-1].Translation(w);
                    scene.Draw();
                }
                catch (std::runtime_error& e)
                {
                    cout << "Blednie podany wektor translacji!" << endl;
                }
                catch(std::out_of_range& exp)
                {
                    cout << "Numer figury moze byc tylko liczba naturalna z przedzialu (0;" + to_string(scene.size()) + "]!" << endl;
                    break;
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
                     << "e - usuniecie odpowiedniej figury" << endl
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



