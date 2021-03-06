#include "Core.h"
#include "NeuralNetwork.h"
#include "GlobalAssetPool.h"

Core::Core() {
	//initialise window
	m_window.create(sf::VideoMode(800, 600), "Artificial Neural Network");

	if (!m_window.isOpen()) {
		throw std::runtime_error("Failed to instantiate application window!");
	}

	//initialise neural network
	m_pNeuralNetwork = NeuralNetwork::getInstance();

	//initialise states
	m_stateManager.init();
}

Core::~Core() {
	//if these exist delete them, if they don't exist they will be created before being immediately deleted.
	//application termination is not a performance critical section of code so this is fine
	delete GlobalAssetPool::getInstance();
	delete NeuralNetwork::getInstance();
}

bool Core::run() {
	while (m_window.isOpen()) {
		//handle events
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}

			m_stateManager.currentState()->handleEvents(event, m_window);
		}

		//update assets
		m_stateManager.currentState()->update();

		//draw assets
		m_window.clear(sf::Color(40, 40, 40));
		m_stateManager.currentState()->draw(m_window);
		m_window.display();
	}

	return 0;
}