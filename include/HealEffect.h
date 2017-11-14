/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file HealEffect.h
 * Brief Description.
 */

#ifndef INCLUDE_HEALEFFECT_H_
#define INCLUDE_HEALEFFECT_H_

#include "Effect.h"

#include <string>

class HealEffect : public Effect {
 private:
    float healing_factor;

 public:
    HealEffect(Fighter* cparent, string csprite, string ctags, int frames = 1,
               float chealing_factor = 0.0);

    void update(float delta);
    bool is_dead();
};

#endif  // INCLUDE_HEALEFFECT_H_
