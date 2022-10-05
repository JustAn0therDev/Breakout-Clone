#pragma once
#include <SFML/Audio.hpp>

class AudioHandler {
private:
	sf::SoundBuffer m_BoopBuffer;
	sf::SoundBuffer m_BubblePopBuffer;
	sf::SoundBuffer m_GameOverThemeBuffer;
	sf::Sound m_Boop;
	sf::Sound m_BubblePop;
	sf::Sound m_GameOverTheme;
public:
	AudioHandler();
	void playBubblePop();
	void playBoop();
	void playGameOverTheme();
};