#include "Shelf.h"

#include "Game.h"

#include <iostream>

Shelf::Shelf()
{
}

Shelf::~Shelf()
{

}

void Shelf::update(float dt)
{

}

void Shelf::render(sf::RenderTarget & target)
{

}

bool Shelf::isFull() const
{
	return m_boxes.size() == MAX_CAPACITY;
}

bool Shelf::appendBox(Box* box)
{
	if (m_boxes.size() == MAX_CAPACITY)
	{
		return false;
	}
	box->setPosition(sf::Vector2f(
		m_position.x + 32 * Game::ZOOM_FACTOR * (m_boxes.size() % 2), 
		m_position.y - 10 + ((m_boxes.size() / 2) * 16 * Game::ZOOM_FACTOR)
	));
	m_boxes.push_back(box);
	return true;
}

Box* Shelf::getBox(int id)
{
	if (m_boxes.empty() || id > m_boxes.size() - 1)
	{
		return nullptr;
	}
	Box* b = m_boxes.at(id);
	for (std::vector<Box*>::iterator it = m_boxes.begin(); it != m_boxes.end();)
	{
		if ((*it) == b)
		{
			it = m_boxes.erase(it);
		}
		else
		{
			++it;
		}
	}

	int i = 0;
	for (std::vector<Box*>::iterator it = m_boxes.begin(); it != m_boxes.end();++it)
	{
		(*it)->setPosition(sf::Vector2f(
			m_position.x + 32 * Game::ZOOM_FACTOR * (i % 2),
			m_position.y - 10 + ((i / 2) * 16 * Game::ZOOM_FACTOR)
		));
		i++;
	}

	b->setInShelf(false);
	return b;
}
