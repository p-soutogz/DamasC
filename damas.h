// DAMAS.H

#ifndef DAMAS_H
#define DAMAS_H


#include <iostream>
#include <vector>
#include <conio.h>
#include "coordenadas.h"

class casilla
{
    //Estas van a ser las casillas del tablero 
public:
    std::string color; //El color va a ser banco negro y /(indeterminado)
    std::string tipo; //Van a ser damas o reinas(damas dobles) o estar vacia
    coordenadas posicion; //coordenadas dentro del tablero
    int estado; //El estado va a ser false por defecto y true si se selecciona con el cursor en la llamada a la funcion seleccionar

public:
    casilla(std::string c = "/", std::string t = " ", coordenadas p = coordenadas(), int e = 0)
    {
        color = c;
        tipo = t;
        posicion = p;
        estado = e;
    };

    void borrar();

    void coronar();

    void imprimir_datos();

    std::string rival(); //Funcion que te indica el color del bando rival
};

std::ostream& operator<<(std::ostream& os, const casilla& f);
//--------------------------------------------------------------------------------------------------------------------------------------------------
//-------Este es el grueso del codigo se define la clase damas que incluira todos los elementos y funciones necesarias para jugar a las damas-------
//--------------------------------------------------------------------------------------------------------------------------------------------------


class damas
{
public:

    std::vector<std::vector<casilla>> tablero;//El tablero de damas
    coordenadas pos;//Este va a ser el cursor de la funccion seleccionar
    bool turno; //true juegan blancas, false juegan negras
    std::string mensajes;//Voy a utilizar esta cariable para imprimir mensajes de error en el tablero
    bool retroceder;

public:

    damas()
    {
        //Inicializacion de las fichas, el cursor y el turno

        pos = coordenadas(5, 2);

        turno = true;

        retroceder = false;

        mensajes = "";

        tablero = std::vector<std::vector<casilla>>(8, std::vector<casilla>(8));

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                tablero[i][j] = casilla("/", " ", { i,j });
            }
        }

        int c = 1;

        for (int i = 0; i < 3; i++)
        {
            for (int j = c % 2; j < 8; j += 2)
            {
                tablero[i][j] = casilla("N", "D", { i,j });
            }
            c++;
        }

        for (int i = 5; i < 8; i++)
        {
            for (int j = c % 2; j < 8; j += 2)
            {
                tablero[i][j] = casilla("B", "D", { i,j });
            }
            c++;
        }
    }

    void borrar_mensaje() 
    {
        mensajes = "";
    }

    void imprimir_damas(); //Funcion que imprime la informacion de todas las casillas

    void imprimir_tablero();//Funcion que imprime el tablero de juego por consola 

    bool is_turno(coordenadas p); //Funcion que comprueba si es tu turno de juego

    std::vector<std::vector<coordenadas>> DR(coordenadas p);
    //Funcion que dada una ficha calcula todas las posiciones a las que se puede mover(DR[0]) y la posicion de todas la fichas que puede comer (DR[1])

    int victoria(); //Funcion que comprueba si algun bando a ganado

    void imprimir_destinos(coordenadas p);

    void imprimir_destinos2(coordenadas p);

    void borrar_destinos();

    bool es_valido(coordenadas p, coordenadas q); //Funcion que comprueba si un movimeiento es valido

    coordenadas seleccionar();//Funcion que permite seleccionar por pantalla la ficha que quieres mover y a donde la quieres mover

    void coronar();//Funcion que barre el tablero en busca de posibles damas que puedan coronar

    void mover_ficha();//Funcion basica de movimiento

    void comermas(coordenadas q);//Funcion auxiliar de movimiento que se llama solamente si se come una ficha rival

};

#endif