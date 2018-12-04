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

#include "luz.h"
#include "grafoparam.h"
#include <chrono>

Luz::Luz(GLenum indice, Tupla4f luz_punto, Tupla4f c_ambiente, Tupla4f c_difusa, Tupla4f c_especular){
    this->indice = indice;
    this->luz_punto = luz_punto;
    this->c_ambiente = c_ambiente;
    this->c_difusa = c_difusa;
    this->c_especular = c_especular;
    this->on = false;   
}

void Luz::activar(){

    on = !on;

    if(on){
        glEnable(indice);
        glEnable(GL_LIGHTING); 

        glLightfv(indice, GL_SPECULAR, c_especular);
        glLightfv(indice, GL_AMBIENT, c_ambiente);
        glLightfv(indice, GL_DIFFUSE, c_difusa);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glLightfv(indice, GL_POSITION, luz_punto);
        glPopMatrix();

        luces = luces + 1;
    }
    else{
        glDisable(indice);
        luces = luces - 1;
    }

    if(luces == 0)  glDisable(GL_LIGHTING);    
}

void Luz::animar(){
    using namespace std::chrono;
    ultima = steady_clock::now();
}

void Luz::rotar(float angulo){
    
    glPushMatrix();
      glTranslatef(angulo, 0.0, 0.0);
      
      Tupla4f pos_luz = {0.0, 0.0, 1.0, 1.0}; //luz posicional
      glLightfv(GL_LIGHT1, GL_POSITION, pos_luz);
     glPopMatrix();

}