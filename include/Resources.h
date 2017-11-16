/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Resources.h
 * This file contains the definitions of all methods and attributes of the class
 * Resources.
 */
#ifndef INCLUDE_RESOURCES_H_
#define INCLUDE_RESOURCES_H_

#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

using std::unordered_map;
using std::string;
using std::shared_ptr;

class Resources {
 private:
    static unordered_map<string, shared_ptr<SDL_Texture> >
        image_table; /**< Map of */
                     /**< a key string and a texture sprite. */
    static unordered_map<string, shared_ptr<Mix_Music> >
        music_table; /**< Map of */
                     /**< a key string and a mix music. */
    static unordered_map<string, shared_ptr<Mix_Chunk> >
        sound_table; /**< Map of */
                     /**< a key string and a mix chunk. */
    static unordered_map<string, shared_ptr<TTF_Font> >
        font_table; /**< Map of */
                    /**< a key string and a text font. */

 public:
    static shared_ptr<SDL_Texture> get_image(string file);
    static void clear_images();

    static shared_ptr<Mix_Music> get_music(string file);
    static void clear_music();

    static shared_ptr<Mix_Chunk> get_sound(string file);

    /**
     * Not used method.
     */
    static void clear_sound();

    static shared_ptr<TTF_Font> get_font(string file, int size);
    static void clear_fonts();
};

#endif  // INCLUDE_RESOURCES_H_
