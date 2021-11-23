#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "../include/board.hpp"
#include "../include/tetromino.hpp"
#include "../include/functions.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode(Board::WIDTH,Board::HEIGHT), "STetris");
	Board board;
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution<> dist(0,6);

	board.add_tetromino(static_cast<Tetromino::Type>(dist(engine)));
	while (window.isOpen()) 
	{
		sf::Event event;
		if(board.is_game_over())
		{
			game_over(window, board);
			return 0;
		}
		while (window.pollEvent(event)) 
		{
			int return_value = handle_input(event, *board.get_current_tetromino(),window);
			if(return_value == 0)
				board.update_transparent(false);
			if(return_value == 1)
				board.update_transparent(true);
			if(board.get_current_tetromino()->did_hit_bottom())
			{
				board.update_state();
				board.add_fallen_tetromino();
				board.update_rows();
				board.add_tetromino(static_cast<Tetromino::Type>(dist(engine)));
			}

		}
		window.clear(sf::Color::Black);
		board.draw(window);

		board.get_current_tetromino()->tic();
		if(board.get_current_tetromino()->did_hit_bottom())
		{
			board.update_state();
			board.add_fallen_tetromino();
			board.update_rows();
			board.add_tetromino(static_cast<Tetromino::Type>(dist(engine)));
		}

		window.display();
	}
	return 0;
}

