/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file FighterMenu.h
 * This file contains the definitions of all methods and attributes of the class
 * FighterMenu.
 */
#ifndef INCLUDE_FIGHTERMENU_H_
#define INCLUDE_FIGHTERMENU_H_

#include <utility>
#include <string>
#include <vector>
#include <assert.h>

#include "Sprite.h"
#include "Text.h"

using std::string;
using std::vector;

#define N_SKINS 4
#define SKIN_SCALE 3

class FighterMenu {
 private:
    Sprite skin[N_SKINS];  /**< Vector of the fighter's skins. */
    Sprite disabled;  /**< Image of fighter when it has been already */
                      /**< selected. */
    Text *name_text;  /**< Text with fighter's name. */
    string name;  /**< String of the fighter's name. */
    int n_frames;  /**< Int with the number of frames of a fighter's skin. */
    bool enabled;  /**< Bool value that indicates if fighter is available. */
    bool skin_available[N_SKINS];  /**< Bool vector that indicates fighter's */
                                   /**< skin available. */

 public:
    FighterMenu();
    FighterMenu(string name,
                int frames,
                bool enabled = true);

    bool is_enabled();
    bool is_skin_available(int idx);
    void lock_skin(int idx);
    void unlock_skin(int idx);
    Text* get_name_text();
    string get_name();
    string get_skin_name(int idx);
    Sprite& get_skin(int idx);
    Sprite& get_disabled();
};

#endif  // INCLUDE_FIGHTERMENU_H_
