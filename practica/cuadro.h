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
            vertices = { {-1.0, -1.0, 0.0},
                         {1.0, -1.0, 0.0},
                         {-1.0, 1.0, 0.0},
                         {1.0, 1.0, 0.0} };
            
            triangulos = { {0, 3, 2}, {0, 1, 3} };

            for(int i = 0; i < triangulos.size(); i++){
                if(i%2)
                    triangulos_pares.push_back(triangulos[i]);
                else
                    triangulos_impares.push_back(triangulos[i]);
            }

            calcular_normales();

            texturas.push_back(Textura("./playa.jpg"));
        }
};

#endif