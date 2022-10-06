#include "AudioHandler.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

AudioHandler::AudioHandler() {
	if (!m_BoopBuffer.loadFromFile("Assets/Audio/Boop.ogg")) {
		std::cout << "Could not load audio from file." << std::endl;
		exit(1);
	}

	m_Boop.setBuffer(m_BoopBuffer);

	if (!m_BubblePopBuffer.loadFromFile("Assets/Audio/Bubble.ogg")) {
		std::cout << "Could not load audio from file." << std::endl;
		exit(1);
	}

	m_BubblePop.setBuffer(m_BubblePopBuffer);

	if (!m_GameOverThemeBuffer.loadFromFile("Assets/Audio/Super Smash Bros Unlock.ogg")) {
		std::cout << "Could not load audio from file." << std::endl;
		exit(1);
	}

	m_GameOverTheme.setBuffer(m_GameOverThemeBuffer);
	m_GameOverTheme.setVolume(20);

	if (!m_ThonkBuffer.loadFromFile("Assets/Audio/Thonk.ogg")) {
		std::cout << "Could not load audio from file." << std::endl;
		exit(1);
	}

	m_Thonk.setBuffer(m_ThonkBuffer);
	m_Thonk.setVolume(30);
}

void AudioHandler::playBubblePop() {
	if (m_BubblePop.getStatus() == sf::SoundSource::Playing) {
		m_BubblePop.stop();
	}

	m_BubblePop.setPlayingOffset(sf::seconds(0.35f));
	m_BubblePop.play();
}

void AudioHandler::playBoop() {
	if (m_Boop.getStatus() == sf::SoundSource::Playing) {
		m_Boop.stop();
	}

	m_Boop.setPlayingOffset(sf::seconds(0.2f));
	m_Boop.play();
}

void AudioHandler::playGameOverTheme() {
	if (m_GameOverTheme.getStatus() == sf::SoundSource::Playing) {
		m_GameOverTheme.stop();
	}

	m_GameOverTheme.setPlayingOffset(sf::seconds(0.2f));
	m_GameOverTheme.play();
}

void AudioHandler::playThonk() {
	if (m_Thonk.getStatus() == sf::SoundSource::Playing) {
		m_Thonk.stop();
	}

	m_Thonk.setPlayingOffset(sf::seconds(0.6f));
	m_Thonk.play();
}
