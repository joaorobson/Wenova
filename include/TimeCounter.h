#ifndef INCLUDE_TIMECOUNTER_H_
#define INCLUDE_TIMECOUNTER_H_

#include <string>

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Text.h"

using std::string;

class TimeCounter : public GameObject {
 public:
    /** Constructor.
     * This constructor builds sprites and texts to indicate the remaining time
     * in a battle.
     */
    TimeCounter();

    /** Destructor.
     * Nothing to do.
     */
    ~TimeCounter();

    /** Function that updates the time showed.
     * This function makes sprites variate and texts accoding to the remaining
     * time.
     *
     * @param delta a float variation to update the remaining time of a battle.
     */
    void update(float delta);

    /** Function that renders a the time.
     * This function renders the text that represents the remaining
     * time of a battle.
     */
    void render();

    /** Function get state dead.
     * This function returns the state dead.
     *
     * @return a boolean default value.
     */
    bool is_dead();

    /** Function get end of battle.
     * This function indicates if a battle has finished or not.
     *
     * @return a boolean value accoding to the remaining time.
     */
    bool is_over();

    /** Function notify collision.
     * Nothing to do.
     *
     * @param GameObject a pointer to a GameObject.
     */
    void notify_collision(GameObject *object);

    static const int total_time = 100;

 private:
    Sprite bg;
    Timer  timer;
    Text  *text;
    float  remaining_seconds;

    /** Function that returns remaining time.
     * This function returns a string representation of the remaining time
     * of a battle.
     *
     * @return is a string representing the remaining time.
     */
    string get_time_string();
};

#endif  // INCLUDE_TIMECOUNTER_H_
