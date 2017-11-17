/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Vector.h
 * Brief Description.
 */

#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <algorithm>

#include "easylogging++.h" //NOLINT

#define INITIAL_VALUE_X 0
#define INITIAL_VALUE_Y 0

class Vector {
 public:
    float x; /**< The first value of the vector. */
    float y; /**< The second value of the vector. */
    explicit Vector(float mx = INITIAL_VALUE_X, float my = INITIAL_VALUE_Y);
    void rotate(Vector origin, float angle);
    /**
     * Not used method.
     */
    void transform(float module, float angle);

    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(const float rhs) const;
};

#endif  // INCLUDE_VECTOR_H_
