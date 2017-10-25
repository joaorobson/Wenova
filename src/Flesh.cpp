/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Flesh.cpp
 * Implements class Flesh methods.  
 */

#include "Flesh.h"
#include "Game.h"
#include "FleshUltimateEffect.h"

#define CROUCH_COOLDOWN 400.0

#define INITIAL_COMBO = 0

#define RATE_ADD_TO_JUMP_ATTACK_UP = 7
#define RATE_ADD_TO_JUMP_ATTACK_NEUTRAL = 7

#define RATE_ADD_TO_IDLE_ATTACK_UP = 3
#define RATE_ADD_TO_IDLE_ATTACK_NEUTRAL_1 = 3
#define RATE_ADD_TO_IDLE_ATTACK_NEUTRAL_2 = 1
#define RATE_ADD_TO_IDLE_ATTACK_NEUTRAL_3 = 1

#define RATE_ADD_TO_IDLE_ATTACK_FRONT = 1

#define RATE_ADD_TO_CROUCH_ATK = 3

#define RATE_ADD_SPEED_JUMP_ATK_DOWN_FALLLOOP = 1
#define RATE_ADD_SPEED_JUMP_ATK_DOWN_DMG = 1
#define RATE_ADD_SPEED_ESPECIAL_1 = 4

#define WALK_TO_LEFT = -1
#define WALK_TO_RIGHT = 1

#define ATTACK_DAMAGE_STUNNED = 0
#define ATTACK_MASK_STUNNED = 0

#define ATTACK_DAMAGE_IDLE = 0
#define ATTACK_MASK_IDLE = 0

#define ATTACK_DAMAGE_DEFENDING = 0
#define ATTACK_MASK_DEFENDING = 0

#define ATTACK_DAMAGE_DYING = 0
#define REMAINING_LIFE_DYING = 0

#define ATTACK_DAMAGE_JUMPING = 0
#define ATTACK_DAMAGE_FALLING = 0
#define ATTACK_DAMAGE_RUNNING = 0
#define ATTACK_DAMAGE_CROUNCH = 0

#define SPEED_Y_JUMP_ATTACK_UP = 0.1
#define SPEED_Y_JUMP_BUTTON = -5

#define SPEED_Y_IDLE_ATTACK_FRONT = 0

#define SPEED_X_JUMP_ATTACK_DOWN_FALLOOP_ON_FLOOR = 0
#define SPEED_X_JUMP_ATTACK_DOWN_DMG = 0

#define SPEED_X_STUNNED = 0;

#define BOX_Y_ESPECIAL_1 = 15

#define MINIMUM_TO_ADD_ESPECIAL_2_ATTACK = 1
#define MAXIMUM_TO_ADD_ESPECIAL_2_ATTACK = 1.0
#define MAXIMUM_TO_ADD_ESPECIAL_2_SPEED = 1.0
#define RATE_TO_REMAINING_LIFE_ESPECIAL_2 = 1.0
#define RATE_TO_INITIAL_SPEED_ESPECIAL_2 = 0.5


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
Flesh::Flesh(string skin, float x, float y, int cid, Fighter *cpartner)
    : Fighter(cid, x, cpartner) {
    path = "characters/flesh/" + skin + "/";
    sound_path = "characters/flesh/sound/";

    sprite[IDLE] = Sprite(path + "idle.png", 8, 10);
    sprite[RUNNING] = Sprite(path + "running.png", 8, 10);
    sprite[JUMPING] = Sprite(path + "jumping.png", 6, 10);
    sprite[FALLING] = Sprite(path + "falling.png", 7, 10);
    sprite[CROUCH] = Sprite(path + "crouch.png", 6, 20);
    sprite[IDLE_ATK_NEUTRAL_1] = Sprite(path + "idle_atk_neutral_1.png", 4,
                                        10);
    sprite[IDLE_ATK_NEUTRAL_2] = Sprite(path + "idle_atk_neutral_2.png", 3,
                                        10);
    sprite[IDLE_ATK_NEUTRAL_3] = Sprite(path + "idle_atk_neutral_3.png", 5,
                                        10);
    sprite[IDLE_ATK_UP] = Sprite(path + "idle_atk_up.png", 4, 10);
    sprite[IDLE_ATK_FRONT] = Sprite(path + "idle_atk_front.png", 4, 10);
    sprite[JUMP_ATK_DOWN_FALLLOOP] = Sprite(path +
           "jump_atk_down_fallloop.png", 3, 10);
    sprite[JUMP_ATK_DOWN_DMG] = Sprite(path + "jump_atk_down_dmg.png", 3, 10);
    sprite[JUMP_ATK_UP] = Sprite(path + "jump_atk_up.png", 4, 10);
    sprite[JUMP_ATK_NEUTRAL] = Sprite(path + "jump_atk_neutral.png", 4, 10);
    sprite[IDLE_ATK_DOWN] = Sprite(path + "idle_atk_down.png", 4, 10);
    sprite[CROUCH_ATK] = Sprite(path + "crouch_atk.png", 4, 10);
    sprite[SPECIAL_1] = Sprite(path + "special_1.png", 3, 30);
    sprite[STUNNED] = Sprite(path + "stunned.png", 2, 10);
    sprite[DYING] = Sprite(path + "dying.png", 10, 10);
    sprite[DEFENDING] = Sprite(path + "defense.png", 2, 10);

    sound[JUMPING] = Sound(sound_path + "jump.ogg");
    sound[IDLE_ATK_NEUTRAL_1] = Sound(sound_path + "attack_1.ogg");
    sound[IDLE_ATK_NEUTRAL_2] = Sound(sound_path + "attack_2.ogg");
    sound[IDLE_ATK_NEUTRAL_3] = Sound(sound_path + "attack_3.ogg");
    sound[IDLE_ATK_UP] = Sound(sound_path + "slash.ogg");
    sound[IDLE_ATK_FRONT] = Sound(sound_path + "slash.ogg");
    sound[IDLE_ATK_DOWN] = Sound(sound_path + "attack_1.ogg");
    sound[JUMP_ATK_UP] = Sound(sound_path + "attack_1.ogg");
    sound[JUMP_ATK_DOWN_DMG] = Sound(sound_path + "slash.ogg");
    sound[JUMP_ATK_NEUTRAL] = Sound(sound_path + "attack_2.ogg");
    sound[CROUCH_ATK] = Sound(sound_path + "attack_2.ogg");

    ultimate_sound = Sound(sound_path + "ultimate.ogg");
    land_sound = Sound(sound_path + "land.ogg");
    hit_sounds[0] = Sound(sound_path + "hit_slash.ogg");
    hit_sounds[1] = Sound(sound_path + "hit_1.ogg");
    hit_sounds[2] = Sound(sound_path + "hit_2.ogg");
    hit_sounds[3] = Sound(sound_path + "hit_3.ogg");

    crouching_size = Vector(84, 59);
    not_crouching_size = Vector(84, 84);

    tags["flesh"] = true;
    tags[skin] = true;
    box = Rectangle(x, y, 84, 84);
    additional_attack_damage = 1;
    additional_speed = 0;
}

/**
 * Fighter's state machine
 * Check and update the Fighter's state according to the attack type and damage
 * suffered.
 *
 * @param float is the variation of character state.
 */
void Flesh::update_machine_state(float) {
    /**
     * State Machine
     */
    switch (state) {
        case FighterState::JUMP_ATK_UP:
            attack_damage = (RATE_ADD_TO_JUMP_ATTACK_UP *
                             additional_attack_damage) *
                            (sprite[state].get_current_frame() == 1);
            attack_mask = get_attack_orientation();
            check_left(false);
            check_right(false);
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                speed.y = SPEED_Y_JUMP_ATTACK_UP;
                check_fall();
                check_idle();
            }
        break;

        case FighterState::IDLE_ATK_UP:
            attack_damage = (RATE_ADD_TO_IDLE_ATTACK_UP *
                             additional_attack_damage) *
                            (sprite[state].get_current_frame() == 1);
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_defense();
                check_crouch();
            }
        break;

        case FighterState::IDLE_ATK_NEUTRAL_1:
            attack_damage = (RATE_ADD_TO_IDLE_ATTACK_NEUTRAL_1 *
                             additional_attack_damage) *
                            (sprite[state].get_current_frame() == 1);
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_defense();
                check_crouch();
                check_idle_atk_neutral_2();
            } else if (pressed[ATTACK_BUTTON]) {
                combo++;
            }
        break;

        case FighterState::IDLE_ATK_NEUTRAL_2:
            attack_damage = (RATE_ADD_TO_IDLE_ATTACK_NEUTRAL_2 *
                             additional_attack_damage) *
                            (sprite[state].get_current_frame() == 1);
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_defense();
                check_crouch();
                check_idle_atk_neutral_3();
            } else if (pressed[ATTACK_BUTTON]) {
                combo++;
            }
        break;

        case FighterState::IDLE_ATK_NEUTRAL_3:
            attack_damage = RATE_ADD_TO_IDLE_ATTACK_NEUTRAL_3 *
                            additional_attack_damage;
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_defense();
                check_crouch();
            }
        break;

        case FighterState::IDLE_ATK_FRONT:
            attack_damage = RATE_ADD_TO_IDLE_ATTACK_FRONT *
                            additional_attack_damage;
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_fall();
                check_defense();
                check_crouch();
            }
        break;

        case FighterState::JUMP_ATK_NEUTRAL:
            attack_damage = (RATE_ADD_TO_JUMP_ATTACK_NEUTRAL *
                             additional_attack_damage) *
                            (sprite[state].get_current_frame() < 1);
            attack_mask = get_attack_orientation();
            check_right(false);
            check_left(false);
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_fall();
            }
            /**
             * Check if in use sprite is on floor
             */
            if (on_floor) {
                check_idle();
                check_defense();
                check_right();
                check_left();
                check_crouch();
            }
        break;

        case FighterState::CROUCH_ATK:
            attack_damage = (RATE_ADD_TO_CROUCH_ATK *
                             additional_attack_damage) *
                            (sprite[state].get_current_frame() == 1);
            attack_mask = get_attack_orientation() | AttackDirection::ATK_DOWN;
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_defense();
                check_crouch();
            }
        break;

        case FighterState::JUMP_ATK_DOWN_FALLLOOP:
            speed.x = (INITIAL_SPEED + RATE_ADD_SPEED_JUMP_ATK_DOWN_FALLLOOP +
                       additional_speed) * (orientation == LEFT ?
                                            WALK_TO_LEFT : WALK_TO_RIGHT);
            speed.y = (INITIAL_SPEED + RATE_ADD_SPEED_JUMP_ATK_DOWN_FALLLOOP +
                       additional_speed);
            attack_damage = BASIC_ATTACK_DAMAGE + additional_attack_damage;
            attack_mask = get_attack_orientation();

            check_jump_atk_down_dmg();
            /**
             * Check if in use sprite is on floor
             */
            if (on_floor) {
                speed.x = SPEED_X_JUMP_ATTACK_DOWN_FALLOOP_ON_FLOOR;
                check_idle();
                check_defense();
                check_left();
                check_right();
                check_crouch();
            }
        break;

        case FighterState::JUMP_ATK_DOWN_DMG:
            speed.x = (INITIAL_SPEED + RATE_ADD_SPEED_JUMP_ATK_DOWN_DMG +
                       additional_speed) * (orientation == LEFT ?
                                            WALK_TO_LEFT : WALK_TO_RIGHT);
            speed.y = (INITIAL_SPEED + RATE_ADD_SPEED_JUMP_ATK_DOWN_DMG +
                       additional_speed);
            /**
             * Check if in use sprite is finished or on floor
             */
            if (sprite[state].is_finished() or on_floor) {
                speed.x = SPEED_X_JUMP_ATTACK_DOWN_DMG;
                check_idle();
                check_defense();
                check_crouch();
                check_fall();
            }
        break;

        case FighterState::IDLE_ATK_DOWN:
            attack_damage = (BASIC_ATTACK_DAMAGE * additional_attack_damage) *
                            (sprite[state].get_current_frame() == 1);
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_idle();
                check_defense();
                check_crouch();
            }
        break;

        case FighterState::STUNNED:
            attack_damage = ATTACK_DAMAGE_STUNNED;
            attack_mask = ATTACK_MASK_STUNNED;
            check_special_2();
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                check_fall();
                check_idle();
                check_defense();
                check_crouch();
                check_dead();
            }
        break;

        case FighterState::SPECIAL_1:
            attack_damage = SPECIAL_1_DAMAGE * additional_attack_damage;
            speed.x = RATE_ADD_SPEED_ESPECIAL_1 * (orientation == LEFT ?
                                                WALK_TO_LEFT : WALK_TO_RIGHT);
            attack_mask = get_attack_orientation();
            /**
             * Check if in use sprite is grabbing
             */
            if (grab) {
                check_idle_atk_front(true, true);
            }
            check_idle(true, on_floor);
            check_defense();
            check_crouch();
        break;

        case FighterState::IDLE:
            combo = INITIAL_COMBO;
            attack_damage = ATTACK_DAMAGE_IDLE;
            attack_mask = ATTACK_MASK_IDLE;
            check_jump();
            check_left(on_floor);
            check_right(on_floor);
            check_idle_atk_down();
            check_crouch();
            check_fall();
            check_idle_atk_neutral_1();
            check_idle_atk_front();
            check_special_1();
            check_special_2();
            check_ultimate();
            check_defense();
            check_pass_through_platform();
            check_idle_atk_up();
            check_dead();
        break;

        case FighterState::JUMPING:
            attack_damage = ATTACK_DAMAGE_JUMPING;
            check_left(on_floor);
            check_right(on_floor);
            check_fall();
            check_jump_atk_neutral();
            check_jump_atk_down_fallloop();
            check_idle();
            check_defense();
            check_crouch();
            check_ultimate();
            check_jump_atk_up();
            check_special_1();
        break;

        case FighterState::FALLING:
            attack_damage = ATTACK_DAMAGE_FALLING;
            check_idle();
            check_left(false);
            check_right(false);
            check_fall();
            check_crouch();
            check_jump_atk_neutral();
            check_jump_atk_down_fallloop();
            check_ultimate();
            check_jump_atk_up();
            check_special_1();
        break;

        case FighterState::RUNNING:
            attack_damage = ATTACK_DAMAGE_RUNNING;
            combo = INITIAL_COMBO;
            check_jump();
            check_left(false);
            check_right(false);
            check_idle();
            check_crouch();
            check_idle_atk_neutral_1();
            check_idle_atk_front();
            check_fall();
            check_special_1();
            check_ultimate();
            check_defense();
            check_pass_through_platform();
            check_idle_atk_up();
        break;

        case FighterState::CROUCH:
            attack_damage = ATTACK_DAMAGE_CROUNCH;
            check_idle();
            check_crouch_atk();
            check_fall();
        break;

        case FighterState::DEFENDING:
            attack_damage = ATTACK_DAMAGE_DEFENDING;
            attack_mask = ATTACK_MASK_DEFENDING;
            check_idle();
            check_fall();
        break;

        case FighterState::DYING:
            attack_damage = ATTACK_DAMAGE_DYING;
            /**
             * Check if in use sprite is finished
             */
            if (sprite[state].is_finished()) {
                remaining_life = REMAINING_LIFE_DYING;
            }
        break;

        case FighterState::JUMP_ATK_DOWN:
        case FighterState::SPECIAL_1_1:
        case FighterState::SPECIAL_1_2:
        case FighterState::SPECIAL_2:
        case FighterState::LAST:
            printf("Invalid flesh %d %d state\n", id, state);
            exit(-1);
        break;
    }
}

/**
 * Makes the character jump
 *
 * @param change check if the state os character changed
 */
void Flesh::check_jump(bool change) {
    /**
     * Check if the user is pressing the jump button
     */
    if (pressed[JUMP_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::JUMPING;
        }
        speed.y = SPEED_Y_JUMP_BUTTON;
        on_floor = false;
    }
}

/**
 * Change de state of character if it is falling
 *
 * @param change check if the state os character changed
 */
void Flesh::check_fall(bool change) {
    /**
     * Check if in use sprite is falling
     */
    if (speed.y > 0) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::FALLING;
        }
    }
}

/**
 * Makes the character go to left
 *
 * @param change check if the state os character changed
 */
void Flesh::check_left(bool change) {
    /**
     * Check if user is pressing the left button
     */
    if (is_holding[LEFT_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::RUNNING;
        }
        speed.x = - (INITIAL_SPEED + additional_speed);
        orientation = Orientation::LEFT;
    }
}

/**
 * Makes the character go to right
 *
 * @param change check if the state os character changed
 */
void Flesh::check_right(bool change) {
    /**
     * Check if user is pressing the right button
     */
    if (is_holding[RIGHT_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::RUNNING;
        }
        speed.x = (INITIAL_SPEED + additional_speed);
        orientation = Orientation::RIGHT;
    }
}

/**
 * Makes the character stay stoped
 *
 * @param change check if the state os character changed
 */
void Flesh::check_idle(bool change, bool condition) {
    /**
     * Check if the character isn't doing anything
     */
    if ((speed.x == 0 and on_floor and not is_holding[DOWN_BUTTON] and not
        is_holding[BLOCK_BUTTON]) or condition) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE;
        }
    }
}

/**
 * Makes the character crounch
 *
 * @param change check if the state os character changed
 */
void Flesh::check_crouch(bool change) {
    /**
     * Check if user is pressing down button when his character is on floor
     */
    if (is_holding[DOWN_BUTTON] and on_floor) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::CROUCH;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 */
void Flesh::check_idle_atk_neutral_1(bool change) {
    /**
     * Check if user is pressing attack button without pressing down button
     */
    if (pressed[ATTACK_BUTTON] and not is_holding[DOWN_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE_ATK_NEUTRAL_1;
        }
    }
}

/**
 * Keep the character attacking
 *
 * @param change check if the state os character changed
 */
void Flesh::check_idle_atk_neutral_2(bool change) {
    /**
     * Check if combo happened
     */
    if (combo) {
        combo--;
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE_ATK_NEUTRAL_2;
        }
    }
}

/**
 * Keep the character attacking
 *
 * @param change check if the state os character changed
 */
void Flesh::check_idle_atk_neutral_3(bool change) {
    /**
     * Check if combo happened
     */
    if (combo) {
        combo--;
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE_ATK_NEUTRAL_3;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 * @param condition check if the character is in condition
 */
void Flesh::check_idle_atk_front(bool change, bool condition) {
    /**
     * Check if user is pressing attack button and left or right button
     */
    if ((pressed[ATTACK_BUTTON] and (is_holding[LEFT_BUTTON] or
        is_holding[RIGHT_BUTTON])) or condition) {
        speed.y = SPEED_Y_IDLE_ATTACK_FRONT;
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE_ATK_FRONT;
        }
        /**
         * Check if condition did't happen
         */
        if (not condition) {
            orientation = is_holding[LEFT_BUTTON] ? Orientation::LEFT
            : Orientation::RIGHT;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 */
void Flesh::check_jump_atk_down_fallloop(bool change) {
    /**
     * Check if user is pressing attack and down button
     */
    if (pressed[ATTACK_BUTTON] and is_holding[DOWN_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::JUMP_ATK_DOWN_FALLLOOP;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 */
void Flesh::check_jump_atk_down_dmg(bool change) {
    /**
     * Check if grab happened
     */
    if (grab) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::JUMP_ATK_DOWN_DMG;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 */
void Flesh::check_jump_atk_neutral(bool change) {
    /**
     * Check if user is pressing attack button without down or up button
     */
    if (is_holding[ATTACK_BUTTON] and not is_holding[DOWN_BUTTON] and not
        is_holding[UP_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::JUMP_ATK_NEUTRAL;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 */
void Flesh::check_idle_atk_down(bool change) {
    /**
     * Check if user is pressing attack and down button
     */
    if (is_holding[ATTACK_BUTTON] and is_holding[DOWN_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE_ATK_DOWN;
        }
    }
}

/**
 * Makes the character activate him special
 *
 * @param change check if the state os character changed
 */
void Flesh::check_special_1(bool change) {
    /**
     * Check if user is pressing special button
     */
    if (pressed[SPECIAL1_BUTTON]) {
        if (speed.y == 0) {
            speed.y = -5;
        }
        box.y - = BOX_Y_ESPECIAL_1;
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::SPECIAL_1;
        }
    }
}

/**
 * Makes the character more stronger cause him special
 *
 * @param bool
 */
void Flesh::check_special_2(bool) {
    additional_attack_damage = MINIMUM_TO_ADD_ESPECIAL_2_ATTACK +
                               (MAXIMUM_TO_ADD_ESPECIAL_2_ATTACK -
                                (get_remaining_life()) / MAX_LIFE);
    additional_speed = (MAXIMUM_TO_ADD_ESPECIAL_2_SPEED -
                       (RATE_TO_REMAINING_LIFE_ESPECIAL_2 *
                        get_remaining_life()) / MAX_LIFE) * INITIAL_SPEED *
                        RATE_TO_INITIAL_SPEED_ESPECIAL_2;
}

/**
 * Makes the character activate him ultimate
 *
 * @param bool
 */
void Flesh::check_ultimate(bool) {
    /**
     * Check if user is pressing ultimate button with his atribute special on
     * maximun
     */
    if (pressed[ULTIMATE_BUTTON] and special == MAX_SPECIAL) {
        Game::get_instance().get_current_state().add_object(new
            FleshUltimateEffect(this, path + "ult_effect.png", "has_sprite",
                                1));
        ultimate_sound.play();
    }
}

/**
 * Makes the character pass through platform
 *
 * @param change check if the state os character changed
 */
void Flesh::check_pass_through_platform(bool change) {
    /**
     * Check if user is pressing down button without attack button
     */
    if (pressed[DOWN_BUTTON] and not is_holding[ATTACK_BUTTON]) {
        /**
         * Check if the crouch isn't in cooldown
         */
        if (crouch_timer.get() < CROUCH_COOLDOWN) {
            /**
             * Check if change happened
             */
            if (change) {
                temporary_state = FighterState::FALLING;
            }
            pass_through_timer.restart();
        }
        crouch_timer.restart();
    }
}

/**
 * Makes the character in defense mode
 *
 * @param change check if the state os character changed
 */
void Flesh::check_defense(bool change) {
    /**
     * Check if user is pressing block button with his character on floor
     */
    if (is_holding[BLOCK_BUTTON] and on_floor) {
        /**
         * Check if change happened
         */
        if (change) {
                temporary_state = FighterState::DEFENDING;
        }
    }
}

/**
 * Makes the character in stunned mode
 *
 * @param change check if the state os character changed
 */
void Flesh::check_stunned(bool change) {
    speed.x = SPEED_X_STUNNED;
    /**
     * Check if change happened
     */
    if (change) {
        temporary_state = FighterState::STUNNED;
    }
}

/**
 * Makes the character dead
 *
 * @param change check if the state os character changed
 */
void Flesh::check_dead(bool change) {
    /**
     * Check if in use sprite is dying
     */
    if (is("dying")) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::DYING;
        }
    }
}

/**
 * Makes the character attack crounched
 *
 * @param change check if the state os character changed
 */
void Flesh::check_crouch_atk(bool change) {
    /**
     * Check if user is pressing attack button
     */
    if (pressed[ATTACK_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::CROUCH_ATK;
        }
    }
}

/**
 * Makes the character attack jumping
 *
 * @param change check if the state os character changed
 */
void Flesh::check_jump_atk_up(bool change) {
    /**
     * Check if user is pressing attack and up button
     */
    if (pressed[ATTACK_BUTTON] and is_holding[UP_BUTTON]) {
        /**
         * Check if combo happened
         */
        if (combo) {
            return;
        }
        combo++;
        speed.y = SPEED_Y_JUMP_BUTTON;
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::JUMP_ATK_UP;
        }
    }
}

/**
 * Makes the character attack
 *
 * @param change check if the state os character changed
 */
void Flesh::check_idle_atk_up(bool change) {
    /**
     * Check if user is pressing attack and up button
     */
    if (pressed[ATTACK_BUTTON] and is_holding[UP_BUTTON]) {
        /**
         * Check if change happened
         */
        if (change) {
            temporary_state = FighterState::IDLE_ATK_UP;
        }
    }
}
