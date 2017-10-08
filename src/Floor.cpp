/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Floor.cpp
 * Implements class Floor methods.  
 */

#include "Floor.h"
#include "InputManager.h"
#include "Camera.h"

#define LAYER 0
#define PI 3.14159265358979
#define HEIGHT 20

int Floor::floor_id = 1;

/**
 * The constructor.
 * Initialize the floor
 * container coordinates of the Floor class. The Floor class inherits the
 * GameObject class.
 *
 * @param x is the box horizontal coordinate.
 * @param y is the box veretical coordinate.
 * @param widht is the widht of the floor.
 * @param height is the height of the floor.
 * @param crotation is the rotation of the floor.
 * @param cplataform is the type of the plataform selected.
 */
Floor::Floor(float x, float y, float width, float crotation, bool cplatform) {
    is_platform = cplatform;
    rotation = crotation * PI / 180.0;
    box = Rectangle(x, y, width, HEIGHT);
    id = floor_id++;
    tags["floor"] = true;
    /*
     * Check if exist floor on platform
     */
    if (is_platform) {
        tags["platform"] = true;
    }
}

/*
 * The destructor.
 * Destroy the floor.
 */
Floor::~Floor() {}

/*
 * Update the traits of floor
 */
void Floor::update(float) {}
    /*
     * Comentário de printf para testes
     * printf("%.f %.f %.f %.f %.f\n", box.x, box.y, box.width, box.height, 
     *         rotation);
     */

/*
 * Render the floor
 */
void Floor::render() {}

/*
 * Check if the floor is dead
 */
bool Floor::is_dead() {
    return false;
}

/*
 * Notify a collision in the floor
 */
void Floor::notify_collision(GameObject &) {}

/*
 * Check the ID of floor
 *
 * @return the id of the floor
 */
int Floor::get_id() {
    return id;
}
