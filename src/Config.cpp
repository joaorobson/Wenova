#include "Config.h"

#include <fstream>

int Config::width;
int Config::height;
int Config::fullscreen;

/** 
 * Will write current screen configurations to res/config_file.dat.  
 */
void Config::init() {
    std::fstream config_file(RES_FOLDER + "config_file.dat");
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
    std::ofstream config_file(RES_FOLDER + "config_file.dat", std::ios::trunc);
    config_file << width << " " << height << " " << fullscreen << std::endl;
    config_file.close();
}
