/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Floor.cpp
 * Brief Description.
 */

#include "Floor.h"

#include "Camera.h"
#include "InputManager.h"

#define LAYER 0
#define PI 3.14159265358979

#define HEIGHT 20

int Floor::floor_id = 1;

/**
 * Brief Description.
 *
 * @param x
 * @param y
 * @param width
 * @param crotation
 * @param cplatform
 */
// TODO reavaliar se precisa ou não de Camera
Floor::Floor(float x, float y, float width, float crotation, bool cplatform) {
    is_crossingable = cplatform;
    rotation = crotation * PI / 180.0;
    box = Rectangle(x, y, width, HEIGHT);
    id = floor_id++;
    tags["floor"] = true;
    if (is_crossingable) {
        tags["platform"] = true;
    }
}

/**
 * Brief Description.
 */
Floor::~Floor() {
}

/**
 * Brief Description.
 *
 * @param float
 */
void Floor::update(float) {
    // printf("%.f %.f %.f %.f %.f\n", box.x, box.y, box.width, box.height,
    // rotation);
}

/**
 * Brief Description.
 */
void Floor::render() {
}

/**
 * Brief Description.
 *
 * @returns
 */
bool Floor::is_dead() {
    return false;
}

/**
 * Brief Description.
 *
 * @param
 */
void Floor::notify_collision(GameObject &) {
}

/**
 * Brief Description.
 *
 * @returns
 */
int Floor::get_id() {
    return id;
}
