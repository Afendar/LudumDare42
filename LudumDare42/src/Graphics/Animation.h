#pragma once

#include <SFML/Graphics.hpp>

namespace Graphics
{

	class Animation
	{
		public:
			Animation();

			void addFrame(sf::IntRect rect);
			void setSpritesheet(const sf::Texture& texture);
			const sf::Texture* getSpritesheet() const;
			std::size_t getSize() const;
			const sf::IntRect& getFrame(std::size_t size) const;

		private:

			const sf::Texture* m_texture;
			std::vector<sf::IntRect> m_frames;
	};
}