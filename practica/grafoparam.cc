// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam(){

   cilindro = new Cilindro(4, 16, true, true);
   cubo     = new Cubo();
   esfera = new Esfera(50, 10, true, true);

}

// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe(const unsigned iparam, const float valor_na){

   assert(iparam < num_parametros);
   using namespace std;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5;

   switch(iparam){
     case 0:
        // ángulo en grados de rotacion 1 (pierna izquierda y brazo derecho)
        // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
        ag_rotacion_1 = 37.5*sin( 1.5*(2.0*M_PI*valor_na) );
     break;
     case 1:
       // ángulo en grados de rotacion 2 (pierna derecha y brazo izquierdo)
       // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
       ag_rotacion_2 = 37.5*-sin( 1.5*(2.0*M_PI*valor_na) );
     break;
     case 2:
       // angulo en grados de rotacion 3 (cabeza y cuello)
       // crece linealmente a 150 grados por segundo
       ag_rotacion_3 = 150.0*valor_na ;
     break ;
     case 3:
       // traslacion de cabeza y cuello
       // altura 1: oscila entre 0.7 y 1.3, a 0.9 oscilaciones por segundo
       altura_1 = 0.1*sin( 0.9*(2.0*M_PI*valor_na) );
     break ;
     case 4:
       // angulo en grados de rotacion 4 (cuerpo y brazos)
       // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
       ag_rotacion_4 = 37.5*sin( 1.5*(2.0*M_PI*valor_na) );
     break;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw(const ModoVis p_modo_vis, const bool p_usar_diferido){

   assert(esfera != nullptr);
   assert(cilindro != nullptr);

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)
   modo_vis      = p_modo_vis;
   usar_diferido = p_usar_diferido;

   Modo_vis = false;
   if(modo_vis == 3) Modo_vis = true;

   // dibujar objetos
   constexpr float
      sep       = 1.5,  // separación entre centros de las columnas
      radio_cil = 0.5 , // radio del cilindro más fino
      radio_cil2 = radio_cil+0.1 ; // radio del cilindro más grueso

   /*glPushMatrix();
      // primera columna
      glColor3f( 0.6, 0.2, 0.0 );
      columna( altura_1, ag_rotacion_1, radio_cil );
      // segunda columna
      glPushMatrix();
         glTranslatef( sep, 0.0, 0.0 );
         glColor3f( 0.0, 0.2, 0.6 );
         columna( altura_2, ag_rotacion_2, radio_cil2 );
      glPopMatrix();
      // base
      glColor3f( 0.1, 0.6, 0.1 );
      glTranslatef( -radio_cil2, -0.1*radio_cil2, -radio_cil2 );
      glScalef( sep+2.0*radio_cil2, 0.1*radio_cil2, 2.0*radio_cil2 );
      glTranslatef( 0.5, 0.5, 0.5 );
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();*/

   glPushMatrix();
     glTranslatef(0.0, 0.35, 0.0);
      glPushMatrix();
        glRotatef(ag_rotacion_3, 0.0, 1.0, 0.0);
        glTranslatef(0.0, -0.7, 0.0);
        //cabeza
        glTranslatef(0.0, 0.7, 0.0);
        cabeza(altura_1, 0.2, 0.1, 0.5);
      glPopMatrix();
      //cuerpo + piernas + brazos
      glPushMatrix();
        //glTranslatef(0.0, 0.5, 0.0);
        //cuerpo + piernas
        glPushMatrix();
          glRotatef(ag_rotacion_4, 0.0, 1.0, 0.0);
          cuerpo(-0.3, 0.7);
          //brazo derecho
          glPushMatrix();
            glTranslatef(0.25, 0.0, 0.0);
            glRotatef(45, 0.0, 0.0, 1.0);
            glTranslatef(0.0, -0.2, 0.0);
            articulacion(0.075);
            extremidad(ag_rotacion_1, 0.075, 0.075, 0.3);
          glPopMatrix();
          //brazo izquierdo
          glPushMatrix();
            glTranslatef(-0.25, 0.0, 0.0);
            glRotatef(-45, 0.0, 0.0, 1.0);
            glTranslatef(0.0, -0.2, 0.0);
            articulacion(0.075);
            extremidad(ag_rotacion_2, 0.075, 0.075, 0.3);
          glPopMatrix();
        glPopMatrix();
        //pierna izquierda
        glPushMatrix();
          glTranslatef(-0.2, -0.85, 0.0);
          articulacion(0.075);
          extremidad(ag_rotacion_1, 0.075, 0.075, 0.3);
        glPopMatrix();
        //pierna derecha
        glPushMatrix();
          glTranslatef(0.2, -0.85, 0.0);
          articulacion(0.075);
          extremidad(ag_rotacion_2, 0.075, 0.075, 0.3);
        glPopMatrix();
      glPopMatrix();
   glPopMatrix();

}

//-----------------------------------------------------------
//dibuja un sub-objeto parametrizado
//es un pie/mano (esfera) de radio radioE, con un cilindro encima
//de altura alturaC y radio radioC

void GrafoParam::extremidad(const float ag_rotacion, const float radioE, const float radioC, const float alturaC){

  glRotatef(ag_rotacion, 1.0, 0.0, 0.0);
  glTranslatef(0.0, -alturaC, 0.0);
  glPushMatrix();
    glScalef(radioC, alturaC, radioC);
    cilindro->draw(Modo_vis, usar_diferido);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0.0, -radioE, 0.0);
    glScalef(radioE, radioE, radioE);
    esfera->draw(Modo_vis, usar_diferido);
  glPopMatrix();


}

//-----------------------------------------------------------
//dibuja un sub-objeto parametrizado

void GrafoParam::oreja(const float traslacion, const float radioE, const float Tx, const float Ty, const float Tz){

  glPushMatrix();
    glTranslatef(Tx, Ty+traslacion, Tz);
    glTranslatef(0.0, radioE, 0.0);
    glScalef(radioE, radioE, radioE);
    esfera->draw(Modo_vis, usar_diferido);
  glPopMatrix();

}

//-----------------------------------------------------------
//dibuja un sub-objeto parametrizado

void GrafoParam::cabeza(const float traslacion, const float radioE, const float radioC, const float alturaC){

  glPushMatrix();
    glTranslatef(0.0, -alturaC*0.7 + traslacion, 0.0);
    glScalef(radioC, alturaC, radioC);
    cilindro->draw(Modo_vis, usar_diferido);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0.0, -radioE+alturaC-0.05 + traslacion, 0.0);
    glScalef(radioE, radioE, radioE);
    esfera->draw(Modo_vis, usar_diferido);
  glPopMatrix();
  //oreja izquierda
  oreja(traslacion, 0.09, -0.15, radioE+0.1, 0.0);
  //oreja derecha
  oreja(traslacion, 0.09, 0.15, radioE+0.1, 0.0);

}

//-----------------------------------------------------------
//dibuja un sub-objeto parametrizado

void GrafoParam::cuerpo(const float radioC, const float alturaC){

  glPushMatrix();
    glTranslatef(0.0, -alturaC, 0.0);
    glScalef(radioC, alturaC, radioC);
    cilindro->draw(Modo_vis, usar_diferido);
  glPopMatrix();

}

//-----------------------------------------------------------
//dibuja un sub-objeto parametrizado

void GrafoParam::articulacion(const float radioE){

  glPushMatrix();
    glTranslatef(0.0, radioE, 0.0);
    glScalef(radioE, radioE, radioE);
    esfera->draw(Modo_vis, usar_diferido);
  glPopMatrix();

}

// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es una columna (cilindro) de altura = 'altura', con un cubo encima,
// rotado entorno a Y un ángulo en grados = 'ag_rotacion'

void GrafoParam::columna(const float altura, const float ag_rotacion, const float radio_cil){

   glPushMatrix();
      glScalef( radio_cil, altura, radio_cil );
      cilindro->draw( modo_vis, usar_diferido );
   glPopMatrix();
   glPushMatrix( );
      glTranslatef( 0.0, 0.5+altura, 0.0 );
      glRotatef( ag_rotacion, 0.0, 1.0, 0.0 );
      cubo->draw( modo_vis, usar_diferido );
   glPopMatrix();

}
