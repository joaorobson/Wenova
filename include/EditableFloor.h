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
#include "easylogging++.h" // NOLINT

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
     * Get information about many aspects of an platform.
     *
     * @returns String in format: "x y width rotated level is_platform?"
     */
    string get_information();

    /**
     * Select elements which will be edited.
     *
     * @param cis_selected [0,1]
     */
    void set_selected(bool cis_selected);

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
     * Not implemented.
     *
     * @param unamed An game object.
     */
    void notify_collision(GameObject&);
};

#endif  // INCLUDE_EDITABLEFLOOR_H_
