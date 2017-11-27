/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file HealEffect.h
 * Control the HealEffect of the fighters.
 */

#ifndef INCLUDE_HEALEFFECT_H_
#define INCLUDE_HEALEFFECT_H_

#include <string>

#include "Effect.h"

#include "easylogging++.h" //NOLINT

class HealEffect : public Effect {
 private:
    float healing_factor = 0.0; /**< The healing factor of the character. */

 public:
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
    HealEffect(Fighter* cparent, string csprite, string ctags, int frames = 1,
               float chealing_factor = 0.0);

	/**
	 * Update the Heal Effects
	 * 
	 * @params delta is the variation of the heal.
	 */
    void update(float delta);

    /**
	 * Check if the Heal Effect is dead
	 *
	 * @return the sprite dead
	 */
    bool is_dead();
};

#endif  // INCLUDE_HEALEFFECT_H_
