#pragma once
#include <string>
#include <stdexcept>

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

	hangman() = delete;

	bool guess_letter(char letter);
	bool guess_solution(const std::string& solution);

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

	unsigned char missed_letters_count() const noexcept
	{
		return missed_letters_count_;
	}

	unsigned char guesses_left() const noexcept
	{
		return max_amount_of_wrong_guesses - missed_letters_count();
	}


protected:
	void set_new_game(std::string&& solution);
	static bool validate_solution(const std::string& solution);

	e_game_state game_state_;
	std::string solution_;
	std::string working_solution_;

	unsigned char missed_letters_count_;
};