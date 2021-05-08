#ifndef SCENE_HPP
#define SCENE_HPP
#include <Figure.hpp>
#include <gnuplot.hpp>
#include <vector>

/*!
 * @file
 * @brief Definicja klasy Scena
 *
 */
 
/**
 * @brief Klasa modeluje pojęcie wielu brył naraz w przestrzeni 3D
 *
 * Zawiera ona kontener przechopwujący wszystkie bryły
 * oraz elementy niezbędne do wyświetlania operacji w programie gnuplot.
 */
class Scene
{
    /**
     * @brief Wektor przechowujący wszystkie figury
     *
     * Może ich od 1 do bardzo dużej ilości ograniczoną pamięcią urządzenia.
     */
    std::vector<Figure> figures;
    
    /**
     * @brief Struktura odpowiedzialna za wyswietlanie informacji w programie gnuplot
     */
    PzG::LaczeDoGNUPlota lacze;
    
    /**
     * @brief Macierz za pomocą której obracane sa wybrane figury
     *
     * Macierz jest pamiętana z uwagi na możliwość powtórzenia obrotu o tą samą sekwencje co poprzednio.
     */
    MacierzRot3x3 macierzRot;
    
public:
    /*
     * @brief Inicjalizuje scene za pomocą zakresu wartości na osiach.
     */
    Scene(Wektor3D range);

    /**
     * @brief Odświeżenie obszaru roboczego programu gnuplot
     */
    void Draw();
    
    /**
     * @brief Dodanie nowej figury
     */
    void Add(std::string name);
    
    /**
     * @brief Usunięcie bryły z przestrzeni na podstawie jej numeru
     */
    void Remove(uint16_t);
    
    /**
     * @brief Zwracanie ilości figur w przestrzeni
     *
     * @return Rozmiar wektora, przechowującego wszystkie figury
     */
    std::size_t size() const { return figures.size(); }
    
    /**
     * @brief Operator dostępowy do macierzy rotacji
     */
    const MacierzRot3x3& operator()() const;
    
    /**
     * @brief Operator dostępowy do macierzy rotacji
     */
    MacierzRot3x3& operator()();
    
    /**
    * \brief Operator dostępowy do figur na scenie
    */
    const Figure& operator[](unsigned int n) const;
    
    /**
    * \brief Operator dostępowy do figur na scenie
    */
    Figure& operator[](unsigned int n);
    
    /**
     * @brief Destruktor
     *
     * Usuwa plik "temp.dat" który służy do komunikacji miedzy programem, a gnuplotem.
     */
    ~Scene()
    {
        system("rm -f temp.dat");
    }
};


#endif //SCENE_HPP
