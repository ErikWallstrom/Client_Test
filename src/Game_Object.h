#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../include/SDL2/SDL.h"
#include "Event_Handler.h"
#include "Vector2d.h"
class Game_Object
{
protected:
    SDL_Texture* texture;
    int width, height;

public:
    Vector2d position;

    Game_Object(double x, double y, int width, int height);
    virtual ~Game_Object();

    virtual void print();
    virtual void update(int delta_time);
    virtual void render(SDL_Renderer* renderer);
    virtual void handle_events(Event_Handler& handler);

    bool intersects_rect(Game_Object& object);
	bool intersects_point(Vector2d& point);

    void set_texture(SDL_Texture* texture);
    void set_width(int width);
    void set_height(int height);

    int get_width();
    int get_height();
};

#endif
