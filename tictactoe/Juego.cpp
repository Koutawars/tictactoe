#include "pch.h"
#include "Juego.h"

void Juego::initialize() {
	dibujar = true;
	// inicializando las variable dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		menu = std::vector <std::string>();
		break;
	case 1:
		turn = true;
		break;
	}

}

void Juego::loadContent() {
	// cargando el contenido dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		fuente = al_load_font("LemonMilkbold.otf", 38, NULL);
		menu.push_back("Iniciar");
		menu.push_back("Detalles");
		menu.push_back("Salir");
		posXMenu = 30;
		posYMenu = 145;
		separador = 55;
		select = -1; // -1 seleccionado ninguno
		break;
	case 1:
		fuente = al_load_font("LemonMilkbold.otf", 30, NULL);
		fuente2 = al_load_font("LemonMilkbold.otf", 40, NULL);
		fondoMap = al_load_bitmap("mapa.png");
		O = al_load_bitmap("O.png");
		X = al_load_bitmap("X.png");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mapa[i][j] = ' ';
			}
		}
		break;
	case 2:
		fuente = al_load_font("LemonMilkbold.otf", 30, NULL);
		break;
	}

}

void Juego::update(ALLEGRO_EVENT ev, bool *done) {
	// actualizando dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				int mouseY = ev.mouse.y;
				for (int i = 0; i < menu.size(); i++) {
					int posicionTexto = separador * i + posYMenu;
					if (posicionTexto < mouseY && posicionTexto + separador > mouseY) {
						switch (i) {
						case 0:
							cambiarPantalla(1);
							break;
						case 1:
							cambiarPantalla(2);
							break;
						case 2:
							*done = true;
							break;
						}
					}
				}
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			int mouseY = ev.mouse.y;
			bool encontrado = false;
			for (int i = 0; i < menu.size(); i++) {
				int posicionTexto = separador * i + posYMenu;
				if (posicionTexto < mouseY && posicionTexto + separador > mouseY) {
					select = i;
					dibujar = true;
					encontrado = true;
				}
			}
			if (!encontrado && select != -1) {
				select = -1;
				dibujar = true;
			}
		}
		break;
	case 1:
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				int mouseY = ev.mouse.y;
				int mouseX = ev.mouse.x;
				if (500 < mouseX && 640 > mouseX && 0 < mouseY && 46 > mouseY) {
					cambiarPantalla(0);
				}
			}
		}
		if (turn) {
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (ev.mouse.button & 1)
				{
					int mouseY = ev.mouse.y;
					int mouseX = ev.mouse.x;
					int posX = 141, posY = 55, casi = 105, tam = 13;
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							if (posX + (j * casi) + tam * (j + 1) < mouseX && posX + (j * casi) + tam * (j + 1) + casi > mouseX && posY + (i * casi) + tam * (i + 1) < mouseY && posY + (i * casi) + tam * (i + 1) + casi > mouseY) {
								mapa[i][j] = 'o';
								turn = false;
								dibujar = true;
							}
						}
					}
				}
			}
		}
		else {
			al_rest(1);
			mover(mapa);
			dibujar = true;
			turn = true;
		}

		break;
	case 2:
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				int mouseY = ev.mouse.y;
				int mouseX = ev.mouse.x;
				if (500 < mouseX && 640 > mouseX && 0 < mouseY && 46 > mouseY) {
					cambiarPantalla(0);
				}
			}
		}

		break;
	}
	
}

void Juego::draw(ALLEGRO_DISPLAY *display) {
	// dibujar dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		for (int i = 0; i < menu.size(); i++) {
			if (select == i) {
				al_draw_text(fuente, al_map_rgb(0, 255, 255), posXMenu, (i * separador) + posYMenu, NULL, menu[i].c_str());
			}
			else {
				al_draw_text(fuente, al_map_rgb(255, 255, 255), posXMenu, (i * separador) + posYMenu, NULL, menu[i].c_str());
			}
		}
		break;
	case 1: 
		{
			al_draw_bitmap(fondoMap, 0, 0, NULL);
			al_draw_text(fuente, al_map_rgb(255, 255, 255), 500, 8, NULL, "Atras");
			int posX = 141, posY = 55, casi = 105, tam = 13;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (mapa[i][j] == 'x') {
						al_draw_bitmap(X, posX + (j * casi) + tam * (j + 1), posY + (i * casi) + tam * (i + 1), NULL);
					}
					if (mapa[i][j] == 'o') {
						al_draw_bitmap(O, posX + (j * casi) + tam*(j + 1), posY + (i * casi) + tam * (i + 1), NULL);
					}
				}
			}

			if (evaluar(mapa) == 10) {
				al_flip_display();
				al_rest(1);
				al_draw_filled_rectangle(320 - 100, 210, 320 + 80, 220 + 50, al_map_rgb(0, 98, 88));
				al_draw_text(fuente2, al_map_rgb(255, 255, 255), 320, 215, ALLEGRO_ALIGN_CENTER, "Perdiste");
				al_flip_display();
				al_rest(2);
				cambiarPantalla(1);
				draw(display);
			}
			if (evaluar(mapa) == -10) {
				al_flip_display();
				al_rest(1);
				al_draw_filled_rectangle(320 - 100, 210, 320 + 80, 220 + 50, al_map_rgb(0, 98, 88));
				al_draw_text(fuente2, al_map_rgb(255, 255, 255), 320, 215, ALLEGRO_ALIGN_CENTER, "Usaste hacks");
				al_flip_display();
				al_rest(2);
				cambiarPantalla(1);
				draw(display);
			}
			if (!quedanMovimientos(mapa)) {
				al_flip_display();
				al_rest(1);
				al_draw_filled_rectangle(320 - 100, 200, 320 + 80, 220 + 50, al_map_rgb(0, 98, 88));
				al_draw_text(fuente2, al_map_rgb(255, 255, 255), 320, 215, ALLEGRO_ALIGN_CENTER, "Empate");
				al_flip_display();
				al_rest(2);
				cambiarPantalla(1);
				draw(display);
			}
		}
		break;
	case 2:
		al_draw_text(fuente, al_map_rgb(255, 255, 255), 500, 8, NULL, "Atras");
		break;
	}
}

void Juego::unLoadContent() {
	// quitar el contenido dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		menu.clear();
		al_destroy_font(fuente);
		break;
	case 1:
		al_destroy_bitmap(fondoMap);
		al_destroy_bitmap(X);
		al_destroy_bitmap(O);
		al_destroy_font(fuente);
		al_destroy_font(fuente2);
		
		break;
	case 2:
		al_destroy_font(fuente);
		break;
	}
}

void Juego::cambiarPantalla(int pantalla) {
	this->unLoadContent();
	this->pantalla = pantalla;
	this->initialize();
	this->loadContent();
}

void Juego::imprimir() {
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

void Juego::mover(char board[3][3]) {
	int maxEval = -99999, eval, moveI, moveJ;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				board[i][j] = 'x';
				eval = minimax(board, 0, false);
				maxEval = max(eval, maxEval);
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

int Juego::minimax(char board[3][3], int prof, bool turno) {
	int value = evaluar(board); // 10 = gana IA, -10 = gana jugador
	if (value == 10 || value == -10) return value;
	if (!quedanMovimientos(board)) return 0; // empate (no quedan movimientos)

	// turno = true (IA - X), turno = false (jugador - O)
	if (turno) {
		int maxEval = -99999, eval;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == ' ') {
					board[i][j] = 'x';
					eval = minimax(board, prof + 1, false);
					maxEval = max(eval, maxEval);
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
					eval = minimax(board, prof + 1, true);
					minEval = min(eval, minEval);
					board[i][j] = ' ';
				}
			}
		}
		return minEval;
	}
}

int Juego::evaluar(char board[3][3]) {
	int reg = 0;
	if (board[0][0] == 'x' && board[0][1] == 'x' && board[0][2] == 'x') reg = 10;
	if (board[0][0] == 'o' && board[0][1] == 'o' && board[0][2] == 'o') reg = -10;
	if (board[1][0] == 'x' && board[1][1] == 'x' && board[1][2] == 'x') reg = 10;
	if (board[1][0] == 'o' && board[1][1] == 'o' && board[1][2] == 'o') reg = -10;
	if (board[2][0] == 'x' && board[2][1] == 'x' && board[2][2] == 'x') reg = 10;
	if (board[2][0] == 'o' && board[2][1] == 'o' && board[2][2] == 'o') reg = -10;
	if (board[0][0] == 'x' && board[1][0] == 'x' && board[2][0] == 'x') reg = 10;
	if (board[0][0] == 'o' && board[1][0] == 'o' && board[2][0] == 'o') reg = -10;
	if (board[0][1] == 'x' && board[1][1] == 'x' && board[2][1] == 'x') reg = 10;
	if (board[0][1] == 'o' && board[1][1] == 'o' && board[2][1] == 'o') reg = -10;
	if (board[0][2] == 'x' && board[1][2] == 'x' && board[2][2] == 'x') reg = 10;
	if (board[0][2] == 'o' && board[1][2] == 'o' && board[2][2] == 'o') reg = -10;
	if (board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x') reg = 10;
	if (board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o') reg = -10;
	if (board[0][2] == 'x' && board[1][1] == 'x' && board[2][0] == 'x') reg = 10;
	if (board[0][2] == 'o' && board[1][1] == 'o' && board[2][0] == 'o') reg = -10;
	return reg;
}

bool Juego::quedanMovimientos(char board[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == ' ')
				return true;
	return false;
}

int Juego::max(int value1, int value2) {
	return value1 < value2 ? value2 : value1;
}

int Juego::min(int value1, int value2) {
	return value1 > value2 ? value2 : value1;
}

Juego &Juego::GetInstance()
{
	static Juego instance;
	return instance;
}

Juego::Juego() {}
Juego::~Juego() {}
