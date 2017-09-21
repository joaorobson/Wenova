/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Main.cpp 
 */

#include "Game.h"
#include "MenuState.h"

//Inicializes the game
int main(int, char **) {
    Game game("Wenova - Rise of Conquerors");

    State * state =  new MenuState(false);
    game.push(state);

    game.run();

    return 0;
}
