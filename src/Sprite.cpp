/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.

 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Sprite.cpp
 * This file contains the definition of the Sprite class methods.
 */

#include <assert.h>

#include "Config.h"
#include "Game.h"
#include "Resources.h"
#include "Sprite.h"

#include <cmath>
#include <iostream>

#define PI 3.14159265358979
#define _180_DEGREES 180
#define NO_TIME_ELAPSED 0
#define X_AXIS_SCALE_MIN 0.05
#define INITIAL_X_Y_AXES_SCALE 1
#define INITIAL_FRAME_COUNT_VALUE 1
#define INITIAL_FRAME_TIME 1

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
    open(RESOURCES_FOLDER + file);

    scale_x_axis = scale_y_axis = 1;
}

/**
 * A constructor.
 * Initialize the texture, scales of x and y, counting and time of frames and the
 * current frame and the elapsed time to each one initial value.
 */
Sprite::Sprite() {
    assert(NO_TIME_ELAPSED == 0);
    assert(INITIAL_X_Y_AXES_SCALE == 1);
    texture = nullptr;
    scale_x_axis = scale_y_axis = INITIAL_X_Y_AXES_SCALE;
    frame_count = INITIAL_FRAME_COUNT_VALUE;
    frame_time = INITIAL_FRAME_TIME;
    current_frame = time_elapsed = NO_TIME_ELAPSED;
}


/**
 * The destructor.
 * Free the memory allocated to store Sprite objects.
 */
Sprite::~Sprite() {
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
    /**
     * Check if the SDL texture was initialized correctly.
     */
    if (query_texture) {
        printf("Open: %s\n", SDL_GetError());
        exit(-1);
    } else {
        /* Nothing to do. */
    }

    set_clip((current_frame % columns) * width,
             (current_frame / columns) * height,
             width,
             height);
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
    SDL_Rect dstrect = SDL_Rect {x,
                             y,
                             static_cast<int>(clip_rect.w * scale_x_axis),
                             static_cast<int>(clip_rect.h * scale_y_axis)};

    angle *= (_180_DEGREES / PI); /**< Conversion from degrees to radians. */
    int render_copy = SDL_RenderCopyEx(Game::get_instance().get_renderer(),
                                       texture.get(),
                                       &clip_rect,
                                       &dstrect,
                                       angle,
                                       nullptr,
                                       flip);
    /**
     * Check if the texture portion copied was initialized correctly.
     */
    if (render_copy) {
        printf("Render: %s\n", SDL_GetError());
        exit(-1);
    } else {
        /* Nothing to do. */
    }
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
void Sprite::set_clip(int x_axis_coordinate, int y_axis_coordinate,
                      int clip_width, int clip_height) {
    clip_rect = SDL_Rect {x_axis_coordinate, y_axis_coordinate, clip_width,
                      clip_height};
}

/**
 * Frame setter.
 * Sets a new frame.
 * Not used method.
 *
 * @param frame stores the value of the new frame that will be saved and updated
 * as a current frame.
 */
/*
void Sprite::set_frame(int frame) {
    current_frame = frame;
    set_clip((current_frame % columns) * width,
             (current_frame / columns) * height,
             width,
             height);
}
*/

/**
 * Frame counting setter.
 * Sets the current value of the frame counter.
 *
 * @param cframe_count stores the value that will be saved and updated the time
 * of the counter.
 */
/*
void Sprite::set_frame_count(int cframe_count) {
    frame_count = cframe_count;
}
*/

/**
 * Frame time setter.
 * Sets the current time of a frame.
 * Not used method.
 *
 * @param cframe_time stores the value that will be saved and updated the time
 * of
 * the old frame.
 */
/*
void Sprite::set_frame_time(float cframe_time) {
    frame_time = cframe_time;
}
*/

/**
 * Update method.
 * Update the sprites in the game.
 *
 * @param delta is the variation of time in the game. The elapsed time increases
 * according to this variation.
 */
void Sprite::update(float delta_time) {
    assert(NO_TIME_ELAPSED == 0);
    time_elapsed += delta_time;
    /**
     * Check if the elapsed time of a frame was enough. If so, the elapsed time
     * restarts.
     */

    if (time_elapsed >= frame_time) {
        time_elapsed = NO_TIME_ELAPSED;

        current_frame = current_frame + 1;
        /**
         * Check if the current frame has reached the limit number of repetitions.
         */
        if (current_frame == frame_count) {
            finished = true;
            current_frame = NO_TIME_ELAPSED;
        } else {
            /* Nothing to do. */
        }
        set_clip((current_frame % columns) * width,
                 (current_frame / columns) * height,
                 width,
                 height);
    } else {
        /* Nothing to do. */
    }
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

/**
 * Check if Sprite is open.
 * Returns true if texture has some value (if is not null).
 *
 * @return true or false according to texture pointer value.
 */
bool Sprite::is_open() {
    return texture != nullptr;
}

/* Sprite current frame getter.
 * Returns the saved current frame.
 *
 * @return the current frame.
 */
int Sprite::get_current_frame() {
    assert(current_frame >= 0);
    return current_frame;
}

/**
 * Sprite width getter.
 * Returns the saved sprite width on x scale units.
 *
 * @return the sprite width.
 */
int Sprite::get_width() {
    assert(width * scale_x_axis >= 0);
    return width * scale_x_axis;
}

/**
 * Sprite height getter.
 * Returns the saved sprite height on y scale units.
 *
 * @return the sprite height.
 */
int Sprite::get_height() {
    assert(height * scale_y_axis >= 0);
    return height * scale_y_axis;
}

/**
 * Scale x setter.
 * Sets individually the x axis scale to a new value.
 *
 * @param scale stores the value that will be saved and updated in the
 * scale_x.
 */
void Sprite::set_scale_x(float scale) {
    assert(scale >= 0);
    scale_x_axis = scale;
}

/**
 * Scale y setter.
 * Sets individually the y axis scale to a new value.
 *
 * @param scale stores the value that will be saved and updated in the
 * scale_y.
 */
void Sprite::set_scale_y(float scale) {
    assert(scale >= 0);
    scale_y_axis = scale;
}

/**
 * Scale y and xsetter.
 * Sets simultaneously the y and the x axis scale to the same value.
 *
 * @param scale stores the value that will be saved and updated in the
 * scale_y and scale_x variables.
 */
void Sprite::set_scale(float scale) {
    assert(scale >= 0);
    scale_x_axis = scale_y_axis = scale;
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
void Sprite::set_scale(float cscale_x_axis, float cscale_y_axis) {
    assert(cscale_x_axis >= 0);
    assert(cscale_y_axis >= 0);

    scale_x_axis = cscale_x_axis;
    scale_y_axis = cscale_y_axis;
}

/**
 * Update scale x.
 * Updates the scale x to a new value.
 *
 * @param scale stores value of the scale that will be saved and updated in the
 * scale_x variable. If the value is very small (< 0.5), scale_x receive 0.5.
 */
void Sprite::update_scale_x(float scale) {
    assert(X_AXIS_SCALE_MIN == 0.05);
    assert(scale >= 0);
    scale_x_axis += scale;
    /**
     * Check if the x axis is very small. If so, the scale is set to 0.05.
     */
    if (scale_x_axis < X_AXIS_SCALE_MIN) {
        scale_x_axis = X_AXIS_SCALE_MIN;
    } else {
        /* Nothing to do. */
    }
}
