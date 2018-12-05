// *****************************************************************************
// Clase Cubo (práctica 1)
// *****************************************************************************
/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _CUBO_H
#define _CUBO_H

class Cubo : public ObjMallaIndexada{
    public:
        Cubo(){
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

        calcular_normales();
        }
};


#endif