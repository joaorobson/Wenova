/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 *
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file FleshUltimateEffect.cpp
 * This file contains the definition of the FleshUltimateEffect class methods.
 */

#include "FleshUltimateEffect.h"

/**
 * The constructor.
 * Initialize the fighter character and the respective sprite, tags and frames
 * of the FleshUltimateEffect.
 *
 * @param cparent is a Fighter object.
 * @param csprite is the respective sprite.
 * @param ctags is the character condition tag.
 * @param frames is the respective effect frame.
 f*/
FleshUltimateEffect::FleshUltimateEffect(Fighter * cparent,
                                         string csprite,
                                         string ctags,
                                         int frames) :
                                         Effect(cparent, csprite,
                                         ctags, frames) {
  if (parent) {
    parent->add_tags("in_ultimate");
  }
  parent->MAX_LIFE *= 1.5;
}

/**
 * Update effect position.
 * Update effect position according to character old position.
 *
 * @param delta is the character state variation.
 */
void FleshUltimateEffect::update(float delta) {
  if (parent) {
    box.x = parent->box.x;
    box.y = parent->box.get_draw_y() - box.get_height() / 2 - 10;
    parent->increment_special(-0.4 * delta);
  }
  sprite.update(delta);
}

/**
 * Render method.
 * Show effect on screen according to character current position.
 */
void FleshUltimateEffect::render() {
  sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
}

/**
 * Check life condition method.
 * Check if the character is dead and change his tags.
 *
 *@return Return true if the character is dead and false if not.
 */
bool FleshUltimateEffect::is_dead() {
  bool dead = parent->get_special() <= 0 or parent->is("dying");
  if (dead) {
    parent->remove_tags("in_ultimate");
    parent->MAX_LIFE /= 1.5;
    parent->increment_life(0);
  }
  return dead;
}
