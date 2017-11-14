/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Main.cpp
 * Brief Description.
 */

#include "Game.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
#include "MenuState.h"


int main(int, char **) {
    Game game("Wenova - Rise of Conquerors");

    State *state = new MenuState(false);
    game.push(state);

    game.run();

    return 0;
}
