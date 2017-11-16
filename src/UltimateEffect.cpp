/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 *
 * For a copy, see <https://opensource.org/licenses/MIT>.
*/
/**
 * @file UltimateEffect.cpp
 * This file contains the definition of the Sprite class methods.
 */

#include "UltimateEffect.h"

/**
 * A constructor.
 * Initialize the Fighter and his corresponding sprite, aura, tags and
 * frames when he is apllying a UltimateEffect.
 * The UltimateEffect class inherits the Effect class.
 *
 * @param Fighter who applies the effect.
 * @param csprite is the name of the corresponding sprite.
 * @param caura is the name of the corresponding aura.
 * @param ccolumns is the name of the tags.
 * @param frames if the number of the frames.
 */
UltimateEffect::UltimateEffect(Fighter *cparent, string csprite, string caura,
                               string ctags, int frames)
        : Effect(cparent, csprite, ctags, frames)
        , aura(Sprite(caura, 14, 10, 4))
        , sprite_box(box)
        , healing_factor(1) {
    box = Rectangle(0, 0, aura.get_width(), aura.get_height());

    /**
     * Check if is the parent fighter. If so, adds the "in ultimate" tag.
     */
    if (parent) {
        parent->add_tags("in_ultimate");
    }
}

/**
 * Update method.
 * Update the effect in the game updating positions and corresponding sprites.
 *
 * @param delta is the variation of character state.
 */
void UltimateEffect::update(float delta_character_state) {
    healing_factor = 1 * delta_character_state;
    if (parent) {
        sprite_box.x = parent->box.x;
        sprite_box.y =
            parent->box.get_draw_y() - sprite_box.get_height() / 2 - 10;
        box.x = parent->box.x;
        box.y = parent->box.y;
        parent->increment_special(-0.4 * delta_character_state);
        parent->increment_life(healing_factor);
    }
    sprite.update(delta_character_state);
    aura.update(delta_character_state);
}

/**
 * Render method.
 * Render the UltimateEffect sprites in the game.
 */
void UltimateEffect::render() {
    sprite.render(sprite_box.get_draw_x(), sprite_box.get_draw_y(), rotation);
    aura.render(box.get_draw_x(), box.get_draw_y(), rotation);
}

/**
 * Check death.
 * Check if the last state of Figher is dead.
 */
bool UltimateEffect::is_dead() {
    bool dead = parent->get_special() <= 0 or parent->is_dead();
    /**
     * Check if fighter is dead. If so, update his life tags.
     *
     */
    if (dead) {
        parent->remove_tags("in_ultimate");
    }
    return dead;
}

/**
 * Notify collision between two fighters.
 * Check if the fighters have collided.
 */
void UltimateEffect::notify_collision(const GameObject &object) {
    int partner_id =
        (parent->get_partner() ? parent->get_partner()->get_id() : -100);
    if (not object.is("player")) {
        return;
    }
    Fighter const &fighter = (const Fighter &) object;
    if (fighter.get_id() == partner_id) {
        parent->get_partner()->increment_life(healing_factor);
    }
}
