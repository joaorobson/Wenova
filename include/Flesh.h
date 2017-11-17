/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Flesh.h
 * Control the states of the fighters.
 */

#ifndef INCLUDE_FLESH_H_
#define INCLUDE_FLESH_H_

#include <string>

#include "Fighter.h"

#include "easylogging++.h" //NOLINT

class Flesh : public Fighter {
 public:
    /**
     * The constructor.
     * Initialize the flesh
     * container coordinates of the Flesh class. The Flesh class inherits the
     * Fighter class.
     *
     * @param skin is the Fighter skin.
     * @param x is the box horizontal coordinate.
     * @param y is the box veretical coordinate.
     * @param cid is the partner fighter identifier.
     * @param cparter is the fighter
     */
    Flesh(string skin, float x, float y, int cid, Fighter *cpartner = nullptr);
    const float BASIC_ATTACK_DAMAGE = 0.3;  ///< The basic attack damage of the
    ///< characters.
    const float SPECIAL_1_DAMAGE = 1;  ///< The attack damage of the characters
    ///< on special 1.
    const float INITIAL_SPEED = 3;/**< The initia speed of the characters. */

 private:
    float additional_attack_damage;   ///< Additional attack damage possible
    ///< for characters.
    float additional_speed; /**< Additional speed possible for characters. */

    /**
     * Makes the character jump
     *
     * @param change check if the state os character changed
     */
    void check_jump(bool change = true);

    /**
     * Change de state of character if it is falling
     *
     * @param change check if the state os character changed
     */
    void check_fall(bool change = true);

    /**
     * Makes the character go to left
     *
     * @param change check if the state os character changed
     */
    void check_left(bool change = true);

    /**
     * Makes the character go to right
     *
     * @param change check if the state os character changed
     */
    void check_right(bool change = true);

    /**
     * Makes the character stay stoped
     *
     * @param change check if the state os character changed
     * @param condition
     */
    void check_idle(bool change = true, bool condition = false);

    /**
     * Makes the character crounch
     *
     * @param change check if the state os character changed
     */
    void check_crouch(bool change = true);

    /**
     * Not implemented.
     */
    void check_idle_atk_neutral(bool change = true);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     */
    void check_idle_atk_neutral_1(bool change = true);

    /**
     * Keep the character attacking
     *
     * @param change check if the state os character changed
     */
    void check_idle_atk_neutral_2(bool change = true);

    /**
     * Keep the character attacking
     *
     * @param change check if the state os character changed
     */
    void check_idle_atk_neutral_3(bool change = true);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     * @param condition check if the character is in condition
     */
    void check_idle_atk_front(bool change = true, bool condition = false);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     */
    void check_idle_atk_up(bool change = true);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     */
    void check_jump_atk_down_fallloop(bool change = true);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     */
    void check_jump_atk_down_dmg(bool change = true);

    /**
     * Makes the character attack jumping
     *
     * @param change check if the state os character changed
     */
    void check_jump_atk_up(bool change = true);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     */
    void check_jump_atk_neutral(bool change = true);

    /**
     * Makes the character attack
     *
     * @param change check if the state os character changed
     */
    void check_idle_atk_down(bool change = true);

    /**
     * Makes the character attack crounched
     *
     * @param change check if the state os character changed
     */
    void check_crouch_atk(bool change = true);

    /**
     * Makes the character activate him special
     *
     * @param change check if the state os character changed
     */
    void check_special_1(bool change = true);

    /**
     * Makes the character more stronger cause him special
     *
     * @param bool
     */
    void check_special_2(bool change = true);

    /**
     * Makes the character activate him ultimate
     *
     * @param bool
     */
    void check_ultimate(bool change = true);


    /**
     * Makes the character pass through platform
     *
     * @param change check if the state os character changed
     */
    void check_pass_through_platform(bool change = true);

    /**
     * Makes the character in defense mode
     *
     * @param change check if the state os character changed
     */
    void check_defense(bool change = true);

    /**
     * Makes the character in stunned mode
     *
     * @param change check if the state os character changed
     */
    void check_stunned(bool change = true);

    /**
     * Makes the character dead
     *
     * @param change check if the state os character changed
     */
    void check_dead(bool change = true);

    /**
     * Fighter's state machine
     * Check and update the Fighter's state according to the attack type and
     * damage suffered.
     *
     * @param float is the variation of character state.
     */
    void update_machine_state(float delta);
};

#endif  // INCLUDE_FLESH_H_
