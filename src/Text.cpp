/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 *
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Text.cpp
 * This file contains the definition of the Text class methods.
 */

#include "Text.h"
#include <assert.h>
#include "Game.h"
#include "Resources.h"
#include "Config.h"

#define SOLID Text::TextStyle::SOLID
#define SHADED Text::TextStyle::SHADED
#define BLENDED Text::TextStyle::BLENDED

#define RECTANGLE_UPPER_LEFT_CORNER_POSITION_X 0 
#define RECTANGLE_UPPER_LEFT_CORNER_POSITION_Y 0 
#define CLIP_BORDERS_OFFSET 0.5
#define NO_OFFSET 0
#define BLACK_BACKGROUND_ON_SDL_RGBA_COLOR {0,0,0,255}


/**
 * A constructor.
 * Initialize the style, color, textuxe, font size and position of the text in 
 * the game.
 *
 * @param cfont_file is the font file where the respective font is.
 * @param cfont_size is the size of the font.
 * @param cstyle is the text style from the class TextStyle.
 * @param ctext is the text that will be rendered.
 * @param ccolor is text color.
 * @param x_axis_position is the text horizontal position.
 * @param y_axis_position is the text vertical position.
 */ 
Text::Text(string cfont_file, int cfont_size, TextStyle cstyle, string ctext,
           SDL_Color ccolor, int x_axis_position, int y_axis_position) {

  font_size = cfont_size;  
  style = cstyle;
  text = ctext;
  color = ccolor;
  box.set_x(x_axis_position);
  box.set_y(y_axis_position);
  texture = nullptr;
  open(cfont_file, font_size);
  remake_texture();
  set_pos(x_axis_position, y_axis_position, true, true);
}

/**
 * A constructor.
 * Initialize the texture attribute to null.
 */
Text::Text() {
  texture = nullptr;
}


/**
 * The destructor.
 * Free the memory allocated to store Text objects.
 */
Text::~Text() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  } else { 
    LOG(FATAL) << "texture has null value";
  } 
}

/**
 * Render method.
 * Render the text in menus and game titles.
 *
 * @param camera_x is the scenario horizontal position.
 * @param camera_y is the scenario vertical position.
 */
void Text::render(int camera_x, int camera_y) {
  SDL_Rect src_rect = { RECTANGLE_UPPER_LEFT_CORNER_POSITION_X,
                        RECTANGLE_UPPER_LEFT_CORNER_POSITION_Y,
                        static_cast<int>(box.get_width()),
                        static_cast<int>(box.get_height())
                      };

  SDL_Rect dest_rect = { static_cast<int>(box.get_x()) + camera_x,
                         static_cast<int>(box.get_y()) + camera_y,
                         static_cast<int>(box.get_width()),
                         static_cast<int>(box.get_height())
                       };


  int render_copy = SDL_RenderCopy(Game::get_instance().get_renderer(),
                                   texture, &src_rect, &dest_rect);
  if (render_copy) {
    printf("Render text: %s\n", SDL_GetError());
    exit(-1);
  } else { 
    /* Nothing to do. */    
  } 
}

/**
 * Set the text position.
 * From the x and y coordinates set the Text object position.
 *
 * @param x is the text horizontal position.
 * @param y is the text vertical position.
 * @param center_x checks if the text is centered horizontally;
 * @param center_y checks if the text is centered vertically.
 */
void Text::set_pos(int x_axis_position, int y_axis_position, bool center_x, 
                   bool center_y) {
  box.set_x(x_axis_position - (center_x ? clip_rect.w * CLIP_BORDERS_OFFSET : 
                                          NO_OFFSET));
  box.set_y(y_axis_position - (center_y ? clip_rect.h * CLIP_BORDERS_OFFSET : 
                                          NO_OFFSET));
}

/**
 * ctext setter.
 * Sets the text to a new text.
 *
 * @param ctext stores the text that will be saved and updated in the
 * texture.
 */
void Text::set_text(string ctext) {
  assert(ctext != "");
  text = ctext;
  remake_texture();
}

/**
 * color setter.
 * Sets the color to a new color.
 *
 * @param ccolor stores the color that will be saved and updated in the
 * texture.
 */
void Text::set_color(SDL_Color ccolor) {
  color = ccolor;
  remake_texture();
}

/**
 * style setter.
 * Sets the style to a new style.
 *
 * @param cstyle stores the style that will be saved and updated in the
 * texture.
 */
void Text::set_style(TextStyle cstyle) {
  assert(cstyle != (TextStyle) NULL);
  style = cstyle;
  remake_texture();
}

/**
 * cfont_size setter.
 * Sets the style to a new style.
 *
 * @param cfont_size stores the font size that will be saved and updated in the
 * texture.
 */
void Text::set_font_size(int cfont_size) {
  assert(cfont_size > 0);
  font_size = cfont_size;
  remake_texture();
}

/**
 * Change texture.
 * Remakes the texture of the game interface from styles options and sets the new
 * text box width and height.
 */
void Text::remake_texture() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  } else { 
    LOG(FATAL) << "texture has null value";
  } 

  SDL_Surface * surface;
  switch (style) {
    case SOLID:
      surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
      break;
    case SHADED:
      surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color,
                                      BLACK_BACKGROUND_ON_SDL_RGBA_COLOR);
      break;
    case BLENDED:
      surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
      break;
  }

  if (surface == nullptr) {
    printf("%s\n", SDL_GetError());
    exit(-3);
  } else { 
    /* Nothing to do. */    
  } 

  texture = SDL_CreateTextureFromSurface(Game::get_instance().get_renderer(),
                                         surface);
  SDL_FreeSurface(surface);

  int w, h;
  int query_texture = SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  if (query_texture) {
    printf("Remake texture: %s\n", SDL_GetError());
    exit(-1);
  } else {
    /* Nothing to do. */
  }

  box.set_width(w);
  box.set_height(h);
  clip_rect.w = w;
  clip_rect.h = h;
}

/**
 * Opens resource file.
 * Get the fonts files from the resources folder.
 *
 * @param file is the file where the text fonts are.
 * @param size is the font size.
 */
void Text::open(string file, int size) {
  assert(file != "");
  font = Resources::get_font(RESOURCES_FOLDER + file, size);
}

/**
 * Text box horizontal coordinate getter.
 * Returns the saved text box horizontal coordinate.
 *
 * @return the new text box horizontal coordinate.
 */
float Text::get_x() {
  assert(box.get_x() >= 0);
  return box.get_x();
}

/**
 * Text box vertical coordinate getter.
 * Returns the saved text box vertical coordinate.
 *
 * @return the new text box vertical coordinate.
 */
float Text::get_y() {
  assert(box.get_y() >= 0);
  return box.get_y();
}

/**
 * Text box width getter.
 * Returns the saved text box width.
 *
 * @return the new text box width.
 */
float Text::get_width() {
  assert(box.get_width() >= 0);
  return box.get_width();
}

/**
 * Text box height getter.
 * Returns the saved text box height.
 *
 * @return the new text box height.
 */
float Text::get_height() {
  assert(box.get_height() >= 0);
  return box.get_height();
}

/**
 * Text getter.
 * Returns the saved text.
 *
 * @return the new text.
 */
string Text::get_text() {
  assert(text != "");
  return text;
}


