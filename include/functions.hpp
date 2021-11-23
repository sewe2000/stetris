#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <bitset>
#include "../include/tetromino.hpp"
#include "../include/board.hpp"

constexpr int SHOULD_UPDATE_TRANSPARENT_TETROMINO = 0;
constexpr int SHOULD_ROTATE_TRANSPARENT_TETROMINO = 1;

int handle_input(sf::Event& e, Tetromino& t, sf::RenderWindow& w);
bool does_tetromino_fit(Tetromino& t, std::bitset<BOARD_COLS * BOARD_ROWS>& board, sf::Vector2f new_location); 
void game_over(sf::RenderWindow& w, const Board& b);
void shift_bits(std::bitset<160>& bits, int deleted_row);
