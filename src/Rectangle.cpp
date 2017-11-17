/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Rectangle.cpp
 * Implements class Rectangle methods.
 */

#include "Rectangle.h"

/**
 * The constructor
 * Initialize the rectangle null
 */
Rectangle::Rectangle() {}

/**
 * The constructor
 * Initialize the retangle
 * container coordinates of the Rectangle class.
 *
 * @param ax is the cordinate x of the object
 * @param ay is the cordinate y of the object
 * @param w is the width of object
 * @param h is the height of object
 */
Rectangle::Rectangle(float ax, float ay, float w, float h)
        : x(ax)
        , y(ay)
        , width(w)
        , height(h) {
}

/**
 * Check if any object is inside the rectangle
 * Not used method.
 *
 * @param mx is the cordinate x of the object
 * @param my is the cordinate y of the object
 *
 * @return if the rectangle is inside of the other
 */
bool Rectangle::is_inside(float mx, float my) {
    bool horizontal_in = (mx >= x - width/2 and mx <= x + width/2);
    bool vertical_in = (my >= y - height/2 and my <= y + height/2);

    return horizontal_in and vertical_in;
}

/**
 * Check the horizontal size of rectangle
 *
 * @return the cordinate x of rectangle
 */
float Rectangle::get_x() const {
    return x;
}

/**
 * Check the vertical size of rectangle
 *
 * @return the cordinate y of rectangle
 */
float Rectangle::get_y() const {
    return y;
}

/**
 * Inserts a horizontal size in rectangle
 *
 * @param cx is the size to be put in the cordinate x
 */
void Rectangle::set_x(float cx) {
    this->x = cx;
}

/**
 * Inserts s vertical size in rectangle
 *
 * @param cy is the size to be put in the cordinate y
 */
void Rectangle::set_y(float cy) {
    this->y = cy;
}

/**
 * Check the horizontal draw of rectangle
 *
 * @return the cordinate y of the middle of widht of rectangle
 */
float Rectangle::get_draw_x() const {
    return x - width/2;
}

/**
 * Check the vertical draw of rectangle
 *
 * @return the cordinate y of the middle of height of rectangle
 */
float Rectangle::get_draw_y() const {
    return y - height/2;
}

/**
 * Chack the width of rectangle
 *
 * @return the widht of rectangle
 */
float Rectangle::get_width() const {
    return width;
}

/**
 * Check the height of rectangle
 *
 * @return the height of rectangle
 */
float Rectangle::get_height() const {
    return height;
}

/**
 * Inserts the width of rectangle
 *
 * @param w is the size to be put in the variable 'width' of Rectangle
 */
void Rectangle::set_width(float w) {
    width = w;
}

/**
 * Inserts the height of rectangle
 *
 * @param h is the size to be put in the variable 'height' of Rectangle
 */
void Rectangle::set_height(float h) {
    height = h;
}

/**
 * Check the center of rectangle
 *
 * @return the conter of rectangle
 */
Vector Rectangle::get_center() const {
    return Vector(x, y);
}
