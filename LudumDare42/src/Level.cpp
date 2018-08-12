#include "Level.h"
#include "Game.h"

Level::Level() :
	m_timerRestock(0),
	m_delayBetweenRestocks(15),
	m_selectedShelf(0),
	m_selectedBox(0)
{
	m_random = new Utils::Random();

	Box* b = new Box(Article::CLOTHING, 3, true);
	b->setPosition(sf::Vector2f(
		11 * 16 * Game::ZOOM_FACTOR,
		8 * 16 * Game::ZOOM_FACTOR
	));
	m_restockBoxes.push_back(b);

	if (!m_texture.loadFromFile("gfx/template.png"))
	{
		std::cerr << "Unable to find template" << std::endl;
	}

	if (!m_sprites.loadFromFile("gfx/gameassets.png"))
	{
		std::cerr << "Unable to find gameassets" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));

	m_hand.setTexture(m_sprites);
	m_hand.setTextureRect(sf::IntRect(0, 73, 9, 13));
	m_hand.setPosition(sf::Vector2f(13 * 16 * Game::ZOOM_FACTOR, 16 * Game::ZOOM_FACTOR));
	m_hand.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));

	Shelf* s = new Shelf();
	s->setPosition(sf::Vector2f(13 * 16 * Game::ZOOM_FACTOR, 2 * 16 * Game::ZOOM_FACTOR));
	m_shelves[2] = s;

	s = new Shelf();
	s->setPosition(sf::Vector2f(19 * 16 * Game::ZOOM_FACTOR, 2 * 16 * Game::ZOOM_FACTOR));
	m_shelves[3] = s;

	s = new Shelf();
	s->setPosition(sf::Vector2f(25 * 16 * Game::ZOOM_FACTOR, 2 * 16 * Game::ZOOM_FACTOR));
	m_shelves[4] = s;
}

Level::~Level()
{
}

void Level::selectedShelf(int shelfId)
{
	m_selectedBox = 0;
	m_selectedShelf = shelfId;
	switch (m_selectedShelf)
	{
		case 2:
			m_hand.setPosition(sf::Vector2f(
				13 * 16 * Game::ZOOM_FACTOR + (m_selectedBox % 2) * 32 * Game::ZOOM_FACTOR,
				16 * Game::ZOOM_FACTOR + (m_selectedBox / 2) * 16 * Game::ZOOM_FACTOR)
			);
			break;
		case 3:
			m_hand.setPosition(sf::Vector2f(
				19 * 16 * Game::ZOOM_FACTOR + (m_selectedBox % 2) * 32 * Game::ZOOM_FACTOR,
				16 * Game::ZOOM_FACTOR + (m_selectedBox / 2) * 16 * Game::ZOOM_FACTOR)
			);
			break;
		case 4:
			m_hand.setPosition(sf::Vector2f(
				25 * 16 * Game::ZOOM_FACTOR + (m_selectedBox % 2) * 32 * Game::ZOOM_FACTOR,
				16 * Game::ZOOM_FACTOR + (m_selectedBox / 2) * 16 * Game::ZOOM_FACTOR)
			);
			break;
	}
}

Box* Level::selectBox()
{
	return m_shelves[m_selectedShelf]->getBox(m_selectedBox);
}

void Level::moveHand(int x)
{
	if (m_selectedBox + x > 3 || m_selectedBox + x < 0)
	{
		return;
	}

	m_selectedBox += x;
	switch(m_selectedShelf)
	{
		case 2:
			m_hand.setPosition(sf::Vector2f(
				13 * 16 * Game::ZOOM_FACTOR + (m_selectedBox % 2) * 32 * Game::ZOOM_FACTOR,
				16 * Game::ZOOM_FACTOR + (m_selectedBox / 2) * 16 * Game::ZOOM_FACTOR)
			);
			break;
		case 3:
			m_hand.setPosition(sf::Vector2f(
				19 * 16 * Game::ZOOM_FACTOR + (m_selectedBox % 2) * 32 * Game::ZOOM_FACTOR,
				16 * Game::ZOOM_FACTOR + (m_selectedBox / 2) * 16 * Game::ZOOM_FACTOR)
			);
			break;
		case 4:
			m_hand.setPosition(sf::Vector2f(
				25 * 16 * Game::ZOOM_FACTOR + (m_selectedBox % 2) * 32 * Game::ZOOM_FACTOR,
				16 * Game::ZOOM_FACTOR + (m_selectedBox / 2) * 16 * Game::ZOOM_FACTOR)
			);
			break;
	}
}

void Level::update(float dt)
{
	if (m_selectedShelf != 0)
	{
		return;
	}

	m_timerRestock += dt;
	//Generate new restocking
	if (m_timerRestock > m_delayBetweenRestocks)
	{
		m_delayBetweenRestocks = m_random->getNumberInRange(6, 12);
		std::cout << "waiting restock: " << m_delayBetweenRestocks << "s" << std::endl;
		m_timerRestock = 0;
		if (m_random->getNumberInRange(0, 3) > 1)
		{
			std::cout << "generate Restock" << std::endl;

			int nbArticles = m_random->getNumberInRange(1, 4);
			Box* b;

			switch (m_random->getNumberInRange(0, 3))
			{
				case Article::BEACH_ACCESSORIES:
					b = new Box(Article::BEACH_ACCESSORIES, nbArticles, true);
					break;
				case Article::CLOTHING:
					b = new Box(Article::CLOTHING, nbArticles, true);
					break;
				case Article::ELECTRONICS:
					b = new Box(Article::ELECTRONICS, nbArticles, true);
					break;
				case Article::FOOD:
					b = new Box(Article::FOOD, nbArticles, true);
					break;
				default:
					b = new Box(Article::CLOTHING, 1, true);
			}

			b->setPosition(sf::Vector2f(
				m_random->getNumberInRange(8, 11) * 16 * Game::ZOOM_FACTOR,
				m_random->getNumberInRange(4, 13) * 16 * Game::ZOOM_FACTOR
			));
			m_restockBoxes.push_back(b);
		}
	}

	for (std::vector<Box*>::iterator it = m_restockBoxes.begin(); it != m_restockBoxes.end();)
	{
		(*it)->update(dt);

		if ((*it)->toRemove())
		{
			delete *it;
			it = m_restockBoxes.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool Level::appendBoxToShelf(int shelfId, Box* box)
{
	int nbArticles = box->getNbArticles();
	for (int i = 0; i < nbArticles; i++)
	{
		if (m_shelves[shelfId]->isFull())
		{
			break;
		}
		Box* b = new Box(box->getArticle(), 1, false, true);
		m_restockBoxes.push_back(b);
		m_shelves[shelfId]->appendBox(b);
		box->setNbArticles(nbArticles - (i + 1));
	}

	if (box->getNbArticles() == 0)
	{
		for (std::vector<Box*>::iterator it = m_restockBoxes.begin(); it != m_restockBoxes.end();)
		{
			if ((*it) == box)
			{
				delete *it;
				it = m_restockBoxes.erase(it);
			}
			else
			{
				++it;
			}
		}
		return true;
	}
	return false;
}

bool Level::removeBox(Box* box)
{
	for (std::vector<Box*>::iterator it = m_restockBoxes.begin(); it != m_restockBoxes.end();)
	{
		if ((*it) == box)
		{
			delete *it;
			it = m_restockBoxes.erase(it);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

int Level::getNumber(int x, int y) const
{
	int xa = x / (16 * Game::ZOOM_FACTOR);
	int ya = y / (16 * Game::ZOOM_FACTOR);

	return m_collisionMap[xa][ya];
}

std::vector<Box*> Level::getBoxes() const
{
	return m_restockBoxes;
}

void Level::render(sf::RenderTarget& target)
{
	target.draw(m_sprite);

	if (m_selectedShelf != 0)
	{
		target.draw(m_hand);
	}
}

bool Level::collisionWall(int x, int y)
{
	int xa = x / (16 * Game::ZOOM_FACTOR);
	int ya = y / (16 * Game::ZOOM_FACTOR);

	if(m_collisionMap[xa][ya] == 1)
	{
		return true;
	}

	return false;
}
