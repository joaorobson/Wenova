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

//Saves the platform traits
Floor::Floor(float x, float y, float width, float crotation, bool cplatform) {
    is_platform = cplatform;
    rotation = crotation * PI / 180.0;
    box = Rectangle(x, y, width, HEIGHT);
    id = floor_id++;
    tags["floor"] = true;
    if(is_platform) {
        tags["platform"] = true;
    }

//Destroy the platform
Floor::~Floor() {}

//Update the traits os platform
void Floor::update(float) {}
    //Comentário de printf para testes
    //printf("%.f %.f %.f %.f %.f\n", box.x, box.y, box.width, box.height, rotation);

//Render the platform
void Floor::render() {}

//Check if the platform is dead
bool Floor::is_dead() {
    return false;
}

//Notify a collision in the platform
void Floor::notify_collision(GameObject &) {}

//Check the ID of platform
int Floor::get_id() {
    return id;
