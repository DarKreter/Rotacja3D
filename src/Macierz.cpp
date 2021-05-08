#include <Macierz.hpp>

/**
 * Specjalizacja zdefiniowana dla wartości parametru szablonowego równego 2.
 *
 * @param kat - kąt o który będziemy obracać
 * @param o - oś układu współrzędnych wokół której chcemy wykonywać obrót
 */
template<>
MacierzRot<2>::MacierzRot(double kat, Axis o)
{
	tab[0][0] = cos(kat * M_PI / 180);
	tab[0][1] = -sin(kat * M_PI / 180);
	tab[1][0] = sin(kat * M_PI / 180);
	tab[1][1] = cos(kat * M_PI / 180);
}

/**
 * Specjalizacja zdefiniowana dla wartości parametru szablonowego równego 3.
 *
 * @param kat - kąt o który będziemy obracać
 * @param o - oś układu współrzędnych wokół której chcemy wykonywać obrót
 */
template<>
MacierzRot<3>::MacierzRot(double alpha, Axis o)
{
	double radians = alpha * M_PI / 180;
	switch (o)
	{
	case Axis::OZ:
		tab[0][0] = cos(radians);
		tab[0][1] = -sin(radians);
		tab[1][0] = sin(radians);
		tab[1][1] = cos(radians);
		tab[2][2] = 1;
		tab[2][0] = tab[2][1] = tab[0][2] = tab[1][2] = 0;
		break;

	case Axis::OY:
		tab[0][0] = cos(radians);
		tab[2][0] = -sin(radians);
		tab[0][2] = sin(radians);
		tab[2][2] = cos(radians);
		tab[1][1] = 1;
		tab[1][0] = tab[0][1] = tab[1][2] = tab[2][1] = 0;
		break;

	case Axis::OX:
		tab[1][1] = cos(radians);
		tab[1][2] = -sin(radians);
		tab[2][1] = sin(radians);
		tab[2][2] = cos(radians);
		tab[0][0] = 1;
		tab[1][0] = tab[0][1] = tab[0][2] = tab[2][0] = 0;
		break;
	}

}
