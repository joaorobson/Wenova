/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Rectangle.h
 * Control the rectangles involving the game.
 */

#ifndef INCLUDE_RECTANGLE_H_
#define INCLUDE_RECTANGLE_H_

#include "Vector.h"

#include "SDL2/SDL.h"

class Rectangle {
 public:
    float x = 0.0;      /**< Cordinate on axis x of the rectangle. Unit: px. */
    float y = 0.0;      /**< Cordinate on axis y of the rectangle. Unit: px. */
    float width = 0.0;  /**< Width of the rectangle. Unit: px. */
    float height = 0.0; /**< Height of the rectangle. Unit: px. */

    /**
     * The constructor
     * Initialize the rectangle null
     */
    Rectangle();

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
    Rectangle(float x, float y, float width, float height);


    /**
     * Check if any object is inside the rectangle
     * Not used method.
     *
     * @param mx is the cordinate x of the object
     * @param my is the cordinate y of the object
     *
     * @return if the rectangle is inside of the other
     */
    bool is_inside(float mx, float my);

    /**
     * Check the horizontal size of rectangle
     *
     * @return the cordinate x of rectangle
     */
    float get_x() const;

    /**
     * Check the vertical size of rectangle
     *
     * @return the cordinate y of rectangle
     */
    float get_y() const;

    /**
     * Inserts a horizontal size in rectangle
     *
     * @param cx is the size to be put in the cordinate x
     */
    void set_x(float cx);

    /**
     * Inserts s vertical size in rectangle
     *
     * @param cy is the size to be put in the cordinate y
     */
    void set_y(float cy);

    /**
     * Check the horizontal draw of rectangle
     *
     * @return the cordinate y of the middle of widht of rectangle
     */
    float get_draw_x() const;

    /**
     * Check the vertical draw of rectangle
     *
     * @return the cordinate y of the middle of height of rectangle
     */
    float get_draw_y() const;

    /**
     * Chack the width of rectangle
     *
     * @return the widht of rectangle
     */
    float get_width() const;

    /**
     * Check the height of rectangle
     *
     * @return the height of rectangle
     */
    float get_height() const;

    /**
     * Inserts the width of rectangle
     *
     * @param w is the size to be put in the variable 'width' of Rectangle
     */
    void set_width(float w);

    /**
     * Inserts the height of rectangle
     *
     * @param h is the size to be put in the variable 'height' of Rectangle
     */
    void set_height(float h);

    /**
     * Check the center of rectangle
     *
     * @return the conter of rectangle
     */
    Vector get_center() const;
};

#endif  // INCLUDE_RECTANGLE_H_
