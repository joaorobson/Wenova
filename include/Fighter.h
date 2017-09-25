/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

/**
 * @file Fighter.h
 * This file contains the definition of the Fighter.h class methods.
 */
#ifndef FIGHTER_H
#define FIGHTER_H

#include "InputManager.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Vector.h"
#include "Timer.h"

#include <vector>

using std::vector;

class Fighter : public GameObject {
protected:
    enum FighterState { IDLE, RUNNING, JUMPING, FALLING, CROUCH, IDLE_ATK_NEUTRAL_1, IDLE_ATK_NEUTRAL_2, IDLE_ATK_NEUTRAL_3, IDLE_ATK_FRONT, IDLE_ATK_UP, IDLE_ATK_DOWN, CROUCH_ATK, JUMP_ATK_UP, JUMP_ATK_NEUTRAL, JUMP_ATK_DOWN, JUMP_ATK_DOWN_FALLLOOP, JUMP_ATK_DOWN_DMG, DEFENDING, STUNNED, SPECIAL_1, SPECIAL_1_1, SPECIAL_1_2, SPECIAL_2, DYING, LAST };
    enum Button { JUMP_BUTTON, UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON, ATTACK_BUTTON, SPECIAL1_BUTTON, SPECIAL2_BUTTON, BLOCK_BUTTON, ULTIMATE_BUTTON };
    enum Orientation { LEFT, RIGHT };
    enum AttackDirection { ATK_DOWN = 1, ATK_LEFT = 2, ATK_UP = 4, ATK_RIGHT = 8 };
    vector<Sprite>sprite;
    vector<Sound>sound;
    Sound hit_sounds[4];
    FighterState state, temporary_state;
    Orientation orientation;
    Vector speed;
    Vector acceleration;
    Sound land_sound, ultimate_sound;
    Vector crouching_size, not_crouching_size;
    float vertical_speed;
    bool on_floor, grab;
    int last_collided_floor;
    float max_speed;
    float remaining_life;
    int id;
    int combo;
    int n_sprite_start;
    float attack_damage;
    int attack_mask;
    Fighter *partner;

    /**
     * test_limits method.
     * this method checks the limits the character can reach in the game frame.
     */
    void test_limits();

    /**
     * play_sound method.
     * this method plays a given sound if the file is open.
     */
    void play_sound();

    float special;
    Timer crouch_timer;
    Timer pass_through_timer;

    bool pressed[20];
    bool is_holding[20];
    bool released[20];

    bool ultimate_ready, played;

    string path, sound_path;

    /**
     * process_input method.
     * Implements the controls of the character.
     */
    void            process_input();

    virtual void    check_jump(bool change = true)               = 0;
    virtual void    check_fall(bool change = true)               = 0;
    virtual void    check_left(bool change = true)               = 0;
    virtual void    check_right(bool change = true)              = 0;
    virtual void    check_crouch(bool change = true)             = 0;
    virtual void    check_idle_atk_neutral_1(bool change = true) = 0;
    virtual void    check_idle_atk_neutral_2(bool change = true) = 0;
    virtual void    check_idle_atk_neutral_3(bool change = true) = 0;
    virtual void    check_stunned(bool change = true)            = 0;

    AttackDirection get_attack_orientation();

    virtual void    update_machine_state(float delta) = 0;

public:
    /**
     * The constructor.
     * Initialize the fighter character.
     *
     * @param cid is a number of the type integer.
     * @param x is a number of the type float.
     * @param cpartner is a object of Fighter.
     */
    Fighter(int      cid,
            float    x,
            Fighter *cpartner = nullptr);

    /**
     * The Destructor.
     * Destructs a previously initialized object of this class.
     */
    ~Fighter();

    /**
     * update method.
     * updates some of the fighter characteristics.
     */
    void  update(float delta);

    /**
     * render method.
     * renders a character orientation.
     * renders the character sprit based on is position.
     */
    void  render();

    /**
     * is_dead method.
     * tells if a character is dead or not.
     * this method returns a boolean type, true or false.
     */
    bool  is_dead();

    /**
     * get_remaining_life method.
     * this method returns how much life a character has left.
     */
    float get_remaining_life();

    /**
     * get_special method.
     * this method returns a character's special skill.
     */
    float get_special();

    /**
     * notify_collision method.
     * Implements the character collision.
     * Checks the current state of the fighter and uses the corret collision
     *state.
     *
     *@param GameObject
     *@param object
     */
    void  notify_collision(GameObject& object);

    /**
     * kill method.
     * this method sets the fighter's remaining_life to 0.
     * Kills the fighter.
     */
    void  kill();

    /**
     * change_state method.
     * this method changes a character state.
     * Changes it from jumping, crouching and combined possibilities.
     * @param cstate is a object of the FightState class and is passed as a
     *parameter
     * to change the current character state.
     */
    void  change_state(FighterState cstate);

    /**
     * reset_position method.
     * this method resets the character position given a x and y.
     *
     * @param x is a number of the float type passed as the position in the x
     *axis.
     * @param y is a number of the float type passed as the position in the y
     *axis.
     */
    void  reset_position(float x,
                         float y);

    /**
     * play_hit method.
     * this method returns a corresponding sound according to a given situation.
     */
    void     play_hit();

    /**
     * is_attacking method.
     * this method returns if the character is attacking given the method return
     *is
     * bigger than 0.
     */
    bool     is_attacking();

    /**
     * get_attack_damage method.
     * this method returns the fighter  attack_damage variable value.
     */
    float    get_attack_damage();

    /**
     * get_attack_mask method.
     * this method returns the fighter attack_mask variable value.
     */
    int      get_attack_mask();

    /**
     * get_id method.
     * this method returns the fighter id variable value.
     */
    int      get_id();

    /**
     * get_max_life method.
     * this method returns the fighter's MAX_LIFE variable value.
     */
    int      get_max_life();

    /**
     * increment_life method.
     * this method incremenets the fighter's life.
     *
     * @param increment is the amount of life that should be incremented to the
     * fighter.
     */
    void     increment_life(float increment);

    /**
     * increment_special method.
     * this method increments a fighter's special.
     *
     * @param increment is the amount special of a fighter that should be
     * incremented.
     */
    void     increment_special(float increment);

    /**
     * set_partner method.
     * this method sets the partner variable value.
     *
     * @param cpartner is another instance of fighter that is passed and set in
     *the
     * parter variable.
     */
    void     set_partner(Fighter *cpartner);

    /**
     * get_partner method.
     * this method returns the fighter partner variable value.
     */
    Fighter* get_partner();

    /**
     * get_path method.
     * this method returns the fighter's path.
     */
    string   get_path();

    double MAX_LIFE              = 2000;
    static const int MAX_SPECIAL = 250;
};

#endif // ifndef FIGHTER_H
