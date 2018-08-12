#include "Box.h"
#include "Game.h"

#include <iostream>

Box::Box(Article articleType, int nbArticles, bool isRestock, bool inShelf) :
	m_articleType(articleType),
	m_nbArticles(nbArticles),
	m_timer(0),
	m_goingDown(true),
	m_isRestock(isRestock),
	m_inShelf(inShelf),
	m_lifeTime(20),
	m_toRemove(false),
	m_alpha(255),
	m_isHeld(false)
{
	m_position.x = 5 * 16 * Game::ZOOM_FACTOR;
	m_position.y = 5 * 16 * Game::ZOOM_FACTOR;

	m_yPanel = m_position.y - 34;

	m_bounds->top = m_position.y;
	m_bounds->left = m_position.x;
	m_bounds->width = 16 * Game::ZOOM_FACTOR;
	m_bounds->height = 16 * Game::ZOOM_FACTOR;

	if(!m_texture.loadFromFile("gfx/gameassets.png"))
	{
		std::cerr << "Fail to load gameassets.png" << std::endl;
	}
	
	m_sprite.setTexture(m_texture);

	if (m_inShelf)
	{
		switch (m_articleType)
		{
			case Article::BEACH_ACCESSORIES:
				m_sprite.setTextureRect(sf::IntRect(77, 58, 20, 14));
				break;
			case Article::CLOTHING:
				m_sprite.setTextureRect(sf::IntRect(17, 58, 20, 14));
				break;
			case Article::ELECTRONICS:
				m_sprite.setTextureRect(sf::IntRect(37, 58, 20, 14));
				break;
			case Article::FOOD:
				m_sprite.setTextureRect(sf::IntRect(57, 58, 20, 14));
				break;
			default:
				m_sprite.setTextureRect(sf::IntRect(17, 58, 20, 14));
		}
	}
	else
	{
		switch (m_articleType)
		{
			case Article::BEACH_ACCESSORIES:
				m_sprite.setTextureRect(sf::IntRect(80, 0, 16, 16));
				break;
			case Article::CLOTHING:
				m_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
				break;
			case Article::ELECTRONICS:
				m_sprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
				break;
			case Article::FOOD:
				m_sprite.setTextureRect(sf::IntRect(64, 0, 16, 16));
				break;
			default:
				m_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
		}
	}

	m_sprite.setPosition(m_position);
	m_sprite.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));

	if (m_isRestock)
	{
		m_infoPanel.setTexture(m_texture);
		m_infoPanel.setPosition(sf::Vector2f(m_position.x - 1, m_position.y - m_yPanel));
		m_infoPanel.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));

		switch (m_nbArticles)
		{
			case 1:
				m_infoPanel.setTextureRect(sf::IntRect(264, 40, 17, 15));
				break;
			case 2:
				m_infoPanel.setTextureRect(sf::IntRect(264, 56, 17, 15));
				break;
			case 3:
				m_infoPanel.setTextureRect(sf::IntRect(264, 72, 17, 15));
				break;
			case 4:
				m_infoPanel.setTextureRect(sf::IntRect(264, 88, 17, 15));
				break;
			default:
				m_infoPanel.setTextureRect(sf::IntRect(264, 40, 17, 15));
		}
	}
}

Box::~Box()
{
}

void Box::setIsHeld(bool hold)
{
	m_isHeld = hold;
}

void Box::setPosition(sf::Vector2f pos)
{
	Entity::setPosition(pos);

	m_yPanel = pos.y - 34;

 	m_bounds->top = pos.y;
	m_bounds->left = pos.x;
}

int Box::getNbArticles() const
{
	return m_nbArticles;
}

void Box::setNbArticles(int nbArticles)
{
	switch (nbArticles)
	{
		case 1:
			m_infoPanel.setTextureRect(sf::IntRect(264, 40, 17, 15));
			break;
		case 2:
			m_infoPanel.setTextureRect(sf::IntRect(264, 56, 17, 15));
			break;
		case 3:
			m_infoPanel.setTextureRect(sf::IntRect(264, 72, 17, 15));
			break;
		case 4:
			m_infoPanel.setTextureRect(sf::IntRect(264, 88, 17, 15));
			break;
		default:
			m_infoPanel.setTextureRect(sf::IntRect(264, 40, 17, 15));
	}
	m_nbArticles = nbArticles;
}

bool Box::toRemove() const
{
	return m_toRemove;
}

Article Box::getArticle() const
{
	return m_articleType;
}

void Box::update(float dt)
{
	m_timer += dt;

	if (m_inShelf)
	{
		switch (m_articleType)
		{
			case Article::BEACH_ACCESSORIES:
				m_sprite.setTextureRect(sf::IntRect(77, 58, 20, 14));
				break;
			case Article::CLOTHING:
				m_sprite.setTextureRect(sf::IntRect(17, 58, 20, 14));
				break;
			case Article::ELECTRONICS:
				m_sprite.setTextureRect(sf::IntRect(37, 58, 20, 14));
				break;
			case Article::FOOD:
				m_sprite.setTextureRect(sf::IntRect(57, 58, 20, 14));
				break;
			default:
				m_sprite.setTextureRect(sf::IntRect(17, 58, 20, 14));
		}
	}
	else
	{
		switch (m_articleType)
		{
			case Article::BEACH_ACCESSORIES:
				m_sprite.setTextureRect(sf::IntRect(80, 0, 16, 16));
				break;
			case Article::CLOTHING:
				m_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
				break;
			case Article::ELECTRONICS:
				m_sprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
				break;
			case Article::FOOD:
				m_sprite.setTextureRect(sf::IntRect(64, 0, 16, 16));
				break;
			default:
				m_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
		}
	}

	m_sprite.setPosition(m_position);
	
	if (m_isRestock && !m_isHeld)
	{
		m_lifeTime -= dt;

		if (m_lifeTime < 5 && m_timer > 0.3f)
		{
			m_alpha -= 51;
			if (m_alpha <= 0)
			{
				m_alpha = 0;
				m_toRemove = true;
			}
			m_sprite.setColor(sf::Color(255, 255, 255, m_alpha));
			m_infoPanel.setColor(sf::Color(255, 255, 255, m_alpha));
		}
	}

	if (m_timer > 0.3f)
	{
		m_timer -= 0.3f;
		if (m_goingDown)
		{
			if (m_yPanel <= m_position.y - 30)
			{
				m_goingDown = false;
				m_yPanel++;
			}
			else
			{
				m_yPanel--;
			}
		}
		else
		{
			if (m_yPanel >= m_position.y - 34)
			{
				m_goingDown = true;
				m_yPanel--;
			}
			else
			{
				m_yPanel++;
			}
		}
	}

	m_infoPanel.setPosition(sf::Vector2f(m_position.x - 1, m_yPanel));
}

void Box::setInShelf(bool inShelf)
{
	m_inShelf = inShelf;
}

bool Box::isRestock() const
{
	return m_isRestock;
}

void Box::render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
	if(m_isRestock && !m_inShelf)
	{
		target.draw(m_infoPanel);
	}
	//renderBounds(target);
}
