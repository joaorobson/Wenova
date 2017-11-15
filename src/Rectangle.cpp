/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Rectangle.cpp
 * Brief Description.
 */

#include "Rectangle.h"

/**
 * Brief Description.
 */
Rectangle::Rectangle() {
}

/**
 * Brief Description.
 *
 * @param ax
 * @param ay
 * @param w
 * @param h
 */
Rectangle::Rectangle(float ax, float ay, float w, float h)
    : x(ax), y(ay), width(w), height(h) {
}

/**
 * Brief Description.
 *
 * @param mx
 * @param my
 *
 * @returns
 */
bool Rectangle::is_inside(float mx, float my) {
    bool horizontal_in = (mx >= x - width / 2 and mx <= x + width / 2);
    bool vertical_in = (my >= y - height / 2 and my <= y + height / 2);

    return horizontal_in and vertical_in;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Rectangle::get_x() const {
    return x;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Rectangle::get_y() const {
    return y;
}

/**
 * Brief Description.
 *
 * @param cx
 */
void Rectangle::set_x(float cx) {
    this->x = cx;
}

/**
 * Brief Description.
 *
 * @param cy
 */
void Rectangle::set_y(float cy) {
    this->y = cy;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Rectangle::get_draw_x() const {
    return x - width / 2;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Rectangle::get_draw_y() const {
    return y - height / 2;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Rectangle::get_width() const {
    return width;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Rectangle::get_height() const {
    return height;
}

/**
 * Brief Description.
 *
 * @param w
 */
void Rectangle::set_width(float w) {
    width = w;
}

/**
 * Brief Description.
 *
 * @param h
 */
void Rectangle::set_height(float h) {
    height = h;
}

/**
 * Brief Description.
 *
 * @returns
 */
Vector Rectangle::get_center() const {
    return Vector(x, y);
}
