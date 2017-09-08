#include "Rectangle.h"

//Create a object "rectangle" null
Rectangle::Rectangle() {}

//Create a object "rectangle" complete
Rectangle::Rectangle(float ax, float ay, float w, float h) : x(ax), y(ay), width(w), height(h) {}

//Check if any object is inside the rectangle
bool Rectangle::is_inside(float mx, float my) {
    bool horizontal_in = (mx >= x - width/2 and mx <= x + width/2);
    bool vertical_in = (my >= y - height/2 and my <= y + height/2);

    return horizontal_in and vertical_in;
}

//Check the horizontal size of rectangle
float Rectangle::get_x() const {
    return x;
}

//Check the vertical size of rectangle
float Rectangle::get_y() const {
    return y;
}

//Inserts a horizontal size in rectangle
void Rectangle::set_x(float cx) {
    this->x = cx;
}

//Inserts s vertical size in rectangle
void Rectangle::set_y(float cy) {
    this->y = cy;
}

//Check the horizontal draw of rectangle
float Rectangle::get_draw_x() const {
    return x - width/2;
}

//Check the vertical draw of rectangle
float Rectangle::get_draw_y() const {
    return y - height/2;
}

//Chack the width of rectangle
float Rectangle::get_width() const {
    return width;
}

//Check the height of rectangle
float Rectangle::get_height() const {
    return height;
}

//Inserts the width of rectangle
void Rectangle::set_width(float w) {
    width = w;
}

//Inserts the height of rectangle
void Rectangle::set_height(float h) {
    height = h;
}

//Check the center of rectangle
Vector Rectangle::get_center() const {
    return Vector(x, y);
}
