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

#define N_CHARS 8

class CharacterSelectState : public State {
 private:
    Sprite background[2]; /**< Images for background. */
    Sprite planet; /**< Image from planet logo. */
    Sprite character_slots;  /**< Images for character thumbnails. */
    Sprite number[4]; /**< Images for numbers that represent the player. */
    Sprite name_tag[4]; /**< Images for characters name tag. */
    Sprite selected_tag; /**< Image to highlight selected characters. */
    Sprite ready_to_fight; /**< Image for when everything is ready. */

    Sound blocked; /**< Sound when try to select not allowed characters. */
    Sound selected_sound; /**< Sound when really select characters.  */
    Sound changed; /**< Sound when switching between characters. */

    int cur_row[4];
    int cur_col[4];
    int cur_skin[4];

    bool selected[4];
    bool ready;   /**< Ready to start the match. */

    string selected_stage;

    enum Button { A, B, Y, LEFT,
                  RIGHT, UP, DOWN,
                  SELECT, START, LT, RT }; /**< Based on Xbox controller. */

    bool pressed[4][15]; /**< One array of buttons for each player. */


    /** 
     * Vectors for elements Positions.
     * The following vectors have ordered pairs which are the
     * positions (x, y), given in pixels. Those pixels are not counted 
     * based on window size, but instead, based on the picture on background.
     * 
     * For example, to centralize the left side of an object relative to
     * background, suposing background picture has 1280 pixels in width,
     * we would put x position of the object at 1280/2 ().
     * 
     * Remembering (0 0) is on left top corner.
     * 
     * So, for the following coordinates:
     * Unit: px;
     * Range: [0, background_image_size - size_of_object].
     * (Range for fit on screen)
     */
    vector<ii> name_tag_positions; /**< Relative to background image */
    vector<ii> sprite_pos;  /**< Relative to background image. */
    vector<ii> name_delta;  /**< Relative to name_tag_positions. */
    vector<ii> number_delta; /**< Relative to character thumbnail. */

    FighterMenu chars[N_CHARS];  /**< Board of fighters */

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
