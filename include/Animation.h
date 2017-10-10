/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Animation.h
 * Brief Description.
 */

#ifndef INCLUDE_ANIMATION_H_
#define INCLUDE_ANIMATION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

#include <string>

class Animation : public GameObject {
 private:
    Timer end_timer;
    float time_limit;
    bool one_time_only;
    Sprite sprite;

 public:
    Animation(float x, float y, float crotation, string csprite,
              int frame_count, float frame_time, bool ends);
    void update(float delta);
    void render();

    bool is_dead();

    void notify_collision(const GameObject& object);
};

#endif  // INCLUDE_ANIMATION_H_
