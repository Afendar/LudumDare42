#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Box.h";

class Shelf : public Entity
{
	public:
		Shelf();
		~Shelf();

		void update(float dt);
		void render(sf::RenderTarget& target);

		bool appendBox(Box* box);
		bool isFull() const;
		Box* getBox(int id);

	private:

		std::vector<Box*> m_boxes;

		int MAX_CAPACITY = 4;
};