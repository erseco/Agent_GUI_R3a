/******************************************************************************
*
* Inteligencia Artificial
* Grado en Ingeniería Informática
*
* 2014 - Ernesto Serrano Collado <erseco@correo.ugr.es>
* -----------------------------------------------------
*
* Codigo fuente del agente
*
******************************************************************************/
#include "agent.h"
#include "environment.h"

#include <cstdlib>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think() {

	if (bump_) {

		// Si ha chocado actualizamos el valor siguiente con 0 (esta en FORWARD)
			 if (compass == N) map[x][y-1] = OBSTACLE;
		else if (compass == E) map[x+1][y] = OBSTACLE;
		else if (compass == S) map[x][y+1] = OBSTACLE;
		else if (compass == O) map[x-1][y] = OBSTACLE;

	}


	map[x][y] = counter;


	if (!bump_ && action == actFORWARD) {

		// avance correcto

		// Guardamos los valores de la posición anterior
		antX = x;
		antY = y;

		// actualizamos la posicion actual
			 if (compass == N) y--;
		else if (compass == E) x++;
		else if (compass == S) y++;
		else if (compass == O) x--;

	}  

	if (dirty_) {

		// Si está sucio, limpia e incrementa el contador
		action = actSUCK;

	} else {

		// Si no, obtiene una acción y la realiza
		action = GetNextAction(x, y);
		
	}

	// Actualiza el valor de la brújula (compass)
	ChangeOrientation(action);

	counter++;

	return action;

}

Agent::ActionType Agent::min(int frente, int derecha, int izquierda) {

	if (frente <= derecha && frente <= izquierda && frente == OBSTACLE)
		return actTURN_R;
	else if (frente <= derecha && frente <= izquierda) 
		return actFORWARD;
	else if (izquierda)
		return actTURN_L;
	else
		return actTURN_R;

}

Agent::ActionType Agent::GetNextAction(int sigX, int sigY) {

	int north = map[sigX][sigY-1];
	int east =  map[sigX+1][sigY];
	int south =   map[sigX][sigY+1];
	int west = map[sigX-1][sigY];

	//action = min(north, east, west);


	if (north == -1) { // Explora Norte

		if (compass == N) {
			action = actFORWARD;
		} else if (compass == E) {
			action = actTURN_L;
		} else if (compass == O) {
			action = actTURN_R;
		} else if (compass == S) {
			// Giramos uno y marcamos la bandera para que rote la siguiente
			action = actTURN_R; 
			rotate = true;
		}

	} else if (east == -1) { // Explora Este

		if (compass == E) {
			action = actFORWARD;
		} else if (compass == S) {
			action = actTURN_L; 
		} else if (compass == N) {
			action = actTURN_R;
		} else if (compass == O) {
			// Giramos uno y marcamos la bandera para que rote la siguiente
			action = actTURN_R;
			rotate = true;
		} 

	} else if (south == -1) { // Explora Sur

		if (compass == S) {
			action = actFORWARD; 
		} else if (compass == O) {
			action = actTURN_L;
		} else if (compass == E) {
			action = actTURN_R;
		} else if (compass == N) {
			// Giramos uno y marcamos la bandera para que rote la siguiente
			action = actTURN_R;
			rotate = true;
		}

	} else if (west == -1) { // Explora Oeste

		if (compass == O) {
			action = actFORWARD;
		} else if (compass == N) {
			action = actTURN_L;
		} else if (compass == S) {
			action = actTURN_R; 
		} else if (compass == E) {
			// Giramos uno y marcamos la bandera para que rote la siguiente
			action = actTURN_R;
			rotate = true;
		}


	// Supuesto en el que estén todas las celdas de alrededor reconocidas y a partir
	// de ahi todo el funcionamiento es aleatorio
	// Activar solo para hacer mediciones
	// } else if (north > -1 && east > -1 && south > -1 && west > -1) {
	// 	 action = static_cast<ActionType>(rand() % 3);		

	// Aqui evitamos el que se quede "enganchado" volviendo a la anterior
	} else if (compass == N && north != OBSTACLE && antX != sigX && antY != sigY-1) {

		// Obtenemos una nueva acción
		ActionType new_action = static_cast<ActionType>(rand() % 3);

		// Comprobamos que esa acción no signifique retornar a la anterior
		if (action == actTURN_R && new_action == actTURN_L) {
			action = actFORWARD;
		} else if (action == actTURN_L && new_action == actTURN_R) {
			action = actFORWARD;
		} else {
			action = new_action;
		}

	} else if (compass == E && east != OBSTACLE && antX != sigX+1 && antY != sigY) {

		// Obtenemos una nueva acción
		ActionType new_action = static_cast<ActionType>(rand() % 3);

		// Comprobamos que esa acción no signifique retornar a la anterior
		if (action == actTURN_R && new_action == actTURN_L) {
			action = actFORWARD;
		} else if (action == actTURN_L && new_action == actTURN_R) {
			action = actFORWARD;
		} else {
			action = new_action;
		}

	} else if (compass == S && south != OBSTACLE && antX != sigX && antY != sigY+1) {
		
		// Obtenemos una nueva acción
		ActionType new_action = static_cast<ActionType>(rand() % 3);

		// Comprobamos que esa acción no signifique retornar a la anterior
		if (action == actTURN_R && new_action == actTURN_L) {
			action = actFORWARD;
		} else if (action == actTURN_L && new_action == actTURN_R) {
			action = actFORWARD;
		} else {
			action = new_action;
		}

	} else if (compass == O && west != OBSTACLE && antX != sigX-1 && antY != sigY) {
		
		// Obtenemos una nueva acción
		ActionType new_action = static_cast<ActionType>(rand() % 3);

		// Comprobamos que esa acción no signifique retornar a la anterior
		if (action == actTURN_R && new_action == actTURN_L) {
			action = actFORWARD;
		} else if (action == actTURN_L && new_action == actTURN_R) {
			action = actFORWARD;
		} else {
			action = new_action;
		}

	// Se va moviendo al vecino con menor valor (probabilidad de suciedad mas alta)
	} else if (compass == N && north != OBSTACLE && north <= east && north <= west) {
		action = actFORWARD;
	} else if (compass == N && east != OBSTACLE  && east < north && action != actTURN_L) {
		action = actTURN_R;
	} else if (compass == N && west != OBSTACLE  && west < north&& action != actTURN_R) {
		action = actTURN_L;


	} else if (compass == E && east != OBSTACLE && east <= north && east <= south) {
		action = actFORWARD;
	} else if (compass == E && south != OBSTACLE  && south < east && action != actTURN_L) {
		action = actTURN_R;
	} else if (compass == E && north != OBSTACLE  && north < east && action != actTURN_R) {
		action = actTURN_L;


	} else if (compass == S && south != OBSTACLE && south <= east && south <= west) {
		action = actFORWARD;
	} else if (compass == S && west != OBSTACLE  && west < south && action != actTURN_L) {
		action = actTURN_R;
	} else if (compass == S && east != OBSTACLE  && east < south && action != actTURN_R) {
		action = actTURN_L;


	} else if (compass == O && west != OBSTACLE && west <= south && west <= north) {
		action = actFORWARD;
	} else if (compass == O && north != OBSTACLE  && north < west && action != actTURN_L) {
		action = actTURN_R;
	} else if (compass == O && south != OBSTACLE  && south < west && action != actTURN_R) {
		action = actTURN_L;


	// Excepcion para el caso de girar, asi si se queda "encerrado" puede volver
	} else if (compass == N) {
		action = actTURN_R;
		rotate = true;
	} else if (compass == E) {
		action = actTURN_R;
		rotate = true;
	} else if (compass == S) {
		action = actTURN_R;
		rotate = true;
	} else if (compass == O) {
		action = actTURN_R;
		rotate = true;

	} else {

		cout << "resto";
	}

	return action;
}

// Pinta el mapa en la salida estándar, en un terminal bash (linux/mac) se puede ver el camino
// recorrido con color rojo y el punto actual en azul
void Agent::PrintMap() {

	cout << "------------" << endl;
	for (int i=0; i<MAPSIZE; i++) {

		// Pintamos un encabezado
		if (i == 0) {
		   cout << setw(3) << " " << "|";
	
			for (int j=0; j<MAPSIZE; j++) {
				
					cout << setw(3) << j;

			}
			cout << endl;
		}

		cout << setw(3) << i << "|";

		// Pintamos el mapa
		for (int j=0; j<MAPSIZE; j++) {

			int value = map[j][i];

			if (j == x && i == y) {
				// Azul
				cout << "\033[1;34m" << setw(3) << value << "\033[0m";

			} else if (value == OBSTACLE) {

				cout << setw(3) << 0;

			} else if (value == -1) {

				cout << setw(3) << ' ';

			} else if (value > 0) {
				// Rojo
				cout << "\033[1;31m" << setw(3) << value << "\033[0m";
			
			} else {
				// Normal
				cout << setw(3) << value ;
			}

		}
		cout << endl; // cada fila se muestra en una linea diferente
	}

}

// Esta función actualiza la variable compass (brujula) segun la última accion
void Agent::ChangeOrientation(ActionType action) {

	if (compass == N && action == actTURN_R) {
		compass = E;

	} else if (compass == N && action == actTURN_L) {
		compass = O;

	} else if (compass == E && action == actTURN_R) {
		compass = S;

	} else if (compass == E && action == actTURN_L) {
		compass = N;

	} else if (compass == S && action == actTURN_R) {
		compass = O;

	} else if (compass == S && action == actTURN_L) {
		compass = E;

	} else if (compass == O && action == actTURN_R) {
		compass = N;

	} else if (compass == O && action == actTURN_L) {
		compass = S;

	}

}

void Agent::Perceive(const Environment &env) {
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}

string ActionStr(Agent::ActionType action) {
	switch (action) {
		case Agent::actFORWARD: return "FORWARD";
		case Agent::actTURN_L: return "TURN LEFT";
		case Agent::actTURN_R: return "TURN RIGHT";
		case Agent::actSUCK: return "SUCK";
		case Agent::actIDLE: return "IDLE";
		default: return "???";
	}
}