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
      /**
	     *update function.
       *updates the objects on the menu screen of the game.
	     */
  	  void update(float delta);
      /**
	     *render function.
       *Renders the objects at the game menu screen.
	     */
  	  void render();
      /**
			 *Pause function.
			 *Nothing to do.
			 */
    	void pause();
      /**
			 *Resume Function.
			 *Nothing to do.
			 */
  	  void resume();
      /**
       * process_input method.
       * this method recognizes the user input button and acts accordingly.
       */
  	  void process_input();

  private:
  	  Sprite background, green_ship, red_ship, title, planet;
  	  Text* start_option;
  	  Sound blocked, selected, changed;
  	  Music music;
  	  Timer text_timer;
  	  vector<Text*> options;
      /**
       * Buttons the controller has for input.
       */
  	  enum Button { A, B, Y, LEFT, RIGHT, SELECT, START, LB, RT };
  	  bool pressed[N_VALUE], is_holding[N_VALUE];
  		bool start_pressed, show_text;
  		int current_option;
};


#endif
