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

        if(indice == 0 || indice == 2){
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
        }
        else if(indice == 1 || indice == 3){
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        }

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

void Luz::rotar(bool rota, char eje){

    if(rota)
        contador++;
    else
        contador = 0;

    if(eje == 'x'){
        glPushMatrix();
        glRotatef(8*contador, 1.0, 0.0, 0.0);
        glTranslatef(-1.0, 0.0, 0.0);
        glLightfv(GL_LIGHT3, GL_POSITION, luz_punto);
        glPopMatrix();
    }
    else if(eje == 'y'){
        glPushMatrix();
        glRotatef(8*contador, 0.0, 1.0, 0.0);
        glTranslatef(-1.0, 0.0, 0.0);
        glLightfv(GL_LIGHT1, GL_POSITION, luz_punto);
        glPopMatrix();
    }
    else if(eje == 'z'){
        glPushMatrix();
        glRotatef(8*contador, 0.0, 1.0, 0.0);
          glTranslatef(-1.0, 0.0, 0.0);
          glLightfv(GL_LIGHT1, GL_POSITION, luz_punto);
        glPopMatrix();
    }

}