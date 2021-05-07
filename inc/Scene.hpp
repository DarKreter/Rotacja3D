#ifndef SCENE_HPP
#define SCENE_HPP
#include <Figure.hpp>
#include <gnuplot.hpp>
#include <vector>


class Scene
{
    std::vector<Figure> figures;
    PzG::LaczeDoGNUPlota lacze;
    MacierzRot3x3 macierzRot;
    
public:
    Scene(Wektor3D range);

    void Draw();
    void Add(std::string name);
    void Remove(uint16_t);
    std::size_t size() const { return figures.size(); }
    
    const MacierzRot3x3& operator()() const;
    MacierzRot3x3& operator()();
    
    const Figure& operator[](unsigned int n) const;
    Figure& operator[](unsigned int n);
    
    ~Scene()
    {
        system("rm -f temp.dat");
    }
};


#endif //SCENE_HPP
