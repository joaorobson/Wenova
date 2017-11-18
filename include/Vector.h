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

class Vector {
 public:
    float x;
    float y;
    explicit Vector(float mx = 0, float my = 0);
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
