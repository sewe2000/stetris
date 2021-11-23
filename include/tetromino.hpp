#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <bitset>
#include <thread>
#include <chrono>




static constexpr int WIDTH = 384;
static constexpr int HEIGHT = 544;

constexpr int BOARD_ROWS = 16;
constexpr int BOARD_COLS = 10;
class Tetromino 
{
public:
	enum Type { Straight, Square, T, L, Skew, J, S };
	enum Direction {Left, Right};
	static constexpr int BLOCK_WIDTH = 32;
	static constexpr int BLOCK_HEIGHT = 32;
	Tetromino(Type t, bool transparent = false);
	~Tetromino();
	void draw(sf::RenderWindow& w); 
	void rotate();
	void fall_by_1();
	void tic()
	{
		int speed = 20;
		static int counter = 0;
		std::this_thread::sleep_for(std::chrono::duration<int,std::milli>(std::chrono::milliseconds(50)));
		counter++;
		if(counter == speed)
		{
			fall_by_1();
			counter = 0;
		}
	}
	void move(Direction dir);
	void go_bottom();
	bool did_hit_bottom();
	sf::Vector2f get_position()
	{
		return squarePosition;
	}
	friend bool does_tetromino_fit(Tetromino& t, std::bitset<BOARD_COLS * BOARD_ROWS>& board, sf::Vector2f new_location); 
	sf::Vector2f get_block_position(int index)
	{
		if(blocks[index] != nullptr)
			return blocks[index]->getPosition();
		return sf::Vector2f(-1,-1);
	}
	void destroy_block(unsigned int index)
	{
		delete blocks[index];
		blocks[index] = nullptr;
	}
	void fall_by_1_after_deletion(int deleted_row)
	{
		int y = deleted_row * 32;
		for (auto i: blocks) 
		{
			if(i != nullptr && i->getPosition().y <= y)
				i->move(0.0f,BLOCK_HEIGHT);
		}
	}
	Type get_type() {return type;}
	
	void set_position(sf::Vector2f pos)
	{
		squarePosition = pos; 
		update();
	}

private:
	void load(std::string resource_path);
	void update();
	struct TetrominoRotation
	{
		using PointT = int8_t;
		PointT points[4];
		TetrominoRotation() = default;
		TetrominoRotation(PointT a, PointT b, PointT c, PointT d)
		{
			points[0] = a;
			points[1] = b;
			points[2] = c;
			points[3] = d;
		}
	};
	sf::Texture tetromino_texture;
	sf::RectangleShape* blocks[4];
	sf::Vector2f squarePosition;
	Type type;
	TetrominoRotation rotations[4];
	int8_t current_rotation;
	std::bitset<16> representation;
	bool isTransparent;
	
	constexpr int ConvertToIndex(int x, int y, int width) {return y * width + x;}
	int (Tetromino::*index_func) (int,int,int);
	int rightmost_x()
	{
		return std::max({blocks[0]->getPosition().x, blocks[1]->getPosition().x,blocks[2]->getPosition().x, blocks[3]->getPosition().x});
	}
	int bottom_edge_y()
	{
		int max = 0;
		for(auto i: blocks)
		{
			if(i != nullptr)
			{
				if(i->getPosition().y > max)
					max = i->getPosition().y;
			}
		}
		return max + BLOCK_HEIGHT;
	}

	
};

