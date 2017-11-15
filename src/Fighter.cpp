/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Fighter.cpp
 * Brief Description.
 */

#include "Fighter.h"

#include "Floor.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

#define LAYER 0

#define PI 3.14159265358979
#define INVALID_ID -100
#define CROUCH_COOLDOWN 100.0

using std::min;
using std::pair;
using std::vector;

/**
 * Brief Description.
 *
 * @param cid
 * @param x
 * @param cpartner
 */
Fighter::Fighter(int cid, float x, Fighter *cpartner)
        : state(FighterState::IDLE)
        , temporary_state(state)
        , partner(cpartner)
        , orientation((x > 640 ? LEFT : RIGHT))
        , acceleration(Vector(0, 0.1))
        , speed(Vector(0, 0))
        , attack_mask(0)
        , combo(0)
        , id(cid)
        , last_collided_floor(0)
        , n_sprite_start(0)
        , attack_damage(0)
        , max_speed(9)
        , vertical_speed(rotation = 0)
        , on_floor(false)
        , grab(false)
        , special(0)
        , ultimate_ready(false)
        , played(false) {
    /**
     * Can't be on initialization list because fighter state ahst to be
     * set first.
     */
    MAX_LIFE = 2000;
    remaining_life = MAX_LIFE;

    sprite = vector<Sprite>(LAST);
    sound = vector<Sound>(LAST);
    pass_through_timer.set(100);

    memset(&pressed, 0, sizeof(pressed));
    memset(&is_holding, 0, sizeof(is_holding));
    memset(&released, 0, sizeof(released));

    tags["player"] = true;
}

/**
 * Brief Description.
 */
Fighter::~Fighter() {
}

/**
 * Brief Description.
 */
void Fighter::process_input() {
    if (not is("game_over")) {
        InputManager *input_manager = InputManager::get_instance();
        vector<pair<int, int> > joystick_buttons = {
            ii(JUMP_BUTTON, InputManager::A),
            ii(UP_BUTTON, InputManager::UP),
            ii(DOWN_BUTTON, InputManager::DOWN),
            ii(LEFT_BUTTON, InputManager::LEFT),
            ii(RIGHT_BUTTON, InputManager::RIGHT),
            ii(ATTACK_BUTTON, InputManager::X),
            ii(SPECIAL1_BUTTON, InputManager::B),
            ii(SPECIAL2_BUTTON, InputManager::RB),
            ii(BLOCK_BUTTON, InputManager::LB),
            ii(ULTIMATE_BUTTON, InputManager::Y)};

        bool alive = !is("dying");

        for (ii button : joystick_buttons) {
            pressed[button.first] = alive and
                input_manager->joystick_button_press(button.second, id);
            is_holding[button.first] = alive and
                input_manager->is_joystick_button_down(button.second, id);
            released[button.first] = alive and
                input_manager->joystick_button_release(button.second, id);
        }
    } else {
        memset(pressed, false, sizeof pressed);
        memset(is_holding, false, sizeof is_holding);
    }
}

/**
 * Brief Description.
 *
 * @param delta
 */
void Fighter::update(float delta) {
    process_input();

    temporary_state = state;

    sprite[state].update(delta);
    pass_through_timer.update(delta);

    update_machine_state(delta);

    speed.y = std::min(speed.y + !on_floor * acceleration.y * delta, max_speed);
    box.x += speed.x * delta;
    if (not on_floor) {
        box.y += speed.y * delta;
    }

    test_limits();

    crouch_timer.update(delta);

    change_state(temporary_state);

    speed.x = 0;
    grab = false;
    attack_damage *= delta;
    on_floor = false;
}

/**
 * Brief Description.
 *
 * @param object
 */
void Fighter::notify_collision(const GameObject &object) {
    int partner_id = (partner ? partner->get_id() : INVALID_ID);
    int not_in_ultimate = (tags["in_ultimate"] ? 0 : 1);

    // FIXME tá feio
    float floor_y = object.box.y +
        (box.x - object.box.x) * tan(object.rotation) - object.box.height * 0.5;

    if (object.is("floor") and speed.y >= 0 and
        abs(floor_y - (box.y + box.height * 0.5)) < 10) {
        if (pass_through_timer.get() < 30 and object.is("platform"))
            return;

        int floor_id = ((const Floor &) object).get_id();
        speed.y = 0;

        float new_y = object.box.y +
            (box.x - object.box.x) * tan(object.rotation) -
            (box.height + object.box.height) * 0.5;

        if (last_collided_floor != floor_id)
            box.y = min(box.y, new_y);
        else
            box.y = new_y;

        on_floor = true;
        last_collided_floor = ((const Floor &) object).get_id();
    } else if (object.is("player") and not is("dying") and
               not(object.is("dying"))) {
        Fighter const &fighter = (const Fighter &) object;

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
                    ((state == FighterState::DEFENDING) ? 0 : 1) *
                    not_in_ultimate;
                this->increment_special(m_increment_special);
                if (state != FighterState::DEFENDING)
                    check_stunned();
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
 * Brief Description.
 */
void Fighter::render() {
    int x = box.get_draw_x() +
        (orientation == RIGHT ? 0 : -1) * (sprite[state].get_width() - 84);
    int y = box.get_draw_y();

    SDL_RendererFlip flip = (orientation == Orientation::LEFT)
        ? SDL_FLIP_HORIZONTAL
        : SDL_FLIP_NONE;
    sprite[state].render(x, y, rotation, flip);
}

/**
 * Brief Description.
 *
 * @returns
 */
bool Fighter::is_dead() {
    bool dead = remaining_life <= 0;
    if (dead and partner)
        partner->set_partner(nullptr);
    return remaining_life <= 0;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Fighter::get_remaining_life() {
    return remaining_life;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Fighter::get_special() {
    return special;
}

/**
 * Brief Description.
 *
 * @param cstate
 */
// only use in the end of update
void Fighter::change_state(FighterState cstate) {
    if (state == cstate)
        return;

    float old_height = box.height;
    played = false;

    if ((state == FALLING or state == JUMPING) and
        (cstate == IDLE or cstate == RUNNING))
        land_sound.play();
    state = cstate;
    Vector csize;
    if (cstate == CROUCH or cstate == CROUCH_ATK or cstate == SPECIAL_1 or
        cstate == JUMP_ATK_DOWN_FALLLOOP or cstate == JUMP_ATK_DOWN_DMG)
        csize = crouching_size;
    else
        csize = not_crouching_size;
    float new_height = csize.y;

    sprite[state].restart_count(n_sprite_start);
    n_sprite_start = 0;
    play_sound();

    float y = box.y - (new_height - old_height) * 0.5;

    box = Rectangle(box.x, y, csize.x, csize.y);
}

/**
 * Brief Description.
 */
void Fighter::test_limits() {
    if (box.x < box.width / 2)
        box.x = box.width / 2;
    if (box.x > 1280 - box.width / 2)
        box.x = 1280 - box.width / 2;
    if (box.y < -100) {
        box.y = -100;
    }

    if (box.y > 900) {
        if (is("test"))
            box.y = -100;
        else
            increment_life(-10000);
    }
}

/**
 * Brief Description.
 *
 * @returns
 */
Fighter::AttackDirection Fighter::get_attack_orientation() {
    return (orientation == Orientation::LEFT ? AttackDirection::ATK_LEFT
                                             : AttackDirection::ATK_RIGHT);
}

/**
 * Brief Description.
 *
 * @param x
 * @param y
 */
void Fighter::reset_position(float x, float y) {
    box.x = x;
    box.y = y;
    speed.y = 0;
}

/**
 * Brief Description.
 *
 * @returns
 */
bool Fighter::is_attacking() const {
    return attack_damage > 0;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Fighter::get_attack_damage() const {
    return attack_damage;
}

/**
 * Brief Description.
 *
 * @returns
 */
int Fighter::get_attack_mask() const {
    return attack_mask;
}

/**
 * Brief Description.
 *
 * @returns
 */
int Fighter::get_id() const {
    return id;
}

/**
 * Brief Description.
 *
 * @param increment
 */
void Fighter::increment_life(float increment) {
    remaining_life += increment;
    if (remaining_life < 1) {
        remaining_life = 1;
        special = 0;
        if (partner)
            partner->set_partner(nullptr);
        add_tags("dying");
    }

    if (remaining_life > MAX_LIFE)
        remaining_life = MAX_LIFE;
}

/**
 * Brief Description.
 *
 * @param increment
 */
void Fighter::increment_special(float increment) {
    special += increment;
    if (special < 0)
        special = 0;
    if (special > MAX_SPECIAL)
        special = MAX_SPECIAL;
}

/**
 * Brief Description.
 *
 * @param cpartner
 */
void Fighter::set_partner(Fighter *cpartner) {
    partner = cpartner;
}

/**
 * Brief Description.
 *
 * @returns
 */
Fighter *Fighter::get_partner() {
    return partner;
}

/**
 * Brief Description.
 *
 * @returns
 */
string Fighter::get_path() {
    return path;
}

/**
 * Brief Description.
 */
void Fighter::play_sound() {
    if (sound[state].is_open()) {
        sound[state].play(0);
    }
    /**
     * Brief Description.
     *
     * @returns
     */
}
int Fighter::get_max_life() {
    return MAX_LIFE;
}

/**
 * Brief Description.
 */
void Fighter::play_hit() {
    if (played)
        return;
    played = true;
    string sound_file = sound[state].get_file();
    int sound_index = -1;
    if (sound_file == sound_path + "slash.ogg")
        sound_index = 0;
    else if (sound_file == sound_path + "attack_1.ogg")
        sound_index = 1;
    else if (sound_file == sound_path + "attack_2.ogg")
        sound_index = 2;
    else if (sound_file == sound_path + "attack_3.ogg")
        sound_index = 3;
    if (sound_index != -1)
        hit_sounds[sound_index].play();
}

/**
 * Brief Description.
 */
void Fighter::kill() {
    remaining_life = 0;
}
