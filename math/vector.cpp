#include "vector.h"

vector2d::vector2d(float ix, float iy) {
	x = ix;
	y = iy;
}

vector2d::vector2d(float i)
{
	x = i;
	y = i;
}


vector2d::vector2d() {
	x = 0;
	y = 0;
}

vector2d vector2d::operator+(const vector2d& right) const {
	vector2d temp(*this);
	temp += right;
	return temp;
}

vector2d vector2d::operator-(const vector2d& right) const {
	vector2d temp(*this);
	temp -= right;
	return temp;
}

vector2d vector2d::operator*(const vector2d& right) const {
	vector2d temp(*this);
	temp *= right;
	return temp;
}

vector2d vector2d::operator/(const vector2d& right) const {
	vector2d temp(*this);
	temp /= right;
	return temp;
}

vector2d& vector2d::operator+=(const vector2d& right) {
	x += right.x;
	y += right.y;
	return *this;
}

vector2d& vector2d::operator-=(const vector2d& right) {
	x -= right.x;
	y -= right.y;
	return *this;
}

vector2d& vector2d::operator*=(const vector2d& right) {
	x *= right.x;
	y *= right.y;
	return *this;
}

vector2d& vector2d::operator/=(const vector2d& right) {
	if (right.x != 0 && right.y != 0) {
		x /= right.x;
		y /= right.y;
	}
	return *this;
}

vector2d& vector2d::setaddvec(vector2d a) {
	x += a.x;
	y += a.y;
	return *this;
}
vector2d& vector2d::setsubvec(vector2d a) {
	x -= a.x;
	y -= a.y;
	return *this;
}

vector2d vector2d::addvec(vector2d a) {
	return vector2d(x + a.x, y + a.y);
}
vector2d vector2d::subvec(vector2d a) {
	return vector2d(x - a.x, y - a.y);
}



vector2d vector2d::addf(float a) {
	return vector2d(x + a, y + a);
}

vector2d vector2d::mulf(float a) {
	return vector2d(x * a, y * a);
}

vector2d vector2d::divf(float a) {
	if(a==0)
		return vector2d();
	return vector2d(x / a, y / a);
}




vector2d& vector2d::normalize() {
	float l = magnitude();
	if (l > 0) {
		x /= l;
		y /= l;

		return *this;
	}
	clear();
	return *this;
}
vector2d& vector2d::normalize(float mag) {
	if (mag > 0) {
		x /= mag;
		y /= mag;

		return *this;
	}
	clear();
	return *this;
}


float vector2d::dotProduct(const vector2d& left, const vector2d& right) {
	return left.x * right.x + left.y * right.y;
}

float vector2d::magnitudesq() const {
	return (x*x) + (y*y);
}

float vector2d::magnitude() const {
	return sqrtf((x*x) + (y+y));
}

void vector2d::clear()
{
		x = 0;
	y = 0;
}
