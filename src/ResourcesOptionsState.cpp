/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file ResourcesOptionsState.h
 * This file contains the definitions of all methods and attributes of the class
 * ResourcesOptionsState used in the class OptionsState.
 */

#include "ResourcesOptionsState.h"
#include "Config.h"
#include "Game.h"
#include "JoystickConfigState.h"
#include "MenuState.h"
#include "OptionsState.h"

#include <vector>

#define ii std::pair<int, int>

#define TEXT_HEIGHT 30
#define TEXT_OFFSET 8
#define NOT_CENTER_HORIZONTALLY false
#define NOT_CENTER_VERTICALLY false

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

#define SCREEN_RES_OPTION "SCREEN RESOLUTION"

#define DARK_GREY \
    { 80, 80, 80, 1 }
#define DARK_GREEN \
    { 55, 74, 38, 1 }
#define LIGHT_GREEN \
    { 181, 201, 60, 1 }
#define WHITE \
    { 255, 255, 255, 255 }

void ResourcesOptionsState::action_cursor_button(
    bool on_submenu, int *current_option, std::vector<int> *current_sub_option,
    int delta_cursor_state, int limit_options, int limit_sub_options) {
    if (not on_submenu) {
        assert(*current_option >= 0);
        if (*current_option != limit_options) {
            (*current_option) += delta_cursor_state;
        } else {
            /* Nothing to do. */
        }
    } else {
        assert((*current_sub_option)[*current_option] >= 0);
        if ((*current_sub_option)[*current_option] != limit_sub_options) {
            (*current_sub_option)[*current_option] += delta_cursor_state;
        } else {
            /* Nothing to do. */
        }
    }
}

void ResourcesOptionsState::action_selection_button(
    bool *on_submenu, int current_option, bool *m_quit_requested,
    std::vector<int> *current_sub_option, std::vector<Text *> options,
    std::map<string, std::vector<Text *> > sub_options) {
    if (not*on_submenu) {
        if (current_option ==
            static_cast<int>(options.size()) - 1) {  // Back button
            (*m_quit_requested) = true;
            Game::get_instance().push(new MenuState(true));
            return;
        } else if (current_option == 2) {  // Joysticks test
            (*m_quit_requested) = true;
            Game::get_instance().push(new JoystickConfigState(0));
            return;
        } else if (current_option == 3) {  // Keyboard controls
            (*m_quit_requested) = true;
            Game::get_instance().push(new JoystickConfigState(0, true));
            return;
        } else {
            (*on_submenu) = true;
            (*current_sub_option)[current_option] =
                get_current_sub_option(current_option, sub_options);
        }
    } else {
        /**
         * Check if user selected the option to change the screen
         * resolution. Otherwise, the user selected the option to selected
         * fullscreen enable.
         */
        if (current_option == 0) {
            std::vector<std::pair<int, int> > resolutions = {
                ii(RESOLUTION_1_WIDTH, RESOLUTION_1_HEIGHT),
                ii(RESOLUTION_2_WIDTH, RESOLUTION_2_HEIGHT),
                ii(RESOLUTION_3_WIDTH, RESOLUTION_3_HEIGHT),
                ii(RESOLUTION_4_WIDTH, RESOLUTION_4_HEIGHT),
                ii(RESOLUTION_5_WIDTH, RESOLUTION_5_HEIGHT)};

            int id_resolution = (*current_sub_option)[current_option];
            int new_width = resolutions[id_resolution].first;
            int new_height = resolutions[id_resolution].second;

            Game::get_instance().change_resolution(new_width, new_height);
        } else if (current_option == 1) {
            bool fullscreen =
                ((*current_sub_option)[current_option] == 0 ? false : true);
            Game::get_instance().set_fullscreen(fullscreen);
        } else {
            /* Nothing to do. */
        }
    }
}

void ResourcesOptionsState::action_return_button(
    bool *on_submenu, bool *m_quit_requested,
    std::vector<int> *current_sub_option, std::vector<Text *> options,
    std::map<string, std::vector<Text *> > sub_options) {
    if (*on_submenu) {
        (*on_submenu) = false;

        for (unsigned i = 0; i < options.size(); i++) {
            int id_option = get_current_sub_option(i, sub_options);
            assert(id_option >= 0);

            (*current_sub_option)[i] = id_option;
        }
    } else {
        (*m_quit_requested) = true;
        Game::get_instance().push(new MenuState(true));
        return;
    }
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
int ResourcesOptionsState::get_current_sub_option(
    int option, std::map<string, std::vector<Text *> > sub_options) {
    assert(option >= 0);
    /**
     * Check if the selected option was screen resolution.
     * If so, it generates the screen resolution option at the submenu
     * "SCREEN RESOLUTION". Otherwise, it indicates that selecte is at
     * fullscreen
     * option.
     */
    if (option == 0) {
        int width = Config::get_width();
        assert(width >= RESOLUTION_1_WIDTH);
        assert(width <= RESOLUTION_5_WIDTH);

        int height = Config::get_height();
        assert(height >= RESOLUTION_1_HEIGHT);
        assert(height <= RESOLUTION_5_HEIGHT);

        string resolution =
            std::to_string(width) + " x " + std::to_string(height);
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

void ResourcesOptionsState::set_position_options_text(
    std::vector<Text *> options,
    std::map<string, std::vector<Text *> > sub_options) {
    /**
     * Iterates all options of the menu "Options" and set the positions of texts
     * on the menu "Options".
     */
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
        Text *cur_text = options[i];

        int prev_text_size = 1;

        if (i) {
            prev_text_size =
                std::max(static_cast<int>(
                             sub_options[options[i - 1]->get_text()].size()),
                         1);
        } else {
            /* Nothing to do. */
        }
        int prev_text_height = (TEXT_HEIGHT + TEXT_OFFSET * 2) * prev_text_size;

        int text_position_axi_x = 250;
        int text_position_axi_y =
            (i ? options[i - 1]->get_y() + prev_text_height : 200);

        cur_text->set_pos(text_position_axi_x, text_position_axi_y,
                          NOT_CENTER_HORIZONTALLY, NOT_CENTER_VERTICALLY);

        for (int j = 0;
             j < static_cast<int>(sub_options[cur_text->get_text()].size());
             j++) {
            text_position_axi_x = 800;

            if (j) {
                Text *prev_option = sub_options[cur_text->get_text()][j - 1];
                text_position_axi_y = prev_option->get_y() +
                    prev_option->get_height() + TEXT_OFFSET;
            } else {
                /* Nothing to do. */
            }

            Text *option = sub_options[cur_text->get_text()][j];
            option->set_pos(text_position_axi_x, text_position_axi_y);
        }
    }
}

void ResourcesOptionsState::render_main_menu_option(
    int index, bool on_submenu, int current_option, string text_option,
    std::vector<int> current_sub_option,
    std::map<string, std::vector<Text *> > *sub_options) {
    /**
     * Iterates every option of the menu "Options" of a submenu.
     */
    for (int j = 0; j < static_cast<int>((*sub_options)[text_option].size());
         j++) {
        /**
         * Check if selected option indicates that user is on a submenu.
         */
        if (on_submenu and (current_option == index)) {
            /**
             * Check which option of the submenu was selected.
             * Set it's text color to LIGHT_GREEN.
             */
            if (current_sub_option[index] == j) {
                (*sub_options)[text_option][j]->set_color(LIGHT_GREEN);
            } else {
                (*sub_options)[text_option][j]->set_color(WHITE);
            }
        } else {
            /**
             * Check which option of the submenu was selected.
             * Set it's text color to DARK_GREEN.
             */
            if (current_sub_option[index] == j) {
                (*sub_options)[text_option][j]->set_color(DARK_GREEN);
            } else {
                (*sub_options)[text_option][j]->set_color(DARK_GREY);
            }
        }

        (*sub_options)[text_option][j]->render();
    }
}

void ResourcesOptionsState::render_submenu_option(
    int index, bool on_submenu, int current_option,
    std::vector<Text *> *options) {
    /**
     * Check if selected option indicates that user is on a submenu.
     * Set color of current selected option to DARK_GREY.
     */
    if (on_submenu and (index != static_cast<int>(options->size()) - 1) and
        (index != current_option)) {
        (*options)[index]->set_color(DARK_GREY);
    } else {
        /**
         * Check which option of a main was selected.
         * Set it's text color to LIGHT_GREEN.
         */
        if (current_option == index) {
            (*options)[index]->set_color(LIGHT_GREEN);
        } else {
            (*options)[index]->set_color(WHITE);
        }
    }
}
