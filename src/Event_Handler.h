#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "../include/SDL2/SDL.h"
class Event_Handler
{
private:
    SDL_Event event;

    int x, y;
    Uint32 mouse_state;
    const Uint8* keyboard_state;

public:
    enum Mouse_Button : int
    {
        LEFT = 1,
        MIDDLE,
        RIGHT
    };

    Event_Handler();
    ~Event_Handler();

    int update();

    int mouse_x();
    int mouse_y();

    bool mouse_down(Mouse_Button button);
    bool key_down(SDL_Scancode key);
    SDL_Event* triggered(SDL_EventType type);
};

#endif
