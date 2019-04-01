#include "src/hangman_custom.h"
#include <iostream>
#include <vector>
#include <iterator>

void print_letters(const hangman& hangman_game)
{
	std::vector<char> available_letters, unavailable_letters;
	available_letters.resize(hangman_utility::get_letter_count());
	unavailable_letters.resize(hangman_utility::get_letter_count());
	
	for (size_t i = 0; i < hangman_game.guessed_letters().size(); ++i)
	{
		const bool is_guessed = hangman_game.guessed_letters()[i].guessed;
		const char letter = hangman_utility::zero_based_index_to_letter(static_cast<int>(i));

		if(is_guessed)
		{
			unavailable_letters.push_back(letter);
		}
		else
		{
			available_letters.push_back(letter);
		}
	}

	std::cout << "Available letters:\n";
	std::copy(available_letters.begin(), available_letters.end(), std::ostream_iterator<char>(std::cout, " "));

	std::cout << "\nUnavailable letters:\n";
	std::copy(unavailable_letters.begin(), unavailable_letters.end(), std::ostream_iterator<char>(std::cout, " "));
}

void print_work_solution(const hangman& hangman_game)
{
	std::cout << "\nCurrent solution state: " << hangman_game.working_solution() << '\n';
}

int main()
{
	hangman_custom hangman_game{};

	hangman_game.begin_new_game("abcd");
	while(hangman_game.game_state() == hangman::e_game_state::playing)
	{
#ifdef _WIN32
		system("cls");
#endif

		print_letters(hangman_game);
		print_work_solution(hangman_game);

		std::cout << "\nEnter available character or entire solution: ";

		std::string input_solution;
		std::cin >> input_solution;

		if (input_solution.empty())
		{
			continue;
		}

		if(input_solution.size() == 1)
		{
			hangman_game.guess_letter(input_solution[0]);
		}
		else
		{
			hangman_game.guess_solution(input_solution);
		}
	}
}