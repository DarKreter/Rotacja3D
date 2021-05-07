#include "Scene.hpp"
#include <fstream>
#include <utility>

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

void Scene::Add(std::string name)
{
    figures.push_back(Figure(std::move(name)));
}

const Figure& Scene::operator[](unsigned int n) const
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    return figures[n];
}


Figure& Scene::operator[](unsigned int n)
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    return figures[n];
}

const MacierzRot3x3 & Scene::operator()() const
{
    return macierzRot;
}


MacierzRot3x3& Scene::operator()()
{
    return macierzRot;
}

void Scene::Remove(uint16_t n)
{
    if ( n >= size())
        throw std::out_of_range{"Figure out of range!"};
    
    figures.erase(figures.begin() + n);
}
