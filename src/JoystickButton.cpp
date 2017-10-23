#include "JoystickButton.h"

#include "InputManager.h"

JoystickButton::JoystickButton(int x, int y, string clabel, int cbutton_id,
                               int cjoystick_id,
                               string csprite) {
    assert(clabel.empty() != true);
    assert(csprite.empty() != true);

    sprite = Sprite("joysticks/" + csprite + ".png");
    pressed_sprite = Sprite("joysticks/pressed_" + csprite + ".png");

    assert(sprite.get_width() > 0);
    assert(sprite.get_height() > 0);
    box = Rectangle(x, y, sprite.get_width(), sprite.get_height());

    button_id = cbutton_id;
    joystick_id = cjoystick_id;
    rotation = 0;
    label = clabel;
    pressed = false;
}

JoystickButton::~JoystickButton() {}

void JoystickButton::update(float) {
    InputManager *input_manager = InputManager::get_instance();
    assert(input_manager != nullptr);

    pressed = input_manager->is_joystick_button_down(button_id, joystick_id);
}

void JoystickButton::render() {
    assert(box.get_draw_x() > 0.0);
    assert(box.get_draw_y() > 0.0);
    sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);

    if (pressed) {
        pressed_sprite.render(box.get_draw_x(), box.get_draw_y(), rotation);
    }
}

bool JoystickButton::is_dead() {
    return false;
}

void JoystickButton::notify_collision(GameObject&) {}
