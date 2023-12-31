#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "AllegroSettings.h"
#include "ProgramTypes.h"

int main()
{
    DisplaySettings* Display = malloc(sizeof(DisplaySettings));
    PositionMouse* Mouse = malloc(sizeof(PositionMouse));
    
    if (Display != NULL && Mouse != NULL) {
        Display->Height = 720;
        Display->Width = 920;
        Mouse->x = 0;
        Mouse->y = 0;

        initialize();

        ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
        ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
        ALLEGRO_DISPLAY* disp = al_create_display(Display->Width, Display->Height);
        ALLEGRO_FONT* font = al_create_builtin_font();

        if (!timer || !queue || !font || !disp) {
            printf("[ERROR] Não foi possível iniciar as variáveis de inicialização do jogo!");
            return 1;
        }

        registersEvent(disp, timer, queue);

        bool redraw = true;
        ALLEGRO_EVENT event;
        al_start_timer(timer);

        while (1)
        {
            bool done = false;

            al_wait_for_event(queue, &event);

            switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                Mouse->x = event.mouse.x;
                Mouse->y = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(event.mouse.button == 1)
                    al_draw_filled_rectangle(Mouse->x - 15, Mouse->y - 15, Mouse->x + 15, Mouse->y + 15, al_map_rgb(0, 0, 255));
                else
                    al_draw_filled_rectangle(Mouse->x - 15, Mouse->y - 15, Mouse->x + 15, Mouse->y + 15, al_map_rgb(255, 0, 0));

            }

            if (done) break;

            if (redraw && al_is_event_queue_empty(queue))
            {   
                al_flip_display();
                redraw = false;
            }
        }

        finish(timer, queue, disp, font);
        freeAllTypes(Display, Mouse);
    }
    return 0;
}