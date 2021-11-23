#include "../include/functions.hpp"
#include "../include/board.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>
#include <stdexcept>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <thread>


void game_over(sf::RenderWindow& w, const Board& b)
{
	w.clear(sf::Color::Black);
	sf::Font font;
	if(!font.loadFromFile("assets/fonts/FreeSans.otf"))
	{
		throw std::runtime_error("Cannot load font file: assets/FreeSans.otf");
	}
	sf::Text game_over_text;
	sf::Text points_txt;
	sf::Text levels_txt;

	points_txt.setFont(font);
	levels_txt.setFont(font);
	game_over_text.setFont(font);

	game_over_text.setString("GAME OVER");
	levels_txt.setString("LEVEL: " + std::to_string(b.get_levels()));
	points_txt.setString("POINTS: " + std::to_string(b.get_points()));

	game_over_text.setPosition(100.0f, 100.0f);
	points_txt.setPosition(100.0f, 200.0f);
	levels_txt.setPosition(100.0f, 300.0f);

	w.draw(game_over_text);
	w.draw(points_txt);
	w.draw(levels_txt);
	w.display();

	std::this_thread::sleep_for(std::chrono::seconds(5));

}
