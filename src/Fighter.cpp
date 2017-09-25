/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Fighter.cpp
 * This file contains the definition of the Fighter.h class methods.
 */
#include "Fighter.h"

#include "Floor.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

#define LAYER 0

#define ii pair<int, int>

#define PI 3.14159265358979
#define INVALID_ID -100
#define CROUCH_COOLDOWN 100.0

using std::min;
using std::pair;
using std::vector;

/**
 * The constructor.
 * Initialize the fighter character.
 *
 * @param cid is a number of the type integer.
 * @param x is a number of the type float.
 * @param cpartner is a object of Fighter.
 */
Fighter::Fighter(int cid, float x, Fighter * cpartner) {
    partner = cpartner;

    MAX_LIFE = 2000;

    state = FighterState::IDLE;
    id = cid;
    remaining_life = MAX_LIFE;

    special = 0;
    attack_damage = 0;
    vertical_speed = rotation = 0;
    speed = Vector(0, 0);
    acceleration = Vector(0, 0.1);
    max_speed = 9;
    attack_mask = 0;
    sprite = vector<Sprite>(LAST);
    sound = vector<Sound>(LAST);
    temporary_state = state;
    pass_through_timer.set(100);
    played = false;

    orientation = (x > 640 ? LEFT : RIGHT);

    on_floor = false;
    last_collided_floor = 0;
    grab = false;

    ultimate_ready = false;

    n_sprite_start = 0;
    tags["player"] = true;
}

/**
 * The Destructor.
 * Destructs a previously initialized object of this class.
 */
Fighter::~Fighter() {}

/**
 * process_input method.
 * Implements the controls of the character.
 */
void Fighter::process_input() {
    if (not is("game_over")) {
        InputManager * input_manager = InputManager::get_instance();
        vector< pair<int, int> > joystick_buttons = {
            ii(JUMP_BUTTON, InputManager::A),
            ii(UP_BUTTON, InputManager::UP),
            ii(DOWN_BUTTON, InputManager::DOWN),
            ii(LEFT_BUTTON, InputManager::LEFT),
            ii(RIGHT_BUTTON, InputManager::RIGHT),
            ii(ATTACK_BUTTON, InputManager::X),
            ii(SPECIAL1_BUTTON, InputManager::B),
            ii(SPECIAL2_BUTTON, InputManager::RB),
            ii(BLOCK_BUTTON, InputManager::LB),
            ii(ULTIMATE_BUTTON, InputManager::Y)
        };

        bool alive = !is("dying");

        for (ii button : joystick_buttons) {
            pressed[button.first] = alive and input_manager->joystick_button_press(button.second, id);
            is_holding[button.first] = alive and input_manager->is_joystick_button_down(button.second, id);
            released[button.first] = alive and input_manager->joystick_button_release(button.second, id);
        } else {
            memset(pressed, false, sizeof pressed);
            memset(is_holding, false, sizeof is_holding);
        }
}

/**
 * update method.
 * updates some of the fighter characteristics.
 */
void Fighter::update(float delta) {
    process_input();

    temporary_state = state;

    sprite[state].update(delta);
    pass_through_timer.update(delta);

    update_machine_state(delta);

    speed.y = std::min(speed.y + !on_floor * acceleration.y * delta, max_speed);
    box.x += speed.x * delta;
    if (not on_floor) box.y += speed.y * delta;

    test_limits();

    crouch_timer.update(delta);

    change_state(temporary_state);

    speed.x = 0;
    grab = false;
    attack_damage *= delta;
    on_floor = false;
}

/**
 * notify_collision method.
 * Implements the character collision.
 * Checks the current state of the fighter and uses the corret collision state.
 *
 *@param GameObject
 *@param object
 */
void Fighter::notify_collision(GameObject & object) {
    int partner_id = (partner ? partner->get_id() : INVALID_ID);
    int not_in_ultimate = (tags["in_ultimate"] ? 0 : 1);

    float floor_y = object.box.y + (box.x - object.box.x) * tan(object.rotation)
                     - object.box.height * 0.5;
    if (object.is("floor") and speed.y >= 0 and abs(floor_y - (box.y +
                                                               box.height *
                                                               0.5)) < 10){
        if (pass_through_timer.get() < 30 and object.is("platform")) {
            return;
        }

        int floor_id = ((Floor&)object).get_id();
        speed.y = 0;
        float new_y = object.box.y + (box.x - object.box.x) *
																			tan(object.rotation) -
																			(box.height + object.box.height ) * 0.5;
        if (last_collided_floor != floor_id) {
            box.y = min(box.y, new_y);
        } else {
            box.y = new_y;
        }


        on_floor = true;
        last_collided_floor = ((Floor&)object).get_id();
    } else if (object.is("player")
               and !is("dying") and not(object.is("dying"))) {
        Fighter & fighter = (Fighter &) object;

        if (fighter.is_attacking() and fighter.get_id() != partner_id) {
            int left = AttackDirection::ATK_LEFT * (fighter.box.x > box.x);
            int right = AttackDirection::ATK_RIGHT * (fighter.box.x <= box.x);
            int up = AttackDirection::ATK_UP * (fighter.box.y > box.y);
            int down = AttackDirection::ATK_DOWN * (fighter.box.y <= box.y);
            int position_mask = left | right | up | down;
            if (position_mask & fighter.get_attack_mask()) {
                float damage = fighter.get_attack_damage() *
															 ((state == FighterState::DEFENDING) ? 0.5 : 1);
                increment_life(-damage);
                float m_increment_special = (fighter.get_attack_damage() / 3) *
																						((state == FighterState::DEFENDING)
																						? 0 : 1) * not_in_ultimate;
                this->increment_special(m_increment_special);
                if (state != FighterState::DEFENDING) {
                    check_stunned();
                }
            }
        } else if (is_attacking() and fighter.get_id() != partner_id) {
            int left = AttackDirection::ATK_LEFT * (fighter.box.x <= box.x);
            int right = AttackDirection::ATK_RIGHT * (fighter.box.x > box.x);
            int up = AttackDirection::ATK_UP * (fighter.box.y <= box.y);
            int down = AttackDirection::ATK_DOWN * (fighter.box.y > box.y);
            int position_mask = left | right | up | down;
            if (position_mask & get_attack_mask()) {
                grab = true;
                play_hit();
                this->increment_special((attack_damage / 2) * not_in_ultimate);
            }
        }
  }

    change_state(temporary_state);
}

/**
 * render method.
 * renders a character orientation.
 * renders the character sprit based on is position.
 */
void Fighter::render() {
    int x = box.get_draw_x() + (orientation == RIGHT ? 0 : -1) *
															 (sprite[state].get_width() - 84);
    int y = box.get_draw_y();

    SDL_RendererFlip flip = (orientation == Orientation::LEFT) ?
														 SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    sprite[state].render(x, y, rotation, flip);
}

/**
 * is_dead method.
 * tells if a character is dead or not.
 * this method returns a boolean type, true or false.
 */
bool Fighter::is_dead() {
    bool dead = remaining_life <= 0;
    if (dead and partner) {
        partner->set_partner(nullptr);
    }
    return remaining_life <= 0;
}

/**
 * get_remaining_life method.
 * this method returns how much life a character has left.
 */
float Fighter::get_remaining_life() {
  return remaining_life;
}

/**
 * get_special method.
 * this method returns a character's special skill.
 */
float Fighter::get_special() {
  return special;
}

/**
 * change_state method.
 * this method changes a character state.
 * Changes it from jumping, crouching and combined possibilities.
 * @param cstate is a object of the FightState class and is passed as a parameter
 * to change the current character state.
 */
void Fighter::change_state(FighterState cstate) {
    if (state == cstate) {
        return;
    }

    float old_height = box.height;
    played = false;

    if ((state == FALLING or state == JUMPING) and (cstate == IDLE or cstate
																										== RUNNING)) {
        land_sound.play();
        state = cstate;
        Vector csize;
    }
    if (cstate == CROUCH or cstate == CROUCH_ATK or cstate == SPECIAL_1 or
									cstate == JUMP_ATK_DOWN_FALLLOOP or cstate ==
									JUMP_ATK_DOWN_DMG) {
        csize = crouching_size;
    } else {
        csize = not_crouching_size;
    }
    float new_height = csize.y;

    sprite[state].restart_count(n_sprite_start);
    n_sprite_start = 0;
    play_sound();

    float y = box.y - (new_height - old_height) * 0.5;

    box = Rectangle(box.x, y, csize.x, csize.y);
}

/**
 * test_limits method.
 * this method checks the limits the character can reach in the game frame.
 */
void Fighter::test_limits() {
    if (box.x < box.width / 2) {
        box.x = box.width / 2;
    }
    if (box.x > 1280 - box.width / 2) {
        box.x = 1280 - box.width / 2;
    }
    if (box.y < -100) {
        box.y = -100;
    }

    if (box.y > 900) {
        if (is("test")) {
            box.y = -100;
        } else {
            increment_life(-10000);
        }
    }
}

Fighter::AttackDirection Fighter::get_attack_orientation() {
    return (orientation == Orientation::LEFT ? AttackDirection::ATK_LEFT :
						AttackDirection::ATK_RIGHT);
}

/**
 * reset_position method.
 * this method resets the character position given a x and y.
 *
 * @param x is a number of the float type passed as the position in the x axis.
 * @param y is a number of the float type passed as the position in the y axis.
 */
void Fighter::reset_position(float x, float y) {
    box.x = x;
    box.y = y;
    speed.y = 0;
}

/**
 * is_attacking method.
 * this method returns if the character is attacking given the method return is
 * bigger than 0.
 */
bool Fighter::is_attacking() {
    return attack_damage > 0;
}

/**
 * get_attack_damage method.
 * this method returns the fighter  attack_damage variable value.
 */
float Fighter::get_attack_damage() {
    return attack_damage;
}

/**
 * get_attack_mask method.
 * this method returns the fighter attack_mask variable value.
 */
int Fighter::get_attack_mask() {
    return attack_mask;
}

/**
 * get_id method.
 * this method returns the fighter id variable value.
 */
int Fighter::get_id() {
    return id;
}

/**
 * increment_life method.
 * this method incremenets the fighter's life.
 *
 * @param increment is the amount of life that should be incremented to the
 * fighter.
 */
void Fighter::increment_life(float increment) {
    remaining_life += increment;
    if (remaining_life < 1) {
        remaining_life = 1;
        special = 0;
        if (partner) {
            partner->set_partner(nullptr);
        }
        add_tags("dying");
    }

    if (remaining_life > MAX_LIFE) {
        remaining_life = MAX_LIFE;
    }
}

/**
 * increment_special method.
 * this method increments a fighter's special.
 *
 * @param increment is the amount special of a fighter that should be
 * incremented.
 */
void Fighter::increment_special(float increment) {
    special += increment;
    if (special < 0) {
      special = 0;
    }
    if (special > MAX_SPECIAL) {
        special = MAX_SPECIAL;
    }
}

/**
 * set_partner method.
 * this method sets the partner variable value.
 *
 * @param cpartner is another instance of fighter that is passed and set in the
 * parter variable.
 */
void Fighter::set_partner(Fighter * cpartner) {
    partner = cpartner;
}

/**
 * get_partner method.
 * this method returns the fighter partner variable value.
 */
Fighter * Fighter::get_partner() {
    return partner;
}

/**
 * get_path method.
 * this method returns the fighter's path.
 */
string Fighter::get_path() {
    return path;
}

/**
 * play_sound method.
 * this method plays a given sound if the file is open.
 */
void Fighter::play_sound() {
    if (sound[state].is_open()) {
        sound[state].play(0);
    }
}

/**
 * get_max_life method.
 * this method returns the fighter's MAX_LIFE variable value.
 */
int Fighter::get_max_life() {
    return MAX_LIFE;
}

/**
 * play_hit method.
 * this method returns a corresponding sound according to a given situation.
 */
void Fighter::play_hit() {
    if (played) {
        return;
    }
    played = true;
    string sound_file = sound[state].get_file();
    int sound_index = -1;
    if (sound_file == sound_path + "slash.ogg") {
        sound_index = 0;
    } else if (sound_file == sound_path + "attack_1.ogg") {
        sound_index = 1;
    } else if (sound_file == sound_path + "attack_2.ogg") {
        sound_index = 2;
    } else if (sound_file == sound_path + "attack_3.ogg") {
        sound_index = 3;
    }
    if (sound_index != -1) {
        hit_sounds[sound_index].play();
}

/**
 * kill method.
 * this method sets the fighter's remaining_life to 0.
 * Kills the fighter.
 */
void Fighter::kill() {
  remaining_life = 0;
}
