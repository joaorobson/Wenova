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
#define PI 3.14159265358979


/** 
 * Create box with default width of 100px.
 * 
 * @param x Position in X axis. Unit: px, [0,screen_width]
 * @param y Position in Y axis. Unit: px, [0,screen_height]
 * @param crotation Unit: degrees
 * @param cplatform [0,1]
 */
EditableFloor::EditableFloor(float x, float y, float crotation, bool cplatform)
    : Floor(x, y, 100, crotation, cplatform),
      normal_sprite(Sprite("edit_state/floor/editable_floor.png")),
      platform_sprite(Sprite("edit_state/floor/editable_platform.png")),
      selected_sprite(Sprite("edit_state/floor/selected_editable_floor.png")) {
    box =
        Rectangle(x, y, normal_sprite.get_width(), normal_sprite.get_height());
    deleted = false;
    selected = false;
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
    normal_sprite.set_scale_x(width / normal_sprite.get_width());
    platform_sprite.set_scale_x(width / platform_sprite.get_width());
    selected_sprite.set_scale_x(width / selected_sprite.get_width());
    box.width = normal_sprite.get_width();
}

/** 
 * Not implemented.
 */
EditableFloor::~EditableFloor() {}

/** 
 * Manages player interecation with the box.  
 * 
 * @param delta Difference in position of the box.
 */
void EditableFloor::update(float delta) {
    InputManager *input_manager = InputManager::get_instance();

    if (input_manager->mouse_press(InputManager::LEFT_MOUSE_BUTTON)) {
        int x = input_manager->get_mouse_x();
        int y = input_manager->get_mouse_y();
        Rectangle mouse = Rectangle(x, y, 1, 1);
        selected = Collision::is_colliding(box, mouse, rotation, 0);
    }

    if (selected) {
        static float acceleration = 1;
        float value = 0.5 * delta * acceleration;
        bool moved = false;

        // Move floor
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

        if (box.x < 0) {
            box.x = 0;
        }
        if (box.x > 1280) {
            box.x = 1280;
        }
        if (box.y < 0) {
            box.y = 0;
        }
        if (box.y > 720) {
            box.y = 720;
        }

        // Rotate floor to left
        if (input_manager->is_key_down(InputManager::K_ROT_LEFT)) {
            rotation += 0.01 * value / acceleration;
        }

        // Rotate floor to right
        if (input_manager->is_key_down(InputManager::K_ROT_RIGHT)) {
            rotation -= 0.01 * value / acceleration;
        }

        // Reset rotation
        if (input_manager->is_key_down(InputManager::K_ROT_RESET)) {
            rotation = 0;
        }

        // Toggle floor
        if (input_manager->key_press(InputManager::K_C)) {
            is_platform = not is_platform;
        }

        // Increase floor width
        if (input_manager->is_key_down(InputManager::K_INC_W)) {
            normal_sprite.update_scale_x(0.005 * value);
            platform_sprite.update_scale_x(0.005 * value);
            selected_sprite.update_scale_x(0.005 * value);
            box.width = normal_sprite.get_width();
            moved = true;
        }

        // Decrease floor width
        if (input_manager->is_key_down(InputManager::K_DEC_W)) {
            normal_sprite.update_scale_x(-0.005 * value);
            platform_sprite.update_scale_x(-0.005 * value);
            selected_sprite.update_scale_x(-0.005 * value);
            box.width = normal_sprite.get_width();
            moved = true;
        }

        if (moved) {
            acceleration = fmin(acceleration + 0.2, 4);
        } else {
            acceleration = 1;
        }

        // Delete floor
        if (input_manager->is_key_down(InputManager::K_DEL)) {
            deleted = true;
        }
    }
}

/** 
 * Render selected box considering if it is selected.  
 */
void EditableFloor::render() {
    if (selected) {
        selected_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    }

    if (is_platform)
        platform_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    else
        normal_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
}

/** 
 * True if box has been deleted.  
 * 
 * @returns [0,1] 
 */
bool EditableFloor::is_dead() {
    return deleted;
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
 * @returns String in format: "x y width rotated level is_platform?"
 */
string EditableFloor::get_information() {
    char info[500];
    snprintf(info, sizeof(info), "%f %f %f %f %d", box.x, box.y, box.width,
             rotation * 180 / PI, static_cast<int>(is_platform));
    string s(info);
    for (auto &c : s) {
        c += 15;
    }

    return s;
}

/** 
 * Select elements which will be edited. 
 * 
 * @param cselected [0,1]
 */
void EditableFloor::set_selected(bool cselected) {
    selected = cselected;
}
