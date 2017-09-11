#ifndef INCLUDE_JOYSTICKCONFIGSTATE_H_
#define INCLUDE_JOYSTICKCONFIGSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Sound.h"

class JoystickConfigState : public State{
 private:
    Sprite background, joystick_help, back_btn, test_btn, keyboard;
    Text *back_txt, *test_txt, *press, *select_text, *and_text, *start_text,
        *to_go_back;
    bool on_test, is_keyboard;
    Sound blocked, selected, changed;

 public:
	 /** Constructor.
		* This constructor builds sprites to render the option 'JOYSTICK' located on
		* the menu 'Options' of the game.
		*
		* @param joystick_id and integer argument that represents the id of one of
		* the four joysticks that can be pluged.
		* @param ckeyboard a boolean argument that indicates if a keyboard is
		* connected.
		*/
    explict JoystickConfigState(int joystick_id, bool ckeyboard = false);

		/** Function that updates sprites on joystick test mode.
		 * This function makes sprites change color accoding to the button pressed by
		 * the user on the joystick test mode located at the menu
		 * "Options->Joystick->Test".
		 *
		 * @param delta a float variation to update joystick state.
		 */
    void update(float delta);
		/** Function that renders keyboard or joystick help images.
		 * This function renders keyboard or joystick help images if user select one of
		 * the options: 'keyboard' and 'joystick'; located at the menu 'Options'.
		 * Besides that, it will render buttons on the joystick test mode.
		 */
    void render();

		/** Pause function.
		 * Nothing to do.
		 */
    void pause();
		/** Resume function.
		 * Nothing to do.
		 */
    void resume();
};

#endif  // INCLUDE_JOYSTICKCONFIGSTATE_H_
