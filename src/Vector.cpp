/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Vector.cpp
 * Implements class Vector methods.
 */

#include "Vector.h"

#include <cmath>

#define RATE_TO_ROTATE_CORDINATE_X 200
#define RATE_TO_ROTATE_CORDINATE_Y 200

/**
 * The constructor
 * Initialize the vector
 *
 * @param mx is the cordinate inicial x of vector
 * @param my is the cordinate inicial y of vector
 */
Vector::Vector(float mx, float my)
        : x(mx)
        , y(my) {
}

/**
 * Rotate the vector
 *
 * @param origin is the origin of vector
 * @param angle is the angle you want to rotate
 */
void Vector::rotate(Vector origin, float angle) {
    LOG(DEBUG) << "Vector full constructor activated";
    x = origin.x + RATE_TO_ROTATE_CORDINATE_X * cos(angle);
    y = origin.y + RATE_TO_ROTATE_CORDINATE_Y * sin(angle);
}

/**
 * Transform the Vector
 * Not used method.
 *
 * @param module is the module of vector
 * @param angle is the angle you want to put
 */
void Vector::transform(float module, float angle) {
    LOG(DEBUG) << "Vector is transforming";
    x = module * cos(angle);
    y = module * sin(angle);
}

/**
 * Define the operater "+"
 * @param rhs is the vector to sum
 *
 * @return is the sum of the vectors
 */
Vector Vector::operator+(const Vector& rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}

/**
 * Define the operater "-"
 *
 * @param rhs is the vector to subtract
 *
 * @return is the subtract of the vectors
 */
Vector Vector::operator-(const Vector& rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}

/**
 * Define the operater "*"
 *
 * @param rhs is the float to multiply the vector
 *
 * @return is the vector multiply for the constant
 */
Vector Vector::operator*(const float rhs) const {
    return Vector(x * rhs, y * rhs);
}
