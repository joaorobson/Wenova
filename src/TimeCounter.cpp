/*
 *Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 *This work is licensed under the terms of the MIT license.
 *For a copy, see <https://opensource.org/licenses/MIT>.
 *
 *This file contains implementation of the methods of the class
 *TimeCounter.
 *
 *This file renders and updates a clock during a battle indicating the remaining
 *time.
 */
#include "TimeCounter.h"

using std::to_string;

/** Constructor.
 * This constructor builds sprites and texts to indicate the remaining time
 * in a battle.
 */
TimeCounter::TimeCounter() {
    remaining_seconds = total_time;

    text = new Text("font/8-BIT WONDER.ttf", 50, Text::TextStyle::SOLID, "99",
                    { 255, 255, 255, 255 });

    bg = Sprite("hud/time_board.png");
    box = Rectangle(640, 664, bg.get_width(), bg.get_height());

    text->set_pos(640, 664, true, true);
}

/** Destructor.
 * Nothing to do.
 */
TimeCounter::~TimeCounter() {}

/** Function that updates the time showed.
 * This function makes sprites variate and texts accoding to the remaining time.
 *
 * @param delta a float variation to update the remaining time of a battle.
 */
void TimeCounter::update(float delta) {
    text->set_pos(640, 664, true, true);
    timer.update(delta);
    remaining_seconds -= delta * 0.01 / 3;

    // FIXME
    if (remaining_seconds < 0) {
        remaining_seconds = 0;
    }
    text->set_text(get_time_string());
}

/** Function that renders a the time.
 * This function renders the text that represents the remaining
 * time of a battle.
 */
void TimeCounter::render() {
    bg.render(box.get_draw_x(), box.get_draw_y());
    text->render();
}

/** Function that returns remaining time.
 * This function returns a string representation of the remaining time
 * of a battle.
 *
 * @return is a string representing the remaining time.
 */
string TimeCounter::get_time_string() {
    return to_string(static_cast<int>(remaining_seconds));
}

/** Function get state dead.
 * This function returns the state dead.
 *
 * @return a boolean default value.
 */
bool TimeCounter::is_dead() {
    return false;
}

/** Function get end of battle.
 * This function indicates if a battle has finished or not.
 *
 * @return a boolean value accoding to the remaining time.
 */
bool TimeCounter::is_over() {
    return remaining_seconds <= 0;
}

/** Function notify collision.
 * Nothing to do.
 *
 * @param GameObject a pointer to a GameObject.
 */
void TimeCounter::notify_collision(GameObject*) {}
