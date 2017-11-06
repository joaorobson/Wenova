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

#include "OptionsState.h"
#include "MenuState.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"
#include "JoystickConfigState.h"

#define FONT_X 640
#define FONT_Y 680
#define TEXT_OFFSET 8
#define TEXT_HEIGHT 30
#define OPTION_OFFSET 70
#define FONT_SIZE_OPTIONS 30
#define FONT_SIZE_LABEL_OPTIONS 50

#define DARK_GREY { 80, 80, 80, 1 }
#define DARK_GREEN { 55, 74, 38, 1 }
#define LIGHT_GREEN { 181, 201, 60, 1 }
#define WHITE { 255, 255, 255, 255 }

#define RESOLUTION_1_WIDTH 800
#define RESOLUTION_1_HEIGHT 600

#define RESOLUTION_2_WIDTH 1024
#define RESOLUTION_2_HEIGHT 768

#define RESOLUTION_3_WIDTH 1280
#define RESOLUTION_3_HEIGHT 720

#define RESOLUTION_4_WIDTH 1366
#define RESOLUTION_4_HEIGHT 768

#define RESOLUTION_5_WIDTH 1920
#define RESOLUTION_5_HEIGHT 1080

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

    current_option = 0;
    on_submenu = false;

    background = Sprite("menu/background.jpg");
    title = new Text(FONT_FILE,
                     FONT_SIZE_LABEL_OPTIONS,
                     Text::TextStyle::SOLID,
                     TEXT_OPTIONS,
                     WHITE,
                     FONT_X,
                     100);

    blocked = Sound("menu/sound/cancel.ogg");
    selected = Sound("menu/sound/select.ogg");
    changed = Sound("menu/sound/cursor.ogg");

    build_options();

    for (unsigned i = 0; i < options.size(); i++) {
        assert(get_current_sub_option(i) >= 0);

        current_sub_option.push_back(get_current_sub_option(i));
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
     * Check if the pressed button was the cursor DOWN.
     * When user press that button, the selected item goes to another one below
     * it if the current item is not the last.
     */
    if (pressed[DOWN]) {
        changed.play();

        if (not on_submenu) {
            assert(current_option <= static_cast<int>(options.size() - 1));

            if (current_option != static_cast<int>(options.size()) - 1) {
                current_option++;
            } else {
                /* Nothing to do. */
            }
        } else {
            string text = options[current_option]->get_text();
            assert(text.empty() != true);

            assert(current_sub_option[current_option] <=
                   static_cast<int>(sub_options[text].size()) - 1);

            if (current_sub_option[current_option] !=
                static_cast<int>(sub_options[text].size()) - 1) {
                current_sub_option[current_option]++;
            } else {
                /* Nothing to do. */
            }
        }
    } else {
        /* Nothing to do. */
    }

    /**
     * Check if the pressed button was START (Keyboard) or A (Joystick).
     * When user press one of these buttons and isn't on a submenu of the menu
     * "Options" he enters to the submenu selected.
     */
    if (pressed[START] or pressed[A]) {
        selected.play();

        assert(current_option >= 0);
        assert(current_option <= static_cast<int>(options.size()) - 1);

        if (not on_submenu) {
            if (current_option ==
                static_cast<int>(options.size()) - 1) {  // Back button
                m_quit_requested = true;
                Game::get_instance().push(new MenuState(true));
                return;
            } else if (current_option == 2) {  // Joysticks test
                m_quit_requested = true;
                Game::get_instance().push(new JoystickConfigState(0));
                return;
            } else if (current_option == 3) {  // Keyboard controls
                m_quit_requested = true;
                Game::get_instance().push(new JoystickConfigState(0, true));
                return;
            } else {
                on_submenu = true;
                current_sub_option[current_option] = get_current_sub_option(
                    current_option);
            }
        } else {
            /**
             * Check if user selected the option to change the screen
             * resolution. Otherwise, the user selected the option to selected
             * fullscreen enable.
             */
            if (current_option == 0) {
                vector<pair<int, int> > resolutions = {
                    ii(RESOLUTION_1_WIDTH, RESOLUTION_1_HEIGHT),
                    ii(RESOLUTION_2_WIDTH, RESOLUTION_2_HEIGHT),
                    ii(RESOLUTION_3_WIDTH, RESOLUTION_3_HEIGHT),
                    ii(RESOLUTION_4_WIDTH, RESOLUTION_4_HEIGHT),
                    ii(RESOLUTION_5_WIDTH, RESOLUTION_5_HEIGHT)
                };

                int id_resolution = current_sub_option[current_option];
                int new_width = resolutions[id_resolution].first;
                int new_height = resolutions[id_resolution].second;

                Game::get_instance().change_resolution(new_width, new_height);
            } else if (current_option == 1) {
                bool fullscreen =
                    (current_sub_option[current_option] == 0 ? false : true);
                Game::get_instance().set_fullscreen(fullscreen);
            } else {
                /* Nothing to do. */
            }
        }
    } else {
        /* Nothing to do. */
    }

    /**
     * Check if the pressed button was SELECT (Keyboard) or B (Joystick).
     * When user press one of these buttons and is on a submenu of the menu
     * "Options" he return to the main menu of it's submenu.
     */
    if (pressed[SELECT] or pressed[B]) {
        if (on_submenu) {
            // FIXME insert back sound
            selected.play();
            on_submenu = false;

            for (unsigned i = 0; i < options.size(); i++) {
                assert(get_current_sub_option(i) >= 0);

                current_sub_option[i] = get_current_sub_option(i);
            }
        } else {
            selected.play();
            m_quit_requested = true;
            Game::get_instance().push(new MenuState(true));
            return;
        }
    } else {
        /* Nothing to do. */
    }

    /**
     * Check if the pressed button was the cursor UP.
     * When user press that button, the selected item goes to another one above
     * it if the current item is not the first.
     */
    if (pressed[UP]) {
        changed.play();

        if (not on_submenu) {
            assert(current_option >= 0);
            if (current_option != 0) {
                current_option--;
            } else {
                /* Nothing to do. */
            }
        } else {
            assert(current_sub_option[current_option] >= 0);
            if (current_sub_option[current_option] != 0) {
                current_sub_option[current_option]--;
            } else {
                /* Nothing to do. */
            }
        }
    } else {
        /* Nothing to do. */
    }

    /**
     * Iterates all options of the menu "Options" and set the positions of texts
     * on the menu "Options".
     */
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
        Text *cur_text = options[i];

        int prev_text_size = 1;

        if (i) {
            prev_text_size = std::max(static_cast<int>
                                         (sub_options[options[i - 1]->
                                         get_text()].size()), 1);
        } else {
            /* Nothing to do. */
        }
        int prev_text_height = (TEXT_HEIGHT + TEXT_OFFSET * 2) * prev_text_size;

        int text_position_axi_x = 250;
        int text_position_axi_y = (i ? options[i - 1]->get_y() +
                                       prev_text_height : 200);

        cur_text->set_pos(text_position_axi_x,
                          text_position_axi_y,
                          NOT_CENTER_HORIZONTALLY,
                          NOT_CENTER_VERTICALLY);

        for (int j = 0;
             j < static_cast<int>(sub_options[cur_text->get_text()].size());
             j++) {
            text_position_axi_x = 800;

            if (j) {
                Text *prev_option = sub_options[cur_text->get_text()][j - 1];
                text_position_axi_y = prev_option->get_y() +
                                      prev_option->get_height() +
                                      TEXT_OFFSET;
            } else {
                /* Nothing to do. */
            }

            Text *option = sub_options[cur_text->get_text()][j];
            option->set_pos(text_position_axi_x, text_position_axi_y);
        }
    }

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
        render_submenu_option(i);

        options[i]->render();
        string text = options[i]->get_text();
        render_main_menu_option(i, text);
    }
}

/**
 *
 */
void OptionsState::render_submenu_option(int index) {
  /**
   * Check if selected option indicates that user is on a submenu.
   * Set color of current selected option to DARK_GREY.
   */
  if (on_submenu and (index != static_cast<int>(options.size()) - 1) and
      (index != current_option)) {
      options[index]->set_color(DARK_GREY);
  } else {
      /**
       * Check which option of a main was selected.
       * Set it's text color to LIGHT_GREEN.
       */
      if (current_option == index) {
          options[index]->set_color(LIGHT_GREEN);
      } else {
          options[index]->set_color(WHITE);
      }
  }
}

/**
 *
 */
void OptionsState::render_main_menu_option(int index, string text_option) {
    /**
     * Iterates every option of the menu "Options" of a submenu.
     */
    for (int j = 0; j < static_cast<int>(sub_options[text_option].size());
         j++) {
        /**
         * Check if selected option indicates that user is on a submenu.
         */
        if (on_submenu and(current_option == index)) {
            /**
             * Check which option of the submenu was selected.
             * Set it's text color to LIGHT_GREEN.
             */
            if (current_sub_option[index] == j) {
                sub_options[text_option][j]->set_color(LIGHT_GREEN);
            } else {
                sub_options[text_option][j]->set_color(WHITE);
            }
        } else {
            /**
             * Check which option of the submenu was selected.
             * Set it's text color to DARK_GREEN.
             */
            if (current_sub_option[index] == j) {
                sub_options[text_option][j]->set_color(DARK_GREEN);
            } else {
                sub_options[text_option][j]->set_color(DARK_GREY);
            }
        }

        sub_options[text_option][j]->render();
    }
}

/**
 * Build options function.
 * This function builds the text of all options and sub options of the menu
 * 'Options' and update the attributes that represent these options.
 */
void OptionsState::build_options() {
    options.push_back(new Text(FONT_FILE,
                               FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID,
                               SCREEN_RES_OPTION,
                               WHITE,
                               HORIZONTAL_POSITION_SCREEN_RES,
                               VERTICAL_POSITION_SCREEN_RES));
    options.back()->set_pos(HORIZONTAL_POSITION_SCREEN_RES,
                            VERTICAL_POSITION_SCREEN_RES,
                            NOT_CENTER_HORIZONTALLY,
                            NOT_CENTER_VERTICALLY);
    options.push_back(new Text(FONT_FILE,
                               FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID,
                               FULLSCREEN_OPTION,
                               WHITE));
    options.push_back(new Text(FONT_FILE,
                               FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID,
                               JOYSTICK_OPTION,
                               WHITE));
    options.push_back(new Text(FONT_FILE,
                               FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID,
                               KEYBOARD_OPTION,
                               WHITE));
    options.push_back(new Text(FONT_FILE,
                               FONT_SIZE_OPTIONS,
                               Text::TextStyle::SOLID,
                               BACK_OPTION,
                               WHITE));

    sub_options[SCREEN_RES_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_800x600,
                                                      WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_1024x768,
                                                      WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_1280x720,
                                                      WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_1366x768,
                                                      WHITE));
    sub_options[SCREEN_RES_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_1920x1080,
                                                      WHITE));

    sub_options[FULLSCREEN_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_FULLSCREEN_OFF,
                                                      WHITE));
    sub_options[FULLSCREEN_OPTION].push_back(new Text(FONT_FILE,
                                                      FONT_SIZE_OPTIONS,
                                                      Text::TextStyle::SOLID,
                                                      TEXT_FULLSCREEN_ON,
                                                      WHITE));
}

/**
 * Get the option on a sub menu.
 * This function identifies which sub menu and option the user selected.
 *
 * @param option an integer argument that represents the selected option of the
 * main menu.
 *
 * @return an integer value that represents the current sub option of a sub
 * menu.
 */
int OptionsState::get_current_sub_option(int option) {
    assert(option >= 0);
    /**
     * Check if the selected option was screen resolution.
     * If so, it generates the screen resolution option at the submenu
     * "SCREEN RESOLUTION". Otherwise, it indicates tha selecte is at fullscreen
     * option.
     */
    if (option == 0) {
        int width = Config::get_width();
        assert(width >= RESOLUTION_1_WIDTH);
        assert(width <= RESOLUTION_5_WIDTH);

        int height = Config::get_height();
        assert(height >= RESOLUTION_1_HEIGHT);
        assert(height <= RESOLUTION_5_HEIGHT);

        string resolution = std::to_string(width) + " x " +
                            std::to_string(height);
        int sub_option = 0;

        for (auto text : sub_options[SCREEN_RES_OPTION]) {
            if (text->get_text() == resolution) {
                return sub_option;
            } else {
                sub_option++;
            }
        }
        return 0;
    } else {  // Fullscreen
        return Config::is_fullscreen();
    }
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
                    ii(A, InputManager::A),
                    ii(B, InputManager::B),
                    ii(UP, InputManager::UP),
                    ii(DOWN, InputManager::DOWN),
                    ii(SELECT, InputManager::SELECT),
                    ii(START, InputManager::START)
    };

    /**
     * Iterate on every key of the vector "joystick_buttons" and call it's
     * manager input.
     */
    for (ii button : joystick_buttons) {
        pressed[button.first] = input_manager->joystick_button_press(
            button.second,
            0);
    }
}

/**
 * Pause function.
 * Nothing to do.
 */
void OptionsState::pause() {}

/**
 * Resume function.
 * Nothing to do.
 */
void OptionsState::resume() {}
