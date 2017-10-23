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

#include <assert.h>

#include <string>
#include <utility>
#include <vector>

#include "FighterMenu.h"
#include "InputManager.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "easylogging++.h" // NOLINT


#define N_CHARS 8
#define N_BACKGROUNDS_SPRITES 2
#define N_PLAYERS 4
#define N_BUTTONS 15

class CharacterSelectState : public State {
 private:
    Sprite backgrounds_sprites[N_BACKGROUNDS_SPRITES];  ///< Some screens have
    ///< multilayer
    ///< background.
    Sprite planet_sprite;
    Sprite characters_slots_sprites; /**< Images for character thumbnails. */
    Sprite players_numbers_sprites[N_PLAYERS];  ///< Numbers which jump
    ///< for slots.
    Sprite names_tags_sprites[N_PLAYERS];
    Sprite selected_tags_sprites; /**< Highlight selected characters. */
    Sprite ready_to_fight_sprite; /**< When everything is ready. */

    Sound blocked_sound; /**< When try to select not allowed things. */
    Sound select_sound; /**< When really select characters. */
    Sound changed_sound; /**< When switching between characters. */

    FighterMenu chars[N_CHARS]; /**< Board of fighters */

    /**
     * Vectors for elements Positions.
     * The following vectors have ordered pairs which are the
     * positions (x, y), given in pixels. Those pixels are not counted
     * based on window size, but instead, based on the picture on
     * backgrounds_sprites.
     *
     * For example, to centralize the left side of an object relative to
     * backgrounds_sprites, suposing backgrounds_sprites picture has 1280 pixels
     * in width,
     * we would put x position of the object at 1280/2 ().
     *
     * Remembering (0 0) is on left top corner.
     *
     * So, for the following coordinates:
     * Unit: px;
     * Range: [0, backgrounds_sprites_image_size - size_of_object].
     * (Range for fit on screen)
     */
    vector<ii> names_tags_positions; /**< Relative to backgrounds_sprites. */
    vector<ii> characters_positions; /**< Relative to backgrounds_sprites. */
    vector<ii> names_positions_deltas; /**< Relative to names_tags_positions. */
    vector<ii> numbers_positions_deltas; /**< Relative to slots. */

    string selected_stage;

    enum Button {
        A,
        B,
        Y,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        SELECT,
        START,
        LT,
        RT
    }; /**< Based on Xbox controller. */

    int current_row[N_PLAYERS];
    int current_column[N_PLAYERS];
    int current_skin[N_PLAYERS];

    bool is_character_selected[N_PLAYERS];
    bool is_ready; /**< Ready to start the match. */

    bool is_key_pressed[N_PLAYERS][N_BUTTONS];

 public:
    /**
     * Load all artistic files and initializes board variables based
     * on the stage that was selected
     *
     * @param cselected_stage Name of the stage that was selected.
     */
    explicit CharacterSelectState(string cselected_stage);

    /**
     * Process interaction of the player with joystick while
     * choosing character.
     */
    void process_input();

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
     * Get information about players choice about characters and skins.
     *
     * @returns Vector of pairs of strings containing information about
     * characters and skins choosen.
     */
    vector<pair<string, string>> export_players();

    /**
     * Searchs for characters identifying which the player chose.
     *
     * @returns
     */
    bool all_players_selected();

    /**
     * Get information about the character the player choose.
     *
     * @param idx  Index of the character
     *
     * @returns Name and number of frames in corresponding sprite
     */
    pair<string, int> get_chars_info(int idx);

    /**
     * Get slot of character on the board.
     *
     * @param row [510 or 645]
     * @param col [55 or 197 or 395 or 536]
     *
     * @returns pair of ints which indicates the corresponding slot.
     */
    pair<int, int> get_slot(int row, int col);

    /**
     * Not implemented.
     */
    void pause();

    /**
     * Not implemented.
     */
    void resume();

    /**
     * Not implemented.
     */
    bool character_enabled(int row, int col);
};

#endif  // INCLUDE_CHARACTERSELECTSTATE_H_
