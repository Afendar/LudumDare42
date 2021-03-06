#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Box.h"
#include "Shelf.h"
#include "Utils/Random.h"

class Level
{
	public:
		Level();
		~Level();

		void update(float dt);
		void render(sf::RenderTarget& target);
		void moveHand(int x);
		Box* selectBox();
		void selectedShelf(int shelfId);
		bool appendBoxToShelf(int shelfId, Box* box);

		bool removeBox(Box* box);

		int getNumber(int x, int y) const;

		bool collisionWall(int x, int y);

		std::vector<Box*> getBoxes() const;

	private:

		Utils::Random* m_random;

		float m_timerRestock;

		int m_delayBetweenRestocks;
		int m_selectedShelf;
		int m_selectedBox;

		int m_collisionMap[32][24] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
			{1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
			{1,1,1,1,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
			{1,1,1,1,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
			{1,1,1,1,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,3,0,0,0,0,0,0,0,0,0,1,1,1,5,0,0,0,0,0,1},
			{1,1,1,1,3,0,0,0,0,0,0,0,0,0,1,1,1,1,5,0,0,0,0,1},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,5,0,0,0,0,1},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,5,0,0,0,0,1},
			{1,1,1,1,4,0,0,0,0,0,0,0,0,0,1,1,1,1,5,0,0,0,0,1},
			{1,1,1,1,4,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
			{1,1,1,1,4,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
			{1,1,1,1,4,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
			{1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

		std::vector<Box*> m_restockBoxes;
		std::map<int, Shelf*> m_shelves;

		sf::Texture m_texture, m_sprites;
		sf::Sprite m_sprite, m_hand;
};