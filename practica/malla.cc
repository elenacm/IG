/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"
#include <math.h>

// *****************************************************************************
// Clase ObjMallaIndexada
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato(bool ajedrez){

  glEnableClientState(GL_VERTEX_ARRAY); //habilitar uso de un array de vértices
  glEnableClientState(GL_COLOR_ARRAY);  //habilitar uso de un array de colores

  glColorPointer(3, GL_FLOAT, 0, color.data()); //Establecer el color inicial
  glVertexPointer(3, GL_FLOAT, 0, vertices.data()); //Establecer los vértices

  //Dibujar los triangulos_pares de la figura
  glDrawElements(GL_TRIANGLES, triangulos_pares.size()*3, GL_UNSIGNED_INT, triangulos_pares.data());

  if(ajedrez){ glColorPointer(3, GL_FLOAT, 0, color_otro.data()); } //Establecer otro color

  //Dibujar los triangulos_impares
  glDrawElements(GL_TRIANGLES, triangulos_impares.size()*3, GL_UNSIGNED_INT, triangulos_impares.data());

  glDisableClientState(GL_COLOR_ARRAY);   //deshabilitar array de colores
  glDisableClientState(GL_VERTEX_ARRAY);  //deshabilitar array de vértices

}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(bool ajedrez){

  glEnableClientState( GL_VERTEX_ARRAY ); //habilitar uso de un array de vértices

  if(id_vbo_ver == 0)
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, sizeof(float)*3*vertices.size(), vertices.data());

  glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activar VBO de vértices
  glVertexPointer(3, GL_FLOAT, 0, 0); // especifica formato y offset (=0)
  glBindBuffer(GL_ARRAY_BUFFER, 0); // desactivar VBO de vértices.

  glEnableClientState(GL_COLOR_ARRAY); //habilitar uso de un array de colores

  if(id_vbo_par == 0)
    id_vbo_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*3*triangulos_pares.size(), triangulos_pares.data());

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_par); // activar VBO de triángulos
  glColorPointer(3, GL_FLOAT, 0, color.data()); //Establecer un color inicial
  glDrawElements(GL_TRIANGLES, triangulos_pares.size()*3, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  if(id_vbo_impar == 0)
    id_vbo_impar = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*3*triangulos_impares.size(), triangulos_impares.data());

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_impar);// activar VBO de triángulos

  if(ajedrez){ glColorPointer(3, GL_FLOAT, 0, color_otro.data()); }

  glDrawElements(GL_TRIANGLES, triangulos_impares.size()*3, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

}

GLuint ObjMallaIndexada::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){

  GLuint id_vbo;
  // resultado: identificador de VBO
  glGenBuffers(1, & id_vbo);
  // crear nuevo VBO, obtener identificador (nunca 0)
  glBindBuffer(tipo_vbo, id_vbo); // activar el VBO usando su identificador

  // esta instrucción hace la transferencia de datos desde RAM hacia GPU
  glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW); // desactivación del VBO (activar 0)
  glBindBuffer(tipo_vbo, 0); // devolver el identificador resultado
  return id_vbo;

}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(bool ajedrez, int modo_dibujado){

   if(modo_dibujado == 0) draw_ModoInmediato(ajedrez);
   else draw_ModoDiferido(ajedrez);

}

// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales(){

   // completar .....(práctica 2)

}

// *****************************************************************************
// Clase Cubo (práctica 1)
// *****************************************************************************

Cubo::Cubo(){

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;

   for(int i = 0; i < triangulos.size(); i++){
     if(i%2)
       triangulos_pares.push_back(triangulos[i]);
     else
       triangulos_impares.push_back(triangulos[i]);
   }

   for(int i = 0; i < vertices.size(); i++){
     color.push_back({0.0, 0.0, 0.0});
     color_otro.push_back({0.9, 0.0, 1.0});
   }

 }

// *****************************************************************************
// Clase Tetraedro (práctica 1)
// *****************************************************************************

Tetraedro::Tetraedro(){

  //inicializamos la tabla de vértices
  vertices = { {1.0, 0.0, 0.0},   //0
               {-1.0, 0.0, 0.0},  //1
               {0.0, 0.0, 1.0},   //2
               {0.0, 1.0, 0.0}    //3
             };

  //Inicializamos la tabla de caras(triángulos)
  triangulos = { {0,2,1}, {0,1,3}, {1,2,3}, {0,3,2} };

  for(int i = 0; i < triangulos.size(); i++){
    if(i%2)
      triangulos_pares.push_back(triangulos[i]);
    else
      triangulos_impares.push_back(triangulos[i]);
  }

  for(int i = 0; i < vertices.size(); i++){
    color.push_back({0.0, 0.0, 0.0});
    color_otro.push_back({0.9, 0.0, 1.0});
  }

}

// *****************************************************************************
// Clase ObjPLY (práctica 2)
// *****************************************************************************

ObjPLY::ObjPLY(const std::string & nombre_archivo){

   // leer la lista de caras y vértices
   ply::read(nombre_archivo, vertices, triangulos);

   for(int i = 0; i < triangulos.size(); i++){
     if(i%2)
       triangulos_pares.push_back(triangulos[i]);
     else
       triangulos_impares.push_back(triangulos[i]);
   }

   for(int i = 0; i < vertices.size(); i++){
     color.push_back({0.0, 0.0, 0.0});
     color_otro.push_back({0.9, 0.0, 1.0});
   }

}

// *****************************************************************************
// Clase ObjRevolucion (práctica 2)
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(const std::string & nombre_ply_perfil){

   ply::read_vertices(nombre_ply_perfil, vertices);
   crearMalla(vertices, 50, false, false);

}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool cono, bool esfera){
  Tupla3f v,v1;
  int a, b;
  Tupla3i t;

  int M = perfil_original.size();
  int N = num_instancias_perf;

  vertices.clear();

  // rotaciones de los vertices
  for(int i = 0; i < N; i++){
    //v = perfil_original[j];
    for(int j = 0; j < M; j++){
      float rotacion = (2*M_PI*i)/N;
      v = perfil_original[j];
      v1[0] = cos(rotacion)*v[0] + sin(rotacion)*v[2];
      v1[1] = v[1];
      v1[2] = cos(rotacion)*v[2] - sin(rotacion)*v[0];

      vertices.push_back(v1);
    }
  }

  triangulos.clear();

  //tabla de triangulos
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M-1; j++){
      a = M*i + j;
      b = M*((i+1)%N) + j;

      t[0] = a;
      t[1] = b;
      t[2] = b+1;
      triangulos.push_back(t);

      t[0] = a;
      t[1] = b+1;
      t[2] = a+1;
      triangulos.push_back(t);
    }
  }

  if(cono){
    v = {0.0, perfil_original[0][1], 0.0};
    vertices.push_back(v); //polo sur

    v = {0.0, 1.0, 0.0};
    vertices.push_back(v);
  }
  else if(esfera){
    v = {0.0, -1.0, 0.0};
    vertices.push_back(v); //polo sur

    v = {0.0, 1.0, 0.0};
    vertices.push_back(v);
  }
  else{
    //HACER TAPAS ARRIBA y ABAJO
    v = {0, perfil_original[0][1], 0};
    vertices.push_back(v); //polo sur

    v = {0, perfil_original[M-1][1], 0};
    vertices.push_back(v); //polo norte
  }

  for(int i = 0; i < N; i++){
    //tapa inferior
    t[2] = M*i;
    t[1] = M*((i+1)%N);
    t[0] = vertices.size()-2;

    triangulos.push_back(t);
  }

  for(int i = 0; i < N; i++){
    //tapa superior
    t[0] = M*(i+1) - 1;
    t[1] = M*(((i+1)%N)+1)-1;
    t[2] = vertices.size()-1;

    triangulos.push_back(t);
  }

  for(int i = 0; i < triangulos.size(); i++){
    if(i%2)
      triangulos_pares.push_back(triangulos[i]);
    else
      triangulos_impares.push_back(triangulos[i]);
  }

  for(int i = 0; i < vertices.size(); i++){
    color.push_back({0.0, 0.0, 0.0});
    color_otro.push_back({0.9, 0.0, 1.0});
  }

}

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf){
  std::cout << "Creando cilinidro..." << std::endl;
  std::vector<Tupla3f> perfil;

  for(int i = 0.0; i < num_vert_perfil; i++){
    perfil.push_back({1.0, (float)(0.0 + (i+1)/num_vert_perfil), 0.0});
  }

  crearMalla(perfil, num_instancias_perf, false, false);
}

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf){
  std::cout << "Creando cono..." << std::endl;
  std::vector<Tupla3f> perfil;

  for (float i = 0.0; i < num_vert_perfil; i+=1.0){
    perfil.push_back({(float)(1.0 - i/num_vert_perfil), (float)(0.0 + i/num_vert_perfil), 0.0});
  }

  crearMalla(perfil, num_instancias_perf, true, false);
}

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf){
  std::cout << "Creando esfera..." << std::endl;
  std::vector<Tupla3f> perfil;

  for(float i = 1.0; i < num_vert_perfil; i+=1.0){
    float y = -1*1.0 + 2*i/num_vert_perfil;
    perfil.push_back({(float)(0.0 + sqrt(1-(y*y))), y, 0.0});
  }

  crearMalla(perfil, num_instancias_perf, false, true);
}
