#include "Event_Handler.h"

Event_Handler::Event_Handler()
    : keyboard_state(SDL_GetKeyboardState(NULL))
{

}

Event_Handler::~Event_Handler()
{

}

int Event_Handler::update()
{
    mouse_state = SDL_GetMouseState(&x, &y);
    return SDL_PollEvent(&event);
}

bool Event_Handler::mouse_down(Mouse_Button button)
{
    if(mouse_state & SDL_BUTTON(button))
    {
        return true;
    }

    return false;
}

int Event_Handler::mouse_x()
{
    return x;
}

int Event_Handler::mouse_y()
{
    return y;
}

bool Event_Handler::key_down(SDL_Scancode key)
{
    if(keyboard_state[key])
    {
        return true;
    }

    return false;
}

SDL_Event* Event_Handler::triggered(SDL_EventType type)
{
    if(event.type == type)
    {
        return &event;
    }

    return NULL;
}
