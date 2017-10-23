#include "Game.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
#include "MenuState.h"

int main(int, char **){
	Game game("Wenova - Rise of Conquerors");
     LOG(INFO) << "My first info log using default logger";

	State * state =  new MenuState(false);
	game.push(state);

	game.run();

	return 0;
}
