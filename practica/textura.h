/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _TEXTURA_H
#define _TEXTURA_H

#include "aux.h"
#include <string>

typedef struct _Aux_RGBImage{
    GLint x, y;
    unsigned char * data;
} Aux_RGBImage;

class Textura{
    protected:
        static int texturasOn;
        GLuint id_textura;
        std::vector<Tupla2f> coordenadas;
        std::vector<unsigned char> datos;
        int ancho, alto;

    public:
        Textura(const char * archivo);
        void activar();
};

#endif