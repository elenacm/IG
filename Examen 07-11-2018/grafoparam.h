// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################
/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 5; //número de parámetros o grados de libertad
                                  //de este modelo

class GrafoParam{

   public:
     // crea mallas indexadas (nodos terminales del grafo)
     GrafoParam();

     // función principal de visualización
     void draw(const ModoVis p_modo_vis, const bool p_usar_diferido, bool flexo);

     // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
     void actualizarValorEfe(const unsigned iparam, const float valor_na);

     // devuelve el número de parámetros
     unsigned numParametros(){ return num_parametros; }

   private:

     //Cuerpo del Flexo
     void cuerpoFlexo(const float radioBase, const float altura, const int rotacionFija);
     //Base del Flexo
     void baseFlexo(const float radioBase, const float altura);
     //cono del flexo
     void conoFlexo(const float radioBase, const float altura, const int rotacionFija);

     // métodos de dibujo de subgrafos
     void columna(const float altura, const float ag_rotacion, const float radio_cil);

     // método para crear los brazos y piernas
     void extremidad(const float ag_rotacion, const float radioE, const float radioC, const float alturaC);

     // método para crear las orejas de la figura
     void oreja(const float traslacion, const float radioE, const float Tx, const float Ty, const float Tz);

     // método para crear la cabeza de la figura
     void cabeza(const float traslacion, const float radioE, const float radioC, const float alturaC);

     // método para crear el cuerpo de la figura
     void cuerpo(const float radioC, const float alturaC);

     // método para crear las esferas que servirán de articulación para la figura
     void articulacion(const float radioE);

     // objetos tipo malla indexada (nodos terminales)
     Cilindro * cilindro = nullptr;
     Cubo *     cubo     = nullptr;
     Esfera * esfera = nullptr;
     Cono * cono = nullptr;

     // parámetros de la llamada actual (o última) a 'draw'
     ModoVis modo_vis;      // modo de visualización
     bool    usar_diferido; // modo de envío (true -> diferido, false -> inmediato)
     bool Modo_vis;

     // valores efectivos de los parámetros (angulos, distancias, factores de
     // escala, etc.....) calculados a partir de los valores no acotados
     float altura_1,       // altura de la cabeza, cuello y orejas
           ag_rotacion_1,  // ángulo en grados de rotación (1)
           ag_rotacion_2,  // ángulo en grados de rotación (2)
           ag_rotacion_3,  // ángulo en grados de rotación (3)
           ag_rotacion_4;  // ángulo en grados de rotación (4)

};

#endif
