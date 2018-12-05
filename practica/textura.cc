/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#include "textura.h"
#include <string>

#include <GL/glut.h>

#include "CImg.h"
using namespace cimg_library;

using namespace std;

int Textura::texturasOn = 0;

Textura::Textura(const char * archivo){
    CImg<unsigned char> imagen;
    imagen.load(archivo);

    for(long y = 0; y < imagen.height(); y++){
        for(long x = 0; x < imagen.width(); x++){
            unsigned char * r = imagen.data(x, y, 0, 0);
            unsigned char * g = imagen.data(x, y, 0, 1);
            unsigned char * b = imagen.data(x, y, 0, 2);

            datos.push_back(*r);
            datos.push_back(*g);
            datos.push_back(*b);
        }
    }

    alto = imagen.height();
    ancho = imagen.width();

    coordenadas.push_back(Tupla2f(0.0, 1.0));
    coordenadas.push_back(Tupla2f(1.0, 1.0));
    coordenadas.push_back(Tupla2f(0.0, 0.0));
    coordenadas.push_back(Tupla2f(1.0, 0.0));
}

void Textura::activar(){

    glGenTextures(1, &id_textura);
    glBindTexture(GL_TEXTURE_2D, id_textura);

    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos.data());

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D,id_textura);
    glTexCoordPointer(2, GL_FLOAT, 0, coordenadas.data());
}