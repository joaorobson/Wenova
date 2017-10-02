/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file CharacterSelectState.h
 * Controls all process of players choosing characters and skins.
 */

#ifndef INCLUDE_CHARACTERSELECTSTATE_H_
#define INCLUDE_CHARACTERSELECTSTATE_H_

#include "FighterMenu.h"
#include "InputManager.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"

#include <string>
#include <utility>
#include <vector>

using std::to_string;
using std::make_pair;

#define N_CHARS 8

class CharacterSelectState : public State {
 private:
    Sprite background[2], planet, character_slots;
    Sprite number[4], name_tag[4], selected_tag, ready_to_fight;
    Sound blocked, selected_sound, changed;
    int cur_row[4], cur_col[4], cur_skin[4];
    bool selected[4], ready;
    string selected_stage;

    enum Button { A, B, Y, LEFT, RIGHT, UP, DOWN, SELECT, START, LT, RT };
    bool pressed[4][15];

    vector<ii> number_delta, sprite_pos, name_tag_positions, name_delta;

    FighterMenu chars[N_CHARS];

 public:
    /**
     * Load all artistic files and initializes board variables based
     * on the stage that was selected
     *
     * @param cselected_stage Name of the stage that was selected.
     */
    explicit CharacterSelectState(string cselected_stage);

    /**
     * Updates player selection while player move between characters.
     *
     * @param delta Variation of how much the characters player travelled
     */
    void update(float delta);

    /**
     * Render the board.
     * Render the board of with characters options, including all effects.
     */
    void render();

    /**
     * Not implemented.
     */
    void pause();

    /**
     * Not implemented.
     */
    void resume();

    /**
     * Process interaction of the player with joystick while
     * choosing character.
     */
    void process_input();

    /**
     * Not implemented.
     */
    bool character_enabled(int row, int col);

    /**
     * Get information about the character the player choose.
     *
     * @param idx  Index of the character
     *
     * @returns Name and number of frames in corresponding sprite
     */
    pair<string, int> get_char_info(int idx);

    /**
     * Searchs for characters identifying which the player chose.
     *
     * @returns
     */
    bool all_players_selected();

    /**
     * Get information about players choice about characters and skins.
     *
     * @returns Vector of pairs of strings containing information about
     * characters and skins choosen.
     */
    vector<pair<string, string>> export_players();

    /**
     * Get slot of character on the board.
     *
     * @param row [510 or 645]
     * @param col [55 or 197 or 395 or 536]
     *
     * @returns pair of ints which indicates the corresponding slot.
     */
    pair<int, int> get_slot(int row, int col);
};

#endif  // INCLUDE_CHARACTERSELECTSTATE_H_
