#pragma once
#include <cmath>
class Vector2D
{
public:
	Vector2D(float x = 0, float y = 0)
		: _x(x), _y(y) {}

	//getters
	float getX() { return _x; }
	float getY() { return _y; }
	
	//setters
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	
	//length of a vector
	float length() { return sqrt(_x*_x + _y * _y); }
	
	//adding & substracting two vectors
	Vector2D operator+(const Vector2D& v1)
	{
		return Vector2D(_x + v1._x, _y + v1._y);
	}
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1._x += v2._x;
		v1._y += v2._y;
		return v1;
	}
	Vector2D operator-(const Vector2D& v1)
	{
		return Vector2D(_x - v1._x, _y - v1._y);
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1._x -= v2._x;
		v1._y -= v2._y;
		return v1;
	}
	
	//vector * scalar, vector / scalar
	Vector2D operator*(float scalar)
	{
		return Vector2D(_x*scalar, _y*scalar);
	}
	Vector2D operator*=(float scalar)
	{
		_x *= scalar;
		_y *= scalar;
		return *this;
	}
	Vector2D operator/(float scalar)
	{
		return Vector2D(_x / scalar, _y / scalar);
	}
	Vector2D operator/=(float scalar)
	{
		_x /= scalar;
		_y /= scalar;
		return *this;
	}
	
	//normalize vector
	void normalize()
	{
		float l = length();
		if (l > 0)
		{
			(*this) *= 1 / l;
		}
	}
private:
	//coordinates
	float _x, _y;
};

