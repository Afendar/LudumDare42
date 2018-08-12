#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

enum Article
{
	CLOTHING,
	FOOD,
	ELECTRONICS,
	BEACH_ACCESSORIES
};

class Box : public Entity
{
	public:
		Box(Article articleType, int nbArticles = 1, bool isRestock = false, bool inShelf = false);
		~Box();

		void setPosition(sf::Vector2f pos);

		int getNbArticles() const;

		bool isRestock() const;
		bool toRemove() const;

		Article getArticle() const;

		void update(float dt);
		void render(sf::RenderTarget& target);
		void setInShelf(bool inShelf);
		void setNbArticles(int nbArticles);
		void setIsHeld(bool hold);
		
	private:

		sf::Texture m_texture;
		sf::Sprite m_sprite, m_infoPanel;
		Article m_articleType;

		float m_timer, m_lifeTime;
		bool m_goingDown, m_inShelf, m_isRestock, m_toRemove, m_isHeld;

		int m_nbArticles, m_yPanel, m_alpha;
};