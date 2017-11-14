/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file MenuState.h
 * Brief Description.
 */

#ifndef INCLUDE_MENUSTATE_H_
#define INCLUDE_MENUSTATE_H_

#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"

#include <vector>

class MenuState : public State {
 private:
    Sprite background, green_ship, red_ship, title, planet;
    Text* start_option;
    Sound blocked, selected, changed;
    Music music;
    Timer text_timer;
    int current_option;
    bool start_pressed, show_text;
    vector<Text*> options;

    enum Button { A, B, Y, LEFT, RIGHT, SELECT, START, LB, RT };
    bool pressed[15], is_holding[15];

 public:
    explicit MenuState(bool main_menu = false);

    void update(float delta);
    void render();

    void pause();
    void resume();

    void process_input();
};

#endif  // INCLUDE_MENUSTATE_H_
