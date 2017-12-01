/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file MenuState.cpp
 * This file contains the definition of the MenuState.h class methods.
 */
#include "SDL_mixer.h"

#include "BattleState.h"
#include "EditState.h"
#include "Game.h"
#include "InputManager.h"
#include "JoystickConfigState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "Resources.h"
#include "StageSelectState.h"

#define OPTION_OFFSET 50 /**< Unity in pixel*/

#define FONT_X 640 /**< Unity in pixel*/
#define FONT_Y 680 /**< Unity in pixel*/

#define LIGHT_GREEN \
    { 181, 201, 60, 1 } /**< Unity in integer*/
#define WHITE \
    { 255, 255, 255, 255 } /**< Unity in integer*/

#define FRAME_TIME 7.5 /**< Unity in seconds*/
#define TEXT_TIMER_COOLDOWN 50 /**< Unity in seconds*/

#define N_ZERO 0 /**< Unity in integer*/
#define N_ONE 1 /**< Unity in integer*/
#define N_TWO 2 /**< Unity in integer*/

#define N_PLANET_RENDER_1 423 /**< Unity in pixel*/
#define N_PLANET_RENDER_2 177 /**< Unity in pixel*/
#define N_GREENSHIP_RENDER_1 805 /**< Unity in pixel*/
#define N_GREENSHIP_RENDER_2 405 /**< Unity in pixel*/
#define N_REDSHIP_RENDER_1 36 /**< Unity in pixel*/
#define N_REDSHIP_RENDER_2 400 /**< Unity in pixel*/
#define N_TITLE_RENDER 260 /**< Unity in pixel*/

#define N_CHANNELS 50 /**< Unity in pixel*/
#define FONT_SIZE 30 /**< Unity in pixel*/
#define SENSIBILITY_VALUE 32000 /**< Unity in pixel*/

#define BACKGROUNDSPRITE "menu/background.jpg" /**< string*/
#define TITLESPRITE "menu/title.png" /**< string*/
#define PLANETSPRITE "menu/planet.png" /**< string*/
#define GREENSHIPSPRITE "menu/green_ship.png" /**< string*/
#define REDSHIPSPRITE "menu/red_ship.png" /**< string*/
#define CANCELSOUND "menu/sound/cancel.ogg" /**< string*/
#define SELECTSOUND "menu/sound/select.ogg" /**< string*/
#define CURSORSOUND "menu/sound/cursor.ogg" /**< string*/
#define MENUMUSIC "menu/wenova.ogg" /**< string*/

#define FONT "font/8-BIT WONDER.ttf"

/**
 * The constructor.
 * Initialize the game menu.
 *
 * @param main_menu is a boolean type that send true or false to the method.
 */
MenuState::MenuState(bool main_menu) {
    Mix_AllocateChannels(N_CHANNELS);

    current_option = N_ZERO;
    start_pressed = main_menu;
    show_text = true;

    backgroundSetUp();
    optionSelection();
    InputManager::get_instance()->set_analogic_sensibility_value(
        SENSIBILITY_VALUE);
    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);

    blocked = Sound(CANCELSOUND);
    selected = Sound(SELECTSOUND);
    changed = Sound(CURSORSOUND);
    music = Music(MENUMUSIC);
    /**
     * Plays music if it is not playing.
     */
    if (!Mix_PlayingMusic()) {
        music.play();
    } else {
        /*Nothing to do*/
    }
}
MenuState::~MenuState() {
}
/**
 *function backgroundSetUp
 *sets up the elements in the background on the menu
 */
void MenuState::backgroundSetUp() {
    background = Sprite(BACKGROUNDSPRITE);
    title = Sprite(TITLESPRITE, 5, FRAME_TIME);
    planet = Sprite(PLANETSPRITE, 8, FRAME_TIME);
    green_ship = Sprite(GREENSHIPSPRITE, 8, FRAME_TIME, N_ZERO, 2);
    red_ship = Sprite(REDSHIPSPRITE, 8, FRAME_TIME);
}
/**
 *function optionSelection
 *defines the style of the options the player has to chose from.
 */
void MenuState::optionSelection() {
    start_option = new Text(FONT, FONT_SIZE, Text::TextStyle::SOLID,
                            "PRESS START", LIGHT_GREEN, FONT_X, FONT_Y);

    options.push_back(new Text(FONT, FONT_SIZE, Text::TextStyle::SOLID, "START",
                               WHITE, FONT_X, FONT_Y));
    options.push_back(new Text(FONT, FONT_SIZE, Text::TextStyle::SOLID, "EDIT",
                               WHITE, FONT_X, FONT_Y));
    options.push_back(new Text(FONT, FONT_SIZE, Text::TextStyle::SOLID,
                               "OPTIONS", WHITE, FONT_X, FONT_Y));
    options.push_back(new Text(FONT, FONT_SIZE, Text::TextStyle::SOLID, "EXIT",
                               WHITE, FONT_X, FONT_Y));
}
/**
 * update method.
 * this method changes the state of the menu.
 * changes the state as the user navigates through the menu.
 *
 * @param cid is a number of the type integer.
 */
void MenuState::update(float delta) {
    assert(delta >= 0);

    title.update(delta);
    planet.update(delta);
    green_ship.update(delta);
    red_ship.update(delta);

    process_input();

    InputManager *input_manager = InputManager::get_instance();

    /**
     * If conditions are met, the body is executed.
     * The music stops playing and leaves the edit state.
     */
    if (input_manager->quit_requested() or pressed[SELECT] or pressed[B]) {
        music.stop();
        m_quit_requested = true;
        return;
    } else {
        /*Nothing to do*/
    }

    /**
     * Select options in the menu.
     */
    if (pressed[LEFT] and (current_option != N_ZERO)) {
        changed.play();
        current_option--;
    } else {
        /*Nothing to do*/
    }

    /**
     * Select options in the menu.
     */
    if (pressed[RIGHT] and
        (current_option != static_cast<int>(options.size()) - 1)) {
        changed.play();
        current_option++;
    } else {
        /*Nothing to do*/
    }

    /**
     * Select options in the menu.
     */
    if (is_holding[LB] and is_holding[RT] and is_holding[Y]) {
        m_quit_requested = true;
        Game::get_instance().push(new EditState("2"));
        return;
    } else {
        /*Nothing to do*/
    }

    /**
     * Starts the game when selected.
     */
    if (pressed[START] or pressed[A]) {
        selected.play();

        if (not start_pressed) {
            assert(start_pressed == 0);

            start_pressed = true;
            current_option = N_ZERO;

            assert(current_option == 0);
        } else {
            m_quit_requested = true;

            /**
             * Opens selected option depending on selected index.
             */
            if (current_option == N_ZERO) {
                Game::get_instance().push(new StageSelectState());
            } else if (current_option == N_ONE) {
                Game::get_instance().push(new StageSelectState(true));
            } else if (current_option == N_TWO) {
                Game::get_instance().push(new OptionsState());
            } else {
                /*Nothing to do*/
            }

            return;
        }
    }

    /**
     * Sets new configuration.
     */
    if (is_holding[LB] and is_holding[RT] and is_holding[Y]) {
        m_quit_requested = true;
        Game::get_instance().push(new EditState("1"));
        return;
    } else {
        /*Nothing to do*/
    }

    /**
     * Selects a option.
     */
    if (start_pressed) {
        options[current_option]->set_pos(FONT_X, FONT_Y, true, true);
        options[current_option]->set_color(LIGHT_GREEN);

        /**
         * Modify the options positioning.
         */
        for (int idx = N_ZERO; idx < current_option; idx++) {
            Text *next_option = options[idx + 1];

            int new_x = next_option->get_x() - options[idx]->get_width() -
                OPTION_OFFSET;
            options[idx]->set_pos(new_x, FONT_Y, false, true);
            options[idx]->set_color(WHITE);
        }

        /**
         * Modify the options positioning after current option select.
         */
        for (unsigned int idx = current_option + 1; idx < options.size();
             idx++) {
            Text *prev_option = options[idx - 1];

            int new_x =
                prev_option->get_x() + prev_option->get_width() + OPTION_OFFSET;
            options[idx]->set_pos(new_x, FONT_Y, false, true);
            options[idx]->set_color(WHITE);
        }
    } else {
        /*Nothing to do*/
    }

    /**
     * Cycles through the options.
     */
    if (text_timer.get() > TEXT_TIMER_COOLDOWN) {
        show_text = !show_text;
        text_timer.restart();
    } else {
        /*Nothing to do*/
    }

    text_timer.update(delta);
}
/**
 * render method.
 * this method renders the menu of the game on the screen.
 */
void MenuState::render() {
    background.render(N_ZERO, N_ZERO);

    planet.render(N_PLANET_RENDER_1, N_PLANET_RENDER_2);
    green_ship.render(N_GREENSHIP_RENDER_1, N_GREENSHIP_RENDER_2);
    red_ship.render(N_REDSHIP_RENDER_1, N_REDSHIP_RENDER_2);
    title.render(N_TITLE_RENDER, N_ZERO);

    /**
     * Renders all the options on screen.
     */
    if (start_pressed) {
        for (auto option_text : options) {
            option_text->render(N_ZERO, N_ZERO);
        }
    } else if (show_text) {
        start_option->render(N_ZERO, N_ZERO);
    } else {
        /*Nothing to do*/
    }
}
/**
 * process_input method.
 * this method recognizes the user input button and acts accordingly.
 */
void MenuState::process_input() {
    InputManager *input_manager = InputManager::get_instance();

    // Menu buttons
    vector<pair<int, int> > joystick_buttons = {
        ii(A, InputManager::A),         ii(B, InputManager::B),
        ii(Y, InputManager::Y),         ii(LEFT, InputManager::LEFT),
        ii(RIGHT, InputManager::RIGHT), ii(SELECT, InputManager::SELECT),
        ii(START, InputManager::START), ii(LB, InputManager::LB),
        ii(RT, InputManager::RT)};

    /**
     * Checks the state of the button the user pressed.
     */
    for (ii button : joystick_buttons) {
        pressed[button.first] =
            input_manager->joystick_button_press(button.second, N_ZERO);
        is_holding[button.first] =
            input_manager->is_joystick_button_down(button.second, N_ZERO);
    }
}

/**
 * pause method.
 * not implemented.
 */
void MenuState::pause() {
}

/**
 * resume method.
 * not implemented.
 */
void MenuState::resume() {
}
