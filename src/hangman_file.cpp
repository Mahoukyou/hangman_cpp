#include "hangman_file.h"

#include <random>

hangman_file::hangman_file(std::filesystem::path file_path) :
	file_path_{ std::move(file_path) },
	solutions_{ get_solutions_from_file() }
{

}

bool hangman_file::begin_new_game()
{
	if(solutions().empty())
	{
		solutions_ = get_solutions_from_file();

		if(solutions().empty())
		{
			game_state_ = e_game_state::none;
			return false;
		}
	}

	set_new_game(get_random_solution());

	return game_state() == e_game_state::playing;
}

bool hangman_file::begin_new_game(const size_t solution_index)
{
	if(solution_index >= solutions().size())
	{
		return false; // todo
	}

	set_new_game(solutions()[solution_index]);

	return game_state() == e_game_state::playing;
}

std::vector<std::string> hangman_file::get_solutions_from_file() const
{
	return {"ab", "wanada", "qowiewq-da dsas"};
}

const std::string& hangman_file::get_random_solution() const
{
	if(solutions().empty())
	{
		// throw todo
	}

	std::mt19937 generator{ std::random_device{}() };
	const std::uniform_int_distribution<size_t> int_distribution{ 0, solutions().size() - 1 };

	return solutions()[int_distribution(generator)];
}
