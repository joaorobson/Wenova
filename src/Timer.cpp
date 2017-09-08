#include "Timer.h"

//Initialize a timer
Timer::Timer() {
    time = 0;
}

//Update the timer
void Timer::update(float delta) {
    time += delta;
}

//Restart the timer
void Timer::restart() {
    time = 0;
}

//Check the timer
float Timer::get() {
    return time;
}

//Insert a timer
void Timer::set(float ctime) {
    time = ctime;
}
