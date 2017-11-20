/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 *
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file FleshUltimateEffect.h
 * This file contains the declaration of the FleshUltimateEffect class methods
 * and attributes.
 */

#ifndef INCLUDE_FLESHULTIMATEEFFECT_H_
#define INCLUDE_FLESHULTIMATEEFFECT_H_

#include <string>
#include "Effect.h"

class FleshUltimateEffect : public Effect {
 public:
    FleshUltimateEffect(Fighter* cparent, string csprite, string ctags,
                        int frames = 1);
    void update(float delta_character_state);
    void render();

 private:
    bool is_dead();
};

#endif  // INCLUDE_FLESHULTIMATEEFFECT_H_
