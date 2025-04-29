#include <iostream>
#include "coordenadas.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------
//-------Esta parte del codigo esta orientada a facilitar el manejo de las coordenadas dentro del tablero--------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------


coordenadas operator+(coordenadas p, coordenadas q)
{
    coordenadas s;
    s.x = p.x + q.x;
    s.y = p.y + q.y;

    return s;
}

coordenadas operator*(int i, coordenadas q)
{
    //Multiplicacion de una coordenada por un escalar
    coordenadas s;
    s.x = i * q.x;
    s.y = i * q.y;

    return s;
}

bool operator==(coordenadas p, coordenadas q)
{
    if (p.x == q.x && p.y == q.y)
    {
        return true;
    }

    return false;

}

std::ostream& operator<<(std::ostream& os, const coordenadas& p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

bool goodposicion(coordenadas p)
{
    //Controlo que la coordenada no se salga del tablero

    if (p.x >= 0 && p.x <= 7 && p.y >= 0 && p.y <= 7)
    {
        return true;
    }
    return false;
}