#include "Player.h"
#include <iostream>

Player::Player(double x, double y, int width, int height)
: Game_Object(x, y, width, height), start(x, y), goal(x, y)
{
    pixel_per_second = 800.0 / 1.8;
    moving = false;
    max_hp = 500.0;
    current_hp = max_hp;
}

Player::~Player()
{

}

void Player::update(int delta_time)
{
	if(moving)
	{
		Vector2d direction = (goal - start).normalize();
        Vector2d move_vec = direction * pixel_per_second * (
			delta_time / 1000.0
		);

        if((position + move_vec - start).get_length() >
          (goal - start).get_length())
        {
            position = goal;
            moving = false;
        }
        else
        {
            position += move_vec;
        }
	}
}

void Player::render(SDL_Renderer* renderer)
{
    Game_Object::render(renderer);
    SDL_Rect hp_bar = {
        static_cast<int>(
            position.get_x() -(static_cast<double>(width) * 1.25) / 2.0
        ),
        static_cast<int>(position.get_y() +
            (static_cast<double>(height) * 1.25) / 2.0
        ),
        static_cast<int>(
            static_cast<double>(
                width * 1.25
            ) * current_hp / max_hp
        ),
        20
    };
    SDL_RenderFillRect(renderer, &hp_bar);
}

void Player::handle_events(Event_Handler handler)
{

}

void Player::move_to(Vector2d goal)
{
    if(goal.get_x() != 0.0 && goal.get_y() != 0.0)
    {
        start = position;
        this->goal = goal;

    	moving = true;
    }
}

void Player::set_hp(double hp)
{
    current_hp = hp;
    if(current_hp < 0)
    {
        current_hp = 0.0;
    }
    /*else if(current_hp > max_hp)
    {
        current_hp = max_hp;
    }*/
}

double Player::get_hp()
{
    return current_hp;
}
