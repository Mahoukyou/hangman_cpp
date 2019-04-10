#include "hangman_file.h"

#include <fstream>
#include <random>

hangman_file::hangman_file(std::filesystem::path file_path) :
	file_path_{ std::move(file_path) },
	invalid_solutions_count_{ 0 },
	solutions_{ get_solutions_from_file() }
{

}

bool hangman_file::begin_new_game()
{
	if (solutions().empty())
	{
		solutions_ = get_solutions_from_file();

		if (solutions().empty())
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
	if (solution_index >= solutions().size())
	{
		throw hangman_exception_solution_index_out_of_bounds{ solution_index };
	}

	set_new_game(solutions()[solution_index]);
	return game_state() == e_game_state::playing;
}

void hangman_file::set_new_solutions_file(std::filesystem::path file_path)
{
	invalid_solutions_count_ = 0;
	solutions_.clear();

	file_path_ = std::move(file_path);
	solutions_ = get_solutions_from_file();
}

std::vector<std::string> hangman_file::get_solutions_from_file() const
{
	invalid_solutions_count_ = 0;

	std::ifstream file_stream{ file_path_ };
	if (!file_stream.good())
	{
		// todo, should be two exceptions<?> one for invalid path and one for io error, but its fine atm
		throw hangman_exception_invalid_file_path{ file_path() };
	}

	std::vector<std::string> new_solutions{};
	for (std::string new_solution; std::getline(file_stream, new_solution);)
	{
		// todo, what to do with invalid solutions?
		// discard or keep a ref for user to check invalid solutions?
		if (validate_solution(new_solution))
		{
			new_solutions.push_back(std::move(new_solution));
		}
		else
		{
			++invalid_solutions_count_;
		}
	}

	return new_solutions;
}

const std::string& hangman_file::get_random_solution() const
{
	if (solutions().empty())
	{
		throw hangman_exception_solutions_are_empty{};
	}

	std::mt19937 generator{ std::random_device{}() };
	const std::uniform_int_distribution<size_t> int_distribution{ 0, solutions().size() - 1 };

	return solutions()[int_distribution(generator)];
}
