/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file EditableFloor.h
 * Defines EditableFloor class.
 * Manages edition of the Floor by the player.
 */

#ifndef INCLUDE_EDITABLEFLOOR_H_
#define INCLUDE_EDITABLEFLOOR_H_

#include <string>

#include "Floor.h"
#include "Sprite.h"
#include "easylogging++.h"  // NOLINT

class EditableFloor : public Floor {
 private:
    Sprite standard_sprite;
    Sprite platform_sprite;
    Sprite selected_sprite;

    enum FloorState { SELECTED, NOT_SELECTED };  ///< Can't be after state
    FloorState state;

    bool is_deleted;
    bool is_selected;

 public:
    /**
     * Create platform with default width of 100px.
     *
     * @param x Position in X axis. Unit: px, [0,screen_width]
     * @param y Position in Y axis. Unit: px, [0,screen_height]
     * @param crotation Unit: degrees
     * @param cplatform [0,1]
     */
    EditableFloor(float x, float y, float crotation, bool cplatform);

    /**
     * Create platform with specific width.
     *
     * @param x Position in X axis. Unit: px, [0,screen_width]
     * @param y Position in Y axis. Unit: px, [0,screen_height]
     * @param width Unit: px, [0,]
     * @param crotation Unit: degrees
     * @param cplatform [0,1]
     */
    EditableFloor(float x, float y, float width, float crotation,
                  bool cplatform);

    /**
     * Not implemented.
     */
    ~EditableFloor();

    /**
     * Select elements which will be edited.
     *
     * @param cis_selected [0,1]
     */
    void set_selected(bool cis_selected);

    /**
     * Get information about many aspects of an platform.
     *
     * @returns String in format: "x y width rotated level is_platform?"
     */
    string get_information();

 private:
    /**
     * Render selected platform considering if it is selected.
     */
    void render();

    /**
     * Manages player interaction with the platform.
     *
     * @param delta Difference in position of the platform.
     */
    void update(float delta);

    /**
     * True if platform has been deleted.
     *
     * @returns [0,1]
     */
    bool is_dead();

    /**
     * Will handle all interaction of the user with the platform.
     *
     * @param delta_time time spent on each frame of sprites
     */
    void handle_platforms_interaction(float delta_time);

    /**
     * Handle platform player interaction with the platforms.
     *
     * @param moved will become true if platform move
     * @param delta_space how much platform will move
     */
    void handle_box_moving(bool &moved, float delta_space); // NOLINT

    /**
     * Will handle rotation for both sides and reset.
     *
     * @param moved will become true if platform resize
     * @param delta_space intensifies resizing speed
     */
    void handle_box_resizing(bool &moved, float delta_space); // NOLINT

    /**
     * Will handle rotation for both sides and reset.
     *
     * @param acceleration acceleration for rotating platform
     * @param delta_space intensifies rotating speed
     */
    void handle_box_rotating(float acceleration, float delta_space);

    /**
     * Will handle if acceleration increase keeps ou reset
     *
     * @param moved if platform was moved, it will change behavior
     * @param acceleration acceleration that will be changed
     */
    void handle_acceleration_increasing(bool &moved,
                                        float &acceleration); //NOLINT

    /**
     * Not implemented.
     *
     * @param unamed An game object.
     */
    void notify_collision(GameObject &);
};

#endif  // INCLUDE_EDITABLEFLOOR_H_
