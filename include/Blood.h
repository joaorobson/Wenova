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

#include "Fighter.h"
#include <string>

class Blood : public Fighter {
 private:
  void check_jump(bool change = true);
  void check_fall(bool change = true);
  void check_left(bool change = true);
  void check_right(bool change = true);
  void check_idle(bool change = true);
  void check_crouch(bool change = true);
  void check_idle_atk_neutral_1(bool change = true);
  void check_idle_atk_neutral_2(bool change = true);
  void check_idle_atk_neutral_3(bool change = true);
  void check_idle_atk_front(bool change = true);
  void check_idle_atk_up(bool change = true);
  void check_idle_atk_down(bool change = true, bool condition = false);
  void check_crouch_atk(bool change = true);
  void check_jump_atk_up(bool change = true);
  void check_jump_atk_neutral(bool change = true);
  void check_jump_atk_down(bool change = true);
  void check_pass_through_platform(bool change = true);
  void check_defense(bool change = true);
  void check_stunned(bool change = true);
  void check_special_1_1(bool change = true);
  void check_special_1_2(bool change = true);
  void check_special_2(bool change = true);
  void check_dead(bool change = true);
  void check_ultimate();

  void update_machine_state(float delta);

 public:
  Blood(string skin, float x, float y, int cid, Fighter * cpartner = nullptr);
};

#endif  // INCLUDE_BLOOD_H_
