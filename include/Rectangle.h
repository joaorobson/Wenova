/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Rectangle.h
 * Brief Description.
 */

#ifndef INCLUDE_RECTANGLE_H_
#define INCLUDE_RECTANGLE_H_

#include "SDL2/SDL.h"

#include "Vector.h"

class Rectangle {
 public:
    float x;
    float y;
    float width;
    float height;

    Rectangle();
    Rectangle(float x, float y, float width, float height);

    /**
     * Not used method.
     */
    bool is_inside(float mx, float my);
    float get_x() const;
    float get_y() const;
    void set_x(float cx);
    void set_y(float cy);
    float get_draw_x() const;
    float get_draw_y() const;
    float get_width() const;
    float get_height() const;
    void set_width(float w);
    void set_height(float h);
    Vector get_center() const;
};

#endif  // INCLUDE_RECTANGLE_H_
