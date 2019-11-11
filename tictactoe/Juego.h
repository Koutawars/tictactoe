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

	void inicializar(); // función para inicializar variables
	void cargarContenido(); // función para cargar el contenido
	void DesCargar(); // función para quitar el contenido
	void actualizar(ALLEGRO_EVENT ev, bool *done); // función para hacer calculos
	void pintar(ALLEGRO_DISPLAY *display); // funcion para dibujar
	void moverScreen(int screen); // función para cambiar de screen
	int screen = 0; // en la screen que te encuentras
	bool dibujar; // true cuando se actualiza la screen

	/* Pantalla = 0 (opciones) */
	std::vector <std::string> opciones; // vector del opciones del opciones (texto)
	ALLEGRO_FONT *tipo_de_letra; // tipo_de_letra que se utilizará para imprimir el opciones en screen
	ALLEGRO_BITMAP *fondoMenu; // el fondo del opciones
	int opcion_seleccionada; // guarda el indice que brilla cuando pasa el mouse encima del vector del opciones
	int Menu_X_ubic; // la posición X desde el 0,0 de la ventana
	int Menu_Y_ubic; // la posición Y desde el 0,0 de la ventana
	int entrelineado; // es el entrelineado en pixeles por cada opcion del opciones

	/* Pantalla = 1 (juego - gameplay) */
	ALLEGRO_BITMAP *Mapa_triquis; // el fondo del mapa 
	ALLEGRO_BITMAP *O; // imagen de O (jugador)
	ALLEGRO_BITMAP *X; // Imagen de X (IA)
	ALLEGRO_FONT *tipo_de_letra2; // tipo_de_letra para mostrar anuncios
	char mapa[3][3]; // el mapa char de 3x3
	bool isturno; // isturno = true(jugador), isturno = false (IA) 
	int MAXIMO(int value1, int value2); // devuelve el mayor de los dos numeros
	int MINIMO(int value1, int value2); // devuelve el menor de los dos numeros
	bool quedanMovimientos(char board[3][3]); // función que mira si hay movimientos o no, (espacios en blanco)
	void Mov(char board[3][3]); // función que mueve la IA 
	int evaluar(char board[3][3]); // evalua quien gana la IA (10) o el jugador (-10) 
	int Algortimo_MiniMax(char board[3][3], int prof, bool turno); // algoritmo Algortimo_MiniMax(recursivo) board, profundidad y el turno
	void imprimir(); // imprimir el tablero en la consola
};

