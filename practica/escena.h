/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"

class Escena{

   private:
     Ejes ejes;

     // variables que definen la posicion de la camara en coordenadas polares
     GLfloat Observer_distance;
     GLfloat Observer_angle_x;
     GLfloat Observer_angle_y;

     // variables que controlan la ventana y la transformacion de perspectiva
     GLfloat Width, Height, Front_plane, Back_plane;

     void clear_window();
	   void dibujar_objeto_actual();

     // Transformación de cámara
	   void change_projection(const float ratio_xy);
	   void change_observer();

     void conmutarAcciones();

     bool animacion = false;

     int objeto_actual = 0, // objeto actual (el que se visualiza)
         num_objetos = 0,   // número de objetos (actualizado al crear los objetos en el constructor)
         num_modos = 0,     //número de modos (actualizado al crear los objetos en el constructor)
         modo_actual = 0;   //modo actual

     int modo_dibujado = 0;

     // Objetos de la escena
     Cubo * cubo = nullptr; // es importante inicializarlo a 'nullptr'
     Tetraedro * tetraedro = nullptr;

     //Ejercicio 1
     Piramide * piramide = nullptr;

     ObjRevolucion * objetoRev = nullptr;
     ObjRevolucion * cono = nullptr;
     ObjRevolucion * cilindro = nullptr;
     ObjRevolucion * esfera = nullptr;
     ObjPLY * objetoPLY = nullptr;

     //Ejercicio 2
     ObjetoBarrido * objetoBarrido = nullptr;

     ObjJerarquico * objJerarquico = nullptr;

     //Ejercicio 3
     ObjJerarquico * objJerarquico1 = nullptr;

   public:

     Escena();
  	 void inicializar( int UI_window_width, int UI_window_height );
  	 void redimensionar( int Width, int Height ) ;

  	 // Dibujar
  	 void dibujar() ;

  	 // Interacción con la escena
  	 bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
  	 void teclaEspecial( int Tecla1, int x, int y );

     void mgeDesocupado();

};
#endif
