#ifndef INCLUDE_TEXT_H_
#define INCLUDE_TEXT_H_

#include "SDL_ttf.h"

#include "Rectangle.h"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Text{
 public:
  enum TextStyle {SOLID, SHADED, BLENDED};

 private:
  shared_ptr<TTF_Font> font;  /**< Text font type. */
  SDL_Texture * texture;  /**< Exhibited text texture. */

  string text;  /**< Words from the text. */
  TextStyle style;  /**< Exhibited text style. */
  int font_size;  /**< Size of the exhibited text. */
  SDL_Color color;  /**< Color of the exhibited text. */
  Rectangle box;  /**< /Text box. */
  SDL_Rect clip_rect;  /**< Text frames positioning box. */

  void set_style(TextStyle cstyle);
  void set_font_size(int cfont_size);
  void remake_texture();
  void open(string font_name, int cfont_size);
 public:
  Text(string cfont_file, int cfont_size, TextStyle cstyle, string ctext,
       SDL_Color ccolor, int x_axis_position = 0, int y_axis_position = 0);
  Text();
  ~Text();
  void render(int camera_position_x_axis = 0, int camera_position_y_axis = 0);
  void set_text(string ctext);
  void set_pos(int x, int y, bool center_x = false, bool center_y = false);
  void set_color(SDL_Color ccolor);
  float get_x();
  float get_y();
  float get_width();
  float get_height();
  string get_text();
};

#endif  // INCLUDE_TEXT_H_
