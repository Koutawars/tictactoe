
#include "pch.h"
#include <iostream>

#include "Implementacion.h"

int main()
{

	ALLEGRO_DISPLAY *display = NULL;
	if (!al_init()) {
		std::cout << "failed to initialize allegro!\n";
		return -1;
	}

	display = al_create_display(640, 480);
	al_install_keyboard();
	al_install_mouse();

	al_init_image_addon();
	al_init_primitives_addon();

	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_BITMAP *icon = al_load_bitmap("icon.png");
	al_set_display_icon(display, icon);
	al_set_window_title(display, "Juego divertido del triqui");


	Implementacion::getSingleton().inicializar();
	Implementacion::getSingleton().cargarContenido();

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0f);


	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	bool done = false;
	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		Implementacion::getSingleton().actualizar(ev, &done);
		if (Implementacion::getSingleton().dibujar) {
			Implementacion::getSingleton().pintar(display);
			Implementacion::getSingleton().dibujar = false;
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	Implementacion::getSingleton().DesCargar();
	return 0;
}