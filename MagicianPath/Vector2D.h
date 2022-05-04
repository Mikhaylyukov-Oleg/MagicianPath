#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
public:

	float X, Y;

	Vector2D(float x = 0, float y = 0) : X(x), Y(y)	{}


	inline Vector2D operator+(const Vector2D v2) const
	{
		return Vector2D(this->X + v2.X, this->Y + v2.Y);
	}

	inline Vector2D operator-(const Vector2D v2) const
	{
		return Vector2D(this->X - v2.X, this->Y - v2.Y);
	}

	inline Vector2D operator*(const float scalar) const
	{
		return Vector2D(scalar * this->X, scalar * this->Y);
	}
	

	void Log(std::string message = "")
	{
		std::cout << message << "(X Y) = (" << X << " " << Y << ")" << std::endl;
	}
};

#endif VECTOR2D_H