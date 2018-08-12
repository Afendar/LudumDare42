#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Player.h"
#include "Order.h"
#include "Gui.h"

#include"Utils/Random.h"

class Game
{
	public:
	
		static Game* getInstance();
		void run();

		void addCustomerFeed(int amount);
		void setDelivery(int amount);
		void displaySelection(int shelfSelected);

		int getCustomerFeed() const;
		int getDeliveries() const;

		std::vector<Order*> getOrders() const;

		const sf::RenderWindow& getWindow() const;

		static const float ZOOM_FACTOR;

	private:
		Game();
		Game(const Game&) = delete;
		Game &operator=(const Game&) = delete;

		void update();
		void render();

		static Game* m_instance;

		sf::RenderWindow m_window;
		sf::Clock m_clock;
		sf::Time m_elapsed;

		Level* m_level;
		Player* m_player;

		Gui* m_gui;
		Utils::Random* m_random;

		std::vector<Order*> m_orders;

		sf::Texture m_start, m_textTutorial;
		sf::Sprite m_startBg, m_tutorialBg;

		sf::Text m_pressEnter, m_looseText, m_websiteText, m_tutorial;
		sf::Font m_font;

		bool m_running, m_goingDown;
		int m_deliveries;
		bool m_displaySelection, m_displayStart, m_displayLoose, m_displayTutorial;

		float m_timer, m_counter;

		int m_customerFeed;
		int m_delayBetweenOrders;
};