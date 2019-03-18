#include "hangman.h"
#include <cctype>

int letter_to_zero_based_index(const char letter)
{
	return 'a' - tolower(letter);
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

	// todo check for win

	return found_letter ? e_guess_letter_result::correct : e_guess_letter_result::incorrect;
}

bool hangman::guess_solution(const std::string& solution)
{
	if (!validate_solution(solution))
	{
		throw hangman_exception_invalid_guess_solution{ solution };
	}

	const auto is_correct = std::equal(solution.begin(), solution.end(), this->solution().begin(), [](const char a, const char b)
	{
		return tolower(a) == tolower(b);
	});

	// todo check for win

	return is_correct;
}

void hangman::set_new_game(std::string&& solution)
{

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