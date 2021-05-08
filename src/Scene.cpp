#include "Scene.hpp"
#include <fstream>
#include <utility>

/**
 * Na podstawie 3 wartości przesłanych w Wektorze3D,
 * ustawiany jest zakres wartości wyświetlany na osiach w programie gnuplot.
 * Konstruktor jednocześnie inicjalizuje podstawowe parametry gnuplota,
 * tak by poprawnie wyświetlał bryły w przestrzeni 3D.
 * Tworzy również plik "temp.dat" na potrzeby komunikacji z programem gnuplot.
 *
 * @param range - wektor którego odpowiednie składowe odpowiadają za zakres wartości na osiach.
 */
Scene::Scene(Wektor3D range)
{
    system("touch temp.dat");
    
    lacze.DodajNazwePliku("temp.dat",PzG::RR_Ciagly,2);
    //lacze.DodajNazwePliku("temp.dat", PzG::RR_Punktowy, 2);
    
    lacze.ZmienTrybRys(PzG::TR_3D);
    
    lacze.UstawZakresX(-range[0],range[0]);
    lacze.UstawZakresY(-range[1],range[1]);
    lacze.UstawZakresZ(-range[2],range[2]);
}

/**
 * Czyści wszystkie narysowane figury oraz rysuje je na podstawie aktualnej ich ilości
 * i ich wartości na wierzchołkach
 * Dane są przekazywane przez plik "temp.dat"
 */
void Scene::Draw()
{
    std::fstream  file;
    
    file.open("temp.dat", std::ios::out);
    if (!file.is_open())
        throw std::runtime_error("Nastapil problem podczas zapisu pliku!");
    
    for(Figure& fig: figures)
        file << fig << std::endl <<  fig[0] << std::endl << fig[1] << std::endl << std::endl << std::endl;
    
    file.close();
    
    lacze.Rysuj();
}

/**
 * Na podstawie nazwy pliku w którym zapisane są wierzchołki nowego prostopadłoscianu,
 * zostanie utworzona nowa bryła, a następnie dodana do kontenera przechowującego wszystkie bryły.
 *
 * @param name - nazwa pliku w którym zapisane są wszystkie wierzchołki
 */
void Scene::Add(std::string name)
{
    figures.push_back(Figure(std::move(name)));
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych figur.
 * Umożliwa on dostęp do figur, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;ILOŚĆ_BRYŁ] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks figury do której chcemy uzyskać dostęp
 * @return zwraca referencję do figury którą chcemy zmodyfikować
 */
const Figure& Scene::operator[](unsigned int n) const
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    return figures[n];
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych figur.
 * Umożliwa on modifikację tychże figur.
 * Gdy indeks jest spoza zakresu [0;ILOŚĆ_BRYŁ] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks figury do której chcemy uzyskać dostęp
 * @return zwraca referencję do figury którą chcemy zmodyfikować
 */
Figure& Scene::operator[](unsigned int n)
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    return figures[n];
}

/**
 * Dostajemy się za jego pomocą do macierzy rotacji która przechowuje informacje o ostatnim obrocie
 * mamy tutaj dostęp jedynie dla podglądu
 *
 * @return Macierz rotacji
 */
const MacierzRot3x3 & Scene::operator()() const
{
    return macierzRot;
}

/**
 * Dostajemy się za jego pomocą do macierzy rotacji która przechowuje informacje o ostatnim obrocie.
 * Używając go mamy możliwość modyfikacji tejże macierzy
 *
 * @return Referencja do macierzy rotacji
 */
MacierzRot3x3& Scene::operator()()
{
    return macierzRot;
}

/*!
 * Usuwa figure z wektora.
 * Jeśli numer figury jest błędny, rzuca wyjątek typu std::out_of_range
 *
 * @param n - indeks bryły do usunięcia w zakresie [1;ILOŚĆ_BRYŁ]
 */
void Scene::Remove(uint16_t n)
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    
    figures.erase(figures.begin() + n);
}
