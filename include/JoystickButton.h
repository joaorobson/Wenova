/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file JoystickButton.h
 * This file contains the definitions of all methods and attributes of the class
 * JoystickButton which controls the behavior of the menu "Test mode".
 */
#ifndef INCLUDE_JOYSTICKBUTTON_H_
#define INCLUDE_JOYSTICKBUTTON_H_

#include "GameObject.h"
#include "Sprite.h"

#include <assert.h>
#include <string>

class JoystickButton : public GameObject {
 private:
    Sprite sprite;  /**< Image of a joystick button at menu "Test mode". */
    Sprite pressed_sprite;  /**< Image of a pressed joystick button at menu */
                            /**< "Test mode". */
    string label;  /**< String with the label of a joystick button. */
    int button_id;  /**< Int number with the id of a joystick button. */
    int joystick_id;  /**< Int number with the id of a joystick */
    bool pressed;  /**< Indicates id a button was pressed */

    // TODO text com label escrito

 public:
    JoystickButton(int x, int y, string clabel, int cbutton, int cjoystick_id,
                   string csprite);

    ~JoystickButton();

    void notify_collision(const GameObject& object);

 private:
    void update(float delta);
    void render();
    bool is_dead();
};

#endif  // INCLUDE_JOYSTICKBUTTON_H_
