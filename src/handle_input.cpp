
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "../include/tetromino.hpp"
#include "../include/functions.hpp"

int handle_input(sf::Event& e, Tetromino& t, sf::RenderWindow& w)
{
	switch (e.type) 
	{
		case sf::Event::KeyPressed:
			 if(e.key.code == sf::Keyboard::Left)
			{
				t.move(Tetromino::Left);
				return SHOULD_UPDATE_TRANSPARENT_TETROMINO;
			}
			if(e.key.code == sf::Keyboard::Right)
			{
				t.move(Tetromino::Right);
				return SHOULD_UPDATE_TRANSPARENT_TETROMINO;
			}
			if(e.key.code == sf::Keyboard::Down)
				t.fall_by_1(); 
			if(e.key.code == sf::Keyboard::Up)
			{
				t.rotate();
				return SHOULD_ROTATE_TRANSPARENT_TETROMINO;
			}
			if(e.key.code == sf::Keyboard::Space)
				t.go_bottom();
			break;
		case sf::Event::Closed:
			w.close();	
		default:
			break;
	}
	return -1;
}
