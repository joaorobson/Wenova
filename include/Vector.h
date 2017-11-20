/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Vector.h
 * Control the interaction of the vectors in game.
 */

#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <algorithm>

#include "easylogging++.h" //NOLINT

#define INITIAL_VALUE_X 0
#define INITIAL_VALUE_Y 0

class Vector {
 public:
    float x; /**< The first value of the vector. Unit: px. */
    float y; /**< The second value of the vector. Unit: px. */

    /**
     * The constructor
     * Initialize the vector
     *
     * @param mx is the cordinate inicial x of vector
     * @param my is the cordinate inicial y of vector
     */
    explicit Vector(float mx = INITIAL_VALUE_X, float my = INITIAL_VALUE_Y);

    /**
     * Rotate the vector
     *
     * @param origin is the origin of vector
     * @param angle is the angle you want to rotate
     */
    void rotate(Vector origin, float angle);

    /**
     * Transform the Vector
     * Not used method.
     *
     * @param module is the module of vector
     * @param angle is the angle you want to put
     */
    void transform(float module, float angle);

    /**
     * Define the operater "+"
     * @param rhs is the vector to sum
     *
     * @return is the sum of the vectors
     */
    Vector operator+(const Vector& rhs) const;

    /**
     * Define the operater "-"
     *
     * @param rhs is the vector to subtract
     *
     * @return is the subtract of the vectors
     */
    Vector operator-(const Vector& rhs) const;

    /**
     * Define the operater "*"
     *
     * @param rhs is the float to multiply the vector
     *
     * @return is the vector multiply for the constant
     */
    Vector operator*(const float rhs) const;
};

#endif  // INCLUDE_VECTOR_H_
