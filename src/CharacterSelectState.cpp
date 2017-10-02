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
#define N_PLAYERS 4
#define N_BACKGROUNDS 2
#define N_SKINS 4
#define FIRST_PLAYER 0
#define N_COLS 2
#define N_ROWS 4

/**
 * Load all artistic files and initializes board variables based
 * on the stage that was selected
 *
 * @param cselected_stage Name of the stage that was selected.
 */
CharacterSelectState::CharacterSelectState(string cselected_stage) {
    Mix_AllocateChannels(50);

    memset(current_column, 0, sizeof current_column);
    memset(current_row, 0, sizeof current_row);
    memset(current_skin, 0, sizeof current_skin);
    memset(is_character_selected, false, sizeof is_character_selected);

    character_slots = Sprite("character_select/character_slots.png");
    selected_tag = Sprite("character_select/selected.png");
    ready_to_fight = Sprite("character_select/ready_to_fight.png");
    planet_logo = Sprite("character_select/planet.png", 8, FRAME_TIME);
    planet_logo.set_scale(1.5);

    is_ready = false;

    selected_stage = cselected_stage;
    blocked = Sound("menu/sound/cancel.ogg");
    select_sound = Sound("menu/sound/select.ogg");
    changed = Sound("menu/sound/cursor.ogg");

    /**
     * Load backgrounds following standards for file name.
     */
    for (int i = 0; i < N_BACKGROUNDS; i++) {
        background[i] = Sprite("character_select/background_" +
                               std::to_string(i + 1) + ".png");
    }

    /**
     * Load information for players based on standards for file name.
     */
    for (int i = 0; i < N_PLAYERS; i++) {
        name_tag[i] = Sprite("character_select/name_tag_" +
                             std::to_string(i + 1) + ".png");
        player_number[i] =
            Sprite("character_select/number_" + std::to_string(i + 1) + ".png");
    }

    /**
     * Load information for characters based on standards for file name.
     */
    for (int i = 0; i < N_CHARS; i++) {
        chars[i] =
            FighterMenu(get_char_info(i).first, get_char_info(i).second, i < 2);
    }

    name_tag_positions = {ii(91, 145), ii(92, 494), ii(956, 145), ii(955, 494)};
    sprite_position = {ii(125, 32), ii(121, 379), ii(943, 34), ii(956, 381)};
    name_delta = {ii(173, 152), ii(172, 154), ii(102, 153), ii(105, 153)};
    number_delta = {ii(12, 9), ii(93, 9), ii(12, 101), ii(93, 101)};

    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);
}

/**
 * Updates player selection while player move between characters.
 *
 * @param delta Variation of how much the characters player travelled
 */
void CharacterSelectState::update(float delta) {
    process_input();

    InputManager* input_manager = InputManager::get_instance();

    /**
     * Process request for leaving the game.
     */
    if (input_manager->quit_requested()) {
        m_quit_requested = true;
        return;
    }

    /**
     * Process request for going next menu.
     */
    if (is_key_pressed[FIRST_PLAYER][SELECT] or
        (not is_character_selected[FIRST_PLAYER] and is_key_pressed[FIRST_PLAYER][B])) {
        select_sound.play();
        m_quit_requested = true;
        Game::get_instance().push(new StageSelectState());
        return;
    }

    /**
     * Only enable start when all players have selected a character.
     */
    if (all_players_selected()) {
        is_ready = true;
        if (is_key_pressed[FIRST_PLAYER][START] or is_key_pressed[FIRST_PLAYER][A]) {
            select_sound.play();
            vector<pair<string, string> > p = export_players();
            m_quit_requested = true;
            Game::get_instance().push(
                new BattleState(selected_stage, export_players()));
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
                changed.play();
                if (current_column[i] != 0) {
                    current_column[i]--;
                }
            }
            if (is_key_pressed[i][RIGHT]) {
                changed.play();
                if (current_column[i] + 1 < N_COLS) {
                    current_column[i]++;
                }
            }
            if (is_key_pressed[i][UP]) {
                changed.play();
                if (current_row[i] != 0) {
                    current_row[i]--;
                }
            }
            if (is_key_pressed[i][DOWN]) {
                changed.play();
                if (current_row[i] + 1 < N_ROWS) {
                    current_row[i]++;
                }
            }

            /**
             * Reset skin if character changed.
             */
            if (current_column[i] != old_col or current_row[i] != old_row) {
                current_skin[i] = 0;
            }

            /**
             * Change skin.
             */
            if (is_key_pressed[i][LT]) {
                changed.play();
                current_skin[i] = (current_skin[i] - 1 + N_SKINS) % N_SKINS;
            }
            if (is_key_pressed[i][RT]) {
                changed.play();
                current_skin[i] = (current_skin[i] + 1) % N_SKINS;
            }

            /**
             * Select character and lock skin.
             */
            if (is_key_pressed[i][A]) {
                int char_sel = current_row[i] * N_COLS + current_column[i];

                /**
                 * Check if character or skin are unblocked.
                 */
                if (chars[char_sel].is_enabled()) {
                    if (not chars[char_sel].is_skin_available(current_skin[i])) {
                        blocked.play();
                    } else {
                        select_sound.play();
                        chars[char_sel].lock_skin(current_skin[i]);
                        is_character_selected[i] = true;
                    }
                } else {
                    blocked.play();
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

    planet_logo.update(delta);
}

/**
 * Render the board.
 * Render the board with characters options, including all effects.
 */
void CharacterSelectState::render() {
    background[0].render(0, 0);
    planet_logo.render(640 - planet_logo.get_width() / 2, 360 - planet_logo.get_height() / 2);
    background[1].render(0, 0);
    character_slots.render(0, 0);

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
            .render(sprite_position[i].first, sprite_position[i].second, 0, flip);

        /**
         * Render not available skins for not selected characters.
         */
        if (not char_selected.is_skin_available(current_skin[i]) and
            not is_character_selected[i]) {
            char_selected.get_disabled().render(sprite_position[i].first,
                                                sprite_position[i].second, 0, flip);
        }

        char_selected.get_name_text()->set_pos(
            name_tag_positions[i].first + name_delta[i].first,
            name_tag_positions[i].second + name_delta[i].second, true, true);

        ii slot = get_slot(row_selected, col_selected);
        name_tag[i].render(name_tag_positions[i].first,
                           name_tag_positions[i].second);
        char_selected.get_name_text()->render();
        player_number[i].render(slot.first + number_delta[i].first,
                         slot.second + number_delta[i].second);

        /**
         * Mark selected character with skin.
         */
        if (is_character_selected[i]) {
            selected_tag.render(name_tag_positions[i].first,
                                name_tag_positions[i].second, 0, flip);
        }
    }

    if (is_ready) {
        ready_to_fight.render(0, 0);
    }
}

/**
 * Check if all players selected their characters and skins.
 *
 * @returns
 */
bool CharacterSelectState::all_players_selected() {
    for (auto cur : is_character_selected) {
        if (not cur) {
            return false;
        }
    }
    return true;
}

/**
 * Get information about the character the player choose.
 *
 * @param idx  Index of the character
 *
 * @returns Name and number of frames in corresponding sprite
 */
pair<string, int> CharacterSelectState::get_char_info(int idx) {
    vector<string> names = {"blood", "flesh", "hookline", "sinker",
                            "trap",  "trip",  "dusk",     "dawn"};
    vector<int> frames = {12, 8, 8, 7, 4, 4, 7, 5};

    return std::make_pair(names[idx], frames[idx]);
}

/**
 * Get information about players choice about characters and skins.
 *
 * @returns Vector of pairs of strings containing information about
 * characters and skins choosen.
 */
vector<pair<string, string> > CharacterSelectState::export_players() {
    vector<pair<string, string> > players;

    for (int i = 0; i < N_PLAYERS; i++) {
        int char_sel = current_row[i] * N_COLS + current_column[i];
        players.push_back(
            std::make_pair(chars[char_sel].get_name(),
                           chars[char_sel].get_skin_name(current_skin[i])));
    }

    return players;
}

/**
 * Process interaction of the player with joystick while
 * choosing character.
 */
void CharacterSelectState::process_input() {
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
    vector<int> x = {510, 645}, y = {55, 197, 395, 536};
    return ii(x[col], y[row]);
}

/**
 * Not implemented.
 */
void CharacterSelectState::pause() {}

/**
 * Not implemented.
 */
void CharacterSelectState::resume() {}
