#include "Macierz3x3.hpp"

template<>
MacierzRot<2>::MacierzRot(double kat, OS o)
{
	tab[0][0] = cos(kat * M_PI / 180);
	tab[0][1] = -sin(kat * M_PI / 180);
	tab[1][0] = sin(kat * M_PI / 180);
	tab[1][1] = cos(kat * M_PI / 180);
}

template<>
MacierzRot<3>::MacierzRot(double alpha, OS o)
{
	double radians = alpha * M_PI / 180;
	switch (o)
	{
	case OS::OX:
		tab[0][0] = cos(radians);
		tab[0][1] = -sin(radians);
		tab[1][0] = sin(radians);
		tab[1][1] = cos(radians);
		tab[2][2] = 1;
		tab[2][0] = tab[2][1] = tab[0][2] = tab[1][2] = 0;
		break;

	case OS::OY:
		tab[0][0] = cos(radians);
		tab[2][0] = -sin(radians);
		tab[0][2] = sin(radians);
		tab[2][2] = cos(radians);
		tab[1][1] = 1;
		tab[1][0] = tab[0][1] = tab[1][2] = tab[2][1] = 0;
		break;

	case OS::OZ:
		tab[1][1] = cos(radians);
		tab[1][2] = -sin(radians);
		tab[2][1] = sin(radians);
		tab[2][2] = cos(radians);
		tab[0][0] = 1;
		tab[1][0] = tab[0][1] = tab[0][2] = tab[2][0] = 0;
		break;
	}

}
