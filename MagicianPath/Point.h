#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
	float X, Y;

	Point(float x = 0, float y = 0) : X(x), Y(y) {}


	inline Point operator+(const Point v2) const
	{
		return Point(this->X + v2.X, this->Y + v2.Y);
	}

	inline Point operator-(const Point v2) const
	{
		return Point(this->X - v2.X, this->Y - v2.Y);
	}

	inline Point operator*(const float scalar) const
	{
		return Point(scalar * this->X, scalar * this->Y);
	}


	void Log(std::string message = "")
	{
		std::cout << message << "(X Y) = (" << X << " " << Y << ")" << std::endl;
	}


};

#endif POINT_H
