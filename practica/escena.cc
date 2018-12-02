/*
 * Prácticas IG Grupo A
 *
 * Elena Cantero Molina   DNI:45744912M
 *
 */

#include "aux.h"     //includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h"   //objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena(){

    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0;
    Observer_angle_y  = 0.0;

    ejes.changeAxisSize(5000);

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();
    tetraedro = new Tetraedro();

    cono = new Cono(5, 20, true, true);
    cilindro = new Cilindro(2, 100, true, true);
    esfera = new Esfera(100, 100, true, true);

    objetoPLY = new ObjPLY("plys/ant.ply");
    objetoRev = new ObjRevolucion("plys/peon.ply", true, true);

    objJerarquico = new ObjJerarquico();

    luz1 = new Luz();

    num_modos = 6;
    num_objetos = 8; // se usa al pulsar la tecla 'O' (rotar objeto actual)

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height){

	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
  redimensionar(UI_window_width, UI_window_height);

}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual(){

   using namespace std;

   glColor3f(0.0, 0.0, 0.0);
   
   switch(modo_actual){
     case 0:
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //cara delantera y trasera con lineas
       break;
     case 1:
       glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); //cara delantera y trasera con puntos
       break;
     case 2:
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //cara delantera y trasera rellenas
       break;
     case 3:
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //cara delantera y trasera rellenas para el modo ajedrez
       break;
     case 4:
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //cara delantera y trasera rellenas ILUMINACION PLANA
       glShadeModel(GL_FLAT);
       luz_plana = true;
       break;
     case 5:
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //cara delantera y trasera rellenas ILUMINACION SUAVE
       glShadeModel(GL_SMOOTH);
       luz_suave = true;
       break;
     default:
       cout << "No se puede dibujar" << endl;
       break;
   }

   //dibujar el objeto actual usando método 'draw' del objeto asociado al
   //valor entero en 'objeto_actual'
   switch(objeto_actual){
      case 0: //Cubo
        if (cubo != nullptr){
          if(modo_actual == 3) cubo->draw(true, modo_dibujado);
          else cubo->draw(false, modo_dibujado);
        }
      break;
      case 1: //Tetraedro
        if (tetraedro != nullptr){
          if(modo_actual == 3) tetraedro->draw(true, modo_dibujado);
          else tetraedro->draw(false, modo_dibujado);
        }
      break;
      case 2: //Objeto PLY
        if (objetoPLY != nullptr){
          if(modo_actual == 3) objetoPLY->draw(true, modo_dibujado);
          else objetoPLY->draw(false, modo_dibujado);
        }
      break;
      case 3: //Objeto Revolución (Peón)
        if(objetoRev != nullptr){
          if(modo_actual == 3) objetoRev->draw(true, modo_dibujado);
          else objetoRev->draw(false, modo_dibujado);
        }
      break;
      case 4: //Cilindro
        if (cilindro != nullptr){
          if(modo_actual == 3) cilindro->draw(true, modo_dibujado);
          else cilindro->draw(false, modo_dibujado);
        }
      break;
      case 5: //Cono
        if (cono != nullptr){
          if(modo_actual == 3) cono->draw(true, modo_dibujado);
          else cono->draw(false, modo_dibujado);
        }
      break;
      case 6: //Esfera
        if (esfera != nullptr){
          if(modo_actual == 3) esfera->draw(true, modo_dibujado);
          else esfera->draw(false, modo_dibujado);
        }
      break;
      case 7: //Objeto Jerárquico
        if(objJerarquico != nullptr){
          bool diferido = false;
          if(modo_dibujado == 1) diferido = true;

          if(modo_actual == 3) objJerarquico->draw(modo_actual, diferido);
          else objJerarquico->draw(modo_actual, diferido);
        }
      break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
      break ;
   }
}

// **************************************************************************
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
// **************************************************************************

void Escena::dibujar(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  ejes.draw();
	dibujar_objeto_actual();
}

//**************************************************************************
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y){
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   if(tecla != 'z'){ tecla = toupper(tecla); }

   switch(tecla){
      case 'Q': //salir
        return true;
      break;
      case 'O': //activar siguiente objeto
        objeto_actual = (objeto_actual+1) % num_objetos;
        cout << "objeto actual == " << objeto_actual << endl;
      break;
      case 'M': //activar siguiente modo
        modo_actual = (modo_actual+1) % num_modos;
        cout << "modo actual == " << modo_actual << endl;
      break;
      case 'V': //Cambio modo diferido e inmediato
        if(modo_dibujado == 0){
          modo_dibujado = 1;
          cout << "modo dibujado == diferido" << endl;
        }
        else{
          modo_dibujado = 0;
          cout << "modo_dibujado == inmediato" << endl;
        }
      break;
      case 'P': //Activar el parámetro siguiente
        objJerarquico->siguienteParametro();
      break;
      case 'A': //activar/desactivar animaciones
        conmutarAcciones();
      break;
      case 'Z': //incrementa el valor del parámetro actual del objeto
        objJerarquico->incrementaParamAct();
      break;
      case 'z': //decrementa el valor del paraámetro actal del objeto
        objJerarquico->decrementaParamAct();
      break;
      case '>': //incrementa el valor usado para las animaciones
        objJerarquico->acelerar();
      break;
      case '<': //decrementa el valor usado para las animaciones
        objJerarquico->decelerar();
      break;
      case 'L': //enciende o apaga la luz
        if(glIsEnabled(GL_LIGHT0)) luz1->desactivar();
        else luz1->activar();
   }

   return false;
}

//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y){

   switch (Tecla1){
     case GLUT_KEY_LEFT:
        Observer_angle_y--;
     break;
	   case GLUT_KEY_RIGHT:
        Observer_angle_y++;
     break;
	   case GLUT_KEY_UP:
        Observer_angle_x--;
     break;
	   case GLUT_KEY_DOWN:
        Observer_angle_x++;
     break;
	   case GLUT_KEY_PAGE_UP:
        Observer_distance *=1.2;
     break;
	   case GLUT_KEY_PAGE_DOWN:
        Observer_distance /= 1.2;
     break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//***************************************************************************

void Escena::change_projection(const float ratio_xy){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   const float wy = 0.84*Front_plane;
   const float wx = ratio_xy*wy;
   glFrustum( -wx, wx, -wy, wy, Front_plane, Back_plane );
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight){
   Width  = newWidth;
   Height = newHeight;
   change_projection(float(Width)/float(Height));
   glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer(){
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

//Se encarga de actualizar el estado de los parámetros del objeto jerárquico
void Escena::mgeDesocupado(){
  objJerarquico->actualizarEstado();
  glutPostRedisplay();
}

//Se encarga de activar o desactivar las animaciones
void Escena::conmutarAcciones(){
  if(objeto_actual == 7){
    if(!animacion){
      animacion = true;
      objJerarquico->inicioAnimaciones();
      glutIdleFunc(funcion_desocupado);
    }
    else{
      animacion = false;
      glutIdleFunc(nullptr);
    }
  }
  else{
    std::cout << "Advertencia -> no es el objeto jerarquico" << std::endl;
  }
}
