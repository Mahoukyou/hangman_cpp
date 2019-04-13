#include "src/hangman_custom.h"
#include "src/hangman_file.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>

void print_letters(const hangman& hangman_game)
{
	std::vector<char> available_letters, unavailable_letters;
	available_letters.resize(hangman_utility::get_letter_count());
	unavailable_letters.resize(hangman_utility::get_letter_count());

	for (size_t i = 0; i < hangman_game.guessed_letters().size(); ++i)
	{
		const bool is_guessed = hangman_game.guessed_letters()[i].guessed;
		const char letter = hangman_utility::zero_based_index_to_letter(static_cast<int>(i));

		if (is_guessed)
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

void print_post_game_info(const hangman& hangman_game)
{
	switch (hangman_game.game_state())
	{
	case hangman::e_game_state::none:
		std::cout << "Seems like you didn't play, something went awry\n";
		break;

	case hangman::e_game_state::playing:
		std::cout << "Seems like you are still playing, something is wrong\n";
		break;

	case hangman::e_game_state::won:
		std::cout << "Congratulations, you've won\n";
		break;

	case hangman::e_game_state::lost:
		std::cout << "Good luck next time\n";
		break;

	default:
		std::cerr << "Nary impl for this game state\n";
		assert(0 && "We should not have got here");
	}
}

int main()
{
	hangman_file hangman_game{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\hangman\build\solutions.txt)" };

	hangman_game.begin_new_game();
	while (hangman_game.game_state() == hangman::e_game_state::playing)
	{
#ifdef _WIN32
		system("cls");
#endif

		print_letters(hangman_game);
		print_work_solution(hangman_game);

		std::cout << "\nEnter available character or entire solution: ";

		std::string input_solution;
		std::getline(std::cin, input_solution);

		if (input_solution.empty())
		{
			continue;
		}

		try
		{
			if (input_solution.size() == 1)
			{
				hangman_game.guess_letter(input_solution[0]);
			}
			else
			{
				hangman_game.guess_solution(input_solution);
			}
		}
		catch (const hangman_exception& exception)
		{
			std::cout << "Your guess is invalid - error message: " << exception.what() << '\n';
			std::cout << "Press any key to continue";

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
	}

	print_post_game_info(hangman_game);
}