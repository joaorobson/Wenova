/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Camera.h
 * Brief Description.
 */

#ifndef INCLUDE_CAMERA_H_
#define INCLUDE_CAMERA_H_

#include "GameObject.h"
#include "Vector.h"

#define LAYERS 4

class Camera {
 private:
    static GameObject* focus;

 public:
    static Vector pos[LAYERS];
    static float layer_speed[LAYERS];
    static Vector speed;

    static void follow(GameObject* new_focus);
    static void unfollow();
    static void update(float delta);
};

#endif  // INCLUDE_CAMERA_H_
