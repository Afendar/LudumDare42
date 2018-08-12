#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Gui
{
	public:

		Gui(const Game* game);
		~Gui();

		void update(float dt);
		void render(sf::RenderTarget& target);

	private:

		sf::Text m_text;
		sf::Font m_font;

		sf::Texture m_texture;
		sf::Sprite m_bars, m_orderTab, m_customer, m_deliveries, m_panel, m_satisfaction, m_customerFeedBar;

		const Game* m_game;
};