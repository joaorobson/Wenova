/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Config.h
 * Manages configuration about screen exhibition.
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <string>

#define RES_FOLDER string("res/")

using std::string;

class Config {
 public:
    /**
     * Will write current screen configurations to res/config_file.dat.
     */
    static void init();

    /**
     * Accessor to width private attribute.
     *
     * @returns Game's windows width. Unit: px, [0,]
     */
    static int get_width();

    /**
     * Accessor to height private attribute.
     * @returns  Game's windows height. Unit: px, [0,]
     */
    static int get_height();

    /**
     * Get fullscreen current status.
     *
     * @returns 0 for no, 1 for yes [0,1]
     */
    static int is_fullscreen();

    /**
     * Writes to file res/config_file.dat screen information.
     *
     * @param cwidth Unit: px, [0,]
     * @param cheight Unit: px, [0,]
     * @param cfullscreen [0,1]
     */
    static void update_information(int cwidth, int cheight, int cfullscreen);

 private:
    static int width;
    static int height;
    static int fullscreen;
};

#endif  // INCLUDE_CONFIG_H_
