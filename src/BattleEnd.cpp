/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file BattleEnd.cpp
 * This file renders images at the end of a battle indicating the team that won.
 */
#include "BattleEnd.h"
#include "InputManager.h"

using std::to_string;

#define WHITE { 255, 255, 255, 255 }

/**
 * Constructor.
 * This constructor builds sprites and texts to indicates the team that won
 * the match redering an image at the end of the battle.
 *
 * @param id_winner and integer argument that represents the id of the team
 * that won the battle.
 */
BattleEnd::BattleEnd(int id_winner) {
    back_btn = Sprite("victory/buttons/back.png");

    back_txt = new Text("font/8-BIT WONDER.ttf", 22, Text::TextStyle::SOLID,
                        "BACK", WHITE);
    back_txt->set_pos(1154, 650);

    back_selected = false;

    sprite = vector<Sprite>(N_SPRITES + 2);

    string path = "victory/" + to_string(id_winner) + "/";

    /**
     * Iterates over the 8 images of victory to create an array of sprites.
     */
    for (int i = 1; i <= N_SPRITES; i++) {
        sprite[i] = Sprite(path + to_string(i) + ".png", 1, 5);
    }

    current_sprite = 1;

    quitRequested = false;
}

/**
 * Function that updates sprite of the end of a Battle.
 * This function makes sprites variate accoding to the input user state.
 *
 * @param delta a float variation to update the sprite that is rendered at the
 * end of the battle.
 */
void BattleEnd::update(float delta) {
    sprite[current_sprite].update(delta);

    /**
     * Check if has rendered all 8 sprites on the vector "sprite".
     */
    if (sprite[current_sprite].is_finished()) {
        if (back_selected and(current_sprite > 1)) {
            current_sprite--;
        } else if (not back_selected and(current_sprite < N_SPRITES)) {
            current_sprite++;
        }
    }

    InputManager *input_manager = InputManager::get_instance();

    /**
     * Check if user has requested to quit the battle so it can restart
     * the sprite count to current_sprite recieve 1.
     */
    if (input_manager->joystick_button_press(InputManager::SELECT, 0) or
        input_manager->joystick_button_press(InputManager::B, 0)
        ) {
        for (int i = 1; i <= N_SPRITES; i++) {
            sprite[i].restart_count();
        }
        back_selected = true;
    }

    /**
     * Check if user has requested to quit the battle.
     */
    if (back_selected and sprite[current_sprite].is_finished() and
        (current_sprite == 1)) {
        quitRequested = true;
        return;
    }
}

/**
 * Function that renders sprite and texts.
 * This function renders sprite and texts at right position when a Battle is
 * finished.
 */
void BattleEnd::render() {
    sprite[current_sprite].render();
    back_btn.render(1094, 642);
    back_txt->render();
}

/**
 * Function get state dead.
 * This function returns the state dead.
 *
 * @return a boolean default value.
 */
bool BattleEnd::is_dead() {
    return false;
}

/**
 * Function get quit request.
 * This function returns true when a quit request is open by the user.
 *
 * @return a boolean value that represents the the quit request of the user.
 */
bool BattleEnd::quit_requested() {
    return quitRequested;
}

/**
 * Function notify collision.
 * Nothing to do.
 *
 * @param GameObject a pointer to a GameObject.
 */
void BattleEnd::notify_collision(GameObject&) {}
