/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Config.cpp
 * Implements class Config methods.
 */

#include "Config.h"

#include <fstream>

int Config::width;
int Config::height;
int Config::fullscreen;

/**
 * Will write current screen configurations to res/config_file.dat.
 */
void Config::init() {
    LOG(INFO) << "Starting CharacterSelectState init";

    std::fstream config_file(CONFIGURATION_FILE_PATH);

    if (not config_file.is_open()) {
        LOG(FATAL) << "File couldn't be open";
    }
    assert(config_file.is_open());

    config_file >> width >> height >> fullscreen;

    LOG(INFO) << "Ending CharacterSelectState init";
}

/**
 * Accessor to width private attribute.
 *
 * @returns Game's windows width. Unit: px, [0,]
 */
int Config::get_width() {
    LOG(INFO) << "Starting CharacterSelectState get_width";

    return_value = width;
    LOG(INFO) << "Ending CharacterSelectState get_width returning value: "
              << return_value;

    return return_value;
}

/**
 * Accessor to height private attribute.
 * @returns  Game's windows height. Unit: px, [0,]
 */
int Config::get_height() {
    LOG(INFO) << "Starting CharacterSelectState get_height";

    return_value = height;
    LOG(INFO) << "Ending CharacterSelectState get_height returning value: "
              << return_value;

    return return_value;
}

/**
 * Get fullscreen current status.
 *
 * @returns 0 for no, 1 for yes [0,1]
 */
int Config::is_fullscreen() {
    LOG(INFO) << "Starting CharacterSelectState is_fullscreen";

    return_value = fullscreen;
    LOG(INFO) << "Ending CharacterSelectState is_fullscreen returning value: "
              << return_value;

    return return_value;
}

/**
 * Writes to file res/config_file.dat screen information.
 *
 * @param cwidth Unit: px, [0,]
 * @param cheight Unit: px, [0,]
 * @param cfullscreen [0,1]
 */
void Config::update_information(int cwidth, int cheight, int cfullscreen) {
    LOG(INFO) << "Starting CharacterSelectState update_information, cwidth: "
              << cwidth << ", cheight: " << cheight
              << ", cfullscreen: " << cfullscreen;

    width = cwidth;
    height = cheight;
    fullscreen = cfullscreen;

    std::ofstream config_file(CONFIGURATION_FILE_PATH, std::ios::trunc);

    if (not config_file.is_open()) {
        LOG(FATAL) << "File couldn't be open";
    }
    assert(config_file.is_open());

    config_file << width << " " << height << " " << fullscreen << std::endl;
    config_file.close();

    LOG(INFO) << "Ending CharacterSelectState update_information";
}
