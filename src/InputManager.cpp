/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file InputManager.cpp
 * Implements methods of class InputManager.
 */

/**
 * Commented debugs should be used with extreme care because it causes
 * extremelly lose of performance and giant log files.
 */

#include "InputManager.h"

#include "Game.h"

#include <SDL2/SDL_render.h>
#include <cstring>
#include <ctime>

#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 720

#define DEFAULT_ANALOGIC_SENSIBILITY 20000
#define DEFAULT_TRIGGERS_SENSIBILITY 3200

#define FIRST_TIME 1492356064

InputManager *InputManager::input_manager;

/**
 * Initializing static variables.
 * For comments look header file.
 */
/**
 * Joysitck keys.
 */
const int InputManager::UP;
const int InputManager::RIGHT;
const int InputManager::DOWN;
const int InputManager::LEFT;
const int InputManager::A;
const int InputManager::B;
const int InputManager::X;
const int InputManager::Y;
const int InputManager::LB;
const int InputManager::RB;
const int InputManager::LT;
const int InputManager::RT;
const int InputManager::L3;
const int InputManager::R3;

/**
 * Keys for battle.
 */
const int InputManager::K_UP;
const int InputManager::K_RIGHT;
const int InputManager::K_DOWN;
const int InputManager::K_LEFT;
const int InputManager::K_A;
const int InputManager::K_B;
const int InputManager::K_X;
const int InputManager::K_Y;
const int InputManager::K_LB;
const int InputManager::K_RB;
const int InputManager::K_LT;
const int InputManager::K_RT;
const int InputManager::K_SELECT;
const int InputManager::K_START;
const int InputManager::ENTER_KEY;
const int InputManager::K_RANDOM;
const int InputManager::RIGHT_MOUSE_BUTTON;
const int InputManager::LEFT_MOUSE_BUTTON;
const int InputManager::K_L3;
const int InputManager::K_R3;

/**
 * Keys for menus.
 */
const int InputManager::K_MENU_A;
const int InputManager::K_MENU_B;
const int InputManager::K_MENU_Y;
const int InputManager::K_MENU_LB;
const int InputManager::SELECT;
const int InputManager::START;

/**
 * Keys for edit mode.
 */
const int InputManager::K_ARROW_UP;
const int InputManager::K_ARROW_RIGHT;
const int InputManager::K_ARROW_DOWN;
const int InputManager::K_ARROW_LEFT;
const int InputManager::K_CTRL;
const int InputManager::K_C;
const int InputManager::K_S;
const int InputManager::K_F;
const int InputManager::K_P;
const int InputManager::K_O;
const int InputManager::K_SHIFT;
const int InputManager::K_ROT_LEFT;
const int InputManager::K_ROT_RIGHT;
const int InputManager::K_ROT_RESET;
const int InputManager::K_INC_W;
const int InputManager::K_DEC_W;
const int InputManager::K_DEL;

/**
 * Modes.
 */
const int InputManager::MENU_MODE;
const int InputManager::BATTLE_MODE;

/**
 * Initializes variables.
 */
InputManager::InputManager() {
    // LOG(DEBUG) << "Starting InputManager constructor";

    memset(mouse_buttons_states, false, sizeof mouse_buttons_states);
    memset(mouse_update, 0, sizeof mouse_update);

    this->analogic_sensibility_value = DEFAULT_ANALOGIC_SENSIBILITY;
    this->triggers_sensibility_value = DEFAULT_TRIGGERS_SENSIBILITY;

    keyboard_to_joystick_id = 0;
    map_keyboard_to_joystick(keyboard_to_joystick_id);

    /**
     * Start controllers with nullptr.
     */
    for (int i = 0; i < N_CONTROLLERS; i++) {
        controllers[i] = nullptr;
    }

    has_quit_request = false;
    update_counter = 0;
    mouse_x_position = 0;
    mouse_y_position = 0;

    // LOG(DEBUG) << "Ending InputManager constructor";
}

/**
 * Clear states about joystick and keyboard.
 */
InputManager::~InputManager() {
    // LOG(DEBUG) << "Starting InputManager constructor";

    /**
     * Clear joystick data.
     */
    for (int i = 0; i < N_CONTROLLERS; i++) {
        joysticks_buttons_states[i].clear();
        joystick_update[i].clear();
    }
    keyboard_to_joystick.clear();
    keys_states.clear();
    keys_updates.clear();

    // LOG(DEBUG) << "Ending InputManager destructor";
}

/**
 * Get instance of InputManage.
 * Creates if not exists
 *
 * @returns Instance of InputManager.
 */
InputManager *InputManager::get_instance() {
    // LOG(DEBUG) << "Starting InputManager get_instance method";

    if (input_manager == nullptr) {
        input_manager = new InputManager();
    }

    // LOG(DEBUG) << "Ending InputManager get_instance method";
    return input_manager;
}

/**
 * Get mouse position in axis X.
 *
 * @returns number respresenting mouse position in axis X.
 * [0,], Unit: px
 */
int InputManager::get_mouse_x_position() {
    // LOG(DEBUG) << "Starting InputManager get_mouse_x_position method";

    int return_value = mouse_x_position;

    /*
    #ifndef NDEBUG
    std::string log_message = "Ending InputManager get_mouse_x_position method
    returning value: " + std::to_string(return_value);
    // LOG(DEBUG) << log_message;

    if (return_value > BACKGROUND_WIDTH or return_value < 0) {
        LOG(FATAL) << "Mouse is out of screen!";
    }
    #endif
    */

    return return_value;
}

/**
 * Get mouse position in axis Y.
 *
 * @returns number respresenting mouse position in axis Y. [0,]
 */
int InputManager::get_mouse_y_position() {
    // LOG(DEBUG) << "Starting InputManager get_mouse_y_position method";

    int return_value = mouse_y_position;

    /*
    #ifndef NDEBUG
    std::string log_message = "Ending InputManager get_mouse_y_position method
    returning value: " + std::to_string(return_value);
    // LOG(DEBUG) << log_message;

    if (return_value > BACKGROUND_HEIGHT or return_value < 0) {
        LOG(FATAL) << "Mouse is out of screen!";
    }
    #endif
    */

    return return_value;
}

/**
 * Configure mouse scale to calibrate sensibility.
 * Bigger the values, more sensible the mouse will be. Util for when
 * resizing the screen
 *
 * @param cmouse_sensibility_value Unit: px, [0,]
 * @param coffset_x Unit: px, [0,]
 * @param coffset_y Unit: px, [0,]
 */
void InputManager::set_mouse_sensibility_value(float cmouse_sensibility_value,
                                               int coffset_x, int coffset_y) {
    /*
    #ifndef NDEBUG
    char log_message_c[80];
    snprintf(log_message_c, sizeof(log_message_c), "Starting InputManager
    set_mouse_sensibility_value method with value: %.2f",
    cmouse_sensibility_value);
    std::string log_message(log_message_c);

    log_message += ", coffset_x: " + std::to_string(coffset_x);
    log_message += ", coffset_y: " + std::to_string(coffset_y);

    // LOG(DEBUG) << log_message;
    #endif
    */

    mouse_sensibility_value = cmouse_sensibility_value;

    offset_x = coffset_x;
    offset_y = coffset_y;

    // LOG(DEBUG) << "Ending InputManager set_mouse_sensibility_value method";
}

/**
 * Set value for joystick hand crank.
 *
 * @param value
 */
void InputManager::set_analogic_sensibility_value(int value) {
    /*
    #ifndef NDEBUG
    string log_message = "Starting InputManager set_analogic_sensibility_value
    method, with value: " + value;
    // LOG(DEBUG) << log_message;
    #endif
    */

    analogic_sensibility_value = value;

    // LOG(DEBUG) << "Ending InputManager set_mouse_sensibility_value method";
}

/**
 * Manages connection of joysticks to the game.
 */
void InputManager::connect_joysticks() {
    // LOG(DEBUG) << "Starting InputManager connect_joysticks method";

    /**
     * Max number of joysticks can be only four.
     */
    int max = SDL_NumJoysticks();
    if (max > N_CONTROLLERS) {
        max = N_CONTROLLERS;
    }
    int n_controller = 0;

    /**
     * To reset connections.
     */
    for (int i = 0; i < max; i++) {
        if (controllers[i] != nullptr) {
            SDL_GameControllerClose(controllers[i]);
            controllers[i] = nullptr;
        }
    }

    /**
     * Detect compability for joystick connected.
     */
    for (int i = 0; i < max; i++) {
        char guid[64];
        SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(i), guid,
                                  sizeof(guid));

        if (SDL_IsGameController(i)) {
            controllers[i] = SDL_GameControllerOpen(i);

            SDL_Joystick *j = SDL_GameControllerGetJoystick(controllers[i]);
            int instance_id = SDL_JoystickInstanceID(j);
            printf("Controller %d (%d real) connected\n", i, instance_id);

            controllers_id[instance_id] = i;
            n_controller++;
        } else {
            LOG(WARNING) << "Joystick is not a game controller";

            SDL_JoystickOpen(i);
        }
    }

    // LOG(DEBUG) << "Ending InputManager connect_joysticks method";
}

/**
 * Translate keyboard keys to the joystick buttons.
 *
 * @param map_id Represents if command is for gameplay or menus handle
 */
void InputManager::map_keyboard_to_joystick(int map_id) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager map_keyboard_to_joystick
    method with map_id: " + std::to_string(map_id);
    // LOG(DEBUG) << log_message;
    #endif
    */

    keyboard_to_joystick = {
        {K_LEFT, LEFT + 1},     {K_RIGHT, RIGHT + 1}, {K_UP, UP + 1},
        {K_DOWN, DOWN + 1},     {K_A, A + 1},         {K_B, B + 1},
        {K_X, X + 1},           {K_Y, Y + 1},         {K_LB, LB + 1},
        {K_RB, RB + 1},         {K_LT, LT + 1},       {K_RT, RT + 1},
        {K_SELECT, SELECT + 1}, {K_START, START + 1}, {K_L3, L3 + 1},
        {K_R3, R3 + 1}};

    if (map_id == MENU_MODE) {
        keyboard_to_joystick[K_A] = 0;
        keyboard_to_joystick[K_B] = 0;
        keyboard_to_joystick[K_Y] = 0;
        keyboard_to_joystick[K_LB] = 0;
        keyboard_to_joystick[K_MENU_A] = A + 1;
        keyboard_to_joystick[K_MENU_B] = B + 1;
        keyboard_to_joystick[K_MENU_Y] = Y + 1;
        keyboard_to_joystick[K_MENU_LB] = LB + 1;
    }

    // LOG(DEBUG) << "Ending InputManager map_keyboard_to_joystick method";
}

/**
 * Integrates engine's resources with project variables.
 */
void InputManager::update() {
    // LOG(DEBUG) << "Starting InputManager update method";

    handle_mouse_update();

    update_counter++;
    has_quit_request = false;

    handle_events();

    // LOG(DEBUG) << "Ending InputManager update method";
}

/**
 * Manages player's request for leaving the game.
 *
 * @returns True if there is a request [0,1]
 */
bool InputManager::quit_requested() {
    // LOG(DEBUG) << "Starting InputManager quit_requested method";

    // LOG(DEBUG) << "Ending InputManager quit_requested method";
    return has_quit_request;
}

/**
 * Manages transition of inputs from keyboard to joystick.
 */
/**
 * Manages player presses of the key (keyboard).
 *
 * @param key [0, 14 (number of keys used in the game)]
 *
 * @returns True if everithing went ok. [0,1]
 */
bool InputManager::key_press(int key) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager key_press method key: " +
    std::to_string(key);
    // LOG(DEBUG) << log_message;

    if (key < 0) {
        LOG(FATAL) << "Key is less than zero";
    }
    #endif
    */

    bool return_value =
        keys_states[key] and keys_updates[key] == update_counter;

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager key_press method returning value: " +
    std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Manages player release of the key (keyboard).
 *
 * @param key [0, 14 (number of keys used in the game)]
 *
 * @returns True if everithing went ok. [0,1]
 */
bool InputManager::key_release(int key) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager key_release method key: " +
    std::to_string(key);
    // LOG(DEBUG) << log_message;

    if (key < 0) {
        LOG(FATAL) << "Key is less than zero";
    }
    #endif
    */

    bool return_value =
        not keys_states[key] and keys_updates[key] == update_counter;

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager key_release method returning value: " +
    std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Watch holding of the player on the key (keyboard).
 *
 * @param key [0, 14 (number of keys used in the game)]
 *
 * @returns True if key is holded
 */
bool InputManager::is_key_down(int key) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager key_release method key: " +
    std::to_string(key);
    // LOG(DEBUG) << log_message;

    if (key < 0) {
        LOG(FATAL) << "Key is less than zero";
    }
    #endif
    */

    bool return_value = keys_states[key];

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager is_key_down method returning value: " +
    std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Manages player press of a mouse button.
 *
 * @param button which button was pressed [0, 5]
 *
 * @returns True if everything went ok.
 */
bool InputManager::mouse_press(int button) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager mouse_press method, button:
    " + std::to_string(button);;
    // LOG(DEBUG) << log_message;

    if (button < 0) {
        LOG(FATAL) << "button is less than zero";
    }

    if (button >= N_MOUSE_BUTTONS) {
        LOG(FATAL) << "button bigger than available";
    }
    #endif
    */

    bool return_value =
        mouse_buttons_states[button] and mouse_update[button] == update_counter;

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager key_release method returning value: " +
    std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Manages player release of a mouse button.
 * @param button which button was pressed [0, 2]
 *
 * @returns True if everything went ok.
 */
bool InputManager::mouse_release(int button) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager mouse_release method,
    button: " + std::to_string(button);;
    // LOG(DEBUG) << log_message;

    if (button < 0) {
        LOG(FATAL) << "button is less than zero";
    }

    if (button >= N_MOUSE_BUTTONS) {
        LOG(FATAL) << "button bigger than available";
    }
    #endif
    */

    bool return_value = not mouse_buttons_states[button] and
        mouse_update[button] == update_counter;

    /*
    #ifndef NDEBUG
    log_message =  "Ending InputManager mouse_release method returning value: "
    + std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Watch holding of the player on the button (mouse).
 * @param button
 *
 * @returns True if button is being pressed.
 */
bool InputManager::is_mouse_down(int button) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager is_mouse_down method,
    button: " + std::to_string(button);;
    // LOG(DEBUG) << log_message;

    if (button < 0) {
        LOG(FATAL) << "button is less than zero";
    }

    if (button >= N_MOUSE_BUTTONS) {
        LOG(FATAL) << "button bigger than available";
    }
    #endif
    */

    bool return_value = mouse_buttons_states[button];

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager is_mouse_down method returning value: " +
    std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Manages player presses of the button (joystick).
 * @param button Which button is being pressed.
 * @param joystick Which joystick pressed the button.
 *
 * @returns True if everithing went ok. [0,1]
 */
bool InputManager::joystick_button_press(int button, int joystick) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager joystick_button_press
    method, button: ";
    log_message += std::to_string(button);
    log_message += ", joystick: " + std::to_string(joystick);
    // LOG(DEBUG) << log_message;

    if (button < 0 or joystick < 0) {
        LOG(FATAL) << "button or joystick less than 0";
    }

    if (joystick >= N_CONTROLLERS) {
        LOG(FATAL) << "joystick bigger than available";
    }
    #endif
    */

    bool return_value = joysticks_buttons_states[joystick][button] and
        joystick_update[joystick][button] == update_counter;

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager joystick_button_press method returning
    value: " + std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Manages player release of the button (joystick).
 *
 * @param button Which button is being released.
 * @param joystick Which joystick is releasing the button.
 *
 * @returns True if everithing went ok. [0,1]
 */
bool InputManager::joystick_button_release(int button, int joystick) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager joystick_button_press
    method, button: ";
    log_message += std::to_string(button);
    log_message += ", joystick: " + std::to_string(joystick);
    // LOG(DEBUG) << log_message;

    if (button < 0 or joystick < 0) {
        LOG(FATAL) << "button or joystick less than 0";
    }

    if (joystick >= N_CONTROLLERS) {
        LOG(FATAL) << "joystick bigger than available";
    }
    #endif
    */

    bool return_value = not joysticks_buttons_states[joystick][button] and
        joystick_update[joystick][button] == update_counter;

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager joystick_button_press method returning
    value: " + std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Watch holding of the player on the key (keyboard).
 *
 * @param button Which button is holding the button.
 * @param joystick Which joystick is holding the button.
 *
 * @returns True if button is being held.
 */
bool InputManager::is_joystick_button_down(int button, int joystick) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager joystick_button_press
    method, button: ";
    log_message += std::to_string(button);
    log_message += ", joystick: " + std::to_string(joystick);
    // LOG(DEBUG) << log_message;

    if (button < 0 or joystick < 0) {
        LOG(FATAL) << "button or joystick less than 0";
    }

    if (joystick >= N_CONTROLLERS) {
        LOG(FATAL) << "joystick bigger than available";
    }
    #endif
    */

    bool return_value = joysticks_buttons_states[joystick][button];

    /*
    #ifndef NDEBUG
    log_message = "Ending InputManager joystick_button_press method returning
    value: " + std::to_string(static_cast<int>(return_value));
    // LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Manages joystick interaction with the game.
 * Map joystick keys to interect with the game through keyboard keys.
 *
 * @param key_id Id of the key is that is interacting with the game
 * @param state State of the key that is interacting with the game
 */
void InputManager::emulate_joystick(int key_id, bool state) {
    /*
    #ifndef NDEBUG
    std::string log_message = "Starting InputManager emulate_joystick method
    with key_id: ";
    log_message += std::to_string(key_id) + ", state: ";
    log_message += std::to_string(static_cast<int>(state));
    // LOG(DEBUG) << log_message;
    #endif
    */

    if (state) {
        /**
         * Map each key for corresponding.
         */
        switch (key_id) {
            case SDLK_0:
                reset_keyboard_to_joystick();
                keyboard_to_joystick_id = -1;
                break;
            case SDLK_1:
                reset_keyboard_to_joystick();
                keyboard_to_joystick_id = 0;
                break;
            case SDLK_2:
                reset_keyboard_to_joystick();
                keyboard_to_joystick_id = 1;
                break;
            case SDLK_3:
                reset_keyboard_to_joystick();
                keyboard_to_joystick_id = 2;
                break;
            case SDLK_4:
                reset_keyboard_to_joystick();
                keyboard_to_joystick_id = 3;
                break;
            case SDLK_5:
                reset_keyboard_to_joystick();
                keyboard_to_joystick_id = 4;
                break;
        }
    }

    /**
     * Will update status for joystick based on profile.
     */
    if (keyboard_to_joystick_id == N_CONTROLLERS) {
        for (int i = 0; i < N_CONTROLLERS; i++) {
            joysticks_buttons_states[i][keyboard_to_joystick[key_id] - 1] =
                state;
            joystick_update[i][keyboard_to_joystick[key_id] - 1] =
                update_counter;
        }
    } else if (keyboard_to_joystick_id >= 0) {
        joysticks_buttons_states[keyboard_to_joystick_id]
                                [keyboard_to_joystick[key_id] - 1] = state;
        joystick_update[keyboard_to_joystick_id]
                       [keyboard_to_joystick[key_id] - 1] = update_counter;
    }

    // LOG(DEBUG) << "Ending InputManager connect_joysticks method";
}

void InputManager::reset_keyboard_to_joystick() {
    // LOG(DEBUG) << "Starting InputManager reset_keyboard_to_joystick";

    /**
     * Check limits.
     */
    if (keyboard_to_joystick_id < 0 or
        keyboard_to_joystick_id > N_CONTROLLERS) {
        /*
        #ifndef NDEBUG
        string log_message = "keyboard_to_joystick_id out of bound with value: "
        + keyboard_to_joystick_id;
        LOG(FATAL) << log_message;
        #endif
        */

        return;
    }

    /**
     * Update all joysticks state based on profile.
     */
    if (keyboard_to_joystick_id == N_CONTROLLERS) {
        for (int i = 0; i < N_CONTROLLERS; i++) {
            for (auto &c : joysticks_buttons_states[i]) {
                c.second = false;
            }
        }
    }

    /**
     * Guess is not necessary.
     * Else?
     */
    for (auto &c : joysticks_buttons_states[keyboard_to_joystick_id]) {
        c.second = false;
    }

    // LOG(DEBUG) << "Ending InputManager reset_keyboard_to_joystick method";
}

/**
 * Handle updates specific for mouse.
 */
void InputManager::handle_mouse_update() {
    SDL_GetMouseState(&mouse_x_position, &mouse_y_position);

    /*
    #ifndef NDEBUG
    if (mouse_x_position > BACKGROUND_WIDTH) {
        LOG(FATAL) << "mouse_x_position out of screen";
    }

    if (mouse_y_position > BACKGROUND_HEIGHT) {
        LOG(FATAL) << "mouse_y_position out of screen";
    }
    #endif
    */

    mouse_x_position = mouse_x_position * mouse_sensibility_value + offset_x;
    mouse_y_position = mouse_y_position * mouse_sensibility_value + offset_y;

    mouse_x_position = std::max(0, mouse_x_position);
    mouse_x_position = std::min(mouse_x_position, BACKGROUND_WIDTH);
    mouse_y_position = std::max(0, mouse_y_position);
    mouse_y_position = std::min(mouse_y_position, BACKGROUND_HEIGHT);
}

/**
 * Handle events from inputs.
 */
void InputManager::handle_events() {
    SDL_Event event;

    /**
     * While proper event has not yet been found.
     * Maybe can be removed if removed breaks for cases. Not sure.
     */
    while (SDL_PollEvent(&event)) {
        int key_id;    /**< key is used for keyboard */
        int button_id; /**< button is used for mouse and joystick */
        int joystick_id = controllers_id[event.cdevice.which];

        /**
         * Map events.
         * Will map events from project variables to engine commands. Following
         * cases will map keys to engine commands or connections and
         * disconnections.
         */
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat) {
                    break;
                }
                key_id = event.key.keysym.sym;
                keys_states[key_id] = true;
                keys_updates[key_id] = update_counter;
                emulate_joystick(key_id, true);
                break;

            case SDL_KEYUP:
                key_id = event.key.keysym.sym;
                keys_states[key_id] = false;
                keys_updates[key_id] = update_counter;
                emulate_joystick(key_id, false);
                break;

            case SDL_MOUSEBUTTONDOWN:
                button_id = event.button.button;
                mouse_buttons_states[button_id] = true;
                mouse_update[button_id] = update_counter;
                break;

            case SDL_MOUSEBUTTONUP:
                button_id = event.button.button;
                mouse_buttons_states[button_id] = false;
                mouse_update[button_id] = update_counter;
                break;

            case SDL_JOYAXISMOTION:
                break;

            case SDL_CONTROLLERAXISMOTION:
                if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                    joysticks_buttons_states[joystick_id][RIGHT] =
                        event.caxis.value > analogic_sensibility_value;
                    joysticks_buttons_states[joystick_id][LEFT] =
                        event.caxis.value < -analogic_sensibility_value;
                    joystick_update[joystick_id][RIGHT] = update_counter;
                    joystick_update[joystick_id][LEFT] = update_counter;
                } else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                    joysticks_buttons_states[joystick_id][DOWN] =
                        event.caxis.value > analogic_sensibility_value;
                    joysticks_buttons_states[joystick_id][UP] =
                        event.caxis.value < -analogic_sensibility_value;
                    joystick_update[joystick_id][DOWN] = update_counter;
                    joystick_update[joystick_id][UP] = update_counter;
                } else if (event.caxis.axis ==
                           SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
                    joysticks_buttons_states[joystick_id][LT] =
                        event.caxis.value > triggers_sensibility_value;
                    joystick_update[joystick_id][LT] = update_counter;
                } else if (event.caxis.axis ==
                           SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
                    joysticks_buttons_states[joystick_id][RT] =
                        event.caxis.value > triggers_sensibility_value;
                    joystick_update[joystick_id][RT] = update_counter;
                }

                break;

            case SDL_JOYBUTTONDOWN:
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                button_id = event.cbutton.button;
                joysticks_buttons_states[joystick_id][button_id] = true;
                joystick_update[joystick_id][button_id] = update_counter;
                break;

            case SDL_JOYBUTTONUP:
                break;

            case SDL_CONTROLLERDEVICEADDED:
                connect_joysticks();
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                connect_joysticks();
                break;

            case SDL_CONTROLLERBUTTONUP:
                button_id = event.cbutton.button;
                joysticks_buttons_states[joystick_id][button_id] = false;
                joystick_update[joystick_id][button_id] = update_counter;
                break;

            case SDL_QUIT:
                has_quit_request = true;
                break;

            default:
                break;
        }
    }
}
