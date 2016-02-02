#ifndef PLAYER_H
#define PLAYER_H

#include "Game_Object.h"
class Player : public Game_Object
{
private:
	Vector2d start;
    Vector2d goal;

    double pixel_per_second;
    bool moving;
	double max_hp;
	double current_hp;

public:
    Player(double x, double y, int width, int height);
    ~Player();

    virtual void update(int delta_time);
	virtual void render(SDL_Renderer* renderer);
	virtual void handle_events(Event_Handler handler);
    void move_to(Vector2d goal);
	void set_hp(double hp);
	double get_hp();
};

#endif
