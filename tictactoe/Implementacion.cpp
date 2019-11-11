#include "pch.h"
#include "Implementacion.h"

void Implementacion::inicializar() {
	dibujar = true;
	// inicializando las variable dependiendo de la screen
	if (screen == 0) {
		opciones = std::vector <std::string>();
	}
	else if (screen == 1) {
		isturno = true;
	}
}

void Implementacion::cargarContenido() {
	// cargando el contenido dependiendo de la screen
	if (screen == 0) {
		tipo_de_letra = al_load_font("Legend M54.ttf", 38, NULL);
		fondoMenu = al_load_bitmap("fondoMenu.png");
		opciones.push_back("Iniciar");
		opciones.push_back("Salir");
		Menu_X_ubic = 380;
		Menu_Y_ubic = 245;
		entrelineado = 85;
		opcion_seleccionada = -1; // -1 seleccionado ninguno
	}
	else if (screen == 1) {
		tipo_de_letra = al_load_font("Legend M54.ttf", 30, NULL);
		tipo_de_letra2 = al_load_font("Legend M54.ttf", 40, NULL);
		Mapa_triquis = al_load_bitmap("mapa.png");
		O = al_load_bitmap("O.png");
		X = al_load_bitmap("X.png");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mapa[i][j] = ' ';
			}
		}
	}

}

void Implementacion::actualizar(ALLEGRO_EVENT ev, bool *terminar) {
	// actualizando dependiendo de la screen
	if (screen == 0) {
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				int mouseY = ev.mouse.y;
				for (int i = 0; i < opciones.size(); i++) {
					int posicionTexto = entrelineado * i + Menu_Y_ubic;
					if (posicionTexto < mouseY && posicionTexto + entrelineado > mouseY) {
						switch (i) {
						case 0:
							moverScreen(1);
							break;
						case 1:
							*terminar = true;
							break;
						}
					}
				}
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			int mouseY = ev.mouse.y;
			bool encontrado = false;
			for (int i = 0; i < opciones.size(); i++) {
				int posicionTexto = entrelineado * i + Menu_Y_ubic;
				if (posicionTexto < mouseY && posicionTexto + entrelineado > mouseY) {
					opcion_seleccionada = i;
					dibujar = true;
					encontrado = true;
				}
			}
			if (!encontrado && opcion_seleccionada != -1) {
				opcion_seleccionada = -1;
				dibujar = true;
			}
		}
	}
	else if (screen == 1) {
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				int mouseY = ev.mouse.y;
				int mouseX = ev.mouse.x;
				if (0 < mouseX && 90 > mouseX && 0 < mouseY && 46 > mouseY) {
					moverScreen(0);
				}
			}
		}
		if (isturno) {
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (ev.mouse.button & 1)
				{
					int mouseY = ev.mouse.y;
					int mouseX = ev.mouse.x;
					int posX = 141, posY = 55, casi = 105, tam = 13;
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							if (mapa[i][j] == ' ') {
								if (posX + (j * casi) + tam * (j + 1) < mouseX && posX + (j * casi) + tam * (j + 1) + casi > mouseX && posY + (i * casi) + tam * (i + 1) < mouseY && posY + (i * casi) + tam * (i + 1) + casi > mouseY) {
									mapa[i][j] = 'o';
									isturno = false;
									dibujar = true;
								}
							}
						}
					}
				}
			}
		}
		else {
			al_rest(1);
			Mov(mapa);
			dibujar = true;
			isturno = true;
		}
	}
	
}

void Implementacion::pintar(ALLEGRO_DISPLAY *display) {
	// dibujar dependiendo de la screen
	if (screen == 0) {
		al_draw_bitmap(fondoMenu, 0, 0, NULL);
		for (int i = 0; i < opciones.size(); i++) {

			al_draw_text(tipo_de_letra, al_map_rgb(0, 0, 0), Menu_X_ubic, (i * entrelineado) + Menu_Y_ubic, NULL, opciones[i].c_str());

		}
	}
	else if (screen == 1) {
		{
			al_draw_bitmap(Mapa_triquis, 0, 0, NULL);
			al_draw_text(tipo_de_letra, al_map_rgb(0, 0, 0), 8, 8, NULL, "Atras");
			int posX = 141, posY = 55, casi = 105, tam = 13;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (mapa[i][j] == 'x') {
						al_draw_bitmap(X, posX + (j * casi) + tam * (j + 1), posY + (i * casi) + tam * (i + 1), NULL);
					}
					if (mapa[i][j] == 'o') {
						al_draw_bitmap(O, posX + (j * casi) + tam * (j + 1), posY + (i * casi) + tam * (i + 1), NULL);
					}
				}
			}

			if (evaluar(mapa) == 10) {
				al_flip_display();
				al_rest(1);
				al_draw_filled_rectangle(320 - 100, 210, 320 + 80, 220 + 50, al_map_rgb(0, 0, 0));
				al_draw_text(tipo_de_letra2, al_map_rgb(255, 255, 255), 320, 215, ALLEGRO_ALIGN_CENTER, "Defeat");
				al_flip_display();
				al_rest(2);
				moverScreen(1);
				pintar(display);
			}
			if (evaluar(mapa) == -10) {
				al_flip_display();
				al_rest(1);
				al_draw_filled_rectangle(320 - 100, 210, 320 + 80, 220 + 50, al_map_rgb(0, 0, 0));
				al_draw_text(tipo_de_letra2, al_map_rgb(255, 255, 255), 320, 215, ALLEGRO_ALIGN_CENTER, "Usaste hacks");
				al_flip_display();
				al_rest(2);
				moverScreen(1);
				pintar(display);
			}
			if (!quedanMovimientos(mapa)) {
				al_flip_display();
				al_rest(1);
				al_draw_filled_rectangle(320 - 100, 200, 320 + 80, 220 + 50, al_map_rgb(0, 0, 0));
				al_draw_text(tipo_de_letra2, al_map_rgb(255, 255, 255), 320, 215, ALLEGRO_ALIGN_CENTER, "Tie");
				al_flip_display();
				al_rest(2);
				moverScreen(1);
				pintar(display);
			}
		}
	}
}

void Implementacion::DesCargar() {
	// quitar el contenido dependiendo de la screen
	if (screen == 0) {
		opciones.clear();
		al_destroy_font(tipo_de_letra);
		al_destroy_bitmap(fondoMenu);
	}
	else if (screen == 1) {
		al_destroy_bitmap(Mapa_triquis);
		al_destroy_bitmap(X);
		al_destroy_bitmap(O);
		al_destroy_font(tipo_de_letra);
		al_destroy_font(tipo_de_letra2);
	}
	else if (screen == 2) {
		al_destroy_font(tipo_de_letra);
		al_destroy_font(tipo_de_letra2);
	}
}

void Implementacion::moverScreen(int screen) {
	this->DesCargar();
	this->screen = screen;
	this->inicializar();
	this->cargarContenido();
}

void Implementacion::imprimir() {
	std::cout << "-------" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << "|";
		for (int j = 0; j < 3; j++) {
			std::cout << mapa[i][j] << " ";
		}
		std::cout <<"|"<< std::endl;
	}
	std::cout << "-------" << std::endl;

}

void Implementacion::Mov(char board[3][3]) {
	int maxEval = -99999, eval, moveI, moveJ;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				board[i][j] = 'x';
				eval = Algortimo_MiniMax(board, 0, false);
				maxEval = MAXIMO(eval, maxEval);
				if (maxEval == eval) {
					moveI = i;
					moveJ = j;
				}
				board[i][j] = ' ';
			}
		}
	}
	mapa[moveI][moveJ] = 'x';
	dibujar = true;
}

int Implementacion::Algortimo_MiniMax(char board[3][3], int prof, bool turno) {
	int value = evaluar(board); // 10 = gana IA, -10 = gana jugador
	//if (value == 10 || value == -10) return value; // otra forma de hacerlo, esto no importa el numero de pasos
	if (value == 10) return value - prof;
	if (value == -10) return value + prof;
	if (!quedanMovimientos(board)) return 0; // empate (no quedan movimientos)

	// turno = true (IA - X), turno = false (jugador - O)
	if (turno) {
		int maxEval = -99999, eval;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = 'x';
					eval = Algortimo_MiniMax(board, prof + 1, false);
					maxEval = MAXIMO(eval, maxEval);
					board[i][j] = ' ';
				}
			}
		}
		return maxEval;
	}
	else {
		int minEval = 99999, eval;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = 'o';
					eval = Algortimo_MiniMax(board, prof + 1, true);
					minEval = MINIMO(eval, minEval);
					board[i][j] = ' ';
				}
			}
		}
		return minEval;
	}
}

int Implementacion::evaluar(char tablero[3][3]) {
	int reg = 0;
	if (tablero[0][0] == 'x' && tablero[0][1] == 'x' && tablero[0][2] == 'x') reg = 10;
	if (tablero[0][0] == 'o' && tablero[0][1] == 'o' && tablero[0][2] == 'o') reg = -10;
	if (tablero[1][0] == 'x' && tablero[1][1] == 'x' && tablero[1][2] == 'x') reg = 10;
	if (tablero[1][0] == 'o' && tablero[1][1] == 'o' && tablero[1][2] == 'o') reg = -10;
	if (tablero[2][0] == 'x' && tablero[2][1] == 'x' && tablero[2][2] == 'x') reg = 10;
	if (tablero[2][0] == 'o' && tablero[2][1] == 'o' && tablero[2][2] == 'o') reg = -10;
	if (tablero[0][0] == 'x' && tablero[1][0] == 'x' && tablero[2][0] == 'x') reg = 10;
	if (tablero[0][0] == 'o' && tablero[1][0] == 'o' && tablero[2][0] == 'o') reg = -10;
	if (tablero[0][1] == 'x' && tablero[1][1] == 'x' && tablero[2][1] == 'x') reg = 10;
	if (tablero[0][1] == 'o' && tablero[1][1] == 'o' && tablero[2][1] == 'o') reg = -10;
	if (tablero[0][2] == 'x' && tablero[1][2] == 'x' && tablero[2][2] == 'x') reg = 10;
	if (tablero[0][2] == 'o' && tablero[1][2] == 'o' && tablero[2][2] == 'o') reg = -10;
	if (tablero[0][0] == 'x' && tablero[1][1] == 'x' && tablero[2][2] == 'x') reg = 10;
	if (tablero[0][0] == 'o' && tablero[1][1] == 'o' && tablero[2][2] == 'o') reg = -10;
	if (tablero[0][2] == 'x' && tablero[1][1] == 'x' && tablero[2][0] == 'x') reg = 10;
	if (tablero[0][2] == 'o' && tablero[1][1] == 'o' && tablero[2][0] == 'o') reg = -10;
	return reg;
}

bool Implementacion::quedanMovimientos(char tablero[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (tablero[i][j] == ' ')
				return true;
	return false;
}

int Implementacion::MAXIMO(int value1, int value2) {
	return value1 < value2 ? value2 : value1;
}

int Implementacion::MINIMO(int value1, int value2) {
	return value1 > value2 ? value2 : value1;
}

Implementacion &Implementacion::getSingleton()
{
	static Implementacion instance;
	return instance;
}

Implementacion::Implementacion() {}
Implementacion::~Implementacion() {}
