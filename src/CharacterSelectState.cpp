/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file CharacterSelectState.cpp
 * Implements class CharacterSelectState methods.
 */

#include "SDL_mixer.h"

#include "BattleState.h"
#include "CharacterSelectState.h"
#include "Game.h"
#include "MenuState.h"
#include "StageSelectState.h"

#define FRAME_TIME 7.5
#define FIRST_PLAYER 0
#define ALLOCATED_CHANNELS 50 /**< Allocated channels for mixing. */

#define N_COLS 2
#define N_ROWS 4
#define N_PLAYERS 4
#define N_backgrounds_sprites 2
#define N_SKINS 4

#define NAMES_TAGS_X_POSITIONS_1 91 /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_1 145 /**< Unit: px*/

#define NAMES_TAGS_X_POSITIONS_2 92 /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_2 494 /**< Unit: px*/

#define NAMES_TAGS_X_POSITIONS_3 956 /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_3 145 /**< Unit: px*/

#define NAMES_TAGS_X_POSITIONS_4 955 /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_4 494 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_1 125 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_1 32 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_2 121 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_2 379 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_3 943 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_3 34 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_4 956 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_4 381 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_DELTAS_1 173 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_DELTAS_1 152 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_DELTAS_2 172 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_DELTAS_2 154 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_DELTAS_3 102 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_DELTAS_3 153 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_DELTAS_4 105 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_DELTAS_4 153 /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_1 12 /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_1 9 /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_2 93 /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_2 9 /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_3 12 /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_3 101 /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_4 93 /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_4 101 /**< Unit: px*/

#define CHARACTER_SLOTS_PATH "character_select/character_slots.png"
#define SELECTED_TAG_PATH "character_select/selected.png"
#define READY_TO_FIGHT_PATH "character_select/ready_to_fight.png"
#define PLANET_SPRITE_PATH "character_select/planet.png"

#define ROWS_X_POSITIONS \
    { 510, 645 }
#define ROWS_Y_POSITIONS \
    { 55, 197, 395, 536 }

/**
 * To allow iterations over many elements.
 */
#define BACKGROUND_SPRITES_PREFIX_PATH "character_select/background_"
#define PLAYERS_NUMBERS_SPRITES_PREFIX_PATH "character_select/number_"
#define NAMES_TAGS_SPRITES_PREFIX_PATH "character_select/name_tag_"
#define CHARACTERS_FORMAT ".png"

#define BLOCKED_SOUND_PATH "menu/sound/cancel.ogg"
#define SELECT_SOUND_PATH "menu/sound/select.ogg"
#define CHANGED_SOUND_PATH "menu/sound/cursor.ogg"

#define PLANET_SPRITE_SCALE 1.5
#define PLANET_SPRITE_AMOUNT 8

#define CHARATERS_SPRITES_AMOUNT \
    { 12, 8, 8, 7, 4, 4, 7, 5 }
#define CHARACTERS_NAMES \
    { "blood", "flesh", "hookline", "sinker", "trap", "trip", "dusk", "dawn" }

#define BACKGROUNDS_SIZE_WIDTH 1280 /**< Unit: px*/
#define BACKGROUNDS_SIZE_HEIGHT 720 /**< Unit: px*/

/**
 * Load all artistic files and initializes board variables based
 * on the stage that was selected
 *
 * @param cselected_stage Name of the stage that was selected.
 */
CharacterSelectState::CharacterSelectState(string cselected_stage) {
    LOG(INFO)
        << "Starting CharacterSelectState constructor with cselected_stage: "
        << cselected_stage;

    if (NAMES_TAGS_X_POSITIONS_1 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NAMES_TAGS_X_POSITIONS_1 is bigger than screen";
    }

    if (NAMES_TAGS_Y_POSITIONS_1 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NAMES_TAGS_Y_POSITIONS_1 is bigger than screen";
    }

    if (NAMES_TAGS_X_POSITIONS_2 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NAMES_TAGS_X_POSITIONS_2 is bigger than screen";
    }

    if (NAMES_TAGS_Y_POSITIONS_2 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NAMES_TAGS_Y_POSITIONS_2 is bigger than screen";
    }

    if (NAMES_TAGS_X_POSITIONS_3 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NAMES_TAGS_X_POSITIONS_3 is bigger than screen";
    }

    if (NAMES_TAGS_Y_POSITIONS_3 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NAMES_TAGS_Y_POSITIONS_3 is bigger than screen";
    }

    if (NAMES_TAGS_X_POSITIONS_4 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NAMES_TAGS_X_POSITIONS_4 is bigger than screen";
    }

    if (NAMES_TAGS_Y_POSITIONS_4 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NAMES_TAGS_Y_POSITIONS_4 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_1 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_1 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_1 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_1 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_2 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_2 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_2 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_2 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_3 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_3 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_3 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_3 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_4 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_4 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_4 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_4 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_DELTAS_1 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_DELTAS_1 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_DELTAS_1 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_DELTAS_1 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_DELTAS_2 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_DELTAS_2 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_DELTAS_2 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_DELTAS_2 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_DELTAS_3 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_DELTAS_3 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_DELTAS_3 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_DELTAS_3 is bigger than screen";
    }

    if (CHARACTERS_X_POSITIONS_DELTAS_4 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "CHARACTERS_X_POSITIONS_DELTAS_4 is bigger than screen";
    }

    if (CHARACTERS_Y_POSITIONS_DELTAS_4 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "CHARACTERS_Y_POSITIONS_DELTAS_4 is bigger than screen";
    }

    if (NUMBERS_X_POSITIONS_DELTAS_1 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NUMBERS_X_POSITIONS_DELTAS_1 is bigger than screen";
    }

    if (NUMBERS_Y_POSITIONS_DELTAS_1 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NUMBERS_Y_POSITIONS_DELTAS_1 is bigger than screen";
    }

    if (NUMBERS_X_POSITIONS_DELTAS_2 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NUMBERS_X_POSITIONS_DELTAS_2 is bigger than screen";
    }

    if (NUMBERS_Y_POSITIONS_DELTAS_2 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NUMBERS_Y_POSITIONS_DELTAS_2 is bigger than screen";
    }

    if (NUMBERS_X_POSITIONS_DELTAS_3 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NUMBERS_X_POSITIONS_DELTAS_3 is bigger than screen";
    }

    if (NUMBERS_Y_POSITIONS_DELTAS_3 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NUMBERS_Y_POSITIONS_DELTAS_3 is bigger than screen";
    }

    if (NUMBERS_X_POSITIONS_DELTAS_4 > BACKGROUNDS_SIZE_WIDTH) {
        LOG(FATAL) << "NUMBERS_X_POSITIONS_DELTAS_4 is bigger than screen";
    }

    if (NUMBERS_Y_POSITIONS_DELTAS_4 > BACKGROUNDS_SIZE_HEIGHT) {
        LOG(FATAL) << "NUMBERS_Y_POSITIONS_DELTAS_4 is bigger than screen";
    }

    for (auto x : ROWS_X_POSITIONS) {
        if (x < BACKGROUNDS_SIZE_WIDTH) {
            LOG(FATAL) << "ROWS_X_POSITIONS, element: " << x
                       << "is bigger than screen";
        }
    }

    for (auto y : ROWS_Y_POSITIONS) {
        if (x < BACKGROUNDS_SIZE_WIDTH) {
            LOG(FATAL) << "ROWS_Y_POSITIONS, element: " << y
                       << "is bigger than screen";
        }
    }

#ifndef NDEBUG
    assert(NAMES_TAGS_X_POSITIONS_1 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NAMES_TAGS_Y_POSITIONS_1 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NAMES_TAGS_X_POSITIONS_2 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NAMES_TAGS_Y_POSITIONS_2 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NAMES_TAGS_X_POSITIONS_3 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NAMES_TAGS_Y_POSITIONS_3 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NAMES_TAGS_X_POSITIONS_4 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NAMES_TAGS_Y_POSITIONS_4 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_1 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_1 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_2 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_2 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_3 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_3 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_4 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_4 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_DELTAS_1 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_DELTAS_1 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_DELTAS_2 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_DELTAS_2 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_DELTAS_3 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_DELTAS_3 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(CHARACTERS_X_POSITIONS_DELTAS_4 <= BACKGROUNDS_SIZE_WIDTH);
    assert(CHARACTERS_Y_POSITIONS_DELTAS_4 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NUMBERS_X_POSITIONS_DELTAS_1 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NUMBERS_Y_POSITIONS_DELTAS_1 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NUMBERS_X_POSITIONS_DELTAS_2 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NUMBERS_Y_POSITIONS_DELTAS_2 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NUMBERS_X_POSITIONS_DELTAS_3 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NUMBERS_Y_POSITIONS_DELTAS_3 <= BACKGROUNDS_SIZE_HEIGHT);
    assert(NUMBERS_X_POSITIONS_DELTAS_4 <= BACKGROUNDS_SIZE_WIDTH);
    assert(NUMBERS_Y_POSITIONS_DELTAS_4 <= BACKGROUNDS_SIZE_HEIGHT);

    for (auto x : ROWS_X_POSITIONS) {
        assert(x <= BACKGROUNDS_SIZE_WIDTH);
    }

    for (auto y : ROWS_Y_POSITIONS) {
        assert(y <= BACKGROUNDS_SIZE_HEIGHT);
    }
#endif
  
    Mix_AllocateChannels(ALLOCATED_CHANNELS);

    memset(current_column, 0, sizeof current_column);
    memset(current_row, 0, sizeof current_row);
    memset(current_skin, 0, sizeof current_skin);
    memset(is_character_selected, false, sizeof is_character_selected);

    characters_slots_sprites = Sprite(CHARACTER_SLOTS_PATH);
    selected_tags_sprites = Sprite(SELECTED_TAG_PATH);
    ready_to_fight_sprite = Sprite(READY_TO_FIGHT_PATH);
    planet_sprite =
        Sprite(PLANET_SPRITE_PATH, PLANET_SPRITE_AMOUNT, FRAME_TIME);
    planet_sprite.set_scale(PLANET_SPRITE_SCALE);

    is_ready = false;

    selected_stage = cselected_stage;
    blocked_sound = Sound(BLOCKED_SOUND_PATH);
    select_sound = Sound(SELECT_SOUND_PATH);
    changed_sound = Sound(CHANGED_SOUND_PATH);

    /**
     * Load backgrounds_spritess following standards for file name.
     */
    for (int i = 0; i < N_backgrounds_sprites; i++) {
        backgrounds_sprites[i] = Sprite(BACKGROUND_SPRITES_PREFIX_PATH +
                                        std::to_string(i + 1) + ".png");
    }

    /**
     * Load information for players based on standards for file name.
     */
    for (int i = 0; i < N_PLAYERS; i++) {
        names_tags_sprites[i] =
            Sprite(NAMES_TAGS_SPRITES_PREFIX_PATH + std::to_string(i + 1) +
                   CHARACTERS_FORMAT);

        players_numbers_sprites[i] =
            Sprite(PLAYERS_NUMBERS_SPRITES_PREFIX_PATH + std::to_string(i + 1) +
                   CHARACTERS_FORMAT);
    }

    /**
     * Load information for characters based on standards for file name.
     */
    for (int i = 0; i < N_CHARS; i++) {
        chars[i] = FighterMenu(get_chars_info(i).first,
                               get_chars_info(i).second, i < 2);
    }

    names_tags_positions = {
        ii(NAMES_TAGS_X_POSITIONS_1, NAMES_TAGS_Y_POSITIONS_1),
        ii(NAMES_TAGS_X_POSITIONS_2, NAMES_TAGS_Y_POSITIONS_2),
        ii(NAMES_TAGS_X_POSITIONS_3, NAMES_TAGS_Y_POSITIONS_3),
        ii(NAMES_TAGS_X_POSITIONS_4, NAMES_TAGS_Y_POSITIONS_4)};
    characters_positions = {
        ii(CHARACTERS_X_POSITIONS_1, CHARACTERS_Y_POSITIONS_1),
        ii(CHARACTERS_X_POSITIONS_2, CHARACTERS_Y_POSITIONS_2),
        ii(CHARACTERS_X_POSITIONS_3, CHARACTERS_Y_POSITIONS_3),
        ii(CHARACTERS_X_POSITIONS_4, CHARACTERS_Y_POSITIONS_4)};
    names_positions_deltas = {
        ii(CHARACTERS_X_POSITIONS_DELTAS_1, CHARACTERS_Y_POSITIONS_DELTAS_1),
        ii(CHARACTERS_X_POSITIONS_DELTAS_2, CHARACTERS_Y_POSITIONS_DELTAS_2),
        ii(CHARACTERS_X_POSITIONS_DELTAS_3, CHARACTERS_Y_POSITIONS_DELTAS_3),
        ii(CHARACTERS_X_POSITIONS_DELTAS_4, CHARACTERS_Y_POSITIONS_DELTAS_4)};
    numbers_positions_deltas = {
        ii(NUMBERS_X_POSITIONS_DELTAS_1, NUMBERS_Y_POSITIONS_DELTAS_1),
        ii(NUMBERS_X_POSITIONS_DELTAS_2, NUMBERS_Y_POSITIONS_DELTAS_2),
        ii(NUMBERS_X_POSITIONS_DELTAS_3, NUMBERS_Y_POSITIONS_DELTAS_3),
        ii(NUMBERS_X_POSITIONS_DELTAS_4, NUMBERS_Y_POSITIONS_DELTAS_4)};

    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);

    LOG(INFO) << "Ending CharacterSelectState constructor";
}

/**
 * Updates player selection while player move between characters.
 *
 * @param delta Variation of how much the characters player travelled
 */
void CharacterSelectState::update(float delta) {
    LOG(INFO) << "Starting CharacterSelectState update method with delta: "
              << delta;

    process_input();

    InputManager* input_manager = InputManager::get_instance();

    /**
     * Process request for leaving the game.
     */
    if (input_manager->quit_requested()) {
        m_quit_requested = true;

        LOG(INFO)
            << "Ending CharacterSelectState update due quit request method";
        return;
    }

    /**
     * Process request for going next menu.
     */
    if (is_key_pressed[FIRST_PLAYER][SELECT] or
        (not is_character_selected[FIRST_PLAYER] and
         is_key_pressed[FIRST_PLAYER][B])) {
        select_sound.play();
        m_quit_requested = true;
        Game::get_instance().push(new StageSelectState());

        LOG(INFO)
            << "Ending CharacterSelectState update due quit request method";
        return;
    }

    /**
     * Only enable start when all players have selected a character.
     */
    if (all_players_selected()) {
        is_ready = true;
        if (is_key_pressed[FIRST_PLAYER][START] or
            is_key_pressed[FIRST_PLAYER][A]) {
            select_sound.play();
            vector<pair<string, string> > p = export_players();
            m_quit_requested = true;
            Game::get_instance().push(
                new BattleState(selected_stage, export_players()));

            LOG(INFO)
                << "Ending CharacterSelectState update due quit request method";
            return;
        }
    }

    /**
     * Handle all players selection.
     */
    for (int i = 0; i < N_PLAYERS; i++) {
        if (not is_character_selected[i]) {
            /**
             * Random Character.
             */
            if (is_key_pressed[i][Y]) {
                select_sound.play();
                int rand_col = 0, rand_row = 0, rand_skin = 0, char_sel = 0;

                /**
                 * Select random row and column.
                 */
                do {
                    unsigned int seed1 = clock();
                    unsigned int seed2 = clock();

                    rand_col = rand_r(&seed1) % N_COLS;
                    rand_row = rand_r(&seed2) % N_ROWS;

                    char_sel = rand_row * N_COLS + rand_col;
                } while (not chars[char_sel].is_enabled());

                /**
                 * Select random skin for character.
                 */
                do {
                    unsigned int seed = clock();

                    rand_skin = rand_r(&seed) % N_SKINS;
                } while (not chars[char_sel].is_skin_available(rand_skin));

                current_column[i] = rand_col;
                current_row[i] = rand_row;
                current_skin[i] = rand_skin;
            }

            int old_col = current_column[i];
            int old_row = current_row[i];

            /**
             * Change current selected character.
             */
            if (is_key_pressed[i][LEFT]) {
                changed_sound.play();
                if (current_column[i] != 0) {
                    current_column[i]--;
                }
            }
            if (is_key_pressed[i][RIGHT]) {
                changed_sound.play();
                if (current_column[i] + 1 < N_COLS) {
                    current_column[i]++;
                }
            }
            if (is_key_pressed[i][UP]) {
                changed_sound.play();
                if (current_row[i] != 0) {
                    current_row[i]--;
                }
            }
            if (is_key_pressed[i][DOWN]) {
                changed_sound.play();
                if (current_row[i] + 1 < N_ROWS) {
                    current_row[i]++;
                }
            }

            /**
             * Reset skin if character changed_sound.
             */
            if (current_column[i] != old_col or current_row[i] != old_row) {
                current_skin[i] = 0;
            }

            /**
             * Change skin.
             */
            if (is_key_pressed[i][LT]) {
                changed_sound.play();
                current_skin[i] = (current_skin[i] - 1 + N_SKINS) % N_SKINS;
            }
            if (is_key_pressed[i][RT]) {
                changed_sound.play();
                current_skin[i] = (current_skin[i] + 1) % N_SKINS;
            }

            /**
             * Select character and lock skin.
             */
            if (is_key_pressed[i][A]) {
                int char_sel = current_row[i] * N_COLS + current_column[i];

                /**
                 * Check if character or skin are unblocked_sound.
                 */
                if (chars[char_sel].is_enabled()) {
                    if (not chars[char_sel].is_skin_available(
                            current_skin[i])) {
                        blocked_sound.play();
                    } else {
                        select_sound.play();
                        chars[char_sel].lock_skin(current_skin[i]);
                        is_character_selected[i] = true;
                    }
                } else {
                    blocked_sound.play();
                }
            }
        } else {
            /**
             * Unselect character.
             */
            if (is_key_pressed[i][B]) {
                int char_sel = current_row[i] * N_COLS + current_column[i];
                chars[char_sel].unlock_skin(current_skin[i]);
                is_character_selected[i] = false;
                is_ready = false;
            }
        }
    }

    /**
     * Make characters move while you are selecting (not static).
     */
    for (int i = 0; i < N_CHARS; i++) {
        chars[i].get_disabled().update(delta);

        for (int j = 0; j < N_SKINS; j++) {
            chars[i].get_skin(j).update(delta);
        }
    }

    planet_sprite.update(delta);

    LOG(INFO) << "Ending CharacterSelectState update method";
}

/**
 * Render the board.
 * Render the board with characters options, including all effects.
 */
void CharacterSelectState::render() {
    LOG(INFO) << "Starting CharacterSelectState update method";

    /**
     * Put backgrounds_spritess, planet_sprite and characters_slots_sprites
     * centralized.
     */

    /**
     * Result should be 0 for backgrounds_spritess images.
     */
    backgrounds_sprites[0].render(
        BACKGROUNDS_SIZE_WIDTH / 2 - backgrounds_sprites[0].get_width() / 2,
        BACKGROUNDS_SIZE_HEIGHT / 2 - backgrounds_sprites[1].get_height() / 2);

    planet_sprite.render(
        BACKGROUNDS_SIZE_WIDTH / 2 - planet_sprite.get_width() / 2,
        BACKGROUNDS_SIZE_HEIGHT / 2 - planet_sprite.get_height() / 2);

    backgrounds_sprites[1].render(
        BACKGROUNDS_SIZE_WIDTH / 2 - backgrounds_sprites[0].get_width() / 2,
        BACKGROUNDS_SIZE_HEIGHT / 2 - backgrounds_sprites[1].get_height() / 2);

    characters_slots_sprites.render(
        BACKGROUNDS_SIZE_WIDTH / 2 - characters_slots_sprites.get_width() / 2,
        BACKGROUNDS_SIZE_HEIGHT / 2 -
            characters_slots_sprites.get_height() / 2);

    /**
     * Iterate over elements rendering things.
     */
    for (int i = 0; i < N_PLAYERS; i++) {
        SDL_RendererFlip flip = i >= 2 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        int row_selected = current_row[i];
        int col_selected = current_column[i];
        int char_sel = row_selected * N_COLS + col_selected;

        FighterMenu char_selected = chars[char_sel];

        char_selected.get_skin(current_skin[i])
            .render(characters_positions[i].first,
                    characters_positions[i].second, 0, flip);

        /**
         * Render not available skins for not selected characters.
         */
        if (not char_selected.is_skin_available(current_skin[i]) and
            not is_character_selected[i]) {
            char_selected.get_disabled().render(characters_positions[i].first,
                                                characters_positions[i].second,
                                                0, flip);
        }

        char_selected.get_name_text()->set_pos(
            names_tags_positions[i].first + names_positions_deltas[i].first,
            names_tags_positions[i].second + names_positions_deltas[i].second,
            true, true);

        ii slot = get_slot(row_selected, col_selected);
        names_tags_sprites[i].render(names_tags_positions[i].first,
                                     names_tags_positions[i].second);

        char_selected.get_name_text()->render();
        players_numbers_sprites[i].render(
            slot.first + numbers_positions_deltas[i].first,
            slot.second + numbers_positions_deltas[i].second);

        /**
         * Mark selected character with skin.
         */
        if (is_character_selected[i]) {
            selected_tags_sprites.render(names_tags_positions[i].first,
                                         names_tags_positions[i].second, 0,
                                         flip);
        }
    }

    if (is_ready) {
        ready_to_fight_sprite.render(0, 0);
    }

    LOG(INFO) << "Ending CharacterSelectState update method";
}

/**
 * Check if all players selected their characters and skins.
 *
 * @returns
 */
bool CharacterSelectState::all_players_selected() {
    LOG(INFO) << "Starting CharacterSelectState all_players_selected method";

    for (auto cur : is_character_selected) {
        if (not cur) {
            return_value = false;
            LOG(INFO) << "Ending CharacterSelectState all_players_selected "
                         "method returning value: "
                      << return_value;

            return return_value;
        }
    }

    return_value = true;
    LOG(INFO) << "Ending CharacterSelectState all_players_selected method "
                 "returning value: "
              << return_value;

    return return_value;
}

/**
 * Get information about the character the player choose.
 *
 * @param idx  Index of the character
 *
 * @returns Name and number of frames in corresponding sprite
 */
pair<string, int> CharacterSelectState::get_chars_info(int idx) {
    LOG(INFO)
        << "Starting CharacterSelectState get_chars_info method with idx: "
        << idx;

    vector<string> names = CHARACTERS_NAMES;
    vector<int> frames = CHARATERS_SPRITES_AMOUNT;

    return_value = std::make_pair(names[idx], frames[idx]);
    LOG(INFO)
        << "Ending CharacterSelectState get_chars_info method returning value: "
        << return_value;

    return return_value;
}

/**
 * Get information about players choice about characters and skins.
 *
 * @returns Vector of pairs of strings containing information about
 * characters and skins choosen.
 */
vector<pair<string, string> > CharacterSelectState::export_players() {
    LOG(INFO) << "Starting CharacterSelectState export_players method";

    vector<pair<string, string> > players;

    for (int i = 0; i < N_PLAYERS; i++) {
        int char_sel = current_row[i] * N_COLS + current_column[i];

        if (char_sel >= N_CHARS) {
            LOG(FATAL) << "char_sel is out of bound with value: " << char_sel;
        }
        assert(char_sel < N_CHARS);

        players.push_back(
            std::make_pair(chars[char_sel].get_name(),
                           chars[char_sel].get_skin_name(current_skin[i])));
    }

    return_value = players;
    LOG(INFO)
        << "Ending CharacterSelectState export_players method returning value: "
        << return_value;

    return return_value;
}

/**
 * Process interaction of the player with joystick while
 * choosing character.
 */
void CharacterSelectState::process_input() {
    LOG(INFO) << "Starting CharacterSelectState process_input method";

    InputManager* input_manager = InputManager::get_instance();

    vector<pair<int, int> > joystick_buttons = {
        ii(A, InputManager::A),         ii(B, InputManager::B),
        ii(Y, InputManager::Y),         ii(LEFT, InputManager::LEFT),
        ii(RIGHT, InputManager::RIGHT), ii(UP, InputManager::UP),
        ii(DOWN, InputManager::DOWN),   ii(SELECT, InputManager::SELECT),
        ii(START, InputManager::START), ii(LT, InputManager::LT),
        ii(RT, InputManager::RT)};

    for (int id = 0; id < N_PLAYERS; id++) {
        for (ii button : joystick_buttons) {
            is_key_pressed[id][button.first] =
                input_manager->joystick_button_press(button.second, id);
        }
    }

    LOG(INFO) << "Ending CharacterSelectState process_input method";
}

/**
 * Get slot of character on the board.
 *
 * @param row [510 or 645]
 * @param col [55 or 197 or 395 or 536]
 *
 * @returns pair of ints which indicates the corresponding slot.
 */
pair<int, int> CharacterSelectState::get_slot(int row, int col) {
    LOG(INFO) << "Starting CharacterSelectState get_slot method with row: "
              << row << "and col: " << col;

    vector<int> x = ROWS_X_POSITIONS;
    vector<int> y = ROWS_Y_POSITIONS;

    if ((size_t) col >= x.size()) {
        LOG(FATAL) << "col is out of bound with value: " << col;
    }
    assert((size_t) col < x.size());

    if ((size_t) row >= y.size()) {
        LOG(FATAL) << "char_sel is out of bound with value: " << char_sel;
    }
    assert((size_t) row < y.size());

    return_value = ii(x[col], y[row]);
    LOG(INFO) << "Ending CharacterSelectState get_slot method returning value: "
              << return_value;

    return return_value;

}

/**
 * Not implemented.
 */
void CharacterSelectState::pause() {
}

/**
 * Not implemented.
 */
void CharacterSelectState::resume() {
}
