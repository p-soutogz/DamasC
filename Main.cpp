//main.cpp

#include <iostream>
#include <vector>
#include <conio.h>
#include "coordenadas.h"
#include "DAMAS.h"

using namespace std;


int main()
{
    damas t;

    vector<damas> historial;
   
    historial.push_back(t);

    int num_movimientos=1;

    t.imprimir_tablero();

    while (true)
    {
        if (t.victoria() == 1)
        {
            
            break;
        }
        if (t.victoria() == 2)
        {
           
            break;
        }
        
        t.mover_ficha();
        t.imprimir_tablero();

        //Aqui introduzco la opcion de retroceder tantas veces como quieras

        if (t.retroceder == true && num_movimientos>1)
        {
            t = historial[historial.size()-2];
            historial.pop_back();
            t.retroceder = false;
            num_movimientos--;
            continue;
            
        }

        num_movimientos++;

        historial.push_back(t);

    }

    t.imprimir_tablero();

    return 0;
}