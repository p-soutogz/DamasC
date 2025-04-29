#ifndef COORDENADAS_H
#define COORDENADAS_H

#include <iostream>

struct coordenadas
{
    int x;
    int y;
    coordenadas(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    }
};

coordenadas operator+(coordenadas p, coordenadas q);

coordenadas operator*(int i, coordenadas q);

bool operator==(coordenadas p, coordenadas q);

std::ostream& operator<<(std::ostream& os, const coordenadas& p);

bool goodposicion(coordenadas p);


#endif // COORDENADAS_H
