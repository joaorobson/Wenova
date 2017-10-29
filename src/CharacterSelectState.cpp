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

#define BACKGROUNDS_SIZE_WIDTH 1280 /**< Unit: px*/
#define BACKGROUNDS_SIZE_HEIGHT 720 /**< Unit: px*/

#define N_COLS 2
#define N_ROWS 4
#define N_PLAYERS 4
#define N_SKINS 4

#define FRAME_TIME 7.5
#define FIRST_PLAYER 0
#define ALLOCATED_CHANNELS 50 /**< Allocated channels for mixing. */

#define PLANET_SPRITE_SCALE 1.5
#define PLANET_SPRITE_AMOUNT 8

#define N_backgrounds_sprites 2
#define CHARATERS_SPRITES_AMOUNT \
    { 12, 8, 8, 7, 4, 4, 7, 5 }
#define CHARACTERS_NAMES \
    { "blood", "flesh", "hookline", "sinker", "trap", "trip", "dusk", "dawn" }

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

#define CHARACTER_SLOTS_PATH "character_select/character_slots.png"
#define SELECTED_TAG_PATH "character_select/selected.png"
#define READY_TO_FIGHT_PATH "character_select/ready_to_fight.png"
#define PLANET_SPRITE_PATH "character_select/planet.png"

#define ROWS_X_POSITIONS \
    { 510, 645 }
#define ROWS_Y_POSITIONS \
    { 55, 197, 395, 536 }

#define NAMES_TAGS_X_POSITIONS_1 91  /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_1 145 /**< Unit: px*/

#define NAMES_TAGS_X_POSITIONS_2 92  /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_2 494 /**< Unit: px*/

#define NAMES_TAGS_X_POSITIONS_3 956 /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_3 145 /**< Unit: px*/

#define NAMES_TAGS_X_POSITIONS_4 955 /**< Unit: px*/
#define NAMES_TAGS_Y_POSITIONS_4 494 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_1 125 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_1 32  /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_2 121 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_2 379 /**< Unit: px*/

#define CHARACTERS_X_POSITIONS_3 943 /**< Unit: px*/
#define CHARACTERS_Y_POSITIONS_3 34  /**< Unit: px*/

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
#define NUMBERS_Y_POSITIONS_DELTAS_1 9  /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_2 93 /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_2 9  /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_3 12  /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_3 101 /**< Unit: px*/

#define NUMBERS_X_POSITIONS_DELTAS_4 93  /**< Unit: px*/
#define NUMBERS_Y_POSITIONS_DELTAS_4 101 /**< Unit: px*/

/**
 * Load all artistic files and initializes board variables based
 * on the stage that was selected
 *
 * @param cselected_stage Name of the stage that was selected.
 */
CharacterSelectState::CharacterSelectState(string cselected_stage) {
#ifndef NDEBUG
    string log_message =
        "Starting CharacterSelectState constructor with cselected_stage: " +
        cselected_stage;
    LOG(DEBUG) << log_message;
#endif

    is_ready = false;
    selected_stage = cselected_stage;

    memset(current_column, 0, sizeof current_column);
    memset(current_row, 0, sizeof current_row);
    memset(current_skin, 0, sizeof current_skin);
    memset(is_character_selected, false, sizeof is_character_selected);

    Mix_AllocateChannels(ALLOCATED_CHANNELS);

    check_constants();
    load_resources();
    initialize_elements_positions();

    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);

    LOG(DEBUG) << "Ending CharacterSelectState constructor";
}

/**
 * Process interaction of the player with joystick while
 * choosing character.
 */
void CharacterSelectState::process_input() {
    LOG(DEBUG) << "Starting CharacterSelectState process_input method";

    InputManager* input_manager = InputManager::get_instance();

    vector<pair<int, int>> joystick_buttons = {
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

    LOG(DEBUG) << "Ending CharacterSelectState process_input method";
}

/**
 * Updates what is seen given on each frame.
 *
 * @param delta_time Time for each frame on playing sprites.
 */
void CharacterSelectState::update(float delta_time) {
#ifndef NDEBUG
    string log_message =
        "Starting CharacterSelectState update method with delta_time: " +
        std::to_string(delta_time);
    LOG(DEBUG) << log_message;
#endif

    handle_exiting();
    handle_menu_interaction();

    play_sprites_animation(delta_time);

    LOG(DEBUG) << "Ending CharacterSelectState update method";
}

/**
 * Render the board.
 * Render the board with characters options, including all effects.
 */
void CharacterSelectState::render() {
    LOG(DEBUG) << "Starting CharacterSelectState update method";

    /**
     * Put backgrounds_sprites, planet_sprite and characters_slots_sprites
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

    LOG(DEBUG) << "Ending CharacterSelectState update method";
}

/**
 * Get information about players choice about characters and skins.
 *
 * @returns Vector of pairs of strings containing information about
 * characters and skins choosen.
 */
vector<pair<string, string>> CharacterSelectState::export_players() {
#ifndef NDEBUG
    LOG(DEBUG) << "Starting CharacterSelectState export_players method";
    string log_message = "";
#endif

    vector<pair<string, string>> players;

    for (int i = 0; i < N_PLAYERS; i++) {
        int char_sel = current_row[i] * N_COLS + current_column[i];

#ifndef NDEBUG
        if (char_sel >= N_CHARS) {
            log_message = "char_sel is out of bound with value: " + char_sel;
            LOG(FATAL) << log_message;
        }
#endif

        players.push_back(
            std::make_pair(chars[char_sel].get_name(),
                           chars[char_sel].get_skin_name(current_skin[i])));
    }

#ifndef NDEBUG
    int count = players.size();
    log_message =
        "Ending CharacterSelectState export_players method returning values: ";

    /*
     * Format log_message like (name1, skin_name1), (name2, skin_name2), ...
     */
    for (auto data : players) {
        string info_pair = '(' + data.first + ", " + data.second + ')';
        log_message += count ? info_pair : info_pair + ", ";
        --count;
    }

    if (not players.size()) {
        LOG(FATAL) << "Players vector must return some element";
    }

    LOG(DEBUG) << log_message;
#endif

    return players;
}

/**
 * Check if all players selected their characters and skins.
 *
 * @returns
 */
bool CharacterSelectState::all_players_selected() {
#ifndef NDEBUG
    LOG(DEBUG) << "Starting CharacterSelectState all_players_selected method";
    string log_message = "";
#endif

    bool return_value;
    for (auto cur : is_character_selected) {
        if (not cur) {
            return_value = false;

#ifndef NDEBUG
            log_message =
                "Ending CharacterSelectState all_players_selected method "
                "returning value: " +
                std::to_string(static_cast<int>(return_value));
            LOG(DEBUG) << log_message;
#endif

            return return_value;
        }
    }

    return_value = true;

#ifndef NDEBUG
    log_message =
        "Ending CharacterSelectState all_players_selected method returning "
        "value: " +
        std::to_string(static_cast<int>(return_value));
    LOG(DEBUG) << log_message;
#endif

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
#ifndef NDEBUG
    string log_message =
        "Starting CharacterSelectState get_chars_info method with idx: " +
        std::to_string(idx);
    LOG(DEBUG) << log_message;
#endif

    vector<string> names = CHARACTERS_NAMES;
    vector<int> frames = CHARATERS_SPRITES_AMOUNT;

#ifndef NDEBUG
    if (names.size() != frames.size()) {
        LOG(FATAL) << "Names array size different of frames array size";
    }
#endif

    pair<string, int> return_value = std::make_pair(names[idx], frames[idx]);

#ifndef NDEBUG
    if (not names.size() or not frames.size()) {
        LOG(FATAL) << "Names and frames arrays must have some element";
    }

    log_message =
        "Ending CharacterSelectState get_chars_info method returning values: " +
        return_value.first + ", " + std::to_string(return_value.second);
    LOG(DEBUG) << log_message;
#endif

    return return_value;
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
#ifndef NDEBUG
    string log_message =
        "Starting CharacterSelectState get_slot method with row: " +
        std::to_string(row) + "and col: " + std::to_string(col);
    LOG(DEBUG) << log_message;
#endif

    vector<int> x = ROWS_X_POSITIONS;
    vector<int> y = ROWS_Y_POSITIONS;

#ifndef NDEBUG
    if ((size_t) col >= x.size()) {
        log_message = "col is out of bound with value: " + std::to_string(col);
        LOG(FATAL) << log_message;
    }

    if ((size_t) row >= y.size()) {
        log_message = "row is out of bound with value: " + std::to_string(row);
        LOG(FATAL) << log_message;
    }
#endif

    pair<int, int> return_value = ii(x[col], y[row]);

#ifndef NDEBUG
    log_message =
        "Ending CharacterSelectState get_slot method returning values: " +
        std::to_string(return_value.first) + ", " +
        std::to_string(return_value.second);
    LOG(DEBUG) << log_message;
#endif

    return return_value;
}

/**
 * Initializes attributes relateds to resources.
 * Understand resources as what is inside of folder res
 */
void CharacterSelectState::load_resources() {
    LOG(DEBUG) << "Starting CharacterSelectState load_resources method";

    characters_slots_sprites = Sprite(CHARACTER_SLOTS_PATH);
    selected_tags_sprites = Sprite(SELECTED_TAG_PATH);
    ready_to_fight_sprite = Sprite(READY_TO_FIGHT_PATH);
    planet_sprite =
        Sprite(PLANET_SPRITE_PATH, PLANET_SPRITE_AMOUNT, FRAME_TIME);
    planet_sprite.set_scale(PLANET_SPRITE_SCALE);

    blocked_sound = Sound(BLOCKED_SOUND_PATH);
    select_sound = Sound(SELECT_SOUND_PATH);
    changed_sound = Sound(CHANGED_SOUND_PATH);

    /**
     * Load backgrounds_sprites following standards for file name.
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

    LOG(DEBUG) << "Ending CharacterSelectState load_resources method";
}

/**
 * Set initial values for elements.
 * This method intend to only start the values for the elements of when
 * choosing character, not render them
 *
 */
void CharacterSelectState::initialize_elements_positions() {
    LOG(DEBUG)
        << "Starting CharacterSelectState initialize_elements_positions method";

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

    LOG(DEBUG)
        << "Ending CharacterSelectState initialize_elements_positions method";
}

/**
 * Verify if constants values are ok.
 */
void CharacterSelectState::check_constants() {
    LOG(DEBUG) << "Starting CharacterSelectState check_constants method";

#ifndef NDEBUG
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

    string log_message = "";
    for (auto x : ROWS_X_POSITIONS) {
        if (x > BACKGROUNDS_SIZE_WIDTH) {
            log_message = "ROWS_X_POSITIONS, element: " + std::to_string(x) +
                "is bigger than screen";
            LOG(FATAL) << log_message;
        }
    }

    for (auto y : ROWS_Y_POSITIONS) {
        if (y > BACKGROUNDS_SIZE_HEIGHT) {
            log_message = "ROWS_Y_POSITIONS, element: " + std::to_string(y) +
                "is bigger than screen";
            LOG(FATAL) << log_message;
        }
    }
#endif

    LOG(DEBUG) << "Ending CharacterSelectState check_constants method";
}

/**
 * Handle all options of leaving this menu.
 * Can be forward or backward
 */
void CharacterSelectState::handle_exiting() {
    LOG(DEBUG) << "Starting CharacterSelectState handle_exiting method";

    process_input();
    InputManager* input_manager = InputManager::get_instance();

    /**
     * Process request for leaving the game.
     */
    if (input_manager->quit_requested()) {
        m_quit_requested = true;

        LOG(DEBUG)
            << "Ending CharacterSelectState update due quit request method";
        return;
    }

    /**
     * Process request for going previous menu (SelectStage).
     */
    if (is_key_pressed[FIRST_PLAYER][SELECT] or
        (not is_character_selected[FIRST_PLAYER] and
         is_key_pressed[FIRST_PLAYER][B])) {
        select_sound.play();
        m_quit_requested = true;
        Game::get_instance().push(new StageSelectState());

        LOG(DEBUG)
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
            vector<pair<string, string>> p = export_players();
            m_quit_requested = true;
            Game::get_instance().push(
                new BattleState(selected_stage, export_players()));

            LOG(DEBUG)
                << "Ending CharacterSelectState update due quit request method";
            return;
        }
    }
    LOG(DEBUG) << "Ending CharacterSelectState handle_exiting method";
}

void CharacterSelectState::handle_menu_interaction() {
    LOG(DEBUG) << "Starting CharacterSelectState handle_exiting method";

    for (int player = 0; player < N_PLAYERS; player++) {
        if (not is_character_selected[player]) {
            handle_random_select(player);
            handle_navigating(player);
            handle_select(player);
        } else {
            /**
             * Unselect character.
             */
            if (is_key_pressed[player][B]) {
                int char_sel =
                    current_row[player] * N_COLS + current_column[player];
                chars[char_sel].unlock_skin(current_skin[player]);

                is_character_selected[player] = false;
                is_ready = false;
            }
        }
    }
    LOG(DEBUG) << "Ending CharacterSelectState handle_menu_interaction method";
}

/**
 * Will handle process of choosing random character and skin.
 *
 * @param player player which will random selected [0, N_PLAYERS - 1]
 */
void CharacterSelectState::handle_random_select(unsigned int player) {
    LOG(DEBUG) << "Starting CharacterSelectState handle_random_select method";

    if (is_key_pressed[player][Y]) {
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

        current_column[player] = rand_col;
        current_row[player] = rand_row;
        current_skin[player] = rand_skin;
    }
    LOG(DEBUG) << "Ending CharacterSelectState handle_random_select method";
}

/**
 * Will handle the player navigating through characters.
 *
 * @param player player which will random selected [0, N_PLAYERS - 1]
 */
void CharacterSelectState::handle_navigating(unsigned int player) {
    string log_message =
        "Starting CharacterSelectState handle_navigating method, player "
        "value: " +
        player;
    LOG(DEBUG) << log_message;

    /**
     * To know if should reset skin to default
     */
    int old_col = current_column[player];
    int old_row = current_row[player];

    /**
     * Navigate through characters
     */
    if (is_key_pressed[player][LEFT]) {
        changed_sound.play();
        if (current_column[player] != 0) {
            current_column[player]--;
        }
    }
    if (is_key_pressed[player][RIGHT]) {
        changed_sound.play();
        if (current_column[player] + 1 < N_COLS) {
            current_column[player]++;
        }
    }
    if (is_key_pressed[player][UP]) {
        changed_sound.play();
        if (current_row[player] != 0) {
            current_row[player]--;
        }
    }
    if (is_key_pressed[player][DOWN]) {
        changed_sound.play();
        if (current_row[player] + 1 < N_ROWS) {
            current_row[player]++;
        }
    }

    /**
     * Reset skin for default if character navigate to other character.
     */
    if (current_column[player] != old_col or current_row[player] != old_row) {
        current_skin[player] = 0;
    }

    /**
     * Navigate through skins.
     */
    if (is_key_pressed[player][LT]) {
        changed_sound.play();
        current_skin[player] = (current_skin[player] - 1 + N_SKINS) % N_SKINS;
    }
    if (is_key_pressed[player][RT]) {
        changed_sound.play();
        current_skin[player] = (current_skin[player] + 1) % N_SKINS;
    }
    LOG(DEBUG) << "Ending CharacterSelectState handle_navigating method";
}

void CharacterSelectState::handle_select(unsigned int player) {
    string log_message =
        "Starting CharacterSelectState handle_select method, player value: " +
        player;
    LOG(DEBUG) << log_message;

    /**
     * Select character and lock skin.
     */
    if (is_key_pressed[player][A]) {
        int char_sel = current_row[player] * N_COLS + current_column[player];

        /**
         * Check if character and skin are unblocked.
         */
        if (chars[char_sel].is_enabled()) {
            if (not chars[char_sel].is_skin_available(current_skin[player])) {
                blocked_sound.play();
            } else {
                select_sound.play();
                chars[char_sel].lock_skin(current_skin[player]);
                is_character_selected[player] = true;
            }
        } else {
            blocked_sound.play();
        }
    }

    LOG(DEBUG) << "Ending CharacterSelectState handle_select method";
}

/**
 * Play sprites for every animated object when choosing charater.
 *
 * @param delta_time Time spent on each frame
 */
void CharacterSelectState::play_sprites_animation(float delta_time) {
    string log_message =
        "Starting CharacterSelectState play_sprites_animation method, "
        "delta_time value: " + std::to_string(delta_time);

    LOG(DEBUG) << log_message;

    for (int i = 0; i < N_CHARS; i++) {
        chars[i].get_disabled().update(delta_time);

        for (int j = 0; j < N_SKINS; j++) {
            chars[i].get_skin(j).update(delta_time);
        }
    }

    planet_sprite.update(delta_time);

    LOG(DEBUG) << "Ending CharacterSelectState play_sprites_animation method";
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
