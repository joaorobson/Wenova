/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file HealEffect.cpp
 * Implements class HealEffect methods.  
 */

#include "HealEffect.h"

#include <assert.h>

/**
 * The constructor.
 * Initialize the heal effect
 * container coordinates of the HealEffect class. The HealEffect class inherits
 * the Effect class.
 *
 * @param cparent is the fighter.
 * @param csprite is the sprite of the fighter.
 * @param ctags is the tag of the fighter.
 * @param frames is the frames to show the heal.
 * @param chealing_factor is the chealing factor.
 */
HealEffect::HealEffect(Fighter * cparent, string csprite, string ctags,
                       int frames, float chealing_factor)
    : Effect(cparent, csprite, ctags, frames) {
    LOG(DEBUG) << "HealEffect constructor activated";
    assert(csprite.empty() == false);
    assert(ctags.empty() == false);
    healing_factor = chealing_factor;
}

/**
 * Update the Heal Effects
 * 
 * @params delta is the variation of the heal.
 */
void HealEffect::update(float delta) {
    LOG(DEBUG) << "HealEffect is updating";
    /**
     * Check if the parent is true
     */
    if (parent) {
        box.x = parent->box.x;
        box.y = parent->box.y;
    } else {
        /* Nothing to do. */
    }
    sprite.update(delta);
    /**
     * Check if the parent is true
     */
    if (parent) {
        parent->increment_life(healing_factor);
    } else {
        /* Nothing to do. */
    }
}

/**
 * Check if the Heal Effect is dead
 *
 * @return the sprite dead
 */
bool HealEffect::is_dead() {
    return sprite.is_finished();
}
