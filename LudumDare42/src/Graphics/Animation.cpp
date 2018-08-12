#include "Animation.h"

namespace Graphics
{
	Animation::Animation() : m_texture(NULL)
	{
	}

	void Animation::addFrame(sf::IntRect rect)
	{
		m_frames.push_back(rect);
	}

	void Animation::setSpritesheet(const sf::Texture& texture)
	{
		m_texture = &texture;
	}

	const sf::Texture* Animation::getSpritesheet() const
	{
		return m_texture;
	}

	std::size_t Animation::getSize() const
	{
		return m_frames.size();
	}

	const sf::IntRect& Animation::getFrame(std::size_t size) const
	{
		return m_frames[size];
	}
}