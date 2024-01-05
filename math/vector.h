#pragma once
#include <cmath>

class vector2d {
public:
	//variables
	float x, y;

	//constructors
	vector2d(float ix, float iy);
	vector2d(float i);
	vector2d();

	//operators
	vector2d operator+(const vector2d& right) const;
	vector2d operator-(const vector2d& right) const;
	vector2d operator*(const vector2d& right) const;
	vector2d operator/(const vector2d& right) const;
	vector2d& operator+=(const vector2d& right);
	vector2d& operator-=(const vector2d& right);
	vector2d& operator*=(const vector2d& right);
	vector2d& operator/=(const vector2d& right);

	vector2d addf(float a);
	vector2d mulf(float a);
	vector2d divf(float a);

	vector2d& setaddvec(vector2d a);
	vector2d& setsubvec(vector2d a);
	vector2d addvec(vector2d a);
	vector2d subvec(vector2d a);
	//functions
	/**
	 * @brief Change the vector length to exactly one
	 */
	vector2d& normalize();
	vector2d& normalize(float mag);
	/**
	 * @brief Calcultes the length of the vector and returns it.
	 * @details [long description]
	 * @return floathe lenght of this vector
	 */
	float magnitude() const;
	float magnitudesq() const;
	void clear();
	/**
	 * @brief Calculate the dot product of two vetors.
	 * @details floathe dot product is the product of the vector in the
	 * same length.
	 *
	 * @param left Left hand side of the dot operator.
	 * @param right Right hand side of the dot operator.
	 *
	 * @return Vector result of the dot operation.
	 */
	static float dotProduct(const vector2d& left, const vector2d& right);
};
