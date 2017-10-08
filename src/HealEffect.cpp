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
    healing_factor = chealing_factor;
}

/*
 * Update the Heal Effects
 * 
 * @params delta is the variation of the heal.
 */
void HealEffect::update(float delta) {
    /*
     * Check if the parent
     */
    if (parent) {
        box.x = parent->box.x;
        box.y = parent->box.y;
    }
    sprite.update(delta);
    /*
     * Check if the parent
     */
    if (parent) {
        parent->increment_life(healing_factor);
    }
}

/*
 * Check if the Heal Effect is dead
 */
bool HealEffect::is_dead() {
    return sprite.is_finished();
}
