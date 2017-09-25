/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

/**
 * @file EditState.cpp
 * This file contains the definition of the EditState.h class methods.
 */
#include "EditState.h"

#include <fstream>
#include <sstream>

#include "InputManager.h"
#include "Game.h"
#include "Blood.h"
#include "Flesh.h"
#include "EditableFloor.h"
#include "MenuState.h"
#include "Config.h"
#include "Rectangle.h"

#define WIDTH 1280
#define HEIGHT 720

#define N_BACKGROUND 2

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::to_string;

/**
 * The constructor.
 * Initialize the EditState object.
 *
 * @param cstage is a name.
 */
EditState::EditState(string cstage) : stage(cstage) {
    test_fighter = new Blood("test", WIDTH / 2, HEIGHT / 2 - 200, 0);
    add_object(test_fighter);

    music = Music("stage_" + stage + "/music.ogg");
    sound = Sound("stage_" + stage + "/sound.ogg");

    music.play();
    sound.play(-1);

    read_level_design();
    InputManager::get_instance()->set_analogic_value(20000);
    InputManager::get_instance()->
    map_keyboard_to_joystick(InputManager::BATTLE_MODE);
}

/**
 * update method.
 * Edits some level design characteristics.
 * This method allows resetting the position of the fighter, creating floors
 * or stages and saving them.
 *
 * @param delta is a number of the type float used to update the background.
 */
void EditState::update(float delta) {
    InputManager *input_manager = InputManager::get_instance();

    if (input_manager->quit_requested()) {
        m_quit_requested = true;
        return;
    }

    // leave edit state
    if (input_manager->joystick_button_press(InputManager::SELECT, 0)) {
        music.stop();
        sound.stop();
        m_quit_requested = true;
        Game::get_instance().push(new MenuState());
        return;
    }

    // reset position of fighter
    if (input_manager->mouse_press(InputManager::RIGHT_MOUSE_BUTTON)) {
        int x = input_manager->get_mouse_x();
        int y = input_manager->get_mouse_y();
        test_fighter->reset_position(x, y);
    }

    // create floor or platform
    if (input_manager->key_press(InputManager::K_F) or
        input_manager->key_press(InputManager::K_P)) {
        int  x           = input_manager->get_mouse_x();
        int  y           = input_manager->get_mouse_y();
        bool is_platform = input_manager->key_press(InputManager::K_P);

        for (auto& go : object_array) {
            if (go->is("floor")) {
                ((EditableFloor *)go.get())->set_selected(false);
            }
        }

        auto go = new EditableFloor(x, y, 0, is_platform);
        go->set_selected(true);
        add_object(go);
    }

    // save level design
    if (input_manager->is_key_down(InputManager::K_CTRL) and
        input_manager->key_press(InputManager::K_S)) {
        update_level_design();
    }

    // output
    if (input_manager->is_key_down(InputManager::K_O)) {
        printf("%f, %f\n", object_array[0].get()->box.x,
               object_array[0].get()->box.y);
    }

    if (input_manager->key_press(InputManager::K_SHIFT)) {
        Rectangle player_box = test_fighter->box;
        bool is_blood        = test_fighter->is("blood");
        test_fighter->kill();

        if (is_blood) {
            test_fighter = new Flesh("test", player_box.x, player_box.y, 0);
        } else {
            test_fighter = new Blood("test", player_box.x, player_box.y, 0);
            add_object(test_fighter);
        }
    }

    for (auto& background : backgrounds) {
        background.first.update(delta);
    }

    update_array(delta);
}

/**
 * render method.
 * renders the background given a x and y positions.
 */
void EditState::render() {
    for (auto& background : backgrounds) {
        background.first.render(background.second.x, background.second.y);
    }

    render_array();
}

/**
 * pause method.
 * Not implemented.
 */
void EditState::pause()  {}

/**
 * resume method.
 * Not implemented.
 */
void EditState::resume() {}

/**
 * read_level_design method.
 * Reads the levels in the game given a specific folder.
 */
void EditState::read_level_design() {
    float x, y, width, crotation;
    int   platform;
    ifstream level_design(RES_FOLDER + "stage_" + stage + "/level_design.dat");

    if (not level_design.is_open()) {
        printf("Level design of stage %s can't be opened\n", stage.c_str());
        exit(-5);
    }
    string s;
    int    n_backgrounds, n_sprites, speed, n_columns;

    std::getline(level_design, s);

    for (auto& c : s) c -= 15;
    stringstream n_background_line(s);
    n_background_line >> n_backgrounds;

    for (int i = 0; i < n_backgrounds; ++i) {
        std::getline(level_design, s);

        for (auto& c : s) c -= 15;
        stringstream backgrounds_line(s);
        backgrounds_line >> x >> y >> n_sprites >> speed >> n_columns;

        // printf("Dados: %.f %.f %d %d %d\n", x, y, n_sprites, speed,
        // n_columns);
        Sprite background_sprite("stage_" + stage + "/background_" + to_string(
                                     i) + ".png", n_sprites, speed, n_columns);
        Vector position(x, y);
        backgrounds.push_back(std::make_pair(background_sprite, position));
    }


    while (std::getline(level_design, s)) {
        for (auto& c : s) c -= 15;
        stringstream editable_floors_line(s);
        editable_floors_line >> x >> y >> width >> crotation >> platform;

        // printf("Battle: %.f %.f %.f %.f\n", x, y, width, crotation);
        add_object(new EditableFloor(x, y, width, crotation, (bool)platform));
    }
    level_design.close();
}

/**
 * update_level_design method.
 * updates a level previously created. Overwrights a old fine with the creation
 * of a new file.
 */
void EditState::update_level_design() {
    ifstream level_design(RES_FOLDER + "stage_" + stage + "/level_design.dat",
                          std::ios::binary);
    ofstream old_level_design(
        RES_FOLDER + "stage_" + stage + "/level_design.dat.old",
        std::ios::trunc | std::ios::binary);

    old_level_design << level_design.rdbuf();
    level_design.close();
    old_level_design.close();

    ofstream new_level_design(RES_FOLDER + "stage_" + stage +
                              "/level_design.dat", std::ios::trunc);
    ifstream backup(RES_FOLDER + "stage_" + stage + "/level_design.dat.old",
                    std::ios::binary);
    string s;

    for (unsigned i = 0; i <= backgrounds.size(); ++i) {
        std::getline(backup, s);
        new_level_design << s << std::endl;
    }
    old_level_design.close();

    for (auto& go : object_array) {
        if (go->is("floor")) {
            new_level_design << ((EditableFloor *)go.get())->get_information() <<
            std::endl;
        }
    }
    new_level_design.close();
}
