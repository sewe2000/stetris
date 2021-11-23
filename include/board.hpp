#pragma once

#include "../include/tetromino.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <bitset>
#include <list>

class Tetromino;

class Board
{
public:
	/* fields */
	static constexpr int WIDTH = 384;
	static constexpr int HEIGHT = 544;
	static constexpr int TEXTURE_WIDTH = 32;
	static constexpr int TEXTURE_HEIGHT = 32;
	enum Border {Left, Bottom, Right};
	/* methods */
	Board();
	~Board();
	void draw(sf::RenderWindow &w);
	static sf::FloatRect getBoundries(Border s);
	void add_fallen_tetromino()
	{
		fallen_tetrominoes.push_back(tetrominoes[current_tetromino]);
	}
	void update_state();
	void add_tetromino(Tetromino::Type t)
	{
		tetrominoes.push_back(new Tetromino(t));
		current_tetromino++;
		if(current_tetromino > 0)
			delete transparent_tetromino;
		transparent_tetromino = new Tetromino(tetrominoes[current_tetromino]->get_type(), true);
		transparent_tetromino->go_bottom();
		
	}
	Tetromino* get_current_tetromino()
	{
		return tetrominoes[current_tetromino];
	}
	void update_rows();
	bool is_game_over()
	{
		for(auto i: tetrominoes)
		{
			if(i->did_hit_bottom() && i->get_position().y == 0.0f)
				return true;
		}
		return false;
	}
	int get_points() const {return points;}
	int get_levels() const {return level;}
	void update_transparent(bool rotate)
	{
		sf::Vector2f temp = tetrominoes[current_tetromino]->get_position();
		transparent_tetromino->set_position(temp);
		if(rotate)
			transparent_tetromino->rotate();
		transparent_tetromino->go_bottom();
	}
	friend class Tetromino;
private:
	/* fields */
	static sf::Sprite border[3];
	sf::Texture border_texture;
	static std::bitset<((HEIGHT - TEXTURE_HEIGHT) / TEXTURE_HEIGHT) * ((WIDTH - 2 * TEXTURE_WIDTH) / TEXTURE_WIDTH)> board_representation;
	std::vector<Tetromino*> tetrominoes;
	Tetromino* transparent_tetromino;
	std::list<Tetromino*> fallen_tetrominoes;
	int current_tetromino = -1;
	int points = 0;
	int level = 0;
	
};
