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
    std::fstream config_file(CONFIGURATION_FILE_PATH);
    assert(config_file.is_open());

    config_file >> width >> height >> fullscreen;
}

/** 
 * Accessor to width private attribute.  
 * 
 * @returns Game's windows width. Unit: px, [0,]
 */
int Config::get_width() {
    return width;
}

/** 
 * Accessor to height private attribute.
 * @returns  Game's windows height. Unit: px, [0,]
 */
int Config::get_height() {
    return height;
}

/** 
 * Get fullscreen current status.  
 * 
 * @returns 0 for no, 1 for yes [0,1]  
 */
int Config::is_fullscreen() {
    return fullscreen;
}

/** 
 * Writes to file res/config_file.dat screen information.  
 * 
 * @param cwidth Unit: px, [0,]
 * @param cheight Unit: px, [0,]
 * @param cfullscreen [0,1]
 */
void Config::update_information(int cwidth, int cheight, int cfullscreen) {
    width = cwidth;
    height = cheight;
    fullscreen = cfullscreen;

    std::ofstream config_file(CONFIGURATION_FILE_PATH, std::ios::trunc);
    assert(config_file.is_open());

    config_file << width << " " << height << " " << fullscreen << std::endl;
    config_file.close();
}
