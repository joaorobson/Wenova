/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file EditableFloor.cpp
 * Implements class EditableFloor methods.
 */

/**
 * Commented debugs should be used with extreme care because it causes
 * extremelly lose of performance and giant log files.
 */

#include "EditableFloor.h"

#include "Collision.h"
#include "InputManager.h"
#include "Rectangle.h"

#include <cstdio>

#define BACKGROUND_WIDTH 1280
#define BACKGROUND_HEIGHT 720

#define RESIZING_SPEED 0.005
#define ROTATING_SPEED 0.01
#define MOVE_SPEED 0.5

#define ACCELERATION 1
#define MAXIMUM_ACCELERATION 4
#define ACCELERATION_INCREASE_STEP 0.2

#define RIGID_PLATFORM_PATH "edit_state/floor/editable_floor.png"
#define CROSSINGABLE_PLATFORM_PATH "edit_state/floor/editable_platform.png"
#define SELECTED_CROSSINGABLE_PLATFORM_PATH \
    "edit_state/floor/selected_editable_floor.png"

#define DEBUG_SIZE 500
#define FILL_MISSING_PIXELS_DEBUGRMATIONS 15

#define LAYER 0
#define FLOOR_INITIAL_WIDTH 100
#define PI 3.14159265358979
#define PI_DEGREES 180

/**
 * Create box with default width of 100px.
 *
 * @param x Position in X axis. Unit: px, [0,screen_width]
 * @param y Position in Y axis. Unit: px, [0,screen_height]
 * @param crotation Unit: degrees
 * @param cplatform [0,1]
 */
EditableFloor::EditableFloor(float x, float y, float crotation, bool cplatform)
    : Floor(x, y, FLOOR_INITIAL_WIDTH, crotation, cplatform),
      standard_sprite(Sprite(RIGID_PLATFORM_PATH)),
      platform_sprite(Sprite(CROSSINGABLE_PLATFORM_PATH)),
      selected_sprite(Sprite(SELECTED_CROSSINGABLE_PLATFORM_PATH)) {
#ifndef NDEBUG
    std::string log_message = "Starting EditableFloor constructor with x: ";
    log_message += std::to_string(x) + ", y: " + std::to_string(y);
    log_message += ", crotation: " + std::to_string(crotation);
    log_message +=
        ", cplatfrom: " + std::to_string(static_cast<int>(cplatform));

    LOG(DEBUG) << log_message;
#endif

    box = Rectangle(x, y, standard_sprite.get_width(),
                    standard_sprite.get_height());

    is_deleted = false;
    is_selected = false;

    LOG(DEBUG) << "Ending EditableFloor constructor";
}

/**
 * Create box with specific width.
 *
 * @param x Position in X axis. Unit: px, [0,screen_width]
 * @param y Position in Y axis. Unit: px, [0,screen_height]
 * @param width Unit: px, [0,]
 * @param crotation Unit: degrees
 * @param cplatform [0,1]
 */
EditableFloor::EditableFloor(float x, float y, float width, float crotation,
                             bool cplatform)
    : EditableFloor(x, y, crotation, cplatform) {
#ifndef NDEBUG
    std::string log_message = "Starting EditableFloor constructor with x: ";
    log_message += std::to_string(x) + ", y: " + std::to_string(y);
    log_message += ", width:" + std::to_string(width);
    log_message += ", crotation: " + std::to_string(crotation);
    log_message +=
        ", cplatfrom: " + std::to_string(static_cast<int>(cplatform));
    LOG(DEBUG) << log_message;

    if (x <= BACKGROUND_WIDTH) {
        /* Nothing to do. */
    } else {
        LOG(FATAL) << "platform is out of screen in axis x";
    }

    if (x <= BACKGROUND_WIDTH) {
        /* Nothing to do. */
    } else {
        LOG(FATAL) << "platform is out of screen in axis y";
    }
#endif

    standard_sprite.set_scale_x(width / standard_sprite.get_width());
    platform_sprite.set_scale_x(width / platform_sprite.get_width());
    selected_sprite.set_scale_x(width / selected_sprite.get_width());

    box.width = standard_sprite.get_width();

    LOG(DEBUG) << "Ending EditableFloor init";
}

/**
 * Not implemented.
 */
EditableFloor::~EditableFloor() {
}

/**
 * Get information about many aspects of an box.
 *
 * @returns String in format: "x y width rotated level is_crossingable?"
 */
string EditableFloor::get_information() {
    LOG(DEBUG) << "Starting EditableFloor get_information";

    char info_c[DEBUG_SIZE];
    snprintf(info_c, sizeof(info_c), "%f %f %f %f %d", box.x, box.y, box.width,
             rotation * PI_DEGREES / PI, static_cast<int>(is_crossingable));

    string info(info_c);

    for (auto &c : info) {
        c += FILL_MISSING_PIXELS_DEBUGRMATIONS;
    }

    string return_value = info;

    /*
     * Check if string reallyhas the elements.
     * info == info_c for sure
     */
    float float1, float2, float3, float4;
    int int1;
    if (sscanf(info_c, "%f %f %f %f %d", &float1, &float2, &float3, &float4,
               &int1) == 5) {
        /* Nothing to do. */
    } else {
        LOG(WARNING) << "Info doesn't has all the information it should have";
    }

    std::string log_message =
        "Ending EditableFloor get_information returning value: " + return_value;
    LOG(DEBUG) << log_message;

    return return_value;
}

/**
 * Select elements which will be edited.
 *
 * @param cis_selected [0,1]
 */
void EditableFloor::set_selected(bool cis_selected) {
#ifndef NDEBUG
    std::string log_message =
        "Starting EditableFloor set_selected with cis_selected: " +
        static_cast<int>(cis_selected);
    LOG(DEBUG) << log_message;
#endif

    is_selected = cis_selected;

    LOG(DEBUG) << "Ending EditableFloor set_selected";
}

/**
 * Render selected box considering if it is selected.
 */
void EditableFloor::render() {
    // LOG(DEBUG) << "Starting EditableFloor render";

    if (is_selected) {
        selected_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    } else {
        /* Nothing to do. */
    }

    if (is_crossingable) {
        platform_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    } else {
        standard_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    }

    // LOG(DEBUG) << "Ending EditableFloor render";
}

/**
 * Manages player interaction with the box.
 *
 * @param delta_time Difference in position of the box.
 */
void EditableFloor::update(float delta_time) {
    /*
    #ifndef NDEBUG
    char log_message_c[60];
    snprintf(log_message_c, sizeof(log_message_c), "Starting EditableFloor
    update with delta_time: %.2f", delta_time);

    std::string log_message(log_message_c);
    LOG(DEBUG) << log_message;
    #endif
    */

    handle_platforms_interaction(delta_time);

    // LOG(DEBUG) << "Ending EditableFloor update";
}

/**
 * True if box has been deleted.
 *
 * @returns [0,1]
 */
bool EditableFloor::is_dead() {
    // LOG(DEBUG) << "Starting EditableFloor is_dead";

    bool return_value = is_deleted;

    /*
    #ifndef NDEBUG
    std::string log_message = "Ending EditableFloor is_dead returning value: " +
    std::to_string(static_cast<int>(return_value));
    LOG(DEBUG) << log_message;
    #endif
    */

    return return_value;
}

/**
 * Will handle all interaction of the user with the platform.
 *
 * @param delta_time time spent on each frame of sprites
 */
void EditableFloor::handle_platforms_interaction(float delta_time) {
    // LOG(DEBUG) << "Starting EditableFloor handle_platforms_interaction
    // method";

    InputManager *input_manager = InputManager::get_instance();

    if (input_manager->mouse_press(InputManager::LEFT_MOUSE_BUTTON)) {
        int x = input_manager->get_mouse_x_position();
        int y = input_manager->get_mouse_y_position();

        Rectangle mouse = Rectangle(x, y, 1, 1);
        is_selected = Collision::is_colliding(box, mouse, rotation, 0);
    } else {
        /* Nothing to do. */
    }

    if (is_selected) {
        static float acceleration = ACCELERATION;
        float delta_space = MOVE_SPEED * delta_time * acceleration;
        bool moved = false;

        handle_box_moving(moved, delta_space);
        handle_box_resizing(moved, delta_time);
        handle_box_rotating(acceleration, delta_space);
        handle_acceleration_increasing(moved, acceleration);

        /**
         * Toggle Floor.
         */
        if (input_manager->key_press(InputManager::K_C)) {
            is_crossingable = not is_crossingable;
        } else {
            /* Nothing to do. */
        }

        /**
         * Delete floor.
         */
        if (input_manager->is_key_down(InputManager::K_DEL)) {
            is_deleted = true;
        } else {
            /* Nothing to do. */
        }
    } else {
        /* Nothing to do. */
    }

    // LOG(DEBUG) << "Ending EditableFloor handle_platforms_interaction method";
}

/**
 * Handle platform player interaction with the platforms.
 *
 * @param moved will become true if platform move
 * @param delta_space how much platform will move
 */
void EditableFloor::handle_box_moving(bool &moved,
                                      float delta_space) {  // NOLINT
    // LOG(DEBUG) << "Starting EditableFloor handle_box_moving method";

    InputManager *input_manager = InputManager::get_instance();

    if (input_manager->is_key_down(InputManager::K_ARROW_RIGHT)) {
        box.x += delta_space;
        moved = true;
    } else if (input_manager->is_key_down(InputManager::K_ARROW_LEFT)) {
        box.x -= delta_space;
        moved = true;
    } else {
        /* Nothing to do. */
    }

    if (input_manager->is_key_down(InputManager::K_ARROW_UP)) {
        box.y -= delta_space;
        moved = true;
    } else if (input_manager->is_key_down(InputManager::K_ARROW_DOWN)) {
        box.y += delta_space;
        moved = true;
    } else {
        /* Nothing to do. */
    }

    // LOG(DEBUG) << "Ending EditableFloor handle_box_moving method";
}

/**
 * Handle platform player interaction with the platforms.
 *
 * @param moved will become true if platform move
 * @param delta_space how much platform will move
 */
void EditableFloor::handle_box_resizing(bool &moved,
                                        float delta_space) {  // NOLINT
    // LOG(DEBUG) << "Starting EditableFloor handle_box_resizing method";

    /**
     * Limit box sizes.
     */
    if (box.x < 0) {
        box.x = 0;
    } else if (box.x > BACKGROUND_WIDTH) {
        box.x = BACKGROUND_WIDTH;
    } else if (box.y < 0) {
        box.y = 0;
    } else if (box.y > BACKGROUND_HEIGHT) {
        box.y = BACKGROUND_HEIGHT;
    } else {
        /* Nothing to do. */
    }

    InputManager *input_manager = InputManager::get_instance();

    /**
     * Increase floor width.
     */
    if (input_manager->is_key_down(InputManager::K_INC_W)) {
        standard_sprite.update_scale_x(RESIZING_SPEED * delta_space);
        platform_sprite.update_scale_x(RESIZING_SPEED * delta_space);
        selected_sprite.update_scale_x(RESIZING_SPEED * delta_space);

        box.width = standard_sprite.get_width();
        moved = true;
    } else {
        /* Nothing to do. */
    }

    /**
     * Decrease floor width.
     */
    if (input_manager->is_key_down(InputManager::K_DEC_W)) {
        standard_sprite.update_scale_x(-RESIZING_SPEED * delta_space);
        platform_sprite.update_scale_x(-RESIZING_SPEED * delta_space);
        selected_sprite.update_scale_x(-RESIZING_SPEED * delta_space);

        box.width = standard_sprite.get_width();
        moved = true;
    } else {
        /* Nothing to do. */
    }

    // LOG(DEBUG) << "Ending EditableFloor handle_box_resizing method";
}

/**
 * Will handle rotation for both sides and reset.
 *
 * @param acceleration acceleration for rotating platform
 * @param delta_space intensifies rotating speed
 */
void EditableFloor::handle_box_rotating(float acceleration, float delta_space) {
    // LOG(DEBUG) << "Starting EditableFloor handle_box_rotating method";

    InputManager *input_manager = InputManager::get_instance();

    /**
     * Rotate box to corresponding direction or reset it.
     */
    if (input_manager->is_key_down(InputManager::K_ROT_LEFT)) {
        rotation += ROTATING_SPEED * delta_space / acceleration;
    } else if (input_manager->is_key_down(InputManager::K_ROT_RIGHT)) {
        rotation -= ROTATING_SPEED * delta_space / acceleration;
    } else if (input_manager->is_key_down(InputManager::K_ROT_RESET)) {
        rotation = 0;
    } else {
        /* Nothing to do. */
    }

    // LOG(DEBUG) << "Ending EditableFloor handle_box_rotating method";
}

/**
 * Will handle if acceleration increase keeps ou reset
 *
 * @param moved if platform was moved, it will change behavior
 * @param acceleration acceleration that will be changed
 */
void EditableFloor::handle_acceleration_increasing(
    bool &moved,
    float &acceleration) {  // NOLINT
    // LOG(DEBUG) << "Starting EditableFloor handle_acceleration_increasing
    // method";

    if (moved) {
        acceleration = fmin(acceleration + ACCELERATION_INCREASE_STEP,
                            MAXIMUM_ACCELERATION);
    } else {
        acceleration = ACCELERATION;
    }

    // LOG(DEBUG) << "Ending EditableFloor handle_acceleration_increasing
    // method";
}

/**
 * Not implemented.
 *
 * @param unamed An game object.
 */
void EditableFloor::notify_collision(GameObject &) {
}
