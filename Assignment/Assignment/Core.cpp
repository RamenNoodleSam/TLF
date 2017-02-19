#include "Core.h"
#include "GlobalAssetPool.h"

Core::Core() {
	m_window.create(sf::VideoMode(800, 600), "Artificial Neural Network");

	m_stateManager.init();

	if (!m_window.isOpen()) {
		throw std::runtime_error("Failed to instantiate contents of Core object!");
	}
}

Core::~Core() {
	delete GlobalAssetPool::getInstance();
}

bool Core::run() {
	while (m_window.isOpen()) {
		//handle events
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}

			m_stateManager.currentState()->handleEvents(event);
		}

		//update assets
		m_stateManager.currentState()->update();

		//draw assets
		m_window.clear();
		m_stateManager.currentState()->draw(m_window);
		m_window.display();
	}

	return 0;
}