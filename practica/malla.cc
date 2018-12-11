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

void ObjMallaIndexada::arrayMateriales(){
  Tupla4f especular, ambiental, difusa;
  float brillo;
  
  //material turquesa
  ambiental = {0.1, 0.18725, 0.1745, 1.0};
  difusa = {0.396, 0.74151, 0.69102, 1.0};
  especular = {0.297254, 0.30829, 0.306678, 1.0};
  brillo = 12.8;

  materiales.push_back(Material(especular, ambiental, difusa, brillo));

  //material esmeralda
  ambiental = {0.0215, 0.1745, 0.0215, 1.0};
  difusa = {0.07568, 0.61424, 0.07568, 1.0};
  especular = {0.633, 0.727811, 0.633, 1.0};
  brillo = 76.8;

  materiales.push_back(Material(especular, ambiental, difusa, brillo));

  //material oro
  ambiental = {0.24725, 0.1995, 0.0745, 1.0};
  difusa = {0.75164, 0.60648, 0.22648, 1.0};
  especular = {0.628281, 0.555802, 0.366065, 1.0};
  brillo = 51.2;

  materiales.push_back(Material(especular, ambiental, difusa, brillo));

  //material gris
  ambiental = {0.2, 0.2, 0.2, 1.0};
  difusa = {0.5, 0.5, 0.5, 1.0};
  especular = {0.5, 0.5, 0.5, 1.0};
  brillo = 50.9;

  materiales.push_back(Material(especular, ambiental, difusa, brillo));

  //material rojo
  ambiental = {0.2, 0.0, 0.0, 1.0};
  difusa = {0.6, 0.1,0.1, 1.0};
  especular = {0.7, 0.6, 0.6, 1.0};
  brillo = 75.4;

  materiales.push_back(Material(especular, ambiental, difusa, brillo));
}

void ObjMallaIndexada::sigMaterial(){
  //std::cout << "numero material " << material << std::endl;
  //std::cout << "materiales " << materiales.size() << std::endl;
  if(material == materiales.size()) material = 0;
  material = (material+1) % materiales.size();
}

void ObjMallaIndexada::cambioNormales(){
  float maximo;
  int indice;

  if(!normal_vertices.empty()){
    for(int i = 0; i < normal_vertices.size(); i++){
      maximo = normal_vertices[i][0];
      indice = 0;

      if(abs(maximo) < abs(normal_vertices[i][1])){
        maximo = normal_vertices[i][1];
        indice = 1;
      }
      else if(abs(maximo) < abs(normal_vertices[i][2])){
        maximo = normal_vertices[i][2];
        indice = 2;
      }

      switch(indice){
        case 0: normal_vertices[i] = {maximo, 0.0, 0.0}; break;
        case 1: normal_vertices[i] = {0.0, maximo, 0.0}; break;
        case 2: normal_vertices[i] = {0.0, 0.0, maximo}; break;
      }
    }
  }
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato(bool ajedrez){

  if(glIsEnabled(GL_LIGHTING)){
    //usamos normales y material

    glEnableClientState(GL_NORMAL_ARRAY); //habilitar uso de normales
    glNormalPointer(GL_FLOAT, 0, normal_vertices.data());

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materiales[material].especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materiales[material].ambiental);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materiales[material].difusa);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materiales[material].brillo);
  }

  if(!texturas.empty()){
    glEnableClientState(GL_NORMAL_ARRAY); //habilitar uso de normales
    glEnableClientState(GL_VERTEX_ARRAY); //habilitar uso de un array de vértices

    glVertexPointer(3, GL_FLOAT, 0, vertices.data()); //Establecer los vértices
    glNormalPointer(GL_FLOAT, 0, normal_vertices.data());

    texturas[0].activar();

    glDrawElements(GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);   //deshabilitar array de vértices
    glDisableClientState(GL_NORMAL_ARRAY);  //deshabilitar array de normales
  }
  else{
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
    glDisableClientState(GL_NORMAL_ARRAY);
  }
}

// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(bool ajedrez){

  if(glIsEnabled(GL_LIGHT0)){
    glEnableClientState( GL_VERTEX_ARRAY ); //habilitar uso de un array de vértices
    glDisableClientState(GL_NORMAL_ARRAY);

    if(id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, sizeof(float)*3*vertices.size(), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver); // activar VBO de vértices
    glVertexPointer(3, GL_FLOAT, 0, 0); // especifica formato y offset (=0)
    glNormalPointer(GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // desactivar VBO de vértices.

    glEnableClientState(GL_COLOR_ARRAY); //habilitar uso de un array de colores

    if(id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*3*triangulos.size(), triangulos.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri); // activar VBO de triángulos
    glColorPointer(3, GL_FLOAT, 0, color.data()); //Establecer un color inicial
    glDrawElements(GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);  //deshabilitar array de normales
  }
  else{
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
  
}

//------------------------------------------------------------------------------
// Creación de un VBO

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

  if(materiales_off){
    arrayMateriales();
    materiales_off = false;
  }

  if(modo_dibujado == 0) draw_ModoInmediato(ajedrez);
  else draw_ModoDiferido(ajedrez);

}

// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)
void ObjMallaIndexada::calcular_normales(){
  //std::cout << "Calculo de normales:" << std::endl;
  normal_vertices.resize(vertices.size());

  //Establecemos todos los valores de las normales de los vertices a 0
  for(Tupla3f i : normal_vertices){
    i = {0.0, 0.0, 0.0};
  }

  for(int i=0; i<triangulos.size(); i++){
    Tupla3f v0, v1;

    v0 = vertices[triangulos[i][1]] - vertices[triangulos[i][0]];
    v1 = vertices[triangulos[i][2]] - vertices[triangulos[i][0]];

    //Producto vectorial
    normal_triangulos.push_back((v0.cross(v1)).normalized());

    normal_vertices[triangulos[i][0]] = normal_vertices[triangulos[i][0]] + normal_triangulos[i];
    normal_vertices[triangulos[i][1]] = normal_vertices[triangulos[i][1]] + normal_triangulos[i];
    normal_vertices[triangulos[i][2]] = normal_vertices[triangulos[i][2]] + normal_triangulos[i];
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

   calcular_normales();

}

// *****************************************************************************
// Clase ObjRevolucion (práctica 2)
// *****************************************************************************

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion(const std::string & nombre_ply_perfil, bool tapaArriba, bool tapaAbajo){

   ply::read_vertices(nombre_ply_perfil, vertices);
   crearMalla(vertices, 50, false, false, tapaArriba, tapaAbajo);

   for(int i = 0; i < vertices.size(); i++){
     color.push_back({0.0, 0.0, 0.0});
     color_otro.push_back({0.9, 0.0, 1.0});
   }
}

//******************************************************************************

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool cono, bool esfera, bool tapaArriba, bool tapaAbajo){
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

  if(cono || esfera){
    if(cono){
      v = {0.0, perfil_original[0][1], 0.0};
      vertices.push_back(v); //polo sur
    }
    else{
      v = {0.0, -1.0, 0.0};
      vertices.push_back(v); //polo sur
    }

    v = {0.0, 1.0, 0.0};
    vertices.push_back(v);
  }
  else{
    //HACER TAPAS ARRIBA y ABAJO
    if(tapaAbajo){
      v = {0, perfil_original[0][1], 0};
      vertices.push_back(v); //polo sur
    }

    if(tapaArriba){
      v = {0, perfil_original[M-1][1], 0};
      vertices.push_back(v); //polo norte
    }
  }

  if(tapaAbajo){
    for(int i = 0; i < N; i++){
      //tapa inferior
      t[2] = M*i;
      t[1] = M*((i+1)%N);
      t[0] = vertices.size()-2;

      triangulos.push_back(t);
    }
  }

  if(tapaArriba){
    for(int i = 0; i < N; i++){
      //tapa superior
      t[0] = M*(i+1) - 1;
      t[1] = M*(((i+1)%N)+1)-1;
      t[2] = vertices.size()-1;

      triangulos.push_back(t);
    }
  }

  for(int i = 0; i < triangulos.size(); i++){
    if(i%2)
      triangulos_pares.push_back(triangulos[i]);
    else
      triangulos_impares.push_back(triangulos[i]);
  }

  calcular_normales();

}

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, bool tapaArriba, bool tapaAbajo){
  std::cout << "Creando cilinidro..." << std::endl;
  std::vector<Tupla3f> perfil;

  for(float i = 0.0; i < num_vert_perfil; i++){
    perfil.push_back({1.0, (float)(0.0 + i/num_vert_perfil), 0.0});
  }

  crearMalla(perfil, num_instancias_perf, false, false, tapaArriba, tapaAbajo);

  for(int i = 0; i < vertices.size(); i++){
    color.push_back({0.7, 0.5, 0.0});
    color_otro.push_back({0.0, 0.0, 0.0});
  }
}

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, bool tapaArriba, bool tapaAbajo){
  std::cout << "Creando cono..." << std::endl;
  std::vector<Tupla3f> perfil;

  for (float i = 0.0; i < num_vert_perfil; i+=1.0){
    perfil.push_back({(float)(1.0 - i/num_vert_perfil), (float)(0.0 + i/num_vert_perfil), 0.0});
  }

  crearMalla(perfil, num_instancias_perf, true, false, tapaArriba, tapaAbajo);

  for(int i = 0; i < vertices.size(); i++){
    color.push_back({0.0, 0.0, 0.0});
    color_otro.push_back({0.9, 0.0, 1.0});
  }
}

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, bool tapaArriba, bool tapaAbajo){
  std::cout << "Creando esfera..." << std::endl;
  std::vector<Tupla3f> perfil;

  for(float i = 1.0; i < num_vert_perfil; i+=1.0){
    float y = -1*1.0 + 2*i/num_vert_perfil;
    perfil.push_back({(float)(0.0 + sqrt(1-(y*y))), y, 0.0});
  }

  crearMalla(perfil, num_instancias_perf, false, true, tapaArriba, tapaAbajo);

  for(int i = 0; i < vertices.size(); i++){
    color.push_back({1.0, 0.5, 0.5});
    color_otro.push_back({0.0, 0.0, 0.0});
  }
}