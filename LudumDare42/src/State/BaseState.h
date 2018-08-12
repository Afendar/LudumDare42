#pragma once

#include <SFML/Graphics.hpp>

class Game;

namespace State
{
	class BaseState
	{
		public:
			BaseState(Game& game) : m_game(&game){}

			virtual ~BaseState() = default;

			virtual void handleEvent(sf::Event e){}
			virtual void handleInput() = 0;
			virtual void update(sf::Time dt) {}
			virtual void render(sf::RenderTarget& renderer) = 0;

		protected:
				Game* m_game;
	};
}