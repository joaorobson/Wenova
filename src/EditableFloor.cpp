/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file EditableFloor.cpp
 * Implements class EditableFloor methods.
 */

#include "EditableFloor.h"

#include "Collision.h"
#include "InputManager.h"
#include "Rectangle.h"

#include <cstdio>

#define LAYER 0
#define FLOOR_INITIAL_WIDTH 100
#define PI 3.14159265358979
#define PI_DEGREES 180

#define RIGID_PLATFORM_PATH "edit_state/floor/editable_floor.png"
#define CROSSINGABLE_PLATFORM_PATH "edit_state/floor/editable_platform.png"
#define SELECTED_CROSSINGABLE_PLATFORM_PATH \
    "edit_state/floor/selected_editable_floor.png"

#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 720

#define INFO_SIZE 500
#define FILL_MISSING_PIXELS_INFORMATIOS 15

#define ACCELERATION 1
#define MAXIMUM_ACCELERATION 4
#define ACCELERATION_INCREASE_STEP 0.2

#define RESIZING_SPEED 0.005
#define ROTATING_SPEED 0.01
#define MOVE_SPEED 0.5

/**
 * Create box with default width of 100px.
 *
 * @param x Position in X axis. Unit: px, [0,screen_width]
 * @param y Position in Y axis. Unit: px, [0,screen_height]
 * @param crotation Unit: degrees
 * @param cplatform [0,1]
 */
EditableFloor::EditableFloor(float x, float y, float crotation, bool cplatform)
    : Floor(x, y, FLOOR_INITIAL_WIDTH, crotation, cplatform),
      standard_sprite(Sprite(RIGID_PLATFORM_PATH)),
      platform_sprite(Sprite(CROSSINGABLE_PLATFORM_PATH)),
      selected_sprite(Sprite(SELECTED_CROSSINGABLE_PLATFORM_PATH)) {

    box = Rectangle(x, y,
                         standard_sprite.get_width(),
                         standard_sprite.get_height());

    is_deleted = false;
    is_selected = false;
}

/**
 * Create box with specific width.
 *
 * @param x Position in X axis. Unit: px, [0,screen_width]
 * @param y Position in Y axis. Unit: px, [0,screen_height]
 * @param width Unit: px, [0,]
 * @param crotation Unit: degrees
 * @param cplatform [0,1]
 */
EditableFloor::EditableFloor(float x, float y, float width, float crotation,
                             bool cplatform)
    : EditableFloor(x, y, crotation, cplatform) {

    standard_sprite.set_scale_x(width / standard_sprite.get_width());
    platform_sprite.set_scale_x(width / platform_sprite.get_width());
    selected_sprite.set_scale_x(width / selected_sprite.get_width());

    box.width = standard_sprite.get_width();
}

/**
 * Not implemented.
 */
EditableFloor::~EditableFloor() {}

/**
 * Manages player interaction with the box.
 *
 * @param delta Difference in position of the box.
 */
void EditableFloor::update(float delta) {
    InputManager *input_manager = InputManager::get_instance();

    if (input_manager->mouse_press(InputManager::LEFT_MOUSE_BUTTON)) {
        int x = input_manager->get_mouse_x_position();
        int y = input_manager->get_mouse_y_position();

        Rectangle mouse = Rectangle(x, y, 1, 1);
        is_selected = Collision::is_colliding(box, mouse, rotation, 0);
    }

    if (is_selected) {
        static float acceleration = ACCELERATION;
        float value = MOVE_SPEED * delta * acceleration;
        bool moved = false;

        /**
         * Move box.
         */
        if (input_manager->is_key_down(InputManager::K_ARROW_RIGHT)) {
            box.x += value;
            moved = true;
        }
        if (input_manager->is_key_down(InputManager::K_ARROW_LEFT)) {
            box.x -= value;
            moved = true;
        }
        if (input_manager->is_key_down(InputManager::K_ARROW_UP)) {
            box.y -= value;
            moved = true;
        }
        if (input_manager->is_key_down(InputManager::K_ARROW_DOWN)) {
            box.y += value;
            moved = true;
        }

        /**
         * Limit box sizes.
         */
        if (box.x < 0) {
            box.x = 0;
        }
        if (box.x > BACKGROUND_WIDTH) {
            box.x = BACKGROUND_WIDTH;
        }
        if (box.y < 0) {
            box.y = 0;
        }
        if (box.y > BACKGROUND_HEIGHT) {
            box.y = BACKGROUND_HEIGHT;
        }

        /**
         * Rotate box  to left.
         */
        if (input_manager->is_key_down(InputManager::K_ROT_LEFT)) {
            rotation += ROTATING_SPEED * value / acceleration;
        }

        /**
         * Rotate box  to right.
         */
        if (input_manager->is_key_down(InputManager::K_ROT_RIGHT)) {
            rotation -= ROTATING_SPEED * value / acceleration;
        }

        /**
         * Reset rotation.
         */
        if (input_manager->is_key_down(InputManager::K_ROT_RESET)) {
            rotation = 0;
        }

        /**
         * Toggle Floor.
         */
        if (input_manager->key_press(InputManager::K_C)) {
            is_crossingable = not is_crossingable;
        }

        /**
         * Increase floor width.
         */
        if (input_manager->is_key_down(InputManager::K_INC_W)) {
            standard_sprite.update_scale_x(RESIZING_SPEED * value);
            platform_sprite.update_scale_x(RESIZING_SPEED * value);
            selected_sprite.update_scale_x(RESIZING_SPEED * value);

            box.width = standard_sprite.get_width();
            moved = true;
        }

        /**
         * Decrease floor width.
         */
        if (input_manager->is_key_down(InputManager::K_DEC_W)) {
            standard_sprite.update_scale_x(-RESIZING_SPEED * value);
            platform_sprite.update_scale_x(-RESIZING_SPEED * value);
            selected_sprite.update_scale_x(-RESIZING_SPEED * value);

            box.width = standard_sprite.get_width();
            moved = true;
        }

        if (moved) {
            acceleration =
                fmin(acceleration + ACCELERATION_INCREASE_STEP,
                     MAXIMUM_ACCELERATION);
        } else {
            acceleration = ACCELERATION;
        }

        /**
         * Delete floor.
         */
        if (input_manager->is_key_down(InputManager::K_DEL)) {
            is_deleted = true;
        }
    }
}

/**
 * Render selected box considering if it is selected.
 */
void EditableFloor::render() {
    if (is_selected) {
        selected_sprite.render(box.get_draw_x(), box.get_draw_y(),
                               rotation);
    }

    if (is_crossingable) {
        platform_sprite.render(box.get_draw_x(), box.get_draw_y(),
                               rotation);
    } else {
        standard_sprite.render(box.get_draw_x(), box.get_draw_y(),
                               rotation);
    }
}

/**
 * True if box has been deleted.
 *
 * @returns [0,1]
 */
bool EditableFloor::is_dead() {
    return is_deleted;
}

/**
 * Not implemented.
 *
 * @param unamed An game object.
 */
void EditableFloor::notify_collision(GameObject &) {}

/**
 * Get information about many aspects of an box.
 *
 * @returns String in format: "x y width rotated level is_crossingable?"
 */
string EditableFloor::get_information() {
    char info[INFO_SIZE];
    snprintf(info, sizeof(info), "%f %f %f %f %d", box.x, box.y,
             box.width, rotation * PI_DEGREES / PI,
             static_cast<int>(is_crossingable));

    string s(info);

    for (auto &c : s) {
        c += FILL_MISSING_PIXELS_INFORMATIOS;
    }

    return s;
}

/**
 * Select elements which will be edited.
 *
 * @param cis_selected [0,1]
 */
void EditableFloor::set_selected(bool cis_selected) {
    is_selected = cis_selected;
}
