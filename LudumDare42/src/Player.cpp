#include "Player.h"
#include "Game.h"

#include <iostream>

Player::Player(Level* level, Game* game) :
	m_level(level),
	m_game(game),
	m_heldBox(NULL),
	m_timer(0),
	m_alpha(255),
	m_displaySatisfactionIcon(false)
{
	m_position.x = 15 * 16 * Game::ZOOM_FACTOR;
	m_position.y = 8 * 16 * Game::ZOOM_FACTOR;
	
	m_animation = new Graphics::AnimatedSprite(sf::seconds(0.2), true, true);
	m_animation->setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));
	m_animation->setPosition(m_position);
	
	m_bounds->top = m_position.y + (15 * Game::ZOOM_FACTOR);
	m_bounds->left = m_position.x;
	m_bounds->width = 14 * Game::ZOOM_FACTOR;
	m_bounds->height = 12 * Game::ZOOM_FACTOR;

	if (!m_texture.loadFromFile("gfx/gameassets.png"))
	{
		std::cerr << "Fail to load gameassets" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 16, 14, 27));
	m_sprite.setPosition(m_position);
	m_sprite.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));

	m_walkingLeftAnim = new Graphics::Animation();
	m_walkingLeftAnim->setSpritesheet(m_texture);
	m_walkingLeftAnim->addFrame(sf::IntRect(2, 110, 15, 27));
	m_walkingLeftAnim->addFrame(sf::IntRect(20, 111, 15, 26));
	m_walkingLeftAnim->addFrame(sf::IntRect(38, 110, 15, 27));
	m_walkingLeftAnim->addFrame(sf::IntRect(20, 111, 15, 26));

	m_walkingRightAnim = new Graphics::Animation();
	m_walkingRightAnim->setSpritesheet(m_texture);
	m_walkingRightAnim->addFrame(sf::IntRect(2, 139, 15, 27));
	m_walkingRightAnim->addFrame(sf::IntRect(20, 139, 15, 26));
	m_walkingRightAnim->addFrame(sf::IntRect(39, 138, 15, 27));
	m_walkingRightAnim->addFrame(sf::IntRect(20, 139, 15, 26));

	m_animation->setAnimation(*m_walkingLeftAnim);

	m_satisfactionIcon.setTexture(m_texture);
	m_satisfactionIcon.setTextureRect(sf::IntRect(245, 56, 19, 13));
	m_satisfactionIcon.setScale(sf::Vector2f(Game::ZOOM_FACTOR, Game::ZOOM_FACTOR));

	if (!m_takeSound.loadFromFile("sfx/take.ogg"))
	{
		std::cerr << "Fail to load take.ogg" << std::endl;
	}

	if (!m_placeSound.loadFromFile("sfx/place.ogg"))
	{
		std::cerr << "Fail to load place.ogg" << std::endl;
	}

	if(!m_applauseSound.loadFromFile("sfx/applause.ogg"))
	{
		std::cerr << "Fail to load applause.ogg" << std::endl;
	}

	m_elapsed = m_playerTimer.restart();
}

Player::~Player()
{
}

void Player::update(float dt)
{
	int x = 0, y = 0;

	if (m_displaySatisfactionIcon)
	{
		m_timer += dt;
		if (m_timer > 0.1f && m_alpha > 0)
		{
			m_timer -= 0.1f;
			m_alpha -= (0.1 * 255 / 3);
			if (m_alpha < 0)
				m_alpha = 0;
			sf::Vector2f position = m_satisfactionIcon.getPosition();
			m_satisfactionIcon.setPosition(position.x, position.y - 4);
			m_satisfactionIcon.setColor(sf::Color(255, 255, 255, m_alpha));
		}
		else if(m_alpha <= 0)
		{
			m_displaySatisfactionIcon = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_animation->play(*m_walkingLeftAnim);
		x--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_animation->play(*m_walkingRightAnim);
		x++;
	}
	else
	{
		m_animation->pause();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		y--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		y++;
	}

	if(isBlocked(x, y))
	{
		return;
	}

	m_elapsed = m_playerTimer.restart();
	m_animation->update(m_elapsed);

	m_position.x += x;
	m_position.y += y;

	m_animation->setPosition(m_position);

	if (m_heldBox != NULL)
	{
		m_heldBox->setPosition(sf::Vector2f(m_position.x - 1, m_position.y - (10 * Game::ZOOM_FACTOR)));
	}

	m_sprite.setPosition(m_position);
	m_bounds->top = m_position.y + (15 * Game::ZOOM_FACTOR);
	m_bounds->left = m_position.x;
}

void Player::takeBox()
{
	if(m_heldBox == NULL)
	{
		int shelfId = 0;
		if (m_level->getNumber(m_bounds->left, m_bounds->top) > 1)
		{
			shelfId = m_level->getNumber(m_bounds->left, m_bounds->top);
		}

		if (shelfId != 0)
		{
			m_game->displaySelection(shelfId);
			return;
		}
		else
		{
			std::vector<Box*> boxes = m_level->getBoxes();
			for (std::vector<Box*>::iterator it = boxes.begin(); it != boxes.end(); ++it)
			{
				sf::IntRect* rect = (*it)->getBounds();
				sf::Vector2f boxSizeRadius = sf::Vector2f(rect->width + 20, rect->height + 20);
				sf::Vector2f playerRadius = sf::Vector2f(m_bounds->width + 20, m_bounds->height + 20);

				float radius1 = (boxSizeRadius.x + boxSizeRadius.y) / 4;
				float radius2 = (playerRadius.x + playerRadius.y) / 4;

				sf::Vector2f dist = (*it)->getCenter() - getCenter();

				if (dist.x * dist.x + dist.y * dist.y <= (radius1 + radius2) * (radius1 + radius2))
				{
					m_heldBox = (*it);
					(*it)->setIsHeld(true);
					m_sound.setBuffer(m_takeSound);
					m_sound.play();
					m_sprite.setTextureRect(sf::IntRect(17, 16, 16, 27));
				}
			}
		}
	}
	else
	{
		int shelfId = 0;
		if (m_level->getNumber(m_bounds->left, m_bounds->top) > 1)
		{
			shelfId = m_level->getNumber(m_bounds->left, m_bounds->top);
		}

		if (shelfId != 0 && shelfId != 5)
		{
			int nbArticlesOld = m_heldBox->getNbArticles();
			if (m_level->appendBoxToShelf(shelfId, m_heldBox))
			{
				m_sprite.setTextureRect(sf::IntRect(0, 16, 14, 27));
				m_heldBox = NULL;
				m_sound.setBuffer(m_placeSound);
				m_sound.play();
			}
			else
			{
				if (nbArticlesOld != m_heldBox->getNbArticles())
				{
					m_sound.setBuffer(m_placeSound);
					m_sound.play();
				}
			}
			return;
		}
		else if (shelfId == 5)
		{
			if (m_heldBox->isRestock())
			{
				//Display message to store into shelves..
				return;
			}

			std::vector<Order*> orders = m_game->getOrders();
			for (std::vector<Order*>::iterator it = orders.begin(); it != orders.end(); ++it)
			{
				if ((*it)->getArticle() == m_heldBox->getArticle())
				{
					m_game->addCustomerFeed(10);
					m_level->removeBox(m_heldBox);
					(*it)->setCompleted();
					m_heldBox = NULL;
					m_game->setDelivery(1);
					m_satisfactionIcon.setPosition(m_position.x - 3, m_position.y);
					m_displaySatisfactionIcon = true;
					m_alpha = 255;
					m_timer = 0;
					m_sprite.setTextureRect(sf::IntRect(0, 16, 14, 27));
					m_sound.setBuffer(m_applauseSound);
					m_sound.play();
					return;
				}
			}
			std::cout << "No order founded" << std::endl;
			return;
		}

		m_sound.setBuffer(m_placeSound);
		m_sound.play();
		m_sprite.setTextureRect(sf::IntRect(0, 16, 14, 27));
		m_heldBox->setPosition(sf::Vector2f(m_position.x - 1, m_bounds->top + m_bounds->height + (10 * Game::ZOOM_FACTOR)));
		if (m_heldBox->isRestock())
		{
			m_heldBox->setIsHeld(false);
		}
		m_heldBox = NULL;
	}
}

void Player::setHeldBox(Box* b)
{
	if (b == nullptr)
	{
		return;
	}
	m_sound.setBuffer(m_takeSound);
	m_sound.play();
	m_heldBox = b;
	m_sprite.setTextureRect(sf::IntRect(17, 16, 16, 27));
}

bool Player::isBlocked(int cx, int cy)
{
	sf::IntRect rect(
		m_bounds->left + cx,
		m_bounds->top + cy,
		m_bounds->width,
		m_bounds->height
	);

	//wall collision detection
	if (m_level->collisionWall(rect.left, rect.top) ||
		m_level->collisionWall(rect.left, rect.top + rect.height) ||
		m_level->collisionWall(rect.left + rect.width, rect.top) ||
		m_level->collisionWall(rect.left + rect.width, rect.top + rect.height))
	{
		return true;
	}

	std::vector<Box*> boxes = m_level->getBoxes();
	for (std::vector<Box*>::iterator it = boxes.begin(); it != boxes.end();++it)
	{
		sf::IntRect* boxBounds = (*it)->getBounds();

		if ((*it) != m_heldBox && (*it)->getBounds()->intersects(rect))
		{
			return true;
		}
	}

	return false;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(*m_animation);

	if (m_displaySatisfactionIcon)
	{
		target.draw(m_satisfactionIcon);
	}

	//renderBounds(target);
}
