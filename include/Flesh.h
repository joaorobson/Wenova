/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Flesh.h
 * Brief Description.
 */

#ifndef INCLUDE_FLESH_H_
#define INCLUDE_FLESH_H_

#include <string>
#include "Fighter.h"

#include "easylogging++.h" //NOLINT

class Flesh : public Fighter {
 public:
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

    void check_jump(bool change = true);
    void check_fall(bool change = true);
    void check_left(bool change = true);
    void check_right(bool change = true);
    void check_idle(bool change = true, bool condition = false);
    void check_crouch(bool change = true);
    void check_idle_atk_neutral(bool change = true);
    void check_idle_atk_neutral_1(bool change = true);
    void check_idle_atk_neutral_2(bool change = true);
    void check_idle_atk_neutral_3(bool change = true);
    void check_idle_atk_front(bool change = true, bool condition = false);
    void check_idle_atk_up(bool change = true);
    void check_jump_atk_down_fallloop(bool change = true);
    void check_jump_atk_down_dmg(bool change = true);
    void check_jump_atk_up(bool change = true);
    void check_jump_atk_neutral(bool change = true);
    void check_idle_atk_down(bool change = true);
    void check_crouch_atk(bool change = true);
    void check_special_1(bool change = true);
    void check_special_2(bool change = true);
    void check_ultimate(bool change = true);

    void check_pass_through_platform(bool change = true);
    void check_defense(bool change = true);
    void check_stunned(bool change = true);
    void check_dead(bool change = true);

    void update_machine_state(float delta);
};

#endif  // INCLUDE_FLESH_H_
