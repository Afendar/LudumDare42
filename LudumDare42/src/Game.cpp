#include "Game.h"

Game* Game::m_instance = 0;

const float Game::ZOOM_FACTOR = 2.0f;

Game* Game::getInstance()
{
	if (!m_instance)
	{
		m_instance = new Game();
	}
	return m_instance;
}

Game::Game() :
	m_window(sf::VideoMode(1024, 768), "Stock Overflow"),
	m_timer(0),
	m_delayBetweenOrders(10),
	m_customerFeed(50),
	m_displaySelection(false),
	m_displayStart(true),
	m_counter(0),
	m_goingDown(true),
	m_displayLoose(false),
	m_displayTutorial(false),
	m_deliveries(0)
{
	if (!m_start.loadFromFile("gfx/title.png"))
	{
		std::cerr << "Fail to load title.png" << std::endl;
	}
	m_startBg.setTexture(m_start);
	m_startBg.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));
	m_startBg.setOrigin(1200 / 2, 800 / 2);
	m_startBg.setPosition(1024 / 2, 768 / 2);

	if (!m_textTutorial.loadFromFile("gfx/gameassets.png"))
	{
		std::cerr << "Fail to load gameassets" << std::endl;
	}
	m_tutorialBg.setTexture(m_textTutorial);
	m_tutorialBg.setTextureRect(sf::IntRect(292,2,165,160));
	m_tutorialBg.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));
	m_tutorialBg.setPosition(sf::Vector2f((1024 - 330) / 2, 30));

	if(!m_font.loadFromFile("gfx/fonts/ntailu.ttf"))
	{
		std::cerr << "Fail to load ntailu.ttf" << std::endl;
	}
	m_pressEnter.setFont(m_font);
	m_pressEnter.setCharacterSize(14);
	m_pressEnter.setFillColor(sf::Color::White);
	m_pressEnter.setString("Press Space to start");
	m_pressEnter.setPosition(sf::Vector2f((1024 - m_pressEnter.getGlobalBounds().width) / 2, 600));

	m_looseText.setFont(m_font);
	m_looseText.setCharacterSize(26);
	m_looseText.setFillColor(sf::Color::White);
	m_looseText.setString("You have failed to satisfy your customers.");
	m_looseText.setPosition(sf::Vector2f((1024 - m_looseText.getGlobalBounds().width) / 2, 240));

	m_websiteText.setFont(m_font);
	m_websiteText.setFillColor(sf::Color::White);
	m_websiteText.setString("Game created in 48h for the Ludum Dare 42 game compo \n\n The theme was [run out of space]. \n\n Thanks you for playing \n\n Afendar\n@Afendar_\nwww.afendar.com");
	m_websiteText.setCharacterSize(14);
	m_websiteText.setPosition(sf::Vector2f((1024 - m_websiteText.getGlobalBounds().width) / 2, 384));

	m_tutorial.setFont(m_font);
	m_tutorial.setFillColor(sf::Color::White);
	m_tutorial.setCharacterSize(14);
	m_tutorial.setString("Collect boxes before they\ndisappear.The place taken in the\nstock is indicated by the sign.\n\n\n\nPrepare the orders displayed at\nthe top of screen.\n\n\n\n\nBe careful to maintain a level of\ncustomer satisfaction to stay\nin game.");
	m_tutorial.setPosition(sf::Vector2f(((1024 - m_tutorial.getGlobalBounds().width) / 2) + 52, 60));


	m_random = new Utils::Random();

	m_level = new Level();
	m_player = new Player(m_level, this);

	m_elapsed = m_clock.restart();

	m_orders.push_back(new Order(Article::CLOTHING));

	m_gui = new Gui(this);
}

void Game::run()
{
	while (m_window.isOpen())
	{
		sf::Event e;
		while (m_window.pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
					m_window.close();
					break;
				case sf::Event::KeyReleased:
					if (m_displaySelection)
					{
						int x = 0;
						int y = 0;

						if (e.key.code == sf::Keyboard::Left)
						{
							x = -1;
						}
						else if (e.key.code == sf::Keyboard::Right)
						{
							x = 1;
						}
						else if (e.key.code == sf::Keyboard::Up)
						{
							x = -2;
						}
						else if (e.key.code == sf::Keyboard::Down)
						{
							x = 2;
						}
						if (e.key.code == sf::Keyboard::Space)
						{
							Box* b = m_level->selectBox();
							if (b != nullptr)
							{
								m_displaySelection = false;
								m_level->selectedShelf(0);
								m_player->setHeldBox(b);
								break;
							}
						}
						if (e.key.code == sf::Keyboard::Escape)
						{
							m_displaySelection = false;
							m_level->selectedShelf(0);
						}
						m_level->moveHand(x);
					}
					else if (m_displayStart)
					{
						if (e.key.code == sf::Keyboard::Space)
						{
							if (!m_displayTutorial)
							{
								m_displayTutorial = true;
							}
							else
							{
								m_displayStart = false;
							}
						}
					}
					else
					{
						if (e.key.code == sf::Keyboard::Space)
						{
							m_player->takeBox();
						}
					}
					break;
				default:
					break;
			}
		}

		update();
		render();
	}
}

int Game::getCustomerFeed() const
{
	return m_customerFeed;
}

void Game::displaySelection(int shelfSelected)
{
	m_level->selectedShelf(shelfSelected);
	m_displaySelection = true;
}

std::vector<Order*> Game::getOrders() const
{
	return m_orders;
}

void Game::setDelivery(int amount)
{
	m_deliveries += amount;
	if (m_deliveries < 0)
		m_deliveries = 0;
}

void Game::update()
{
	m_elapsed = m_clock.restart();
	float dt = m_elapsed.asSeconds();

	if (m_displayLoose)
	{
		return;
	}

	if (m_displayStart)
	{
		m_counter += dt;
		if (m_counter > 0.3f)
		{
			m_counter -= 0.3f;
			sf::Vector2f pos = m_pressEnter.getPosition();
			if (m_goingDown)
			{
				if (pos.y < 610)
				{
					m_goingDown = false;
					m_pressEnter.setPosition(sf::Vector2f(pos.x, pos.y++));
				}
				else
				{
					m_pressEnter.setPosition(sf::Vector2f(pos.x, pos.y--));
				}
			}
			else
			{
				if (pos.y > 600)
				{
					m_goingDown = true;
					m_pressEnter.setPosition(sf::Vector2f(pos.x, pos.y--));
				}
				else
				{
					m_pressEnter.setPosition(sf::Vector2f(pos.x, pos.y++));
				}
			}
		}
		return;
	}

	if (m_customerFeed <= 0)
	{
		m_displayLoose = true;
	}

	m_level->update(dt);

	if(m_displaySelection)
	{
		return;
	}

	m_timer += dt;

	m_gui->update(dt);

	m_player->update(dt);

	//Generate new order
	if (m_timer > m_delayBetweenOrders)
	{
		m_delayBetweenOrders = m_random->getNumberInRange(2, 4);
		std::cout << "waiting: " << m_delayBetweenOrders << "s" << std::endl;
		m_timer = 0;
		if (m_random->getNumberInRange(0, 1))
		{
			std::cout << "generate Order" << std::endl;
			switch (m_random->getNumberInRange(0, 3))
			{
				case Article::BEACH_ACCESSORIES:
					m_orders.push_back(new Order(Article::BEACH_ACCESSORIES));
					break;
				case Article::CLOTHING:
					m_orders.push_back(new Order(Article::CLOTHING));
					break;
				case Article::ELECTRONICS:
					m_orders.push_back(new Order(Article::ELECTRONICS));
					break;
				case Article::FOOD:
					m_orders.push_back(new Order(Article::FOOD));
					break;
			}	
		}
	}

	for (std::vector<Order*>::iterator it = m_orders.begin(); it != m_orders.end();)
	{
		(*it)->update(dt);
		if ((*it)->isCanceled() || (*it)->isCompleted())
		{
			if ((*it)->isCanceled())
			{
				m_customerFeed -= 5;
			}
			delete *it;
			it = m_orders.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Game::addCustomerFeed(int amount)
{
	m_customerFeed += amount;
	if (m_customerFeed > 50)
		m_customerFeed = 50;
	if (m_customerFeed < 0)
		m_customerFeed = 0;
}

void Game::render()
{
	m_window.clear();

	if (m_displayStart)
	{
		m_window.draw(m_startBg);
		m_window.draw(m_pressEnter);
		if (m_displayTutorial)
		{
			m_window.draw(m_tutorialBg);
			m_window.draw(m_tutorial);
		}
	}
	else
	{
		m_level->render(m_window);
		m_player->render(m_window);

		std::vector<Box*> restock = m_level->getBoxes();
		for (std::vector<Box*>::iterator it = restock.begin(); it != restock.end();++it)
		{
			(*it)->render(m_window);
		}

		m_gui->render(m_window);

		if (m_displayLoose)
		{
			sf::RectangleShape rect(sf::Vector2f(1024, 768));
			rect.setFillColor(sf::Color(0, 0, 0, 200));
			m_window.draw(rect);
			m_window.draw(m_looseText);
			m_window.draw(m_websiteText);
		}
	}

	m_window.display();
}

int Game::getDeliveries() const
{
	return m_deliveries;
}

const sf::RenderWindow & Game::getWindow() const
{
	return m_window;
}
