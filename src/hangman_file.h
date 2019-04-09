#pragma once

#include "hangman.h"

#include <vector>
#include <filesystem>

class hangman_exception_invalid_file_path : public hangman_exception
{
public:
	explicit hangman_exception_invalid_file_path(std::filesystem::path path) :
		hangman_exception{"Invalid file path"},
		path_{ std::move(path) }
	{
		
	}

	const auto& path() const noexcept
	{
		return path_;
	}

private:
	const std::filesystem::path path_;
};

class hangman_exception_solution_index_out_of_bounds : public hangman_exception
{
public:
	explicit hangman_exception_solution_index_out_of_bounds(const size_t index) :
		hangman_exception{ "Solution index is out of bounds" },
		index_{ index }
	{

	}

	size_t index() const noexcept
	{
		return index_;
	}

private:
	const size_t index_;
};

class hangman_exception_solutions_are_empty : public hangman_exception
{
public:
	explicit hangman_exception_solutions_are_empty() :
		hangman_exception{ "Solutions are empty, cannot get a valid solution" }	{

	}
};


/* Hangman game by using a specific solution */
class hangman_file : public hangman
{
public:
	explicit hangman_file(std::filesystem::path file_path) noexcept(false);
	~hangman_file() noexcept override = default;

	bool begin_new_game() noexcept(false);
	bool begin_new_game(size_t solution_index) noexcept(false);

	void set_new_solutions_file(std::filesystem::path file_path) noexcept(false);

	const auto& file_path() const noexcept
	{
		return file_path_;
	}

	const auto& solutions() const noexcept
	{
		return solutions_;
	}

	size_t invalid_solutions_count() const noexcept
	{
		return invalid_solutions_count_;
	}

private:
	std::vector<std::string> get_solutions_from_file() const noexcept(false);
	const std::string& get_random_solution() const noexcept(false);

	std::filesystem::path file_path_;

	mutable size_t invalid_solutions_count_;
	std::vector<std::string> solutions_;
};