/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
*
* This work is licensed under the terms of the MIT license.

* For a copy, see <https://opensource.org/licenses/MIT>.
*/
/**
* @file Sprite.h
* This file contains the declaration of the Sprite class methods and attributes.
*/

#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

#include <iostream>
#include <memory>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using std::string;
using std::shared_ptr;

class Sprite {
 private:
    shared_ptr<SDL_Texture> texture = nullptr; /**< Sprite texture. */
    int width;                                 /**< Sprite width. Unit: px. */
    int height;                                /**< Sprite height. Unit: px. */
    int current_frame;  /**< Current frame exhibited from all sprites frames. */
    float time_elapsed; /**< Counted time over Sprite exhibition. */
    float frame_time;   /**< Time of a frame ocurrence. */
    int frame_count;    /**< Number of the frame. */
    int rows;           /**< Number of rows filled by a sprite. */
    int columns;        /**< Number of columns filled by a sprite. */
    SDL_Rect clip_rect; /**< Sprites frames positioning box. */
    float scale_x_axis; /**< Horizontal scale. */
    float scale_y_axis; /**< Vertical scale. */
    bool finished;      /**< Check if the sprite use is no longer required. */

 public:
  Sprite(string file, int cframe_count = 1, float cframe_time = 1,
         int columns = 0, int cur_frame = 0);
  Sprite();
  ~Sprite();

  void render(int x = 0, int y = 0, float angle = 0,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
  void set_clip(int x, int y, int w, int h);
  void update(float delta);
  int get_current_frame();
  bool is_finished();
  void restart_count(int cframe = 0);
  int get_height();
  int get_width();
  void set_scale(float scale);
  void set_scale_x(float scale);
  void update_scale_x(float scale);
 private:
  void open(string file);
  void set_frame(int frame);
  void set_frame_count(int cframe_count);
  void set_frame_time(float cframe_time);
  bool is_open();
  void set_scale_y(float scale);
  void set_scale(float cscale_x_axis, float cscale_y_axis);

};

#endif  // INCLUDE_SPRITE_H_
