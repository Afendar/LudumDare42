#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Level.h"
#include "Entity.h"
#include "Graphics/AnimatedSprite.h"

class Game;

class Player : public Entity
{
	public:
		Player(Level* level, Game* game);
		~Player();

		bool isBlocked(int cx, int cy);

		void update(float dt);
		void render(sf::RenderTarget& target);

		void takeBox();
		void setHeldBox(Box* b);

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite, m_satisfactionIcon;

		sf::SoundBuffer m_takeSound, m_placeSound, m_applauseSound;
		sf::Sound m_sound;

		Box* m_heldBox;

		Game* m_game;
		Level* m_level;

		sf::Clock m_playerTimer;
		sf::Time m_elapsed;

		int m_alpha;
		float m_timer;
		bool m_displaySatisfactionIcon;

		Graphics::Animation* m_walkingLeftAnim, *m_walkingRightAnim;
		Graphics::AnimatedSprite* m_animation;
};