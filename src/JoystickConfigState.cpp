/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file JoystickConfigState.cpp
 * This file renders images of options 'JOYSTICK' and 'KEYBOARD' of the menu
 * 'Options' and controls the behavior of the joystick test mode functionality.
 */
#include "SDL_mixer.h"

#include "JoystickConfigState.h"
#include "InputManager.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "JoystickButton.h"
#include "Game.h"

#define MIDDLE_X 250
#define BOTTOM_Y 275
#define A_X MIDDLE_X + 150
#define A_Y BOTTOM_Y
#define LB_X MIDDLE_X - 150
#define LB_Y BOTTOM_Y - 200
#define DOWN_X LB_X
#define DOWN_Y BOTTOM_Y - 15
#define SELECT_X MIDDLE_X - 40
#define SELECT_Y BOTTOM_Y - 100
#define OFFSET_X 700
#define OFFSET_Y 400
#define BUTTON_DISTANCE 50
#define DPAD_DISTANCE 35
#define TRIGGERS_X_DISTANCE 300
#define TRIGGERS_Y_DISTANCE 40
#define DISTANCE_START 40

#define WHITE { 255, 255, 255, 255 }
#define LIGHT_GREEN { 181, 201, 60, 1 }
#define BLUE { 0, 108, 166, 1 }

/**
 * Constructor.
 * This constructor builds sprites to render the option 'JOYSTICK' located on
 * the menu 'Options' of the game.
 *
 * @param joystick_id and integer argument that represents the id of one of the
 * four joysticks that can be pluged.
 * @param ckeyboard a boolean argument that indicates if a keyboard is
 * connected.
 */
JoystickConfigState::JoystickConfigState(int  joystick_id,
                                         bool ckeyboard) {
    Mix_AllocateChannels(50);

    is_keyboard = ckeyboard;

    background = Sprite("joysticks/help/background.png");
    keyboard = Sprite("joysticks/help/keyboard_help.png");
    joystick_help = Sprite("joysticks/help/controls_help.png");
    test_btn = Sprite("joysticks/help/a.png");
    back_btn = Sprite("joysticks/help/b.png");
    test_txt = new Text("font/8-BIT WONDER.ttf", 22, Text::TextStyle::SOLID,
                        "TEST", WHITE);

    back_txt = new Text("font/8-BIT WONDER.ttf", 22, Text::TextStyle::SOLID,
                        "BACK", WHITE);

    press = new Text("font/8-BIT WONDER.ttf", 22, Text::TextStyle::SOLID,
                     "PRESS", LIGHT_GREEN, 640, 300);

    select_text = new Text("font/8-BIT WONDER.ttf", 25, Text::TextStyle::SOLID,
                           "SELECT", BLUE, 500, 350);

    and_text = new Text("font/8-BIT WONDER.ttf", 22, Text::TextStyle::SOLID,
                        "AND", LIGHT_GREEN, 640, 350);

    start_text = new Text("font/8-BIT WONDER.ttf", 25, Text::TextStyle::SOLID,
                          "START", BLUE, 760, 350);

    to_go_back = new Text("font/8-BIT WONDER.ttf", 22, Text::TextStyle::SOLID,
                          "TO GO BACK", LIGHT_GREEN, 640, 400);

    test_txt->set_pos(970, 650);
    back_txt->set_pos(1154, 650);

    blocked = Sound("menu/sound/cancel.ogg");
    selected = Sound("menu/sound/select.ogg");
    changed = Sound("menu/sound/cursor.ogg");

    on_test = false;

    /**
     * Iterates four times to create the buttons of the test mode on menu
     * "Options".
     */
    for (int i = 0; i < 4; i++) {
        joystick_id = i;
        int offset_x = OFFSET_X * (i % 2) + 20;
        int offset_y = OFFSET_Y * (i > 1);
        add_object(new JoystickButton(offset_x + DOWN_X, offset_y + DOWN_Y - 2 *
                                      DPAD_DISTANCE, "UP", InputManager::UP,
                                      joystick_id, "up"));
        add_object(new JoystickButton(offset_x + DOWN_X + DPAD_DISTANCE,
                                      offset_y + DOWN_Y - DPAD_DISTANCE,
                                      "RIGHT",
                                      InputManager::RIGHT,
                                      joystick_id, "right"));
        add_object(new JoystickButton(offset_x + DOWN_X, offset_y + DOWN_Y,
                                      "DOWN", InputManager::DOWN, joystick_id,
                                      "down"));
        add_object(new JoystickButton(offset_x + DOWN_X - DPAD_DISTANCE,
                                      offset_y + DOWN_Y - DPAD_DISTANCE, "LEFT",
                                      InputManager::LEFT, joystick_id,
                                      "left"));

        // ABXY
        add_object(new JoystickButton(offset_x + A_X - BUTTON_DISTANCE,
                                      offset_y + A_Y - BUTTON_DISTANCE, "X",
                                      InputManager::X, joystick_id,
                                      "button"));
        add_object(new JoystickButton(offset_x + A_X, offset_y + A_Y, "A",
                                      InputManager::A, joystick_id, "button"));
        add_object(new JoystickButton(offset_x + A_X + BUTTON_DISTANCE,
                                      offset_y + A_Y - BUTTON_DISTANCE, "B",
                                      InputManager::B, joystick_id,
                                      "button"));
        add_object(new JoystickButton(offset_x + A_X, offset_y + A_Y - 2 *
                                      BUTTON_DISTANCE, "Y", InputManager::Y,
                                      joystick_id, "button"));

        // Triggers
        add_object(new JoystickButton(offset_x + LB_X, offset_y + LB_Y, "LB",
                                      InputManager::LB, joystick_id,
                                      "trigger"));
        add_object(new JoystickButton(offset_x + LB_X + TRIGGERS_X_DISTANCE,
                                      offset_y + LB_Y, "RB", InputManager::RB,
                                      joystick_id, "trigger"));
        add_object(new JoystickButton(offset_x + LB_X, offset_y + LB_Y -
                                      TRIGGERS_Y_DISTANCE, "LT",
                                      InputManager::LT,
                                      joystick_id, "back_trigger"));
        add_object(new JoystickButton(offset_x + LB_X + TRIGGERS_X_DISTANCE,
                                      offset_y + LB_Y - TRIGGERS_Y_DISTANCE,
                                      "RT",
                                      InputManager::RT, joystick_id,
                                      "back_trigger"));

        // Select and start
        add_object(new JoystickButton(offset_x + SELECT_X, offset_y + SELECT_Y,
                                      "select", InputManager::SELECT,
                                      joystick_id,
                                      "select_start"));
        add_object(new JoystickButton(offset_x + MIDDLE_X + DISTANCE_START,
                                      offset_y + SELECT_Y, "start",
                                      InputManager::START, joystick_id,
                                      "select_start"));
    }

    InputManager::get_instance()->set_analogic_value(20000);
    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);
}

/**
 * Function that updates sprites on joystick test mode.
 * This function makes sprites change color accoding to the button pressed by
 * the user on the joystick test mode located at the menu
 * "Options->Joystick->Test".
 *
 * @param delta a float variation to update joystick state.
 */
void JoystickConfigState::update(float delta) {
    InputManager *input_manager = InputManager::get_instance();

    /**
     * Check if user has request to quit the menu "Options".
     */
    if (input_manager->quit_requested()) {
        m_quit_requested = true;
        return;
    }

    /**
     * Check if user request to enter in joystick test mode.
     */
    if (on_test) {
        /**
         * Check if user request to quit the joystick test screen.
         */
        if (input_manager->is_joystick_button_down(InputManager::SELECT, 0) and
            input_manager->is_joystick_button_down(InputManager::START, 0)
            ) {
            selected.play();
            on_test = false;
            InputManager::get_instance()->map_keyboard_to_joystick(
                InputManager::MENU_MODE);
        }

        /**
         * Workaround to uncheck A button pressed in joystick test screen.
         */
        if (input_manager->joystick_button_release(InputManager::A, 0)) {
            InputManager::get_instance()->map_keyboard_to_joystick(
                InputManager::BATTLE_MODE);
        }
    } else {
        /**
         * Check if user request to quit the joystick help screen.
         */
        if (input_manager->joystick_button_press(InputManager::SELECT, 0) or
            input_manager->joystick_button_press(InputManager::B, 0)) {
            selected.play();
            m_quit_requested = true;
            Game::get_instance().push(new OptionsState());
            return;
        }

        /**
         * Check if user request to enter the joystick test mode.
         */
        if (input_manager->joystick_button_press(InputManager::A, 0) and
            not is_keyboard
            ) {
            selected.play();
            on_test = true;
        }
    }

    update_array(delta);
}

/**
 * Function that renders keyboard or joystick help images.
 * This function renders keyboard or joystick help images if user select one of
 * the options: 'keyboard' and 'joystick'; located at the menu 'Options'.
 * Besides that, it will render buttons on the joystick test mode.
 */
void JoystickConfigState::render() {
    /**
     * Check if user selected to enter on joystick test mode.
     * If not, render the joystick or keyboard help image. Otherwise, render
     * the test screen mode.
     */
    if (not on_test) {
        if (!is_keyboard) {
            joystick_help.render(0, 0);
            test_btn.render(914, 642);
            test_txt->render();
        } else {
            keyboard.render(0, 0);
        }

        back_btn.render(1094, 642);

        back_txt->render();
    } else {
        background.render(0, 0);
        render_array();
        press->render();
        select_text->render();
        and_text->render();
        start_text->render();
        to_go_back->render();
    }
}

/**
 * Pause function.
 * Nothing to do.
 */
void JoystickConfigState::pause() {}

/**
 * Resume function.
 * Nothing to do.
 */
void JoystickConfigState::resume() {}
