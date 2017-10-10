/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Animation.cpp
 * Brief Description.
 */

#include "Animation.h"
#include "Camera.h"

#define LAYER 0

/**
 * Brief Description.
 *
 * @param x
 * @param y
 * @param crotation
 * @param csprite
 * @param frame_count
 * @param frame_time
 * @param ends
 */
Animation::Animation(float x, float y, float crotation, string csprite,
                     int frame_count, float frame_time, bool ends) {
    sprite = Sprite(csprite, frame_count, frame_time);
    rotation = crotation;
    box = Rectangle(x, y, sprite.get_width(), sprite.get_height());
    one_time_only = ends;
    time_limit = frame_count * frame_time;
}

/**
 * Brief Description.
 *
 * @param delta
 */
void Animation::update(float delta) {
    end_timer.update(delta);
    sprite.update(delta);
}

/**
 * Brief Description.
 */
void Animation::render() {
    int x = box.get_draw_x() + Camera::pos[LAYER].x;
    int y = box.get_draw_y() + Camera::pos[LAYER].y;
    sprite.render(x, y, rotation);
}

/**
 * Brief Description.
 *
 * @returns
 */
bool Animation::is_dead() {
    return end_timer.get() >= time_limit or not one_time_only;
}

/**
 * Brief Description.
 *
 * @param
 */
void Animation::notify_collision(GameObject &) {
    // nothing to do
}
