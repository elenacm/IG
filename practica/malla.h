// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################
/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"

// *****************************************************************************
// clase para objetos 3D (mallas indexadas)
// *****************************************************************************

enum ModoVis {Line = 0, Fill = 1, Point = 2, Chess = 3};

class ObjMallaIndexada{

   public:
     // dibuja el objeto en modo inmediato
     void draw_ModoInmediato(bool ajedrez);

     // dibuja el objeto en modo diferido (usando VBOs)
     void draw_ModoDiferido(bool ajedrez);

     // función que redibuja el objeto
     // está función llama a 'draw_MI' (modo inmediato)
     // o bien a 'draw_MD' (modo diferido, VBOs)
     void draw(bool ajedrez, int modo_dibujado) ;

     GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   protected:

     void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

     GLuint id_vbo_ver = 0,
            id_vbo_tri = 0,
            id_vbo_par = 0,
            id_vbo_impar = 0;
     std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
     std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

     std::vector<Tupla3i> triangulos_pares, triangulos_impares;

     // completar: tabla de colores, tabla de normales de vértices
     std::vector<Tupla3f> color, color_otro;

} ;

// *****************************************************************************
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 8 vertices y 6 caras)

class Cubo : public ObjMallaIndexada{

   public:
     Cubo();

};

class Tetraedro : public ObjMallaIndexada{

   public:
     Tetraedro();

};

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada{

   public:
      ObjPLY(const std::string & nombre_archivo);

};

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada{

   public:
     ObjRevolucion() {}
     ObjRevolucion(const std::string & nombre_ply_perfil, bool tapaArriba, bool tapaAbajo);

   protected:
     void crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool cono, bool esfera, bool tapaArriba, bool tapaAbajo);

} ;

//******************************************************************************
// Cilindro a partir de un objeto de revolucion

class Cilindro : public ObjRevolucion{

   public:
     Cilindro(const int num_vert_perfil, const int num_instancias_perf, bool tapaArriba, bool tapaAbajo);

};

//******************************************************************************
// Cono a partir de un objeto de revolucion

class Cono : public ObjRevolucion{

   public:
     Cono(const int num_vert_perfil, const int num_instancias_perf, bool tapaArriba, bool tapaAbajo);

};

//******************************************************************************
// Esfera a partir de un objeto de revolucion

class Esfera : public ObjRevolucion{

   public:
     Esfera(const int num_vert_perfil, const int num_instancias_perf, bool tapaArriba, bool tapaAbajo);

};

#endif
