#pragma once

#include <string>
#include <stdexcept>
#include <array>

class hangman_exception : public std::runtime_error
{
public:
	explicit hangman_exception(const std::string& message) : 
		std::runtime_error{ message }
	{

	}
};

class hangman_exception_invalid_guess_letter : public hangman_exception
{
public:
	explicit hangman_exception_invalid_guess_letter(const char letter) :
		hangman_exception{ "Guessed letter is invalid" },
		letter_{ letter }
	{

	}

	char letter() const noexcept
	{
		return letter_;
	}

private:
	const char letter_;
};

class hangman_exception_invalid_guess_solution : public hangman_exception
{
public:
	explicit hangman_exception_invalid_guess_solution(std::string solution) :
		hangman_exception{ "Guessed solution contains at least one invalid character" },
		solution_{ std::move(solution) }
	{

	}

	const std::string& solution() const noexcept
	{
		return solution_;
	}

private:
	const std::string solution_;
};

class hangman_exception_invalid_solution : public hangman_exception
{
public:
	explicit hangman_exception_invalid_solution(std::string solution) :
		hangman_exception{ "Solution is not a valid hangman solution" },
		solution_{ std::move(solution) }
	{

	}

	const std::string& solution() const noexcept
	{
		return solution_;
	}

private:
	const std::string solution_;
};

namespace hangman_utility
{
	constexpr int get_letter_count() noexcept
	{
		return 'z' - 'a' + 1;
	}

	constexpr char zero_based_index_to_letter(const int index) noexcept
	{
		return index + 'A';
	}
}

struct guessed_letter_info
{
	bool guessed{ false };
	bool was_correct{ false };
};

class hangman
{
public:
	static constexpr int max_amount_of_wrong_guesses{ 8 };

	enum class e_game_state
	{
		none,
		playing,
		won,
		lost
	};

	enum class e_guess_letter_result
	{
		correct,
		incorrect,
		already_guessed
	};

	hangman() noexcept;
	virtual ~hangman() noexcept = 0;

	e_guess_letter_result guess_letter(char letter) noexcept(false);
	bool guess_solution(const std::string& solution) noexcept(false);

	e_game_state game_state() const noexcept
	{
		return game_state_;
	}

	const std::string& solution() const noexcept
	{
		return solution_;
	}

	const std::string& working_solution() const noexcept
	{
		return working_solution_;
	}

	const auto& guessed_letters() const noexcept
	{
		return guessed_letters_;
	}

	unsigned char missed_letters_count() const noexcept
	{
		return missed_letters_count_;
	}

	unsigned char guesses_left() const noexcept
	{
		return max_amount_of_wrong_guesses - missed_letters_count();
	}


protected:
	void set_new_game(const std::string& new_solution) noexcept(false);
	static bool validate_solution(const std::string& solution);
	static bool is_same_solution(const std::string& a, const std::string& b);

	e_game_state game_state_;
	std::string solution_;
	std::string working_solution_;

	std::array<guessed_letter_info, hangman_utility::get_letter_count()> guessed_letters_;

	unsigned char missed_letters_count_;
};