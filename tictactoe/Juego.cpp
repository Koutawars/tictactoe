#include "pch.h"
#include "Juego.h"

void Juego::initialize() {
	// inicializando las variable dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		dibujar = true;
		menu = std::vector <std::string>();
		break;
	}

}

void Juego::loadContent() {
	// cargando el contenido dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		fuente = al_load_font("Patchwork Stitchlings.ttf", 20, NULL);
		menu.push_back("Iniciar");
		menu.push_back("Detalles");
		menu.push_back("Salir");
		posXMenu = 30;
		posYMenu = 145;
		separador = 55;
		select = -1; // -1 seleccionado ninguno
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

		break;
	}
}

void Juego::unLoadContent() {
	// quitar el contenido dependiendo de la pantalla
	switch (pantalla) {
	case 0:
		al_destroy_font(fuente);
		break;
	}
}

void Juego::cambiarPantalla(int pantalla) {
	this->unLoadContent();
	this->pantalla = pantalla;
	this->initialize();
	this->loadContent();
	dibujar = true;
}

Juego &Juego::GetInstance()
{
	static Juego instance;
	return instance;
}

Juego::Juego() {}
Juego::~Juego() {}
