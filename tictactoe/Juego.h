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

	static Juego &GetInstance(); // funci�n para obtener un objeto de su propia clase (singleton)

	void initialize(); // funci�n para inicializar variables
	void loadContent(); // funci�n para cargar el contenido
	void unLoadContent(); // funci�n para quitar el contenido
	void update(ALLEGRO_EVENT ev, bool *done); // funci�n para hacer calculos
	void draw(ALLEGRO_DISPLAY *display); // funcion para dibujar
	void cambiarPantalla(int pantalla); // funci�n para cambiar de pantalla
	int pantalla = 0; // en la pantalla que te encuentras
	bool dibujar; // true cuando se actualiza la pantalla

	/* Pantalla = 0 (menu) */
	std::vector <std::string> menu; // vector del opciones del menu (texto)
	ALLEGRO_FONT *fuente; // fuente que se utilizar� para imprimir el menu en pantalla
	int select; // guarda el indice que brilla cuando pasa el mouse encima del vector del menu
	int posXMenu; // la posici�n X desde el 0,0 de la ventana
	int posYMenu; // la posici�n Y desde el 0,0 de la ventana
	int separador; // es el separador en pixeles por cada opcion del menu

};

