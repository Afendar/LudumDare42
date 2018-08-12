#pragma once

class Entity
{
	public:
		Entity()
		{
			m_bounds = new sf::IntRect(0, 0, 0, 0);
		}

		sf::Vector2f getPosition() const
		{
			return m_position;
		}

		void setPosition(sf::Vector2f pos)
		{
			m_position = pos;
		}

		sf::IntRect* getBounds() const
		{
			return m_bounds;
		}

		virtual void update(float dt) {};

		bool isBlocked(int cx, int cy)
		{
			return false;
		}

		void onTouch(Entity e) {};

		bool intersect(sf::IntRect bounds)
		{
			return m_bounds->intersects(bounds);
		}

		sf::Vector2f getCenter()
		{
			return sf::Vector2f(m_bounds->left + m_bounds->width / 2.0f, m_bounds->top + m_bounds->height / 2.0f);
		}

		void renderBounds(sf::RenderTarget& target)
		{
			sf::RectangleShape rect(sf::Vector2f(m_bounds->width, m_bounds->height));
			rect.setPosition(sf::Vector2f(m_bounds->left, m_bounds->top));
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color::Red);
			rect.setOutlineThickness(1);
			target.draw(rect);
		}

	protected:

		sf::Vector2f m_position;
		sf::IntRect* m_bounds;
};