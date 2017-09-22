/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
*
* This work is licensed under the terms of the MIT license.

* For a copy, see <https://opensource.org/licenses/MIT>.
*/
/**
* @file Sprite.cpp
* This file contains the definition of the Sprite class methods.
*/

#include <iostream>

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Config.h"

#include <cmath>

#define PI 3.14159265358979

/**
* A constructor.
* Initialize the texture, scales of x and y, counting and time of frames and the
* current frame and the elapsed time to each one initial value.
*/
Sprite::Sprite() {
  texture = nullptr;
  scale_x = scale_y = 1;
  frame_count = 1;
  frame_time = 1;
  current_frame = time_elapsed = 0;
}

/**
* A constructor.
* Initialize the file where the images come from, counting and time of frames,
* number of columns and the current frame.
*
* @param file where the images come from.
* @param cframe_count is the frames counting.
* @param cframe_time is the frame time.
* @param ccolumns is the number of columns.
* @param cur_frame is the number of the current frame.
*/
Sprite::Sprite(string file, int cframe_count, float cframe_time, int ccolumns,
               int cur_frame) {
  frame_count = cframe_count;
  frame_time = cframe_time;
  current_frame = cur_frame;
  columns = (ccolumns ? ccolumns : frame_count);
  rows = ceil((1.0 * frame_count) / columns);
  time_elapsed = 0;
  texture = nullptr;
  finished = false;
  open(RES_FOLDER + file);

  scale_x = scale_y = 1;
}

/**
* The destructor.
* Free the memory allocated to store Sprite objects.
*/
Sprite::~Sprite() {
}

/**
* Sprite width getter.
* Returns the saved sprite width on x scale units.
*
* @return the sprite width.
*/
int Sprite::get_width() {
  return width * scale_x;
}

/**
* Sprite width getter.
* Returns the saved sprite height on y scale units.
*
* @return the sprite height.
*/
int Sprite::get_height() {
  return height * scale_y;
}

/**
* Check if Sprite is open.
* Returns true if texture has some value (if is not null).
*
* @return true or false according to texture pointer value.
*/
bool Sprite::is_open() {
  return texture != nullptr;
}

/**
* Open the Sprite.
* Initialize the sprites images from the corresponding source file.
*
* @param name of the file from the image come from.
*/
void Sprite::open(string file) {
  texture = Resources::get_image(file);

  int query_texture = SDL_QueryTexture(texture.get(), nullptr, nullptr,
  &width, &height);

  width /= columns;
  height /= rows;
  if (query_texture) {
    printf("Open: %s\n", SDL_GetError());
    exit(-1);
  }

  set_clip((current_frame % columns) * width,
           (current_frame / columns) * height,
            width,
            height);
}

/**
* Clip setter.
* Sets a the frames sequence  position.
*
* @param x stores the horizontal coordinate value.
* @param y stores the vertical coordinate value.
* @param w stores the width value.
* @param h stores the height value.
*/
void Sprite::set_clip(int x, int y, int w, int h) {
  clip_rect = SDL_Rect{x, y, w, h};
}

/**
* Frame setter.
* Sets a new frame.
*
* @param frame stores the value of the new frame that will be saved and updated
* as a current frame.
*/
void Sprite::set_frame(int frame) {
  current_frame = frame;
  set_clip((current_frame % columns) * width,
           (current_frame / columns) * height,
            width,
            height);
}

/**
* Frame counting setter.
* Sets the current value of the frame counter.
*
* @param cframe_count stores the value that will be saved and updated the time
* of the counter.
*/
void Sprite::set_frame_count(int cframe_count) {
  frame_count = cframe_count;
}

/**
* Frame time setter.
* Sets the current time of a frame.
*
* @param cframe_time stores the value that will be saved and updated the time of
* the old frame.
*/
void Sprite::set_frame_time(float cframe_time) {
  frame_time = cframe_time;
}

/**
* Update method.
* Update the sprites in the game.
*
* @param delta is the variation of time in the game. The elapsed time increases
* according to this variation.
*/
void Sprite::update(float delta) {
  time_elapsed += delta;
  if (time_elapsed >= frame_time) {
    time_elapsed = 0;

    current_frame = current_frame + 1;
    if (current_frame == frame_count) {
      finished = true;
      current_frame = 0;
    }
    set_clip((current_frame % columns) * width,
             (current_frame / columns) * height,
              width,
              height);
  }
}

/**
* Render method.
* Render the sprites in the game.
*
* @param x is the scenario horizontal position.
* @param y is the scenario vertical position.
* @param angle is the sprite angle.
* @param flip determines the flip movement.
*/
void Sprite::render(int x, int y, float angle, SDL_RendererFlip flip) {
  SDL_Rect dstrect = SDL_Rect{x,
                              y,
                              static_cast<int>(clip_rect.w * scale_x),
                              static_cast<int>(clip_rect.h * scale_y)};

  angle *= (180 / PI);
  int render_copy = SDL_RenderCopyEx(Game::get_instance().get_renderer(),
                                     texture.get(),
                                     &clip_rect,
                                     &dstrect,
                                     angle,
                                     nullptr,
                                     flip);
  if (render_copy) {
    printf("Render: %s\n", SDL_GetError());
    exit(-1);
  }
}

/**
* Scale x setter.
* Sets individually the x axis scale to a new value.
*
* @param scale stores the value that will be saved and updated in the
* scale_x.
*/
void Sprite::set_scale_x(float scale) {
  scale_x = scale;
}

/**
* Scale y setter.
* Sets individually the y axis scale to a new value.
*
* @param scale stores the value that will be saved and updated in the
* scale_y.
*/
void Sprite::set_scale_y(float scale) {
  scale_y = scale;
}

/**
* Scale y and xsetter.
* Sets simultaneously the y and the x axis scale to the same value.
*
* @param scale stores the value that will be saved and updated in the
* scale_y and scale_x variables.
*/
void Sprite::set_scale(float scale) {
  scale_x = scale_y = scale;
}

/**
* Scale y and xsetter.
* Sets simultaneously the y and the x axis scale to the different value.s
*
* @param cscale_x stores the value that will be saved and updated in the
* scale_x variable.
* @param cscale_y stores the value that will be saved and updated in the
* scale_y variable.
*/
void Sprite::set_scale(float cscale_x, float cscale_y) {
  scale_x = cscale_x;
  scale_y = cscale_y;
}

/**
* Update scale x.
* Updates the scale x to a new value.
*
* @param scale stores value of the scale that will be saved and updated in the
* scale_x variable. If the value is very small (< 0.5), scale_x receive 0.5.
*/
void Sprite::update_scale_x(float scale) {
  scale_x += scale;
  if (scale_x < 0.05) scale_x = 0.05;
}

/* Restart frame counting.
* Reinitialize the current frame and set his finished condition as false.
*
* @param cframe is the new frame to be updated.
*/
void Sprite::restart_count(int cframe) {
  current_frame = cframe;
  finished = false;
}

/* Check if in use sprite is finished.
* Returns true if the sprint use has ended.
*
* @return true or false according to the use state of the sprite.
*/
bool Sprite::is_finished() {
  return finished;
}

/* Sprite current frame getter.
* Returns the saved current frame.
*
* @return the current frame.
*/
int Sprite::get_current_frame() {
  return current_frame;
}
