#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <vector>

class Juego
{
private:
	Juego();
	~Juego();
public:

	static Juego &GetInstance(); // función para obtener un objeto de su propia clase (singleton)

	void initialize(); // función para inicializar variables
	void loadContent(); // función para cargar el contenido
	void unLoadContent(); // función para quitar el contenido
	void update(ALLEGRO_EVENT ev, bool *done); // función para hacer calculos
	void draw(ALLEGRO_DISPLAY *display); // funcion para dibujar
	void cambiarPantalla(int pantalla); // función para cambiar de pantalla
	int pantalla = 0; // en la pantalla que te encuentras
	bool dibujar; // true cuando se actualiza la pantalla

	/* Pantalla = 0 (menu) */
	std::vector <std::string> menu; // vector del opciones del menu (texto)
	ALLEGRO_FONT *fuente; // fuente que se utilizará para imprimir el menu en pantalla
	int select; // guarda el indice que brilla cuando pasa el mouse encima del vector del menu
	int posXMenu; // la posición X desde el 0,0 de la ventana
	int posYMenu; // la posición Y desde el 0,0 de la ventana
	int separador; // es el separador en pixeles por cada opcion del menu

	/* Pantalla = 1 (juego - gameplay) */
	ALLEGRO_BITMAP *fondoMap; // el fondo del mapa 
	ALLEGRO_BITMAP *O; // imagen de O (jugador)
	ALLEGRO_BITMAP *X; // Imagen de X (IA)
	ALLEGRO_FONT *fuente2; // fuente para mostrar anuncios
	char mapa[3][3]; // el mapa char de 3x3
	bool turn; // turn = true(jugador), turn = false (IA) 
	int max(int value1, int value2); // devuelve el mayor de los dos numeros
	int min(int value1, int value2); // devuelve el menor de los dos numeros
	bool quedanMovimientos(char board[3][3]); // función que mira si hay movimientos o no, (espacios en blanco)
	void mover(char board[3][3]); // función que mueve la IA 
	int evaluar(char board[3][3]); // evalua quien gana la IA (10) o el jugador (-10) 
	int minimax(char board[3][3], int prof, bool turno); // algoritmo minimax(recursivo) board, profundidad y el turno
	void imprimir(); // imprimir el tablero en la consola
};

