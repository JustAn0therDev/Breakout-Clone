#pragma once
#include <SFML/Audio.hpp>

class AudioHandler {
private:
	sf::SoundBuffer m_BoopBuffer;
	sf::SoundBuffer m_BubblePopBuffer;
	sf::SoundBuffer m_GameOverThemeBuffer;
	sf::SoundBuffer m_ThonkBuffer;
	sf::Sound m_Boop;
	sf::Sound m_BubblePop;
	sf::Sound m_GameOverTheme;
	sf::Sound m_Thonk;
public:
	AudioHandler();
	void playBubblePop();
	void playBoop();
	void playGameOverTheme();
	void playThonk();
};