#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Sound.h"
#include "Music.h"
#include <assert.h>

#define N_VALUE 15

class MenuState : public State {
public:
    MenuState(bool main_menu = false);

	  void update(float delta);
	  void render();

  	void pause();
	  void resume();

	  void process_input();

private:
	  Sprite background, green_ship, red_ship, title, planet;
	  Text* start_option;
	  Sound blocked, selected, changed;
	  Music music;
	  Timer text_timer;
	  vector<Text*> options;
	  enum Button { A, B, Y, LEFT, RIGHT, SELECT, START, LB, RT };
	  bool pressed[N_VALUE], is_holding[N_VALUE];
		bool start_pressed, show_text;
		int current_option;
};


#endif
