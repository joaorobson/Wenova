/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Floor.h
 * Control the floor of the stages.
 */

#ifndef INCLUDE_FLOOR_H_
#define INCLUDE_FLOOR_H_

#include "GameObject.h"
#include "Sprite.h"

#include "easylogging++.h" //NOLINT

class Floor : public GameObject {
 private:
    int id = 1; /**< The id of the floor. */

 protected:
    bool is_crossingable = false;  ///< Check if the character is crossingable
                                   ///< through the floor.

 public:
    /**
     * The constructor.
     * Initialize the floor
     * container coordinates of the Floor class. The Floor class inherits the
     * GameObject class.
     *
     * @param x is the box horizontal coordinate.
     * @param y is the box veretical coordinate.
     * @param widht is the widht of the floor.
     * @param height is the height of the floor.
     * @param crotation is the rotation of the floor.
     * @param cplataform is the type of the plataform selected.
     */
    Floor(float x, float y, float width, float crotation, bool cplatform);

    /**
     * The destructor.
     * Destroy the floor.
     */
    ~Floor();

    /**
     * Update the traits of floor
     *
     * @param float
     */
    void update(float delta);

    /**
     * Render the floor
     */
    void render();

    /**
     * Check if the floor is dead
     *
     * @returns
     */
    bool is_dead();

    /**
     * Notify a collision in the floor
     *
     * @param & is the object to verify the collision
     */
    void notify_collision(const GameObject& object);

    /**
     * Check the ID of floor
     *
     * @return the id of the floor
     */
    int get_id() const;

    static int floor_id;
};

#endif  // INCLUDE_FLOOR_H_
