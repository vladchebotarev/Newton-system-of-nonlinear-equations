#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <iomanip>
/*
xy = 2
y/2 = sin(PI/4 - z)
x^2 + y^2+ z^2= 4
*/
double PI = 3.14157;

using namespace std;
const int il_iter = 1500;
const double tol = 0.0000000000001;

double funkcja1(double x, double y)
{
	return x*y - 2;
}
double funkcja2(double x, double y, double z)
{
	return y / 2.0 - sin(PI / 4 - z);
}
double funkcja3(double x, double y, double z)
{
	return x*x + y*y + z*z - 4;
}

double detReverse(double x, double y, double z)
{
	double t = cos(PI / 4 - z);
	return (double)(1.0 / (y*z + 2.0*t*x*x - x - 2.0*y*y*t));
}

double norma(double xn1[], double xn0[])
{
	double max = fabs(xn1[0] - xn0[0]);
	if (fabs(xn1[1] - xn0[1])>max)	max = fabs(xn1[1] - xn0[1]);
	if (fabs(xn1[2] - xn0[2])>max)	max = fabs(xn1[2] - xn0[2]);
	return max;
}

double dlugosc(double xn1[])
{
	return sqrt(funkcja1(xn1[0], xn1[1])*funkcja1(xn1[0], xn1[1]) + funkcja2(xn1[0], xn1[1], xn1[2])*funkcja2(xn1[0], xn1[1], xn1[2]) + funkcja3(xn1[0], xn1[1], xn1[2])*funkcja3(xn1[0], xn1[1], xn1[2]));
}

void oblicz()
{
	double xn0[3] = { 1.0, 1.0, -1.0 };
	double xn1[3] = { 0.0, 0.0, 0.0 };
	double Jakobiego[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
	double estn = 1.0;
	double reziduum = 1.0;

	cout << "  n |             x |             y |             z |" << endl;
	/*"     estymator|     |reziduum||   funkcja1(xn)|  funkcja2(yn) |  funkcja3(zn) |"*/
	for (int i = 0; i<il_iter; i++)
	{
		Jakobiego[0][0] = xn0[2] - 2.0*xn0[1] * cos(PI / 4.0 - xn0[2]);
		Jakobiego[0][1] = -2.0*xn0[0] * xn0[2];
		Jakobiego[0][2] = xn0[0] * cos(PI / 4.0 - xn0[2]);
		Jakobiego[1][0] = 2.0*xn0[0] * cos(PI / 4.0 - xn0[2]);
		Jakobiego[1][1] = 2.0*xn0[1] * xn0[2];
		Jakobiego[1][2] = -xn0[1] * cos(PI / 4.0 - xn0[2]);
		Jakobiego[2][0] = -xn0[0];
		Jakobiego[2][1] = 2.0*xn0[0] * xn0[0] - 2.0*xn0[1] * xn0[1];
		Jakobiego[2][2] = 0.5*xn0[1];

		xn1[0] = xn0[0] - (Jakobiego[0][0] * funkcja1(xn0[0], xn0[1]) + Jakobiego[0][1] * funkcja2(xn0[0], xn0[1], xn0[2]) + Jakobiego[0][2] * funkcja3(xn0[0], xn0[1], xn0[2]))*detReverse(xn0[0], xn0[1], xn0[2]); //biezace przyblizenie = poprzednie - [Jakobiego^d]^t * 1/det(Jakobiego) * funkcje od poprzednich przyblizen
		xn1[1] = xn0[1] - (Jakobiego[1][0] * funkcja1(xn0[0], xn0[1]) + Jakobiego[1][1] * funkcja2(xn0[0], xn0[1], xn0[2]) + Jakobiego[1][2] * funkcja3(xn0[0], xn0[1], xn0[2]))*detReverse(xn0[0], xn0[1], xn0[2]);
		xn1[2] = xn0[2] - (Jakobiego[2][0] * funkcja1(xn0[0], xn0[1]) + Jakobiego[2][1] * funkcja2(xn0[0], xn0[1], xn0[2]) + Jakobiego[2][2] * funkcja3(xn0[0], xn0[1], xn0[2]))*detReverse(xn0[0], xn0[1], xn0[2]);

		estn = norma(xn1, xn0);
		reziduum = dlugosc(xn0);


		cout << setw(4) << i << "|" << setw(15) << xn0[0] << "|" << setw(15) << xn0[1] << "|" << setw(15) << xn0[2]  << endl;
		/*<< "|" << setw(15) << estn << "|" << setw(15) <<
		reziduum << "|" << setw(15) << funkcja1(xn0[0], xn0[1]) << "|" << setw(15) << funkcja2(xn0[0], xn0[1], xn0[2]) << "|" << setw(15) <<
		funkcja3(xn0[0], xn0[1], xn0[2]) << "|"*/



		if (fabs(estn)<tol&&reziduum<tol) break;



		xn0[0] = xn1[0];
		xn0[1] = xn1[1];
		xn0[2] = xn1[2];
	}
	cout << "Przyblizone rozwiazanie: x = " << xn1[0] << "; y = " << xn1[1] << "; z = " << xn1[2] << ";" << endl;

}




int main()
{
	oblicz();
	system("pause");
	return 0;
}
