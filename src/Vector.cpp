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

/*
 * The constructor
 * Initialize the vector
 *
 * @param mx is the cordinate inicial x of vector
 * @param my is the cordinate inicial y of vector
 */
Vector::Vector(float mx, float my) : x(mx), y(my) {}

/*
 * Rotate the vector
 *
 * @param origin is the origin of vector
 * @param angle is the angle you want to rotate
 */
void Vector::rotate(Vector origin, float angle) {
    x = origin.x + 200 * cos(angle);
    y = origin.y + 200 * sin(angle);
}

/*
 * Transform the Vector
 *
 * @param module is the module of vector
 * @param angle is the angle you want to put
 */
void Vector::transform(float module, float angle) {
    x = module * cos(angle);
    y = module * sin(angle);
}

/*
 * Define the operater "+"
 */
Vector Vector::operator+(const Vector& rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}

/*
 * Define the operater "-"
 */
Vector Vector::operator-(const Vector& rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}

/*
 * Define the operater "*"
 */
Vector Vector::operator*(const float rhs) const {
    return Vector(x * rhs, y * rhs);
}
