//DAMAS.cpp

#include <iostream>
#include <vector>
#include <conio.h>
#include "coordenadas.h"
#include "damas.h"

void casilla::borrar()
{
    //Funcion que borra una casilla 
    color = "/";
    tipo = " ";
}

void casilla::coronar()
{
    //Funcion que combierte una dama en una reina
    tipo = "R";
}

void casilla::imprimir_datos()
{
    std::cout << "Color: " << color << std::endl;
    std::cout << "Tipo: " << tipo << std::endl;
    std::cout << "Posicion: " << posicion << std::endl;
    std::cout << "Estado: " << estado << std::endl;
}

std::string casilla::rival()
{
    std::string c;
    if (color == "N")
    {
        c = "B";
    }
    if (color == "B")
    {
        c = "N";
    }
    return c;

}

std::ostream& operator<<(std::ostream& os, const casilla& f) {

    std::string red = "\033[31m";
    std::string blue = "\033[34m";
    std::string gold = "\033[38;5;220m";
    std::string reset = "\033[0m";

    if (f.tipo == "D" && f.color == "N" && f.estado == 0) {
        os << red << f.tipo << reset;
        return os;
    }

    if (f.tipo == "D" && f.color == "B" && f.estado == 0) {
        os << blue << f.tipo << reset;
        return os;
    }

    if (f.tipo == "R" && f.color == "N" && f.estado == 0) {
        os << red << f.tipo << reset;
        return os;
    }

    if (f.tipo == "R" && f.color == "B" && f.estado == 0) {
        os << blue << f.tipo << reset;
        return os;
    }

    if (f.tipo == " " && f.estado == 0) {
        os << f.tipo << reset;
        return os;
    }

    if ((f.tipo == "D" || f.tipo == "R") && f.estado == 1)
    {
        os << f.tipo << reset;
        return os;
    }

    if (f.tipo == " " && f.estado == 1)
    {
        os << "_" << reset;
        return os;
    }
    if (f.tipo == "*" && f.estado == 0)
    {
        os << "*" << reset;
        return os;
    }
    if (f.tipo == "*" && f.estado == 1)
    {
        os <<gold<< "*" << reset;
        return os;
    }

    return os;

}

//--------------------------------------------------------------------------------------------------------------------------------------------------
//-------Este es el grueso del codigo se define la clase damas que incluira todos los elementos y funciones necesarias para jugar a las damas-------
//--------------------------------------------------------------------------------------------------------------------------------------------------

void damas::imprimir_damas() //Funcion que imprime la informacion de todas las casillas
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tablero[i][j].imprimir_datos();
        }
    }
}

void damas::imprimir_tablero()
{

    system("cls");

    std::cout << mensajes << std::endl;

    if (turno)
    {
        std::cout << "Juegan blancas" << std::endl;
    }
    else {
        std::cout << "Juegan negras" << std::endl;
    }

    std::cout << "   ";
    for (int i = 0; i < 8; ++i) {
        std::cout << " " << i + 1 << "  ";
    }
    std::cout << '\n';

    std::cout << "  +";
    for (int i = 0; i < 8; ++i) {
        std::cout << "---+";
    }
    std::cout << '\n';

    for (int i = 0; i < 8; ++i) {
        std::cout << 8 - i << " |";
        for (int j = 0; j < 8; ++j) {
            std::cout << " " << tablero[i][j] << " |";
        }
        std::cout << " " << 8 - i << '\n';

        std::cout << "  +";
        for (int k = 0; k < 8; ++k) {
            std::cout << "---+";
        }
        std::cout << '\n';
    }

    std::cout << "   ";
    for (int i = 0; i < 8; ++i) {
        std::cout << " " << i + 1 << "  ";
    }
    std::cout << '\n';
}

bool damas::is_turno(coordenadas p)
{
    if (tablero[p.x][p.y].color == "B" && turno)
    {
        return true;
    }
    if (tablero[p.x][p.y].color == "N" && !turno)
    {
        return true;
    }

    return false;
}

std::vector<std::vector<coordenadas>> damas::DR(coordenadas p)
{
    std::vector<std::vector<coordenadas>> DR;
    std::vector<coordenadas> destinos;
    std::vector<coordenadas> rivales;
    casilla ficha = tablero[p.x][p.y];
    std::string color1 = ficha.color;
    std::string color2 = ficha.rival();


    std::string tipo = ficha.tipo;
    //Distinguimos entre damas y reinas
    if (tipo == "D")
    {
        //Como las damas solo se mueven en diagonal barremos las diagonales buscando posibles destinos,
        coordenadas d(1, 1);
        coordenadas q = p + d;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
        {
            destinos.push_back(q);
        }
        //-------------------------------------------------------------------------------------------
        d = coordenadas(1, -1);
        q = p + d;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
        {
            destinos.push_back(q);
        }
        //-------------------------------------------------------------------------------------------
        d = coordenadas(-1, 1);
        q = p + d;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
        {
            destinos.push_back(q);
        }
        //-------------------------------------------------------------------------------------------
        d = coordenadas(-1, -1);
        q = p + d;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
        {
            destinos.push_back(q);
        }
        //-------------------------------------------------------------------------------------------

        // Vamos a implementar ahora la posibilidad de poder saltar sobre una ficha rival

        d = coordenadas(2, 2);
        coordenadas d1(1, 1);
        q = p + d;
        coordenadas q1 = p + d1;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " " && tablero[q1.x][q1.y].color == color2)
        {
            destinos.push_back(q);
            rivales.push_back(q1);
        }

        //-------------------------------------------------------------------------------------------

        d = coordenadas(2, -2);
        d1 = coordenadas(1, -1);
        q = p + d;
        q1 = p + d1;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " " && tablero[q1.x][q1.y].color == color2)
        {
            destinos.push_back(q);
            rivales.push_back(q1);
        }

        //-------------------------------------------------------------------------------------------

        d = coordenadas(-2, 2);
        d1 = coordenadas(-1, 1);
        q = p + d;
        q1 = p + d1;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " " && tablero[q1.x][q1.y].color == color2)
        {
            destinos.push_back(q);
            rivales.push_back(q1);
        }

        //-------------------------------------------------------------------------------------------

        d = coordenadas(-2, -2);
        d1 = coordenadas(-1, -1);
        q = p + d;
        q1 = p + d1;
        if (goodposicion(q) && tablero[q.x][q.y].tipo == " " && tablero[q1.x][q1.y].color == color2)
        {
            destinos.push_back(q);
            rivales.push_back(q1);
        }

        //-------------------------------------------------------------------------------------------

    }
    // Ahora vamos con el caso de que sea una reina, estas se pueden mover en doda la diagonal

    if (tipo == "R")
    {

        coordenadas d(1, 1);
        coordenadas q;
        for (int i = 1; i <= 7; i++)
        {
            q = p + i * d;

            if (goodposicion(q) && tablero[q.x][q.y].color == color1)
            {
                break; //No puedes pasar sobre tus propias fichas
            }

            if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
            {
                destinos.push_back(q);

                if (tablero[q.x - d.x][q.y - d.y].color == color2)
                {
                    rivales.push_back(coordenadas(q.x - d.x, q.y - d.y));
                }

            }
        }
        //----------------------------------------------------------------------------------------

        d = coordenadas(1, -1);

        for (int i = 1; i <= 7; i++)
        {
            q = p + i * d;

            if (goodposicion(q) && tablero[q.x][q.y].color == color1)
            {
                break; //No puedes pasar sobre tus propias fichas
            }

            if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
            {
                destinos.push_back(q);

                if (tablero[q.x - d.x][q.y - d.y].color == color2)
                {
                    rivales.push_back(coordenadas(q.x - d.x, q.y - d.y));
                }
            }
        }

        //----------------------------------------------------------------------------------------

        d = coordenadas(-1, 1);

        for (int i = 1; i <= 7; i++)
        {
            q = p + i * d;

            if (goodposicion(q) && tablero[q.x][q.y].color == color1)
            {
                break; //No puedes pasar sobre tus propias fichas
            }

            if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
            {
                
                destinos.push_back(q);

                if (tablero[q.x - d.x][q.y - d.y].color == color2)
                {
                    rivales.push_back(coordenadas(q.x - d.x, q.y - d.y));
                }
            }
        }
        //----------------------------------------------------------------------------------------

        d = coordenadas(-1, -1);

        for (int i = 1; i <= 7; i++)
        {
            q = p + i * d;

            if (goodposicion(q) && tablero[q.x][q.y].color == color1)
            {
                break; //No puedes pasar sobre tus propias fichas
            }

            if (goodposicion(q) && tablero[q.x][q.y].tipo == " ")
            {
                destinos.push_back(q);

                if (tablero[q.x - d.x][q.y - d.y].color == color2)
                {
                    rivales.push_back(coordenadas(q.x - d.x, q.y - d.y));
                }
            }

        }

    }


    DR = { destinos,rivales };
    return DR;

}

int damas::victoria()
{
    //0 si no ha ganado ningun bando 1 si han ganado blancas, 2 si han ganado negras
    //Hay dos formas de perder o te quedas sin fichas o tus fichas no tiene movimientos validos
    //Primero veamos si estamos sin fichas
    int contador_blancas = 0;
    int contador_negras = 0;
    std::vector<coordenadas> blancas, negras;

    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            if (tablero[i][j].color == "N")
            {
                contador_negras++;
                negras.push_back(coordenadas(i, j));
            }
            if (tablero[i][j].color == "B")
            {
                contador_blancas++;
                blancas.push_back(coordenadas(i, j));
            }
        }
    }
    if (contador_blancas == 0)
    {
        mensajes = "Ganan negras";
        return 2;
    }
    if (contador_negras == 0)
    {
        mensajes = "Ganan blancas";
        return 1;
    }

    //Vamos a ver si algun bando se ha quedado sin movimientos

    bool blancas_ahogadas = 0;
    bool negras_ahogadas = 0;

    for (int i = 0; i < blancas.size(); i++)
    {
        if (DR(blancas[i])[0].size() != 0)
        {
            break;
        }

        if (i == (blancas.size() - 1))
        {
            blancas_ahogadas = 1;
        }
    }
    for (int i = 0; i < negras.size(); i++)
    {
        if (DR(negras[i])[0].size() != 0)
        {
            break;
        }

        if (i == (negras.size() - 1))
        {
            negras_ahogadas = 1;
        }
    }

    if (negras_ahogadas)
    {
        mensajes = "Ganan blancas";
        return 1;
    }

    if (blancas_ahogadas)
    {
        mensajes = "Ganan negras";
        return 2;
    }

    return 0;

}

bool damas::es_valido(coordenadas p, coordenadas q)
{
    std::vector<coordenadas> d = DR(p)[0];
    int n = d.size();
    for (int i = 0; i < n; i++)
    {
        if (q == d[i])
        {
            return true;
        }
    }

    return false;
}

void damas::imprimir_destinos(coordenadas p) {

    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            coordenadas q(i, j);
            if (es_valido(p, q))
            {
                tablero[i][j].tipo = "*";
            }
        }
    }


}

void damas::imprimir_destinos2(coordenadas p) {

    coordenadas d,aux;

    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            coordenadas q(i, j);
            bool comiste = false;
            if (es_valido(p, q))
            {
                int m = abs(q.x - p.x);
                d = coordenadas((q.x - p.x)/m, (q.y - p.y)/m);
                
                for (int k = 1; k <= m; k++)
                {
                    aux = p + k * d;
                    if (tablero[aux.x][aux.y].tipo != " ")
                    {
                        comiste=true;
                    }
                }

                if (comiste)
                {
                    tablero[i][j].tipo = "*";
                }
            }
        }
    }


}

void damas::borrar_destinos()
{
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            if(tablero[i][j].tipo == "*")
            {
                tablero[i][j].borrar();
            }
        }
    }
}

coordenadas damas::seleccionar()
{
    tablero[pos.x][pos.y].estado = 1;
    char puntero;
    std::cout << "Muevete con  las letras wasd" << '\n';
    while (true)
    {
        imprimir_tablero();
        tablero[pos.x][pos.y].estado = 0;
        puntero = _getch();

        if (puntero == 13)
        {
            tablero[pos.x][pos.y].estado = 0;
            return pos;
        }

        if (puntero == 'r')
        {
            tablero[pos.x][pos.y].estado = 0;
            return coordenadas(9,9);//Esta coordenada no deberia existir es solo para dar una señal
        }

        if (puntero == 'w')
        {
            if (pos.x > 0)
            {
                pos.x--;
            }

        }
        if (puntero == 's')
        {
            if (pos.x < 7)
            {
                pos.x++;
            }

        }
        if (puntero == 'a')
        {
            if (pos.y > 0)
            {
                pos.y--;
            }

        }
        if (puntero == 'd')
        {
            if (pos.y < 7)
            {
                pos.y++;
            }

        }

        tablero[pos.x][pos.y].estado = 1;

    }

    return { 0,0 };
}

void damas::coronar()
{
    for (int i = 0; i <= 7; i++)
    {
        if (tablero[0][i].color == "B" && tablero[0][i].tipo == "D")
        {
            tablero[0][i].coronar();
        }
        if (tablero[7][i].color == "N" && tablero[7][i].tipo == "D")
        {
            tablero[7][i].coronar();
        }
    }

}

void damas::mover_ficha()
{
    coordenadas p;
    coordenadas q;
    casilla aux;
    coordenadas daux;
    bool ok1 = 0;

    while (!ok1)
    {
        p = seleccionar();
        if (p == coordenadas (9,9))
        {
            retroceder = true;

            return;
        }
        if (is_turno(p))
        {
            borrar_mensaje();
        }
        if (!is_turno(p))
        {
            mensajes = "No es tu turno";
            continue;
        }
        imprimir_destinos(p);
        q = seleccionar();
        borrar_destinos();
        ok1 = es_valido(p, q);
        if (!ok1)
        {
            mensajes = "Ahi no te puedes mover";
        }


    }

    aux = tablero[p.x][p.y];
    tablero[p.x][p.y].borrar();
    tablero[q.x][q.y] = aux;

    //Ahora vamos a eliminar todas las fichas sobre las que hayamos saltado
    bool e = false;
    int m = abs(q.x - p.x);
    coordenadas d((q.x - p.x) / m, (q.y - p.y) / m);
    for (int i = 1; i < m; i++)
    {
        daux = p + i * d;
        if (tablero[daux.x][daux.y].tipo != " ")
        {
            e = true;
        }
        tablero[daux.x][daux.y].borrar();
    }

    std::vector<coordenadas> rivales = DR(q)[1];
    int l = rivales.size();
    for (int i = 0; i < l; i++)
    {
        std::cout << rivales[i] << std::endl;
    }

    coronar();

    if (e)
    {
        borrar_mensaje(); //Si hemos entrado aquí es que se ha realizado bien un movimiento
        comermas(q);
    }

    borrar_mensaje(); //Si hemos llegado aquí es que se ha realizado bien un movimiento

    turno = !turno;

}

void damas::comermas(coordenadas p)
{
    imprimir_tablero();

    std::vector<coordenadas> rivales = DR(p)[1];

    if (rivales.size() == 0) //No puedes comer mas fichas
    {
        return;
    }
    coordenadas q;
    casilla aux;
    coordenadas daux;
    bool e;
    bool ok1 = false;
    bool ok2 = false;
    while (!ok1 || !ok2)
    {
        imprimir_destinos2(p);
        q = seleccionar();
        borrar_destinos();

        ok1 = es_valido(p, q);
        if (!ok1)
        {
            mensajes = "Ahi no te puedes mover";
            continue;
        }

        int m = abs(q.x - p.x);
        coordenadas d((q.x - p.x) / m, (q.y - p.y) / m);
        for (int i = 1; i <= m; i++)
        {
            daux = p + i * d;
            if (tablero[daux.x][daux.y].tipo!=" ")
            {
                ok2 = true;
            }
        }
        if (!ok2)
        {
            mensajes = "Ahi no te puedes mover";
        }
    }

    aux = tablero[p.x][p.y];
    tablero[p.x][p.y].borrar();
    tablero[q.x][q.y] = aux;
    int m = abs(q.x - p.x);
    coordenadas d((q.x - p.x) / m, (q.y - p.y) / m);

    for (int i = 1; i < m; i++)
    {
        daux = p + i * d;
        tablero[daux.x][daux.y].borrar();
    }

    coronar();

    borrar_mensaje();

    comermas(q);

}

