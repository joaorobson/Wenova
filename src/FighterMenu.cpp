/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file FighterMenu.cpp
 * Brief Description.
 */

#include "FighterMenu.h"

#define FRAME_TIME 13
#define YELLOW \
    { 202, 236, 4, 1 }
#define NUMBER_SKINS 4
#define MIN_INDEX_ARRAY 0
#define DEFAULT_CHARACTER_NAME "Blood"

/**
 * Brief Description.
 */
FighterMenu::FighterMenu() {
}

/**
 * Brief Description.
 *
 * @param cname
 * @param frames
 * @param cenabled
 */
FighterMenu::FighterMenu(string cname, int frames, bool cenabled) {
    assert(cname.empty() != true);
    name = cname;
    name_text = new Text("font/8-BIT WONDER.ttf", 20, Text::TextStyle::SOLID,
                         name, YELLOW);

    enabled = cenabled;
    n_frames = frames;

    for (int i = 0; i < N_SKINS; i++) {
        if (enabled) {
            assert(get_skin_name(i).empty() != true);

            skin[i] = Sprite(
                "characters/" + name + "/" + get_skin_name(i) + "/idle.png",
                n_frames, FRAME_TIME);
        } else {
            skin[i] = Sprite("characters/" + name + "/idle.png", n_frames,
                             FRAME_TIME);
        }
        skin[i].set_scale(SKIN_SCALE);
    }

    disabled =
        Sprite("characters/" + name + "/disabled.png", n_frames, FRAME_TIME);
    disabled.set_scale(SKIN_SCALE);

    memset(skin_available, true, sizeof skin_available);
}

/**
 * Brief Description.
 *
 * @returns
 */
bool FighterMenu::is_enabled() {
    return enabled;
}

/**
 * Brief Description.
 *
 * @param idx
 *
 * @returns
 */
bool FighterMenu::is_skin_available(int idx) {
    if (idx >= MIN_INDEX_ARRAY and idx < NUMBER_SKINS) {
        return skin_available[idx];
    } else {
        return false;
    }
}

/**
 * Brief Description.
 *
 * @param idx
 */
void FighterMenu::lock_skin(int idx) {
    if (idx >= MIN_INDEX_ARRAY and idx < NUMBER_SKINS) {
        skin_available[idx] = false;
    } else {
        /* Nothing to do. */
    }
}

/**
 * Brief Description.
 *
 * @param idx
 */
void FighterMenu::unlock_skin(int idx) {
    if (idx >= MIN_INDEX_ARRAY and idx < NUMBER_SKINS) {
        skin_available[idx] = true;
    } else {
        /* Nothing to do. */
    }
}

/**
 * Brief Description.
 *
 * @returns
 */
Text* FighterMenu::get_name_text() {
    assert(name_text != NULL);

    return name_text;
}

/**
 * Brief Description.
 *
 * @returns
 */
string FighterMenu::get_name() {
    if (name != "") {
        return name;
    } else {
        return DEFAULT_CHARACTER_NAME;
    }
}

/**
 * Brief Description.
 *
 * @param idx
 *
 * @returns
 */
string FighterMenu::get_skin_name(int idx) {
    vector<string> skins_names = {"default", "alt1", "alt2", "alt3"};

    if (idx >= MIN_INDEX_ARRAY and idx < NUMBER_SKINS) {
        return skins_names[idx];
    } else {
        return skins_names[0];
    }
}

/**
 * Brief Description.
 *
 * @param idx
 *
 * @returns
 */
Sprite& FighterMenu::get_skin(int idx) {
    if (idx >= MIN_INDEX_ARRAY and idx < NUMBER_SKINS) {
        return skin[idx];
    } else {
        return skin[0];
    }
}

/**
 * Brief Description.
 *
 * @returns
 */
Sprite& FighterMenu::get_disabled() {
    return disabled;
}
