/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Effect.cpp
 * Brief Description.
 */

#include "Effect.h"

/**
 * Brief Description.
 *
 * @param cparent
 * @param csprite
 * @param ctags
 * @param frames
 */
Effect::Effect(Fighter *cparent, string csprite, string ctags, int frames)
        : sprite(Sprite(csprite, frames, 10))
        , parent(cparent) {
    box = Rectangle(0, 0, sprite.get_width(), sprite.get_height());
    add_tags(ctags);
}

/**
 * Brief Description.
 *
 * @param ctags
 */
Effect::Effect(string ctags) {
    parent = nullptr;
    add_tags(ctags);
}

/**
 * Brief Description.
 */
void Effect::render() {
    if (is("has_sprite"))
        sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
}

/**
 * Brief Description.
 *
 * @param
 */
void Effect::notify_collision(const GameObject &) {
}
