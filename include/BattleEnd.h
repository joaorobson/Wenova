/*
 *Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 *This work is licensed under the terms of the MIT license.
 *For a copy, see <https://opensource.org/licenses/MIT>.
 *
 *Definition of methods and attributes.
 *
 *This file contains the definitions of the methods and attributes of the class
 *BattleEnd.
 */
#ifndef INCLUDE_BATTLEEND_H_
#define INCLUDE_BATTLEEND_H_

#define N_SPRITES 8

#include "State.h"
#include "Sprite.h"
#include "Text.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class BattleEnd : public GameObject {
 public:
    /** Constructor.
     * This constructor builds sprites and texts to indicates the team that won
     * the match redering an image at the end of the battle.
     *
     * @param id_winner and integer argument that represents the id of the team
     * that won the battle.
     */
    explicit BattleEnd(int id_winner);

    /** Function that updates sprite of the end of a Battle.
     * This function makes sprites variate accoding to the input user state.
     *
     * @param delta a float variation to update the sprite that is rendered at
     * the end of the battle.
     */
    void update(float delta);

    /** Function that renders sprite and texts.
     * This function renders sprite and texts at right position when a Battle is
     * finished.
     */
    void render();

    /** Function get state dead.
     * This function returns the state dead.
     *
     * @return a boolean default value.
     */
    bool is_dead();

    /** Function get quit request.
     * This function returns true when a quit request is open by the user.
     *
     * @return a boolean value that represents the the quit request of the user.
     */
    bool quit_requested();

    /** Function notify collision.
     * Nothing to do.
     *
     * @param GameObject a pointer to a GameObject.
     */
    void notify_collision(GameObject & object);

 private:
    vector<Sprite> sprite;

    int current_sprite;

    bool back_selected, quitRequested;

    Sprite back_btn;
    Text  *back_txt;
};

#endif  // INCLUDE_BATTLEEND_H_
