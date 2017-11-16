/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file JoystickButton.cpp
 * Brief Description.
 */

#include "JoystickButton.h"

#include "InputManager.h"

JoystickButton::JoystickButton(int x, int y, string clabel, int cbutton_id,
                               int cjoystick_id, string csprite)
        : sprite(Sprite("joysticks/" + csprite + ".png"))
        , pressed_sprite(Sprite("joysticks/pressed_" + csprite + ".png"))
        , label(clabel)
        , button_id(cbutton_id)
        , joystick_id(cjoystick_id)
        , pressed(false) {
    assert(clabel.empty() != true);
    assert(csprite.empty() != true);

    assert(sprite.get_width() > 0);
    assert(sprite.get_height() > 0);
    box = Rectangle(x, y, sprite.get_width(), sprite.get_height());

    rotation = 0;
}

/**
 * Brief Description.
 */
JoystickButton::~JoystickButton() {
}

/**
 * Brief Description.
 *
 * @param float
 */
void JoystickButton::update(float) {
    InputManager *input_manager = InputManager::get_instance();
    assert(input_manager != nullptr);

    pressed = input_manager->is_joystick_button_down(button_id, joystick_id);
}

/**
 * Brief Description.
 */
void JoystickButton::render() {
    assert(box.get_draw_x() > 0.0);
    assert(box.get_draw_y() > 0.0);
    sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);

    if (pressed) {
        pressed_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    } else {
        /* Nothing to do. */
    }
}

/**
 * Brief Description.
 *
 * @returns
 */
bool JoystickButton::is_dead() {
    return false;
}

/**
 * Brief Description.
 *
 * @param
 */
void JoystickButton::notify_collision(const GameObject &) {
}
