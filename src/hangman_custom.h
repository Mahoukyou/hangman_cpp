#pragma once

#include "hangman.h"

/* Hangman game by using a specific solution */
class hangman_custom : public hangman
{
public:
	hangman_custom() noexcept = default;
	~hangman_custom() noexcept override = default;

	bool begin_new_game(const std::string& solution) noexcept(false);
};