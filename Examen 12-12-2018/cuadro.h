/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _CUADRO_H
#define _CUADRO_H

class Cuadro : public ObjMallaIndexada{
    public:
        Cuadro(){

            //cuadro pedido en la practica
            /*vertices = { {-1.0, -1.0, 0.0},
                         {1.0, -1.0, 0.0},
                         {-1.0, 1.0, 0.0},
                         {1.0, 1.0, 0.0} };
            
            triangulos = { {0, 3, 2}, {0, 1, 3} };*/

            //cuadro de examen
            vertices = { {0.0, 0.0, 0.0},   //0
                         {1.25, 0.0, 0.0},  //1
                         {0.0, 1.0, 0.0},   //2
                         {1.25, 1.0, 0.0},  //3
                         {-1.25, 0.0, 0.0}, //4
                         {-1.25, 1.0, 0.0}, //5
                         {0.0, -1.0, 0.0},  //6
                         {1.25, -1.0, 0.0}, //7
                         {-1.25, -1.0, 0.0},//8
                         {0.0, 0.0, 0.0},   //9
                         {1.25, 0.0, 0.0},  //10
                         {0.0, 1.0, 0.0}    //11
                         };

            triangulos = { {0, 1, 2}, {2, 1, 3}, {4, 9, 11}, {5, 4, 11}, 
                           {9, 6, 10}, {9, 4, 6}, {6, 7, 10}, {6, 4, 8}};

            for(int i = 0; i < triangulos.size(); i++){
                if(i%2)
                    triangulos_pares.push_back(triangulos[i]);
                else
                    triangulos_impares.push_back(triangulos[i]);
            }

            calcular_normales();

            texturas.push_back(Textura("./logo.jpg"));
        }
};

#endif