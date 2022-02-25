#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>





struct Vector2
{
private:
	

public:
	double x;
	double y;

	Vector2(double _x = 0, double _y = 0);

	~Vector2();

	int   Vector2::vector2DMP();
	bool  Vector2::vector2OK();

	Vector2 operator +  (const Vector2& other) const;
	Vector2 operator -  (const Vector2& other) const;
	Vector2 operator += (const Vector2& other);
	Vector2 operator -= (const Vector2& other);
	double  operator *= (const Vector2& other);
	double  operator ^  (const Vector2& other);
	Vector2 operator *  (const double   k    ) const;
	Vector2 operator /  (const double   k    ) const;
	Vector2 rotate      (      double   k    );
	Vector2 getRotated  (      double   k    ) const;
	Vector2 operator -  ();
	double  angle       (const Vector2& other);

	double  len () const;
	Vector2 norm();
	Vector2 perp();

	friend std::ostream& operator << (std::ostream& stream, const Vector2& v);
	friend std::istream& operator >> (std::istream& stream, Vector2& v);
};

Vector2 operator * (const double k, const Vector2& other);
