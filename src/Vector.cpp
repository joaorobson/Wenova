/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Vector.cpp
 * Brief Description.
 */

#include "Vector.h"
#include <cmath>

/**
 * Brief Description.
 *
 * @param mx
 * @param my
 */
Vector::Vector(float mx, float my)
        : x(mx)
        , y(my) {
}

/**
 * Brief Description.
 *
 * @param origin
 * @param angle
 */
void Vector::rotate(Vector origin, float angle) {
    x = origin.x + 200 * cos(angle);
    y = origin.y + 200 * sin(angle);
}

/**
 * Not used method.
 *
 * @param module
 * @param angle
 */
/*
void Vector::transform(float module, float angle) {
    x = module * cos(angle);
    y = module * sin(angle);
}
*/

/**
 * Brief Description.
 *
 * @param rhs
 *
 * @returns
 */
Vector Vector::operator+(const Vector& rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}

/**
 * Brief Description.
 *
 * @param rhs
 *
 * @returns
 */
Vector Vector::operator-(const Vector& rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}

/**
 * Brief Description.
 *
 * @param rhs
 *
 * @returns
 */
Vector Vector::operator*(const float rhs) const {
    return Vector(x * rhs, y * rhs);
}
