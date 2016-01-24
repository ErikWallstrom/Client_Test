#include "Game_Object.h"
#include <iostream>
#include <cmath>

Game_Object::Game_Object(double x, double y, int width, int height)
: position(x, y)
{
    texture = nullptr;

    this->width = width;
    this->height = height;
}

Game_Object::~Game_Object()
{

}

void Game_Object::print()
{
    std::cout << "Game_Object: \n : ";
    position.print();
    std::cout << " : " << width << "x" << height << std::endl;
}

void Game_Object::update(int delta_time)
{
    delta_time = delta_time;
}

void Game_Object::render(SDL_Renderer* renderer)
{
    if(texture)
    {
        SDL_Rect d_rect = {
            static_cast<int>(
                std::round(
                    position.get_x() - static_cast<double>(width) / 2
                )
            ),
            static_cast<int>(
                std::round(
                    position.get_y() - static_cast<double>(height) / 2
                )
            ),
            width, height
        };

        SDL_RenderCopy(
            renderer, texture, nullptr, &d_rect
        );
    }
}

void Game_Object::handle_events(Event_Handler& event)
{
    event = event;
}

bool Game_Object::intersects_rect(Game_Object& object)
{
    SDL_Rect a = {
        static_cast<int>(
            std::round(
                position.get_x() - static_cast<double>(width) / 2
            )
        ),
        static_cast<int>(
            std::round(
                position.get_y() - static_cast<double>(height) / 2
            )
        ),
        width, height
    };
    SDL_Rect b = {
        static_cast<int>(
            std::round(
                object.position.get_x() - static_cast<double>(object.get_width()) / 2
            )
        ),
        static_cast<int>(
            std::round(
                object.position.get_y() - static_cast<double>(object.get_height()) / 2
            )
        ),
        object.get_width(), object.get_height()
    };

	return SDL_HasIntersection(&a, &b);
}

bool Game_Object::intersects_point(Vector2d& point)
{
	if (point.get_x() > position.get_x() - width / 2.0
		&& point.get_x() < position.get_x() + width / 2.0
		&& point.get_y() > position.get_y() - height / 2.0
		&& point.get_y() < position.get_y() + height / 2.0
	   )
	{
		return true;
	}

	return false;
}

void Game_Object::set_texture(SDL_Texture* texture)
{
    this->texture = texture;
}

void Game_Object::set_width(int width)
{
    this->width = width;
}

void Game_Object::set_height(int height)
{
    this->height = height;
}

int Game_Object::get_width()
{
    return width;
}

int Game_Object::get_height()
{
    return height;
}
