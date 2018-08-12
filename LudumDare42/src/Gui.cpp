#include "Gui.h"

#include <iostream>

#include "Order.h"
#include "Game.h"

Gui::Gui(const Game* game) :
	m_game(game)
{
	if (!m_texture.loadFromFile("gfx/gameassets.png"))
	{
		std::cerr << "Fail to load gameassets.png" << std::endl;
	}

	m_bars.setTexture(m_texture);
	m_bars.setTextureRect(sf::IntRect(111, 13, 29, 21));
	m_bars.setPosition(sf::Vector2f(20, 20));
	m_bars.setScale(sf::Vector2f(2.0f, 2.0f));

	m_orderTab.setTexture(m_texture);
	m_orderTab.setTextureRect(sf::IntRect(154, 17, 30, 59));
	m_orderTab.setPosition(sf::Vector2f(45, 37));
	m_orderTab.setScale(sf::Vector2f(2.0f, 2.0f));

	m_customer.setTexture(m_texture);
	m_customer.setTextureRect(sf::IntRect(66, 73, 88, 30));
	m_customer.setPosition(sf::Vector2f(130, 662));
	m_customer.setScale(sf::Vector2f(2.0f, 2.0f));

	m_deliveries.setTexture(m_texture);
	m_deliveries.setTextureRect(sf::IntRect(14, 73, 51, 35));
	m_deliveries.setPosition(sf::Vector2f(20, 660));
	m_deliveries.setScale(sf::Vector2f(2.0f, 2.0f));

	m_panel.setTexture(m_texture);
	m_panel.setScale(sf::Vector2f(2.0f, 2.0f));

	m_satisfaction.setTexture(m_texture);
	m_satisfaction.setScale(sf::Vector2f(2.0f, 2.0f));

	m_customerFeedBar.setTexture(m_texture);
	m_customerFeedBar.setTextureRect(sf::IntRect(238, 28, 50, 4));
	m_customerFeedBar.setPosition(sf::Vector2f(198, 696));
	m_customerFeedBar.setScale(sf::Vector2f(2.0f, 2.0f));

	if (!m_font.loadFromFile("gfx/fonts/ntailu.ttf"))
	{
		std::cerr << "Fail to load ntailu.ttf" << std::endl;
	}

	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(24);
	m_text.setString("0");
	m_text.setPosition(sf::Vector2f(5 + ((102 - m_text.getGlobalBounds().width) / 2), 673));
}

Gui::~Gui()
{

}

void Gui::update(float dt)
{
	m_customerFeedBar.setTextureRect(sf::IntRect(238, 28, m_game->getCustomerFeed(), 4));
	m_text.setString(std::to_string(m_game->getDeliveries()));
}

void Gui::render(sf::RenderTarget & target)
{
	target.draw(m_bars);

	//Start Render Orders
	std::vector<Order*> orders = m_game->getOrders();
	int i = 0;
	for (std::vector<Order*>::iterator it = orders.begin(); it != orders.end(); ++it)
	{
		m_orderTab.setPosition(sf::Vector2f(45 + (32 * i * Game::ZOOM_FACTOR), 37));
		target.draw(m_orderTab);
		Article a = (*it)->getArticle();
		switch (a)
		{
			case Article::BEACH_ACCESSORIES:
				m_panel.setTextureRect(sf::IntRect(202, 114, 22, 22));
				break;
			case Article::CLOTHING:
				m_panel.setTextureRect(sf::IntRect(202, 92, 22, 22));
				break;
			case Article::ELECTRONICS:
				m_panel.setTextureRect(sf::IntRect(180, 92, 22, 22));
				break;
			case Article::FOOD:
				m_panel.setTextureRect(sf::IntRect(180, 114, 22, 22));
				break;
		}

		m_panel.setPosition(sf::Vector2f(45 + (32 * i * Game::ZOOM_FACTOR) + 4 * Game::ZOOM_FACTOR, 37 + (29 * Game::ZOOM_FACTOR)));
		m_satisfaction.setTextureRect(sf::IntRect(238, 33, (*it)->getCancelBarSize(), 2));
		m_satisfaction.setPosition(sf::Vector2f(45 + (32 * i * Game::ZOOM_FACTOR) + 4 * Game::ZOOM_FACTOR, 37 + (53 * Game::ZOOM_FACTOR)));
		
		target.draw(m_panel);
		target.draw(m_satisfaction);
		i++;
	}
	//End Render Orders

	target.draw(m_customer);
	target.draw(m_customerFeedBar);

	target.draw(m_deliveries);
	target.draw(m_text);
}
