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

#include <assert.h>
#include <fstream>
#include <sstream>

#include "BattleEnd.h"
#include "Blood.h"
#include "Config.h"
#include "FighterStats.h"
#include "Flesh.h"
#include "Floor.h"
#include "Game.h"
#include "InputManager.h"
#include "MenuState.h"

#define N_BACKGROUND

#define HUD1 133 /**< Unity in pixel*/
#define HUD2 589.5 /**< Unity in pixel*/
#define HUD3 1147 /**< Unity in pixel*/
#define HUD4 679.5 /**< Unity in pixel*/

#define CHAR_POS1 177 /**< Unity in pixel*/
#define CHAR_POS2 313 /**< Unity in pixel*/
#define CHAR_POS3 276 /**< Unity in pixel*/
#define CHAR_POS4 510 /**< Unity in pixel*/
#define CHAR_POS5 1128 /**< Unity in pixel*/
#define CHAR_POS6 245 /**< Unity in pixel*/
#define CHAR_POS7 954 /**< Unity in pixel*/
#define CHAR_POS8 474 /**< Unity in pixel*/
#define CHAR_POS9 116 /**< Unity in pixel*/
#define CHAR_POS10 227 /**< Unity in pixel*/
#define CHAR_POS11 146 /**< Unity in pixel*/
#define CHAR_POS12 394 /**< Unity in pixel*/
#define CHAR_POS13 1036 /**< Unity in pixel*/
#define CHAR_POS14 221 /**< Unity in pixel*/
#define CHAR_POS15 1063 /**< Unity in pixel*/
#define CHAR_POS16 382 /**< Unity in pixel*/

#define LEVELNOTFOUND "Level design of stage %s can't be opened\n" /**< \
                                                                      string*/
#define MUSIC "/music.ogg" /**< string*/
#define SOUND "/sound.ogg" /**< string*/
#define SENSIBILITY_VALUE 20000 /**< Unity value*/

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
                         vector<pair<string, string> > players_info) {
    assert(stage.empty() != true);
    assert(players_info.empty() != true);

    game_over = false;
    memset(alive, 1, sizeof alive);

    music = Music("stage_" + stage + MUSIC);
    sound = Sound("stage_" + stage + SOUND);

    read_level_design(stage);
    music.play();
    sound.play(-1);
    setPlayersInfo(stage, players_info);
    setHud();
    startTime();
    InputManager::get_instance()->set_analogic_sensibility_value(
        SENSIBILITY_VALUE);
    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::BATTLE_MODE);
}
/**
 * A Destructor.
 * Destructs a previously initialized object of this class.
 */
BattleState::~BattleState() {
}
/**
 *function setCharPositions
 *set the position of the characters on screen.
 *@param stage is the name of the stage chosen.
 */
vector<pair<int, int> > BattleState::setCharPositions(string stage) {
    vector<pair<int, int> > char_positions;

    /**
     * If the condition is met, the character position is set one way. if not
     * the default settins are used.
     */
    if (stage == "1") {
        char_positions = {ii(CHAR_POS1, CHAR_POS2), ii(CHAR_POS3, CHAR_POS4),
                          ii(CHAR_POS5, CHAR_POS6), ii(CHAR_POS7, CHAR_POS8)};
    } else {
        char_positions = {ii(CHAR_POS9, CHAR_POS10), ii(CHAR_POS11, CHAR_POS12),
                          ii(CHAR_POS13, CHAR_POS14),
                          ii(CHAR_POS15, CHAR_POS16)};
    }
    return char_positions;
}
/**
 *function setPlayersInfo
 *this function sets the characteristics of the character.
 */
void BattleState::setPlayersInfo(string stage,
                                 vector<pair<string, string> > players_info) {
    /**
     * Runs each iteration from 0 to the size of players_info -1.
     */
    for (int i = 0; i < static_cast<int>(players_info.size()); i++) {
        string char_name = players_info[i].first;
        string skin_name = players_info[i].second;

        /**
         * If the condition is met, Blood method is called, else Flesh method
         * is called.
         */
        if (char_name == "blood") {
            players[i] = new Blood(skin_name, setCharPositions(stage)[i].first,
                                   setCharPositions(stage)[i].second, i);

            assert(skin_name.empty() != true);

        } else if (char_name == "flesh") {
            players[i] = new Flesh(skin_name, setCharPositions(stage)[i].first,
                                   setCharPositions(stage)[i].second, i);

            assert(skin_name.empty() != true);

        } else {
            /*Nothing to do*/
        }
        /**
         * Runs each iteration from 0 to the size of players_info -1.
         */
        for (int j = NUMBER_PLAYERS - 1; j >= 0; j--) {
            add_object(players[i]);
        }
    }

    players[0]->set_partner(players[1]);
    players[1]->set_partner(players[0]);
    players[2]->set_partner(players[3]);
    players[3]->set_partner(players[2]);
}
/**
 *function setHud
 *this function sets the elements on screen - non characters.
 */
void BattleState::setHud() {
    vector<pair<int, int> > hud_positions = {ii(HUD1, HUD2), ii(HUD1, HUD4),
                                             ii(HUD3, HUD2), ii(HUD3, HUD4)};

    /**
    * Runs each iteration from NUMBER_PLAYERS-1 until bigger or equal to 0.
    * Each iteration decreases de variable count.
    */
    for (int i = NUMBER_PLAYERS - 1; i >= 0; i--) {
        add_object(new FighterStats(players[i], i + 1, i > 1,
                                    hud_positions[i].first,
                                    hud_positions[i].second));
    }
}
/**
 *function startTime
 *this function starts the time counter for the match.
 */
/**
 *function startTime
 *this function is responsable for the timer in a match.
 */
void BattleState::startTime() {
    time_counter = new TimeCounter();
    add_object(time_counter);
}
/**
 * update method.
 * Checks the current state of a started game.
 * This method checks the current state of the game and updates it.
 *
 * @param delta is a number of the type float used to update the background.
 */
void BattleState::update(float delta) {
    InputManager* input_manager = InputManager::get_instance();
    assert(delta >= 0);
    exitBattle(input_manager);
    returnMenu(input_manager);
    isPlayerAlive();
    isGameOver();
    gameOverOutcome();
    /**
     * Updates the background list.
     */
    for (auto& background : backgrounds) {
        background.first.update(delta);
    }
    update_array(delta);
}
/**
 *exitBattle method
 *checks if exiting the battle is requested.
 */
void BattleState::exitBattle(InputManager* input_manager) {
    /**
     * If quit_requested = true, then m_quit_requested = true.
     */
    if (input_manager->quit_requested()) {
        m_quit_requested = true;
        return;
    } else {
        /*Nothing to do*/
    }
}
/**
 *returnMenu method
 *returns the game to the menu when requested via input from controller.
 */
void BattleState::returnMenu(InputManager* input_manager) {
    /**
     * If joystick_button_press = true, the body is executed.
     * The music stops playing and the menu is updated and leave the edit state.
     */
    if (input_manager->joystick_button_press(InputManager::SELECT, 0)) {
        music.stop();
        Game::get_instance().push(new MenuState(true));
        m_quit_requested = true;
        return;
    } else {
        /*Nothing to do*/
    }
}
/**
 *isPlayerAlive method
 *checks if the player is still alive in a battle
 */
void BattleState::isPlayerAlive() {
    /**
     * Runs each iteration from 0 to the size of NUMBER_PLAYERS -1.
     */
    for (int i = 0; i < NUMBER_PLAYERS; i++) {
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
            } else {
                /*Nothing to do*/
            }
        } else {
            /*Nothing to do*/
        }
    }
}
/**
 *isGameOver method
 *Checks if the game is over or not.
 */
void BattleState::isGameOver() {
    if (time_counter->is_over() and not game_over) {
        game_over = true;

        /**
         * If the first condition is met, battleEnd is instanciated and passed
         * as a
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
            for (int i = 0; i < NUMBER_PLAYERS / 2; i++) {
                /**
                 * If condition is met, the remaining life of a player is added
                 * to the sum_life_team_1 variable.
                 */
                if (alive[i]) {
                    sum_life_team_1 += players[i]->get_remaining_life();
                } else {
                    /*Nothing to do*/
                }
            }

            int sum_life_team_2 = 0;
            /**
             * Runs each iteration from NUMBER_PLAYERS divided by 2 until
             * NUMBER_PLAYERS -1.
             */
            for (int i = NUMBER_PLAYERS / 2; i < NUMBER_PLAYERS; i++) {
                /**
                 * If condition is met, the remaining life of a player is
                 * added to the sum_life_team_1 variable.
                 */
                if (alive[i]) {
                    sum_life_team_2 += players[i]->get_remaining_life();
                } else {
                    /*Nothing to do*/
                }
            }
            /**
             * If the first condition is met, battleEnd is instanciated and
             * passed as a parameter on add_object method. If not, the else
             * body is run.
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
    if (not alive[0] and not alive[1] and not alive[2] and not alive[3] and
        not game_over) {
        game_over = true;
        battleEnd = new BattleEnd(3);
        add_object(battleEnd);
    } else {
        /*Nothing to do*/
    }

    if (not alive[0] and not alive[1] and not game_over) {
        game_over = true;
        battleEnd = new BattleEnd(2);
        add_object(battleEnd);
    } else if (not alive[2] and not alive[3] and not game_over) {
        game_over = true;
        battleEnd = new BattleEnd(1);
        add_object(battleEnd);
    } else {
        /*Nothing to do*/
    }
}
/**
 * render method.
 * renders the background given a x and y positions.
 */
void BattleState::gameOverOutcome() {
    if (game_over) {
        for (int i = 0; i < NUMBER_PLAYERS; i++) {
            if (alive[i]) {
                players[i]->add_tags("game_over");
            } else {
                /*Nothing to do*/
            }
        }
    } else {
        /*Nothing to do*/
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
        } else {
            /*Nothing to do*/
        }
    } else {
        /*Nothing to do*/
    }
}
/**
 *gameOverOutcome method
 *presents one of many outcomes when the game is over.
 */
void BattleState::render() {
    /**
    * Renders each background from the background list.
    */
    for (auto& background : backgrounds) {
        background.first.render(background.second.x, background.second.y);
    }
    render_array();
}
/**
 * pause method.
 * Not implemented.
 */
void BattleState::pause() {
}
/**
 * resume method.
 * Not implemented.
 */
void BattleState::resume() {
}
/**
 * read_level_design method.
 * Reads the levels in the game.
 *
 *@param stage is name and is used to select a specific stage.
 */
void BattleState::read_level_design(string stage) {
    assert(stage.empty() != true);

    float x, y, width, crotation;
    int platform;
    fstream level_design(RESOURCES_FOLDER + "stage_" + stage +
                         "/level_design.dat");

    /**
     * If the condition is false, a message is displayed.
     */
    if (not level_design.is_open()) {
        printf(LEVELNOTFOUND, stage.c_str());
        exit(-5);
    } else {
        /*Nothing to do*/
    }

    string s;
    int n_backgrounds, n_sprites, speed, n_columns;
    std::getline(level_design, s);

    for (auto& c : s) {
        c -= 15;
    }

    stringstream n_background_line(s);
    n_background_line >> n_backgrounds;

    for (int i = 0; i < n_backgrounds; ++i) {
        std::getline(level_design, s);

        for (auto& c : s) {
            c -= 15;
        }

        stringstream backgrounds_line(s);
        backgrounds_line >> x >> y >> n_sprites >> speed >> n_columns;
        /**printf("Dados: %.f %.f %d %d %d\n", x, y, n_sprites, speed,
         *        n_columns);
         */
        Sprite background_sprite(
            "stage_" + stage + "/background_" + to_string(i) + ".png",
            n_sprites, speed, n_columns);
        Vector position(x, y);
        backgrounds.push_back(std::make_pair(background_sprite, position));
    }

    /**
     * For as long as the condition is true, add_object is called.
     */
    while (std::getline(level_design, s)) {
        for (auto& c : s)
            c -= 15;

        stringstream floors_line(s);
        floors_line >> x >> y >> width >> crotation >> platform;

        // printf("Battle: %.f %.f %.f %.f\n", x, y, width, crotation);
        add_object(
            new Floor(x, y, width, crotation, static_cast<bool>(platform)));
    }

    level_design.close();
}
