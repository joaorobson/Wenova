/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Effect.h
 * Brief Description.
 */

#ifndef INCLUDE_EFFECT_H_
#define INCLUDE_EFFECT_H_

#include "Fighter.h"
#include "GameObject.h"
#include "Sprite.h"

#include <string>

class Effect : public GameObject {
 protected:
    Sprite sprite;
    Fighter* parent;

 public:
    Effect(Fighter* cparent, string csprite, string ctags, int frames = 1);
    explicit Effect(string ctags);

    virtual void update(float delta) = 0;
    virtual bool is_dead() = 0;
    virtual void render();
    void notify_collision(GameObject& object);
};

#endif  // INCLUDE_EFFECT_H_
