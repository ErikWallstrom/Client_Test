#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
private:
	double x;
	double y;

public:
	Vector2d(double x, double y);
	~Vector2d();

	void print();
	Vector2d operator+(Vector2d vec);
	void operator+=(Vector2d vec);
	Vector2d operator-(Vector2d vec);
	void operator-=(Vector2d vec);
	Vector2d operator*(double count);
	void operator*=(double count);
	Vector2d operator/(double count);
	void operator/=(double count);
	//bool operator==(Vector2d vec);

	Vector2d normalize();

	void set_x(double x);
	void set_y(double y);

	double get_x();
	double get_y();
	double get_length();
};

#endif
