#include "Vector2d.h"
#include <iostream>
#include <cmath>

Vector2d::Vector2d(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector2d::~Vector2d()
{

}

void Vector2d::print()
{
	std::cout
		<< "Vector: (" << x << ", " << y << "), |"
	  	<< get_length() << "|" <<
	std::endl;
}

Vector2d Vector2d::operator+(Vector2d vec)
{
	return Vector2d(x + vec.x, y + vec.y);
}

void Vector2d::operator+=(Vector2d vec)
{
	x += vec.x;
	y += vec.y;
}

Vector2d Vector2d::operator-(Vector2d vec)
{
	return Vector2d(x - vec.x, y - vec.y);
}

void Vector2d::operator-=(Vector2d vec)
{
	x -= vec.x;
	y -= vec.y;
}

Vector2d Vector2d::operator*(double count)
{
	return Vector2d(x * count, y * count);
}

void Vector2d::operator*=(double count)
{
	x *= count;
	y *= count;
}

Vector2d Vector2d::operator/(double count)
{
	return Vector2d(x / count, y / count);
}

void Vector2d::operator/=(double count)
{
	if(!count)
	{
		throw "Division by zero exception";
	}

	x /= count;
	y /= count;
}
/*
bool Vector2d::operator==(Vector2d vec)
{
	int x1 = std::round(x);
	int x2 = std::round(vec.x);

	int y1 = std::round(y);
	int y2 = std::round(vec.y);

	if (x1 == x2 && y1 == y2)
	{
		return true;
	}

	return false;
}
*/
Vector2d Vector2d::normalize()
{
	if(!get_length())
	{
		return Vector2d(0.0, 0.0);
	}
	return Vector2d(x / get_length(), y / get_length());
}

void Vector2d::set_x(double x)
{
	this->x = x;
}

void Vector2d::set_y(double y)
{
	this->y = y;
}

double Vector2d::get_x()
{
	return x;
}

double Vector2d::get_y()
{
	return y;
}

double Vector2d::get_length()
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
