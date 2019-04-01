#include "hangman_custom.h"

bool hangman_custom::begin_new_game(const std::string& solution)
{
	set_new_game(solution);

	return game_state() == e_game_state::playing;
}
