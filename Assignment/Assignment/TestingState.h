#ifndef TESTINGSTATE_H
#define TESTINGSTATE_H

#include "State.h"
#include "Button.h"
#include "TextField.h"
#include "Arrow.h"
#include "Neuron.h"
#include "NetworkLayer.h"

//prototype
class NeuralNetwork;

class TestingState : public State {
public:
	TestingState(StateManager* pStateManager);
	~TestingState();

	virtual void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

	void setTestOutputs(const std::vector<sf::String>& outputs);
	void createNetworkStructure();

private:
	//visual assets
	std::vector<Button>			m_buttons;
	std::vector<sf::Text>		m_text;

	std::vector<NetworkLayer>	m_layers;
	std::vector<Arrow>			m_connections;

	//link to neural network
	NeuralNetwork*				m_pNeuralNetwork;
};

#endif