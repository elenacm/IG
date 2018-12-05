// *****************************************************************************
// Clase Tetraedro (práctica 1)
// *****************************************************************************
/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _TETRAEDRO_H
#define _TETRAEDRO_H

class Tetraedro : public ObjMallaIndexada{
    public:
        Tetraedro(){
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

            calcular_normales();
        }
};

#endif