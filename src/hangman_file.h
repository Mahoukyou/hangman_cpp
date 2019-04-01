#pragma once

#include "hangman.h"

#include <filesystem>

class hangman_exception_invalid_file_path : public hangman_exception
{
	// todo
	hangman_exception_invalid_file_path() :
		hangman_exception{"Invalid file path"}
	{
		
	}
};

/* Hangman game by using a specific solution */
class hangman_file : public hangman
{
public:
	explicit hangman_file(std::filesystem::path file_path);
	~hangman_file() override = default;

	bool begin_new_game();
	bool begin_new_game(size_t solution_index);

	const auto& file_path() const noexcept
	{
		return file_path_;
	}

	const auto& solutions() const noexcept
	{
		return solutions_;
	}

private:
	std::vector<std::string> get_solutions_from_file() const;
	const std::string& get_random_solution() const;

	std::filesystem::path file_path_;
	std::vector<std::string> solutions_;
};