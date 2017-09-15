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

#include "Floor.h"
#include "Sprite.h"

#include <string>

class EditableFloor : public Floor {
 private:
    enum FloorState { SELECTED, NOT_SELECTED };
    Sprite normal_sprite, platform_sprite, selected_sprite;
    FloorState state;
    bool deleted;
    bool selected;

 public:
    /**
     * Create box with default width of 100px.
     *
     * @param x Position in X axis. Unit: px, [0,screen_width]
     * @param y Position in Y axis. Unit: px, [0,screen_height]
     * @param crotation Unit: degrees
     * @param cplatform [0,1]
     */
    EditableFloor(float x, float y, float crotation, bool cplatform);

    /**
     * Create box with specific width.
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
     * Manages player interaction with the box.
     *
     * @param delta Difference in position of the box.
     */
    void update(float delta);

    /**
     * Render selected box considering if it is selected.
     */
    void render();

    /**
     * True if box has been deleted.
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

    /**
     * Get information about many aspects of an box.
     *
     * @returns String in format: "x y width rotated level is_platform?"
     */
    string get_information();

    /**
     * Select elements which will be edited.
     *
     * @param cselected [0,1]
     */
    void set_selected(bool cselected);
};

#endif  // INCLUDE_EDITABLEFLOOR_H_
