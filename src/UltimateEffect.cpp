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

#include <assert.h>
#include "UltimateEffect.h"
#define IN_ULTIMATE_TAG "in_ultimate"
#define PLAYER_TAG "player"
#define ATTACK_VERTICAL_POSITION_DECREASE 10
#define HEIGHT_DIVISOR_VALUE 2
#define NO_LIFE_STATE 0
#define X_AXIS_POSITION 0
#define Y_AXIS_POSITION 0



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
UltimateEffect::UltimateEffect(Fighter * cparent,
                               string csprite,
                               string caura,
                               string ctags,
                               int frames) :
    Effect(cparent, csprite, ctags, frames) {
    aura = Sprite(caura, 14, 10, 4); /**< Initialize the fighter aura image. */
    sprite_box = box;
    box = Rectangle(X_AXIS_POSITION, Y_AXIS_POSITION, aura.get_width(),
                    aura.get_height());
    /**
     * Check if is the parent fighter. If so, adds the "in ultimate" tag.
     */
    if (parent) {
        parent->add_tags(IN_ULTIMATE_TAG);
    } else {
        /* Nothing to do. */
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

        sprite_box.y = parent->box.get_draw_y() -
                       sprite_box.get_height() / HEIGHT_DIVISOR_VALUE -
                       ATTACK_VERTICAL_POSITION_DECREASE;
        box.x = parent->box.x;
        box.y = parent->box.y;
        parent->increment_special(-0.4 * delta_character_state);
        parent->increment_life(healing_factor);
    } else {
        /* Nothing to do. */
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
    assert(NO_LIFE_STATE == 0);
    assert(strcmp(IN_ULTIMATE_TAG, "") != 0);
    bool dead = parent->get_special() <= NO_LIFE_STATE or parent->is_dead();
    /**
     * Check if fighter is dead. If so, update his life tags.
     *
     */
    if (dead) {
        parent->remove_tags(IN_ULTIMATE_TAG);
    } else {
        /* Nothing to do. */
    }
    return dead;
}

/**
 * Notify collision between two fighters.
 * Check if the fighters have collided.
 */
void UltimateEffect::notify_collision(GameObject & object) {
    assert(strcmp(PLAYER_TAG, "") != 0);
    int partner_id = (parent->get_partner() ? parent->get_partner()->get_id() :
                      -100);
    if (object.is(PLAYER_TAG)) {
        Fighter & fighter = (Fighter &)object;
        if (fighter.get_id() == partner_id) {
            parent->get_partner()->increment_life(healing_factor);
        } else {
            /* Nothing to do. */
        }
    } else {
        /* Nothing to do. */
    }
}
