#include "../include/board.hpp"
#include "../include/functions.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <bitset>
#include <iostream>
#include <list>

sf::Sprite Board::border[3];
std::bitset<((HEIGHT - Board::TEXTURE_HEIGHT) / Board::TEXTURE_HEIGHT) * ((WIDTH - 2 * Board::TEXTURE_WIDTH) / Board::TEXTURE_WIDTH)> Board::board_representation;


Board::Board()
{
	if(!border_texture.loadFromFile("assets/textures/border_texture.png"))
	{
		std::cerr << "STetris: Unable to load texture from file!" << std::endl;
	}
	border_texture.setRepeated(true);
	
	border[0].setTexture(border_texture);
	border[0].setTextureRect(sf::IntRect(0,0,TEXTURE_WIDTH,HEIGHT));
	border[0].setPosition(0,0);

	border[1].setTexture(border_texture);
	border[1].setTextureRect(sf::IntRect(0,0,WIDTH - 2 * TEXTURE_WIDTH,TEXTURE_HEIGHT));
	border[1].setPosition(TEXTURE_WIDTH, HEIGHT - TEXTURE_HEIGHT);

	border[2].setTexture(border_texture);
	border[2].setTextureRect(sf::IntRect(0,0,TEXTURE_WIDTH,HEIGHT));
	border[2].setPosition(WIDTH - TEXTURE_WIDTH, 0);
}

Board::~Board()
{
	for (auto i : tetrominoes) 
	{
		delete i;
	}
}
void Board::draw(sf::RenderWindow& w)
{
	for (auto &i : border)
	{
		w.draw(i);
	}
	for(auto i: tetrominoes)
	{
		i->draw(w);
	}
	if(transparent_tetromino)
		transparent_tetromino->draw(w);
}
sf::FloatRect Board::getBoundries(Border s)
{
	switch(s)
	{
		case Left:
			return border[0].getGlobalBounds();
			break;
		case Right:
			return border[2].getGlobalBounds();
			break;
		case Bottom:
			return border[1].getGlobalBounds();
			break;
	}
	return sf::FloatRect();
}

void Board::update_state()
{
	for(int i = 0; i < 4; i++)
	{
		sf::Vector2f tmp = tetrominoes[current_tetromino]->get_block_position(i);
		tmp.x /= 32;
		tmp.x--;
		tmp.y /= 32;
		board_representation[tmp.y * 10 + tmp.x] = true;
	}

}
void Board::update_rows()
{
        decltype(board_representation) row = 0b1111111111;
	decltype(board_representation) rep = board_representation;
	int shift = BOARD_ROWS - 1;
	std::list<int> full_rows;
	bool deleted_row = false;
	level = points / 250;
	while(shift >= 0)
	{
		if((rep & (row << shift * 10)) == (row << shift * 10))
			full_rows.push_back(shift);
		shift--;
	}

	for(auto i: full_rows)
	{
		deleted_row = true;
		int y = i;
		int min_x = i * 10;
		min_x = -10 * y + (i * 10);
		int max_x = min_x + 9;
		for (auto i : fallen_tetrominoes)
		{
			for(int j = 0; j < 4; j++)
			{
				sf::Vector2f pos = i->get_block_position(j);
				if(pos.x == -1)
					continue;
				pos.x /= 32;
				pos.x--;
				pos.y /= 32;
				if(pos.y == y && pos.x >= min_x && pos.x <= max_x)
					i->destroy_block(j);

			}
		}
		for(short k = min_x; k <= max_x; k++)
			rep[10 * y + k] = false;
		shift_bits(rep, i);
		board_representation = rep;
		for (auto j : tetrominoes) 
		{
			j->fall_by_1_after_deletion(i);
		}
	}
	int multiplier;
	switch (full_rows.size()) 
	{
		case 1:
			multiplier = 40;
			break;
		case 2:
			multiplier = 100;
			break;
		case 3:
			multiplier = 300;
			break;
		case 4:
			multiplier = 1200;
			break;
		default:
			multiplier = 1200 * full_rows.size();
	}
	points += multiplier * (level + 1);
	

}
