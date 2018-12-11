//*************************************************************
//
// Clase Luz (práctica 4)
//
//*************************************************************
/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> ins;
typedef std::chrono::duration<float, std::ratio<1,1>> d_s;

class Luz{

  protected:
    GLenum indice;    //índice de la fuente de luz
    Tupla4f luz_punto;    //posición o vector de direccion de la luz
    Tupla4f c_ambiente;   //componente ambiental de la luz
    Tupla4f c_difusa;     //componente difusa de la luz
    Tupla4f c_especular;  //componente especular de la luz

    bool on;    //indica si la luz está activada
    ins ultima;
    int luces = 0;
    int contador = 0;

  public:

    Luz(GLenum indice, Tupla4f luz_punto, Tupla4f c_ambiente, Tupla4f c_difusa, Tupla4f c_especular);
    
    void activar();
    void rotar(bool rota, char eje);
};

#endif