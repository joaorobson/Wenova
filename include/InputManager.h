/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file InputManager.h
 * Brief Description.
 */

#ifndef INCLUDE_INPUTMANAGER_H_
#define INCLUDE_INPUTMANAGER_H_

#include <algorithm>
#include <map>
#include <unordered_map>
#include <utility>

#include "SDL2/SDL.h"

#define ii std::pair<int, int>

class InputManager {
 private:
    static InputManager* input_manager;

    /**
     * For mouse is not unordered_map because there is only one mouse.
     */
    bool mouse_buttons_states[6];
    int mouse_update[6];

    std::unordered_map<int, bool> joysticks_buttons_states[10];
    std::unordered_map<int, int> joystick_update[10];

    std::unordered_map<int, bool> keys_states;
    std::unordered_map<int, int> keys_updates;

    std::unordered_map<int, int> buttons_maps;
    std::unordered_map<int, int> controllers_id;

    std::unordered_map<int, int> keyboard_to_joystick;

    SDL_GameController* controllers[4];

    bool has_quit_request;
    int update_counter;  ///< Will be incrementes when updating input state,
                         ///< refer to key presses.

    int mouse_x_position; /**< Unit: px */
    int mouse_y_position; /**< Unit: px */

    /**
     * Variations in mouse position in each axis.
     * Unit: px;
     */
    int mouse_delta_x; /**< [0, 1280] */
    int mouse_delta_y; /**< [0, 720] */

    int keyboard_to_joystick_id;  ///< Which profile will be used for mapping
                                  ///< keyboard_for_joystick.
                                  ///< Ex: (Menu handler or gameplay).

    float mouse_sensibility_value; /**< Refer to mouse sensibility. */
    int analogic_sensibility_value = 20000; /**< Refer to joystick lever sensibility. */
    int triggers_sensibility_value =
        32000; /**< Refer to joystick RT and LT (triggers) lever sensibility. */

    /**
     * Manages joystick interaction with the game.
     *
     * @param key_id Id of the key is that is interacting with the game
     * @param state State of the key that is interacting with the game
     */
    void emulate_joystick(int key_id, bool state);

    /**
     * Manages transition of inputs from keyboard to joystick.
     */
    void reset_keyboard_to_joystick();

 public:
    /**
     * Initializes variables.
     */
    InputManager();

    /**
     * Clear states about joystick and keyboard.
     */
    ~InputManager();

    /**
     * Integrates engine's resources with project variables.
     */
    void update();

    /**
     * Manages player presses of the key (keyboard).
     *
     * @param key [0, 14 (number of keys used in the game)]
     *
     * @returns True if everithing went ok. [0,1]
     */
    bool key_press(int key);

    /**
     * Manages player release of the key (keyboard).
     *
     * @param key [0, 14 (number of keys used in the game)]
     *
     * @returns True if everithing went ok. [0,1]
     */
    bool key_release(int key);

    /**
     * Watch holding of the player on the key (keyboard).
     *
     * @param key [0, 14 (number of keys used in the game)]
     *
     * @returns True if key is holded
     */
    bool is_key_down(int key);

    /**
     * Manages player press of a mouse button.
     *
     * @param button which button was pressed [0, 2]
     *
     * @returns True if everything went ok.
     */
    bool mouse_press(int button);

    /**
     * Manages player release of a mouse button.
     * @param button which button was pressed [0, 2]
     *
     * @returns True if everything went ok.
     */
    bool mouse_release(int button);

    /**
     * Watch holding of the player on the button (mouse).
     * @param button
     *
     * @returns True if button is being pressed.
     */
    bool is_mouse_down(int button);

    /**
     * Manages player presses of the button (joystick).
     * @param button Which button is being pressed.
     * @param joystick Which joystick pressed the button.
     *
     * @returns True if everithing went ok. [0,1]
     */
    bool joystick_button_press(int button, int joystick);

    /**
     * Manages player release of the button (joystick).
     *
     * @param button Which button is being released.
     * @param joystick Which joystick is releasing the button.
     *
     * @returns True if everithing went ok. [0,1]
     */
    bool joystick_button_release(int button, int joystick);

    /**
     * Watch holding of the player on the key (keyboard).
     *
     * @param button Which button is holding the button.
     * @param joystick Which joystick is holding the button.
     *
     * @returns True if button is being held.
     */
    bool is_joystick_button_down(int button, int joystick);

    /**
     * Get mouse position in axis X.
     *
     * @returns number respresenting mouse position in axis X.
     * [0,], Unit: px
     */
    int get_mouse_x_position();

    /**
     * Get mouse position in axis Y.
     *
     * @returns number respresenting mouse position in axis Y. [0,]
     */
    int get_mouse_y_position();

    /**
     * Manages player's request for leaving the game.
     *
     * @returns True if there is a request [0,1]
     */
    bool quit_requested();

    /**
     * Get instance of InputManage.
     * Creates if not exists
     *
     * @returns Instance of InputManager.
     */
    static InputManager* get_instance();

    /**
     * Configure mouse scale to calibrae sensibility.
     * Bigger the values, more sensible the mouse will be
     *
     * @param cmouse_sensibility_value Unit: px, [0,]
     * @param cmouse_delta_x Unit: px, [0,]
     * @param cmouse_delta_y Unit: px, [0,]
     */
    void set_mouse_sensibility_value(float mouse_sensibility_value, int mouse_delta_x, int mouse_delta_y);

    /**
     * Set value for joystick hand crank.
     *
     * @param value
     */
    void set_analogic_sensibility_value(int value);

    /**
     * Manages connection of joysticks to the game.
     */
    void connect_joysticks();

    /**
     * Translate keyboard keys to the joystick buttons.
     *
     * @param map_id Represents if command is for gameplay or menus handle
     */
    void map_keyboard_to_joystick(int map_id = 0);

    // joystick keys
    static const int UP = SDL_CONTROLLER_BUTTON_DPAD_UP;
    static const int RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
    static const int DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
    static const int LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
    static const int A = SDL_CONTROLLER_BUTTON_A;
    static const int B = SDL_CONTROLLER_BUTTON_B;
    static const int X = SDL_CONTROLLER_BUTTON_X;
    static const int Y = SDL_CONTROLLER_BUTTON_Y;
    static const int LB = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
    static const int RB = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    static const int LT = 0x20;
    static const int RT = 0x21;  // Valor arbitrário, mas tá certo
    static const int SELECT = SDL_CONTROLLER_BUTTON_BACK;
    static const int START = SDL_CONTROLLER_BUTTON_START;
    static const int L3 = SDL_CONTROLLER_BUTTON_LEFTSTICK;
    static const int R3 = SDL_CONTROLLER_BUTTON_RIGHTSTICK;

    // keys for battle
    static const int K_UP = SDLK_w;
    static const int K_RIGHT = SDLK_d;
    static const int K_DOWN = SDLK_s;
    static const int K_LEFT = SDLK_a;
    static const int K_A = SDLK_SPACE;  // jump
    static const int K_B = SDLK_k;  // skill 1
    static const int K_X = SDLK_h;  // attack
    static const int K_Y = SDLK_r;  // ultimate
    static const int K_LB = SDLK_j;  // defense
    static const int K_RB = SDLK_l;  // skill 2
    static const int K_LT = SDLK_COMMA;  // change skin left
    static const int K_RT = SDLK_PERIOD;  // change skin right
    static const int K_SELECT = SDLK_ESCAPE;  // cancel / back
    static const int K_START = SDLK_RETURN;  // confirm / start
    static const int ENTER_KEY = SDLK_RETURN;  // confirm / start
    static const int K_RANDOM = SDLK_u;  // random
    static const int RIGHT_MOUSE_BUTTON = SDL_BUTTON_RIGHT;
    static const int LEFT_MOUSE_BUTTON = SDL_BUTTON_LEFT;
    static const int K_L3 = SDLK_COMMA;
    static const int K_R3 = SDLK_PERIOD;

    // keys for menus
    static const int K_MENU_A = SDLK_h;
    static const int K_MENU_B = SDLK_j;
    static const int K_MENU_Y = SDLK_u;
    static const int K_MENU_LB = SDLK_y;

    // keys for edit mode
    static const int K_ARROW_UP = SDLK_UP;
    static const int K_ARROW_RIGHT = SDLK_RIGHT;
    static const int K_ARROW_DOWN = SDLK_DOWN;
    static const int K_ARROW_LEFT = SDLK_LEFT;
    static const int K_CTRL = SDLK_LCTRL;
    static const int K_C = SDLK_c;
    static const int K_S = SDLK_s;
    static const int K_F = SDLK_f;
    static const int K_P = SDLK_p;
    static const int K_O = SDLK_o;
    static const int K_SHIFT = SDLK_LSHIFT;
    static const int K_ROT_LEFT = SDLK_z;
    static const int K_ROT_RIGHT = SDLK_x;
    static const int K_ROT_RESET = SDLK_r;
    static const int K_INC_W = SDLK_PERIOD;
    static const int K_DEC_W = SDLK_COMMA;
    static const int K_DEL = SDLK_DELETE;

    static const int MENU_MODE = 0;
    static const int BATTLE_MODE = 1;
};

#endif  // INCLUDE_INPUTMANAGER_H_
