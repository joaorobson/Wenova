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

int Config::width;
int Config::height;
int Config::fullscreen;

/**
 * Will write current screen configurations to res/config_file.dat.
 */
void Config::init() {
    LOG(DEBUG) << "Starting Config init";

    std::fstream config_file(CONFIGURATION_FILE_PATH);

#ifndef NDEBUG
    if (not config_file.is_open()) {
        LOG(FATAL) << "File couldn't be open";
    }
#endif

    config_file >> width >> height >> fullscreen;

    LOG(DEBUG) << "Ending Config init";
}

/**
 * Accessor to width private attribute.
 *
 * @returns Game's windows width. Unit: px, [0,]
 */
int Config::get_width() {
    LOG(DEBUG) << "Starting Config get_width";

    int return_value = width;

#ifndef NDEBUG
    std::string log_message = "Ending Config get_width returning value: " +
        std::to_string(return_value);
    LOG(DEBUG) << log_message;

    if (width <= 0) {
        LOG(WARNING) << "Width is being returned with suspicious values";
    }
#endif

    return return_value;
}

/**
 * Accessor to height private attribute.
 * @returns  Game's windows height. Unit: px, [0,]
 */
int Config::get_height() {
    LOG(DEBUG) << "Starting Config get_height";

    int return_value = height;

#ifndef NDEBUG
    std::string log_message = "Ending Config get_height returning value: " +
        std::to_string(return_value);
    LOG(DEBUG) << log_message;

    if (height <= 0) {
        LOG(WARNING) << "Height is being returned with suspicious values";
    }
#endif

    return return_value;
}

/**
 * Get fullscreen current status.
 *
 * @returns 0 for no, 1 for yes [0,1]
 */
int Config::is_fullscreen() {
    LOG(DEBUG) << "Starting Config is_fullscreen";

    int return_value = fullscreen;

#ifndef NDEBUG
    std::string log_message = "Ending Config is_fullscreen returning value: " +
        std::to_string(return_value);
    LOG(DEBUG) << log_message;
#endif

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
#ifndef NDEBUG
    std::string log_message = "Starting Config update_information, cwidth: ";
    log_message += std::to_string(cwidth) += ", cheight: ";
    log_message += std::to_string(cheight) + ", cfullscreen: " +
        std::to_string(cfullscreen);

    LOG(DEBUG) << log_message;
#endif

    width = cwidth;
    height = cheight;
    fullscreen = cfullscreen;

    std::ofstream config_file(CONFIGURATION_FILE_PATH, std::ios::trunc);

#ifndef NDEBUG
    if (not config_file.is_open()) {
        LOG(FATAL) << "File couldn't be open";
    }
#endif

    config_file << width << " " << height << " " << fullscreen << std::endl;
    config_file.close();

    LOG(DEBUG) << "Ending Config update_information";
}
