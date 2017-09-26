/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file BattleState.cpp
 * This file contains the definition of the BattleState.h class methods.
 */
#include "BattleState.h"

#include <fstream>
#include <sstream>

#include "InputManager.h"
#include "Game.h"
#include "Floor.h"
#include "MenuState.h"
#include "FighterStats.h"
#include "Config.h"
#include "Blood.h"
#include "Flesh.h"
#include "BattleEnd.h"

#define N_BACKGROUND 2

using std::fstream;
using std::stringstream;
using std::to_string;

/**
 * The constructor.
 * Initialize the battle stage and the character locations.
 *
 * @param stage is the name of the stage.
 * @param vector is a vector of strings.
 * @param players_info a description.
 */
BattleState::BattleState(string stage,
                          vector< pair<string, string> > players_info) {
    game_over = false;
    memset(alive, 1, sizeof alive);

    music = Music("stage_" + stage + "/music.ogg");
    sound = Sound("stage_" + stage + "/sound.ogg");

    read_level_design(stage);

    music.play();
    sound.play(-1);

    vector< pair<int, int> > char_positions;
    vector< pair<int, int> > hud_positions = { ii(133, 589.5),
                                               ii(133, 679.5),
                                               ii(1147, 589.5),
                                               ii(1147, 679.5)
                                             };
    /**
     * If the condition is met, the character position is set one way. if not
     * the default settins are used.
     */
    if (stage == "1") {
        char_positions = { ii(177, 313),
                           ii(276, 510), ii(1128, 245), ii(954, 474)
    } else {
        char_positions = { ii(116, 227),
                           ii(146, 394), ii(1036, 221), ii(1063, 382)
        };

    /**
     * Runs each iteration from 0 to the size of players_info -1.
     */
    for (int i = 0; i < (int)players_info.size(); i++) {
        string char_name = players_info[i].first;
        string skin_name = players_info[i].second;

        /**
         * If the condition is met, Blood method is called, else Flesh method
         * is called.
         */
        if (char_name == "blood") {
            players[i] = new Blood(skin_name, char_positions[i].first,
                                   char_positions[i].second, i);
        } else if (char_name == "flesh") {
            players[i] = new Flesh(skin_name, char_positions[i].first,
                                   char_positions[i].second, i);
        }
    }

    players[0]->set_partner(players[1]);
    players[1]->set_partner(players[0]);
    players[2]->set_partner(players[3]);
    players[3]->set_partner(players[2]);

    /**
     * Runs each iteration from N_PLAYERS-1 until bigger or equal to 0.
     * Each iteration decreases de variable count.
     */
    for (int i=N_PLAYERS-1; i >= 0; i--) {
        add_object(new FighterStats(players[i], i + 1, i > 1,
            hud_positions[i].first,
            hud_positions[i].second));
    }

    /**
     * Runs each iteration from 0 to the size of players_info -1.
     */
    for (int i=N_PLAYERS-1; i >= 0; i--) {
        add_object(players[i]);
    }

    time_counter = new TimeCounter();
    add_object(time_counter);

    InputManager::get_instance()->set_analogic_value(20000);
    InputManager::get_instance()->
                            map_keyboard_to_joystick(InputManager::BATTLE_MODE);
}

/**
 * A Destructor.
 * Destructs a previously initialized object of this class.
 */
BattleState::~BattleState() {}

/**
 * update method.
 * Checks the current state of a started game.
 * This method checks the current state of the game and updates it.
 *
 * @param delta is a number of the type float used to update the background.
 */
void BattleState::update(float delta) {
    InputManager * input_manager = InputManager::get_instance();

    /**
     * If quit_requested = true, then m_quit_requested = true.
     */
    if (input_manager->quit_requested()) {
        m_quit_requested = true;
        return;
    }

    /**
     * If joystick_button_press = true, the body is executed.
     * The music stops playing and the menu is updated.
     */
    if (input_manager->joystick_button_press(InputManager::SELECT, 0)) {
        music.stop();
        Game::get_instance().push(new MenuState(true));
        m_quit_requested = true;
        return;
    }

    /**
     * Runs each iteration from 0 to the size of N_PLAYERS -1.
     */
    for (int i = 0; i < N_PLAYERS; i++) {
        /**
         * If alive on a give index returns true, the body is executed.
         */
        if (alive[i]) {
            /**
             * If players on a given index returns the text "dying", the
             * variable alive on that index is set to false.
             */
            if (players[i]->is("dying")) {
                alive[i] = false;
            }
        }
    }

    /**
     * If is_over returns true and game_over equals false, the body is executed.
     */
    if (time_counter->is_over() and not game_over) {
        game_over = true;

        /**
         * If the first condition is met, battleEnd is instanciated and passed as a
         * parameter on add_object method. If not, the else body is run.
         */
        if (alive[0] + alive[1] > alive[2] + alive[3]) {
            battleEnd = new BattleEnd(1);
            add_object(battleEnd);
        } else if (alive[2] + alive[3] > alive[0] + alive[1]) {
            battleEnd = new BattleEnd(2);
            add_object(battleEnd);
        } else {
            int sum_life_team_1 = 0;
            /**
             * Runs each iteration from 0 to the size of players_info divided
             * by 2.
             */
            for (int i = 0; i < N_PLAYERS / 2; i++) {
                /**
                 * If condition is met, the remaining life of a player is added
                 * to the sum_life_team_1 variable.
                 */
                if (alive[i]) {
                    sum_life_team_1 += players[i]->get_remaining_life();
                }
            }

            int sum_life_team_2 = 0;
                /**
                 * Runs each iteration from N_PLAYERS divided by 2 until
                 * N_PLAYERS -1.
                 */
                for (int i = N_PLAYERS / 2; i < N_PLAYERS; i++) {
                    /**
                     * If condition is met, the remaining life of a player is added
                     * to the sum_life_team_1 variable.
                     */
                    if (alive[i]) {
                        sum_life_team_2 += players[i]->get_remaining_life();
                    }
                }
            /**
             * If the first condition is met, battleEnd is instanciated and passed as a
             * parameter on add_object method. If not, the else body is run.
             */
            if (sum_life_team_1 > sum_life_team_2) {
                battleEnd = new BattleEnd(1);
                add_object(battleEnd);
            } else if (sum_life_team_2 > sum_life_team_1) {
                battleEnd = new BattleEnd(2);
                add_object(battleEnd);
            } else {
                battleEnd = new BattleEnd(3);
                add_object(battleEnd);
            }
        }
  }
    /**
     * If the condition is met, battleEnd is instanciated and passed as a
     * parameter on add_object method. If not, the else body is run and the
     * game over tag is added to a player.
     */
    if (not alive[0] && not alive[1] && not alive[2] && not alive[3] &&
        not game_over) {
        game_over = true;
        battleEnd = new BattleEnd(3);
        add_object(battleEnd);
    }

    if (not alive[0] && not alive[1] && not game_over) {
        game_over = true;
        battleEnd = new BattleEnd(2);
        add_object(battleEnd);
    } else if (not alive[2] && not alive[3] && not game_over) {
        game_over = true;
        battleEnd = new BattleEnd(1);
        add_object(battleEnd);
    }

    if (game_over) {
        for (int i = 0; i < N_PLAYERS; i++) {
            if (alive[i]) {
                players[i]->add_tags("game_over");
            }
        }
    }
    /**
     * If game_over is true and quit_requested is also true, the music stops,
     * the sound stops and the menu is loaded again.
     */
    if (game_over) {
        if (battleEnd->quit_requested()) {
            music.stop();
            sound.stop();
            m_quit_requested = true;
            Game::get_instance().push(new MenuState());
            return;
        }
    }
    /**
     * Updates the background list.
     */
    for (auto & background : backgrounds) {
        background.first.update(delta);
    }

    update_array(delta);
}

/**
 * render method.
 * renders the background given a x and y positions.
 */
void BattleState::render() {
    /**
    * Renders each background from the background list.
    */
    for (auto & background : backgrounds) {
        background.first.render(background.second.x, background.second.y);
    }

    render_array();
}

/**
 * pause method.
 * Not implemented.
 */
void BattleState::pause() {}

/**
 * resume method.
 * Not implemented.
 */
void BattleState::resume() {}

/**
 * read_level_design method.
 * Reads the levels in the game.
 *
 *@param stage is name and is used to select a specific stage.
 */
void BattleState::read_level_design(string stage) {
    float x, y, width, crotation;
    int platform;
    fstream level_design(RES_FOLDER + "stage_" + stage + "/level_design.dat");
    /**
     * If the condition is false, a message is displayed.
     */
    if (not level_design.is_open()) {
        printf("Level design of stage %s can't be opened\n", stage.c_str());
        exit(-5);
    }
    string s;
    int n_backgrounds, n_sprites, speed, n_columns;

    std::getline(level_design, s);
    for (auto & c : s) {
      c -= 15;
    }
    stringstream n_background_line(s);
    n_background_line >> n_backgrounds;

    for (int i = 0; i < n_backgrounds; ++i) {
        std::getline(level_design, s);
        for (auto & c : s) {
          c -= 15;
        }
        stringstream backgrounds_line(s);
        backgrounds_line >> x >> y >> n_sprites >> speed >> n_columns;
        //printf("Dados: %.f %.f %d %d %d\n", x, y, n_sprites, speed, n_columns);
        Sprite background_sprite("stage_" + stage + "/background_" +
                                to_string(i) + ".png",
                                n_sprites, speed, n_columns);
        Vector position(x, y);
        backgrounds.push_back(std::make_pair(background_sprite, position));
    }

    /**
     * For as long as the condition is true, add_object is called.
     */
    while (std::getline(level_design, s)) {
        for (auto & c : s) c -= 15;
        stringstream floors_line(s);
        floors_line >> x >> y >> width >> crotation >> platform;
        //printf("Battle: %.f %.f %.f %.f\n", x, y, width, crotation);
        add_object(new Floor(x, y, width, crotation, (bool) platform));
     }

    level_design.close();
}
