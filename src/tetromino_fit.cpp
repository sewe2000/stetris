#include <SFML/System/Vector2.hpp>
#include "../include/tetromino.hpp"
#include "../include/functions.hpp"

constexpr int BLOCK_WIDTH = 32;
constexpr int BLOCK_HEIGHT = 32;

bool does_tetromino_fit(Tetromino& t, std::bitset<BOARD_COLS * BOARD_ROWS>& board, sf::Vector2f new_location)
{
	int x = (new_location.x - 1) / BLOCK_WIDTH;
	int y = (new_location.y) / BLOCK_HEIGHT;

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			if(board[t.ConvertToIndex(x + j, y + i, 10)] == true && t.representation[t.ConvertToIndex(j, i, 4)] == true)
			{
				return false;
			}
		}
	}
	return true;
}
