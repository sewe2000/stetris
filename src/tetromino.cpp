#include "../include/tetromino.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <math.h>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "../include/board.hpp"
#include "../include/functions.hpp"


Tetromino::Tetromino(Type t, bool transparent)
{
	constexpr int HALF_WINDOW_WIDTH = ((Board::WIDTH / 2) / BLOCK_WIDTH) * BLOCK_WIDTH;
	type = t;
	tetromino_texture.setRepeated(true);
	current_rotation = 0;
	isTransparent = transparent;
	for (auto& i : blocks) 
	{
		i = new sf::RectangleShape(sf::Vector2f(BLOCK_WIDTH,BLOCK_HEIGHT));
	}
	switch (t) 
	{
		case Straight:
			load("assets/textures/tetromino_texture_1.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH,0.0f);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH + 2 * BLOCK_WIDTH,0.0f);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH + 3 * BLOCK_WIDTH,0.0f);
			for (int i = 0; i < 4; i++)
				representation[i] = true;					

			rotations[0] = TetrominoRotation(0,1,2,3);
			rotations[1] = TetrominoRotation(0,4,8,12);                      
			rotations[2] = TetrominoRotation(0,1,2,3);
			rotations[3] = TetrominoRotation(0,4,8,12);
			break;
		case Square:
			load("assets/textures/tetromino_texture_2.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH, BLOCK_HEIGHT);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH, BLOCK_HEIGHT);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH,0.0f);
			
			representation[0] = true;
			representation[1] = true;
			representation[4] = true;
			representation[5] = true;

			rotations[0] = TetrominoRotation(0,1,4,5);
			rotations[1] = TetrominoRotation(0,1,4,5);
			rotations[2] = TetrominoRotation(0,1,4,5);
			rotations[3] = TetrominoRotation(0,1,4,5);

			break;
		case T:
			load("assets/textures/tetromino_texture_3.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH, 0.0f);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH + 2 * BLOCK_WIDTH, 0.0f);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH,BLOCK_HEIGHT);

			representation[0] = true;
			representation[1] = true;
			representation[2] = true;
			representation[5] = true;

			rotations[0] = TetrominoRotation(0,1,2,5);
			rotations[1] = TetrominoRotation(1,4,5,9);
			rotations[2] = TetrominoRotation(1,4,5,6);
			rotations[3] = TetrominoRotation(0,4,5,8);
			break;
		case L:
			load("assets/textures/tetromino_texture_4.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH, BLOCK_HEIGHT);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH,  2 * BLOCK_HEIGHT);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH, 2 * BLOCK_HEIGHT); 


			representation[0] = true;
			representation[4] = true;
			representation[8] = true;
			representation[9] = true;

			rotations[0] = TetrominoRotation(0,4,8,9);
			rotations[1] = TetrominoRotation(0,1,2,4);
			rotations[2] = TetrominoRotation(0,1,5,9);
			rotations[3] = TetrominoRotation(2,4,5,6);
		break;
		case J:
			load("assets/textures/tetromino_texture_4.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH, BLOCK_HEIGHT);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH,  2 * BLOCK_HEIGHT);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH - BLOCK_WIDTH, 2 * BLOCK_HEIGHT); 


			representation[1] = true;
			representation[5] = true;
			representation[9] = true;
			representation[8] = true;

			rotations[0] = TetrominoRotation(1,5,9,8);
			rotations[1] = TetrominoRotation(0,4,5,6);
			rotations[2] = TetrominoRotation(0,1,4,8);
			rotations[3] = TetrominoRotation(0,1,2,6);
			break;

		case Skew:
			load("assets/textures/tetromino_texture_5.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH + BLOCK_HEIGHT, 0.0f);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH,  BLOCK_HEIGHT);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH + 2 * BLOCK_WIDTH, BLOCK_HEIGHT);

			representation[0] = true;
			representation[1] = true;
			representation[5] = true;
			representation[6] = true;

			rotations[0] = TetrominoRotation(0,1,5,6);
			rotations[1] = TetrominoRotation(1,4,5,8);
			rotations[2] = TetrominoRotation(0,1,5,6);
			rotations[3] = TetrominoRotation(1,4,5,8);
		break;
		case S:
			load("assets/textures/tetromino_texture_5.png");
			blocks[0]->setPosition(HALF_WINDOW_WIDTH,0.0f);
			blocks[1]->setPosition(HALF_WINDOW_WIDTH, BLOCK_HEIGHT);
			blocks[2]->setPosition(HALF_WINDOW_WIDTH - BLOCK_WIDTH,  BLOCK_HEIGHT);
			blocks[3]->setPosition(HALF_WINDOW_WIDTH + BLOCK_WIDTH, 0.0f);

			representation[1] = true;
			representation[2] = true;
			representation[4] = true;
			representation[5] = true;

			rotations[0] = TetrominoRotation(1,2,4,5);
			rotations[1] = TetrominoRotation(0,4,5,9);
			rotations[2] = TetrominoRotation(1,2,4,5);
			rotations[3] = TetrominoRotation(0,4,5,9);
		break;
	}
	if(isTransparent)
		load("assets/textures/transparent_block.png");
	for (auto& i : blocks) 
	{
		i->setTexture(&tetromino_texture);
	}
	squarePosition = sf::Vector2f(HALF_WINDOW_WIDTH,0.0f);
	

}

Tetromino::~Tetromino()
{
	for (auto i : blocks) {
		delete i;
	}
}
void Tetromino::draw( sf::RenderWindow& w)
{
	for (auto i: blocks ) {
		if(i != nullptr)
		w.draw(*i);

	}
}

void Tetromino::rotate()
{
	constexpr int ARRAY_LENGHT = 16;
	if(current_rotation == 3)
		current_rotation = 0;
	else current_rotation++;
	representation.reset();
	for (int i = 0; i < 4; i++) 
		representation[rotations[current_rotation].points[i]] = true;	
	
	update();
}


void Tetromino::load(std::string resource_path)
{
	if(!tetromino_texture.loadFromFile(resource_path))
	{
		std::cerr << "stetris: Cannot load texture file!";
		throw std::runtime_error("Cannot load texture file!");
	}
}


void Tetromino::move(Direction dir)
{
	sf::Vector2f temp = squarePosition;
	if(dir == Left)
	{
		temp.x -= BLOCK_WIDTH;
		if(squarePosition.x > BLOCK_WIDTH && does_tetromino_fit(*this, Board::board_representation, temp))
		{
			squarePosition.x -= BLOCK_WIDTH;
		}
		else return;
	}
	else 
	{
		temp.x += BLOCK_WIDTH;
		if(((rightmost_x() + BLOCK_WIDTH) < Board::WIDTH - BLOCK_WIDTH) && does_tetromino_fit(*this, Board::board_representation, temp))
		{
			squarePosition.x += BLOCK_WIDTH;
		}
		else return;
	}
	update();
}
void Tetromino::update()
{
	constexpr int ARRAY_WIDTH = 4;	
	constexpr int ARRAY_HEIGHT = 4;	
			
	
	
	int block_count = 0;
	for(int i = 0; i < ARRAY_WIDTH; i++)
	{
		for(int j = 0; j < ARRAY_HEIGHT; j++)
		{
			if(representation[ConvertToIndex(j, i, ARRAY_WIDTH)])
			{
				blocks[block_count]->setPosition(squarePosition.x + j * BLOCK_WIDTH, squarePosition.y + i * BLOCK_HEIGHT);
				if(block_count < 3)
					block_count++;

			}
		}


	}
	for (auto& i : blocks) 
	{
		if(Board::getBoundries(Board::Left).intersects(i->getGlobalBounds()))
			move(Right);
		if(Board::getBoundries(Board::Right).intersects(i->getGlobalBounds()))
			move(Left);
		if(Board::getBoundries(Board::Bottom).intersects(i->getGlobalBounds()))
		{
			squarePosition.y -= BLOCK_HEIGHT;
			update();
		}
	}
}

void Tetromino::fall_by_1()
{

	sf::Vector2f temp = squarePosition;
	temp.y += BLOCK_HEIGHT;
	if(does_tetromino_fit(*this, Board::board_representation, temp))
		squarePosition.y += BLOCK_HEIGHT;
	else return;
	update();
}

void Tetromino::go_bottom()
{
	while(!did_hit_bottom())
		fall_by_1();
}
bool Tetromino::did_hit_bottom()
{
	sf::Vector2f temp = squarePosition;
	temp.y += BLOCK_HEIGHT; 
	return (bottom_edge_y() == (HEIGHT - BLOCK_HEIGHT)) || !does_tetromino_fit(*this, Board::board_representation, temp);
}
