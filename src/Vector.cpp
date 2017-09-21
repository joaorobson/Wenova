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

//Create a object "vector"
Vector::Vector(float mx, float my) : x(mx), y(my) {}

//Rotate the vector
void Vector::rotate(Vector origin, float angle) {
    x = origin.x + 200 * cos(angle);
    y = origin.y + 200 * sin(angle);
}

//Transform the Vector
void Vector::transform(float module, float angle) {
    x = module * cos(angle);
    y = module * sin(angle);
}

//Define the operater "+"
Vector Vector::operator+(const Vector& rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}

//Define the operater "-"
Vector Vector::operator-(const Vector& rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}

//Define the operater "*"
Vector Vector::operator*(const float rhs) const {
    return Vector(x * rhs, y * rhs);
}
