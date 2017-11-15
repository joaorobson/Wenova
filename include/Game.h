/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Game.h
 * Brief Description.
 */

#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <iostream>
#include <memory>
#include <string>

#include <stack>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL_ttf.h"

#include "State.h"

using std::string;
using std::stack;
using std::unique_ptr;

class Game {
 private:
    static Game* instance;

    int frame_start;
    int width, height;
    float delta;

    State* stored_state;
    SDL_Window* window;
    SDL_Renderer* renderer = nullptr;

    stack<unique_ptr<State> > state_stack;

    void calculate_delta_time();
    void manage_stack();
    void update_resolution();

 public:
    explicit Game(string title);
    ~Game();

    static Game& get_instance();
    SDL_Renderer* get_renderer();
    State& get_current_state();

    void push(State* state);

    void run();

    float get_delta_time();
    void change_resolution(int cwidth, int cheight);
    void set_fullscreen(bool on = false);
};

#endif  // INCLUDE_GAME_H_
