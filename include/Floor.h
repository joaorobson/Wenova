/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Floor.h
 * Brief Description.
 */

#ifndef INCLUDE_FLOOR_H_
#define INCLUDE_FLOOR_H_

#include "GameObject.h"
#include "Sprite.h"

class Floor : public GameObject {
 private:
    int id;

 protected:
    bool is_crossingable;

 public:
    Floor(float x, float y, float width, float crotation, bool cplatform);
    ~Floor();

    void update(float delta);
    void render();
    bool is_dead();

    void notify_collision(GameObject& object);

    int get_id();

    static int floor_id;
};

#endif  // INCLUDE_FLOOR_H_
