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
#ifndef INCLUDE_RESOURCESOPTIONSSTATE_H_
#define INCLUDE_RESOURCESOPTIONSSTATE_H_

#include "Text.h"

#include <assert.h>
#include <map>
#include <string>
#include <vector>

class ResourcesOptionsState {
 public:
    static void action_cursor_button(bool on_submenu, int *current_option,
                                     std::vector<int> *current_sub_option,
                                     int delta_cursor_state, int limit_options,
                                     int limit_sub_options);

    static void action_selection_button(
        bool *on_submenu, int current_option, bool *m_quit_requested,
        std::vector<int> *current_sub_option, std::vector<Text *> options,
        std::map<string, std::vector<Text *> > sub_options);

    static void action_return_button(
        bool *on_submenu, bool *m_quit_requested,
        std::vector<int> *current_sub_option, std::vector<Text *> options,
        std::map<string, std::vector<Text *> > sub_options);

    /**
     * Get the option on a sub menu.
     * This function identifies which sub menu and option the user selected.
     *
     * @param option an integer argument that represents the selected option
     * of the main menu.
     *
     * @return an integer value that represents the current sub option of a sub
     * menu.
     */
    static int get_current_sub_option(
        int option, std::map<string, std::vector<Text *> > sub_options);

    static void set_position_options_text(
        std::vector<Text *> options,
        std::map<string, std::vector<Text *> > sub_options);

    static void render_main_menu_option(
        int index, bool on_submenu, int current_option, string text_option,
        std::vector<int> current_sub_option,
        std::map<string, std::vector<Text *> > *sub_options);

    static void render_submenu_option(int index, bool on_submenu,
                                      int current_option,
                                      std::vector<Text *> *options);
};

#endif  // INCLUDE_RESOURCESOPTIONSSTATE_H_
