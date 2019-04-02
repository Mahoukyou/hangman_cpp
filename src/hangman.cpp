#include "hangman.h"

#include <cctype>

inline int letter_to_zero_based_index(const char letter)
{
	return tolower(letter) - 'a';
}

hangman::hangman() :
	game_state_{ e_game_state::none },
	missed_letters_count_{ 0 }
{

}

hangman::~hangman()
{
	// pure virtual destructor - so we can force this class to be abstract
	// since we don't have any other pure virtual function
}

// Using enum since caller might want to call (like a sound) something on guessed or not guessed
// But there is another possibility, an already guessed letter
hangman::e_guess_letter_result hangman::guess_letter(const char letter)
{
	if (std::isalpha(letter) == 0)
	{
		throw hangman_exception_invalid_guess_letter{ letter };
	}

	if (guessed_letters_[letter_to_zero_based_index(letter)].guessed)
	{
		// todo, do we count this as another missed letter
		return e_guess_letter_result::already_guessed;
	}

	bool found_letter{ false };
	for (size_t i = 0; i < solution().size(); ++i)
	{
		// Leaving the original solution intact, so we have to check both, lower and upper case
		if (solution()[i] == tolower(letter) ||
			solution()[i] == toupper(letter))
		{
			found_letter = true;
			working_solution_[i] = solution()[i];
		}
	}

	guessed_letters_[letter_to_zero_based_index(letter)] = { true, found_letter };

	if (!found_letter)
	{
		++missed_letters_count_;

		if (missed_letters_count() == max_amount_of_wrong_guesses)
		{
			game_state_ = e_game_state::lost;
		}

		return e_guess_letter_result::incorrect;
	}

	if (is_same_string(solution(), working_solution()))
	{
		game_state_ = e_game_state::won;
	}

	return e_guess_letter_result::correct;
}

bool hangman::guess_solution(const std::string& solution)
{
	if (!validate_solution(solution))
	{
		throw hangman_exception_invalid_guess_solution{ solution };
	}

	const auto is_correct = is_same_string(solution, this->solution());
	if (!is_correct)
	{
		game_state_ = e_game_state::lost;
	}

	return is_correct;
}

void hangman::set_new_game(const std::string& new_solution)
{
	if (!validate_solution(new_solution))
	{
		throw hangman_exception_invalid_solution{ new_solution };
	}

	solution_ = new_solution;
	working_solution_ = solution();

	for (auto& sign : working_solution_)
	{
		if (isalpha(sign))
		{
			sign = '_';
		}
	}

	game_state_ = e_game_state::playing;
}

bool hangman::validate_solution(const std::string& solution)
{
	if (solution.empty())
	{
		return false;
	}

	for (const auto letter : solution)
	{
		if (!isalpha(letter) && letter != '-' && letter != ' ')
		{
			return false;
		}
	}

	return true;
}

bool hangman::is_same_string(const std::string& a, const std::string& b)
{
	if (a.size() != b.size())
	{
		return false;
	}

	return std::equal(a.begin(), a.end(), b.begin(), [](const char a, const char b)
	{
		return tolower(a) == tolower(b);
	});
}