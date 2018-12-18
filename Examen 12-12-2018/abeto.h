// *****************************************************************************
// Clase Abeto
// *****************************************************************************
/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#ifndef _ABETO_H
#define _ABETO_H

class Abeto : public ObjMallaIndexada{
  public:
    Abeto(){

      vertices =  { {-0.5, 0.0, 0.5},   //0
                    {0.5, 0.0, 0.5},  //1
                    {0.5, 0.0, -0.5},  //2
                    {-0.5, 0.0, -0.5},    //3
                    {0.0, 0.5, 0.0}, //4

                    {-0.5, 0.0, 0.5},   //5
                    {0.5, 0.0, 0.5},  //6
                    {0.5, 0.0, -0.5},  //7
                    {-0.5, 0.0, -0.5},    //8
                    {0.0, 0.5, 0.0}, //9

                    {0.0, 0.5, 0.0}, //10
                    {0.0, 0.5, 0.0}, //11
		         };

      // inicializar la tabla de caras o triángulos:
      // (es importante en cada cara ordenar los vértices en sentido contrario
      //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
      
      /*triangulos = { { 0, 1, 3 }, { 0, 3, 2 },
		            { 5, 4, 7 }, { 4, 6, 7 },
		            { 8, 9, 11 }, { 8, 11, 10 },
		            { 13, 12, 14 }, { 13, 14, 15 },
		            { 16, 17, 19 }, { 16, 19, 18 },
		            { 21, 20, 22 }, { 21, 22, 23 }
		          } ;*/

        triangulos = { {0, 3, 1}, {1, 3, 2}, {0, 1, 4}, {1, 2, 4},
                       {4, 2, 3}, {4, 3, 0}, {5, 8, 6}, {6, 8, 7},
                       {5, 6, 9}, {6, 7, 9}, {9, 7, 8}, {9, 8, 5},
                       {0, 1, 10}, {1, 2, 10}, {10, 2, 3}, {10, 3, 0},
                       {0, 1, 11}, {1, 2, 11}, {11, 2, 3}, {11, 3, 0} };

	   for (int i = 0; i < triangulos.size(); i++){
       if (i%2)
  		  triangulos_pares.push_back(triangulos[i]);
		   else
			  triangulos_impares.push_back(triangulos[i]);
     }

      calcular_normales();
      texturas.push_back(Textura("./abeto.jpg"));

      std::vector<Tupla2f> tVertices;
      
      /*tVertices = {	{ 0.0, 0.66}, { 0.0, 0.33},	// 0 1
              {0.25, 0.66}, {0.25, 0.33},	// 2 3
              {0.50, 0.66}, {0.50, 0.33},	// 4 5
              {0.75, 0.66}, {0.75, 0.33}, // 6 7
              {1.00, 0.66}, {1.00, 0.33}, // 0 1
              {0.25, 0.00}, {0.25, 0.33}, // 1 3
              {0.50, 0.33}, {0.50, 0.00},	// 5 7
              {0.25, 1.00}, {0.25, 0.66}, // 0 2
              {0.50, 0.66}, {0.50, 1.00}	// 4 6
              };*/
      
      tVertices = {	{0.0,1.0}, {0.25,1.0}, {0.0,0.0}, {0.25,0.0},
                  {0.0,1.0}, {0.25,1.0}, {0.0,0.0}, {0.25,0.0}
              };
              
      texturas[0].setTextVert( tVertices );
      
    }
};

#endif