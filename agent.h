/******************************************************************************
*
* Inteligencia Artificial
* Grado en Ingeniería Informática
*
* 2014 - Ernesto Serrano Collado <erseco@correo.ugr.es>
* -----------------------------------------------------
*
* Cabecera del agente
*
******************************************************************************/
#ifndef AGENT__
#define AGENT__

#include <iostream>
#include <iomanip>

using namespace std;

// -----------------------------------------------------------
// 				class Agent
// -----------------------------------------------------------
class Environment;
class Agent {

public:
    // Constructor
	Agent(){

		counter = 0;
	    bump_= false;
        dirty_= false;

        // La posicion inicial será el centro de la matriz
		x = 10;
		y = 10;

		antX = 0;
		antY = 0;

		rotate = false;

		// Inicializamos la matriz con -1 (valor para no reconocido)
		for(int i = 0; i<MAPSIZE; i++) {
			
			for(int j = 0; j<MAPSIZE; j++) {
			
				map[i][j] = -1;
			
			}

		}

		// Establecemos la orientación inicial a Norte
		compass = N;

	};

    // Enumeración de acciones
	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSUCK,
	    actIDLE
	};

    // Este método devuelve la información de los sensores
	void Perceive(const Environment &env);
	ActionType Think();

	// Esta función imprime el mapa (para depurar), 
	// la ponemos aqui fuera porque la llamo desde el GUI
	void PrintMap();

private:
	bool bump_,
		 dirty_;

	// Atributos y métodos agregados por mi
	int x, y; // Empezaran en 10, el centro del array

	// Aqui almacenaremos la posicion inmediatamente anterior
	int antX;
	int antY;

    // Enumeración de direcciones
	enum DirectionType
	{
	    N,
	    E,
	    S,
	    O
	};


	// Creamos una matriz de 20x20 donde ir memorizando el mapa
	static const int MAPSIZE = 20;
	int map[MAPSIZE][MAPSIZE];

	// Bandera para saber si tenemos que hacer un giro
	bool rotate;

	// Variable "brujula" para ir almacenando la dirección actual
	DirectionType compass;

	// Función para ir actualizando la brújula
	void ChangeOrientation(ActionType action);

	// Esta función obtiene la siguiente acción a realizar
	ActionType GetNextAction( int sigX, int sigY);

	// Aqui almacenamos la accion a realizar, asi la tendremos la siguiente vez
	ActionType action;

	int counter;

	const int OBSTACLE = 9999999;

	ActionType min(int frente, int derecha, int izquierda);


};

string ActionStr(Agent::ActionType);

#endif

