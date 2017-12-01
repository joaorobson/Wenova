/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file OptionsState.cpp
 * This file builds all options and sub options of the menu 'Options' of
 * the game and control their behavior.
 */
#include "SDL_mixer.h"

#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "JoystickConfigState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "ResourcesOptionsState.h"

#define FONT_X 640
#define FONT_Y 680
#define OPTION_OFFSET 70
#define FONT_SIZE_OPTIONS 30
#define FONT_SIZE_LABEL_OPTIONS 50
#define UPPER_LIMIT_OPTIONS 4
#define LOWER_LIMIT_OPTIONS 0
#define DELTA_CURSOR_DOWN 1
#define DELTA_CURSOR_UP -1

#define WHITE \
    { 255, 255, 255, 255 }

#define N_JOYSTICK_BUTTON 15

#define HORIZONTAL_POSITION_SCREEN_RES 100
#define VERTICAL_POSITION_SCREEN_RES 200
#define NOT_CENTER_HORIZONTALLY false
#define NOT_CENTER_VERTICALLY false

#define FONT_FILE "font/8-BIT WONDER.ttf"
#define TEXT_800x600 "800 x 600"
#define TEXT_1024x768 "1024 x 768"
#define TEXT_1280x720 "1280 x 720"
#define TEXT_1366x768 "1366 x 768"
#define TEXT_1920x1080 "1920 x 1080"
#define TEXT_FULLSCREEN_OFF "OFF"
#define TEXT_FULLSCREEN_ON "ON"
#define TEXT_OPTIONS "OPTIONS"
#define SCREEN_RES_OPTION "SCREEN RESOLUTION"
#define FULLSCREEN_OPTION "FULLSCREEN"
#define JOYSTICK_OPTION "JOYSTICK"
#define KEYBOARD_OPTION "KEYBOARD"
#define BACK_OPTION "BACK"

/**
 * Constructor.
 * This constructor builds the options and sub options to initialize the
 * attributes.
 */
OptionsState::OptionsState() {
    Mix_AllocateChannels(50);

    for (int i = 0; i < N_JOYSTICK_BUTTON; i++) {
        pressed[i] = false;
    }
    current_option = 0;
    on_submenu = false;

    background = Sprite("menu/background.jpg");
    title = new Text(FONT_FILE, FONT_SIZE_LABEL_OPTIONS, Text::TextStyle::SOLID,
                     TEXT_OPTIONS, WHITE, FONT_X, 100);

    blocked = Sound("menu/sound/cancel.ogg");
    selected = Sound("menu/sound/select.ogg");
    changed = Sound("menu/sound/cursor.ogg");

    build_options();

    for (unsigned i = 0; i < options.size(); i++) {
        int id_option =
            ResourcesOptionsState::get_current_sub_option(i, sub_options);
        assert(id_option >= 0);

        current_sub_option.push_back(id_option);
    }

    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);
}

/**
 * Update function.
 * This function identifies the pressed button and updates the values of the
 * selected option.
 *
 * @param delta a float variation to update menu state.
 */
void OptionsState::update(float) {
    process_input();

    InputManager *input_manager = InputManager::get_instance();
    assert(input_manager != nullptr);

    // Inputs
    if (not input_manager->quit_requested()) {
        /* Nothing to do. */
    } else {
        m_quit_requested = true;
        return;
    }

    /**
     * Check if the pressed button was the cursor DOWN or UP.
     * When user press the button DOWN, the selected item goes to another one
     * below it if the current item is not the last, Otherwise it goes
     * to another one above it if the current item is not the last.
     */
    if (pressed[DOWN] or pressed[UP]) {
        changed.play();

        string text = options[current_option]->get_text();
        assert(text.empty() != true);
        int sub_options_size = static_cast<int>(sub_options[text].size() - 1);
        int delta_cursor_state =
            pressed[DOWN] ? DELTA_CURSOR_DOWN : DELTA_CURSOR_UP;
        int limit_options =
            pressed[DOWN] ? UPPER_LIMIT_OPTIONS : LOWER_LIMIT_OPTIONS;
        int limit_sub_options = pressed[DOWN] ? sub_options_size : 0;

        ResourcesOptionsState::action_cursor_button(
            on_submenu, &current_option, &current_sub_option,
            delta_cursor_state, limit_options, limit_sub_options);
    } else {
        /* Nothing to do. */
    }

    /**
     * Check if the pressed button was START (Keyboard) or A (Joystick) or
     * SELECT (Keyboard) or B (Joystick).
     * When user press one of these buttons and isn't on a submenu of the menu
     * "Options" he enters to the submenu selected (START and A) or return
     * to the main menu of its submenu (SELECT and B).
     */
    if (pressed[START] or pressed[A]) {
        selected.play();

        assert(current_option >= 0);
        assert(current_option <= static_cast<int>(options.size()) - 1);

        ResourcesOptionsState::action_selection_button(
            &on_submenu, current_option, &m_quit_requested, &current_sub_option,
            options, sub_options);
    } else if (pressed[SELECT] or pressed[B]) {
        // FIXME insert back sound
        selected.play();

        ResourcesOptionsState::action_return_button(
            &on_submenu, &m_quit_requested, &current_sub_option, options,
            sub_options);
    } else {
        /* Nothing to do. */
    }

    ResourcesOptionsState::set_position_options_text(options, sub_options);

    // Set back button position
    options.back()->set_pos(FONT_X, FONT_Y, true, true);
}

/**
 * Render function.
 * This function renders all text of the menu 'Options' and changes its color
 * according to the menu tha user selected.
 */
void OptionsState::render() {
    background.render(0, 0);

    title->render();

    /**
     * Iterates every option of the menu "Options" of a main menu.
     */
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
        ResourcesOptionsState::render_submenu_option(i, on_submenu,
                                                     current_option, &options);

        options[i]->render();
        string text = options[i]->get_text();
        ResourcesOptionsState::render_main_menu_option(
            i, on_submenu, current_option, text, current_sub_option,
            &sub_options);
    }
}

/**
 * Build options function.
 * This function builds the text of all options and sub options of the menu
 * 'Options' and update the attributes that represent these options.
 */
void OptionsState::build_options() {
    options.push_back(new Text(
        FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID, SCREEN_RES_OPTION,
        WHITE, HORIZONTAL_POSITION_SCREEN_RES, VERTICAL_POSITION_SCREEN_RES));
    options.back()->set_pos(HORIZONTAL_POSITION_SCREEN_RES,
                            VERTICAL_POSITION_SCREEN_RES,
                            NOT_CENTER_HORIZONTALLY, NOT_CENTER_VERTICALLY);
    options.push_back(new Text(FONT_FILE, FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID, FULLSCREEN_OPTION,
                               WHITE));
    options.push_back(new Text(FONT_FILE, FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID, JOYSTICK_OPTION, WHITE));
    options.push_back(new Text(FONT_FILE, FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID, KEYBOARD_OPTION, WHITE));
    options.push_back(new Text(FONT_FILE, FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID, BACK_OPTION, WHITE));

    sub_options[SCREEN_RES_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_800x600, WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_1024x768, WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_1280x720, WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_1366x768, WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_1920x1080, WHITE));

    sub_options[FULLSCREEN_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_FULLSCREEN_OFF, WHITE));
    sub_options[FULLSCREEN_OPTION].push_back(
        new Text(FONT_FILE, FONT_SIZE_OPTIONS, Text::TextStyle::SOLID,
                 TEXT_FULLSCREEN_ON, WHITE));
}

/**
 * Process an input of the user.
 * This function maps the buttons that are used on the menu 'Option' according
 * to constants of the InputManager class.
 */
void OptionsState::process_input() {
    InputManager *input_manager = InputManager::get_instance();
    assert(input_manager != nullptr);

    vector<pair<int, int> > joystick_buttons = {
        ii(A, InputManager::A),           ii(B, InputManager::B),
        ii(UP, InputManager::UP),         ii(DOWN, InputManager::DOWN),
        ii(SELECT, InputManager::SELECT), ii(START, InputManager::START)};

    /**
     * Iterate on every key of the vector "joystick_buttons" and call it's
     * manager input.
     */
    for (ii button : joystick_buttons) {
        pressed[button.first] =
            input_manager->joystick_button_press(button.second, 0);
    }
}

/**
 * Pause function.
 * Nothing to do.
 */
void OptionsState::pause() {
}

/**
 * Resume function.
 * Nothing to do.
 */
void OptionsState::resume() {
}
