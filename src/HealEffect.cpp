/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file HealEffect.cpp
 * Brief Description.
 */

#include "HealEffect.h"

HealEffect::HealEffect(Fighter* cparent, string csprite, string ctags,
                       int frames, float chealing_factor)
        : Effect(cparent, csprite, ctags, frames) {
    healing_factor = chealing_factor;
}

/**
 * Brief Description.
 *
 * @param delta
 */
void HealEffect::update(float delta) {
    if (parent) {
        box.x = parent->box.x;
        box.y = parent->box.y;
    }
    sprite.update(delta);
    if (parent) {
        parent->increment_life(healing_factor);
    }
}

/**
 * Brief Description.
 *
 * @returns
 */
bool HealEffect::is_dead() {
    return sprite.is_finished();
}
