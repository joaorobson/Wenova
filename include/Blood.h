/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.

 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Blood.h
 * This file contains the declaration of the Blood class methods and attributes.
 */

#ifndef INCLUDE_BLOOD_H_
#define INCLUDE_BLOOD_H_

#include <string>
#include "Fighter.h"

class Blood : public Fighter {
 public:
    Blood(string skin, float x_axis_position, float y_axis_position,
          int character_id, Fighter* cpartner = nullptr);

 private:
    void update_machine_state(float delta);
    void check_jump(bool change = true);
    void check_fall(bool change = true);
    void check_right(bool change = true);
    void check_left(bool change = true);
    void check_defense(bool change = true);
    void check_idle(bool change = true);
    void check_crouch(bool change = true);
    void check_stunned(bool change = true);
    void check_dead(bool change = true);
    void check_jump_atk_up(bool change = true);
    void check_jump_atk_down(bool change = true);
    void check_jump_atk_neutral(bool change = true);
    void check_idle_atk_neutral_1(bool change = true);
    void check_idle_atk_neutral_2(bool change = true);
    void check_idle_atk_neutral_3(bool change = true);
    void check_idle_atk_up(bool change = true);
    void check_idle_atk_down(bool change = true, bool condition = false);
    void check_idle_atk_front(bool change = true);
    void check_crouch_atk(bool change = true);
    void check_pass_through_platform(bool change = true);
    void check_special_1_1(bool change = true);
    void check_special_1_2(bool change = true);
    void check_special_2(bool change = true);
    void check_ultimate();
    void idle_state_on();
    void jumping_state_on();
    void falling_state_on();
    void running_state_on();
    void defending_state_on();
    void crouch_state_on();
};

#endif  // INCLUDE_BLOOD_H_
