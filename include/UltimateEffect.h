/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 *
 * For a copy, see <https://opensource.org/licenses/MIT>.
*/
/**
 * @file UltimateEffect.h
 * This file contains the declaration of the UltimateEffect class methods and
 * attributes.
 */

#ifndef INCLUDE_ULTIMATEEFFECT_H_
#define INCLUDE_ULTIMATEEFFECT_H_

#include <string>
#include "Effect.h"

class UltimateEffect : public Effect {
 private:
    Sprite aura;          /**< Character aura. */
    Rectangle sprite_box; /**< Box where the effect sprite is positionated. */
    float healing_factor; /**< Healing factor applied after a attack. */

 public:
    UltimateEffect(Fighter *cparent, string csprite, string caura, string ctags,
                   int frames = 1);

    void update(float delta_character_state);
    void render();
    bool is_dead();
    void notify_collision(GameObject &object);
};

#endif  // INCLUDE_ULTIMATEEFFECT_H_
