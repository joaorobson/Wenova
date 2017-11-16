/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Resources.cpp
 * Brief Description.
 */

#include "Resources.h"

#include "Game.h"

#include <algorithm>

unordered_map<string, shared_ptr<SDL_Texture> > Resources::image_table;
unordered_map<string, shared_ptr<Mix_Music> > Resources::music_table;
unordered_map<string, shared_ptr<Mix_Chunk> > Resources::sound_table;
unordered_map<string, shared_ptr<TTF_Font> > Resources::font_table;

/**
 * Brief Description.
 *
 * @param file
 *
 * @returns
 */
shared_ptr<SDL_Texture> Resources::get_image(string file) {
    assert(file.empty() != true);

    if (image_table.find(file) == image_table.end()) {
        SDL_Texture *tx =
            IMG_LoadTexture(Game::get_instance().get_renderer(), file.c_str());

        if (tx == nullptr) {
            printf("%s: %s\n", SDL_GetError(), file.c_str());
            exit(-1);
        } else {
            /* Nothing to do. */
        }

        shared_ptr<SDL_Texture> texture(
            tx, [](SDL_Texture *txt) { SDL_DestroyTexture(txt); });

        image_table.emplace(file, texture);
    } else {
        /* Nothing to do. */
    }

    return image_table[file];
}

/**
 * Brief Description.
 */
void Resources::clear_images() {
    for (auto texture : image_table) {
        if (texture.second.unique()) {
            image_table.erase(texture.first);
        } else {
            /* Nothing to do. */
        }
    }
}

/**
 * Brief Description.
 *
 * @param file
 *
 * @returns
 */
shared_ptr<Mix_Music> Resources::get_music(string file) {
    assert(file.empty() != true);

    if (music_table.find(file) == music_table.end()) {
        Mix_Music *mx = Mix_LoadMUS(file.c_str());

        if (mx == nullptr) {
            printf("%s: %s\n", Mix_GetError(), file.c_str());
            exit(-1);
        } else {
            /* Nothing to do. */
        }

        shared_ptr<Mix_Music> music(mx,
                                    [](Mix_Music *msc) { Mix_FreeMusic(msc); });

        music_table.emplace(file, music);
    } else {
        /* Nothing to do. */
    }

    return music_table[file];
}

/**
 * Brief Description.
 */
void Resources::clear_music() {
    for (auto music : music_table) {
        if (music.second.unique()) {
            music_table.erase(music.first);
        } else {
            /* Nothing to do. */
        }
    }
}

/**
 * Brief Description.
 *
 * @param file
 *
 * @returns
 */
shared_ptr<Mix_Chunk> Resources::get_sound(string file) {
    assert(file.empty() != true);

    if (sound_table.find(file) == sound_table.end()) {
        Mix_Chunk *ck = Mix_LoadWAV(file.c_str());

        if (ck == nullptr) {
            printf("%s: %s\n", Mix_GetError(), file.c_str());
            exit(-1);
        } else {
            /* Nothing to do. */
        }

        shared_ptr<Mix_Chunk> sound(ck,
                                    [](Mix_Chunk *chk) { Mix_FreeChunk(chk); });

        sound_table.emplace(file, sound);
    } else {
        /* Nothing to do. */
    }

    return sound_table[file];
}

/**
 * Not used method.
 */
void Resources::clear_sound() {
    for (auto sound : sound_table) {
        if (sound.second.unique()) {
            sound_table.erase(sound.first);
        } else {
            /* Nothing to do. */
        }
    }
}

/**
 * Brief Description.
 *
 * @param file
 * @param size
 *
 * @returns
 */
shared_ptr<TTF_Font> Resources::get_font(string file, int size) {
    assert(file.empty() != true);

    string tsize = std::to_string(size);

    if (font_table.find(file + tsize) == font_table.end()) {
        TTF_Font *ft = TTF_OpenFont(file.c_str(), size);

        if (ft == nullptr) {
            printf("%s: %s\n", SDL_GetError(), file.c_str());
            exit(-1);
        } else {
            /* Nothing to do. */
        }

        shared_ptr<TTF_Font> font(ft,
                                  [](TTF_Font *fnt) { TTF_CloseFont(fnt); });

        font_table.emplace(file + tsize, font);
    } else {
        /* Nothing to do. */
    }

    return font_table[file + tsize];
}

/**
 * Brief Description.
 */
void Resources::clear_fonts() {
    for (auto font : font_table) {
        if (font.second.unique()) {
            font_table.erase(font.first);
        } else {
            /* Nothing to do. */
        }
    }
}
