/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file FighterStats.h
 * Brief Description.
 */

#ifndef INCLUDE_FIGHTERSTATS_H_
#define INCLUDE_FIGHTERSTATS_H_

#include <string>

#include "Fighter.h"
#include "GameObject.h"
#include "Sprite.h"

using std::string;

class FighterStats : public GameObject {
 public:
    FighterStats(Fighter *p_fighter, int p_index_fighter, int p_side,
                 double p_x, double p_y);
    ~FighterStats();

    void update(float delta);

    void render();

    bool is_dead();

    void notify_collision(const GameObject &object);

 private:
    Sprite bg[3];
    Sprite empty_bg[3];
    Sprite life[3];
    Sprite special[3];
    Sprite player_image;
    Fighter *fighter;

    double percent_to_draw_life;
    double percent_to_draw_special;
    int index_fighter;
    int side;
    int condition;
    bool is_ultimate_diff;
    double x, y;
};

#endif  // INCLUDE_FIGHTERSTATS_H_
