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

	//overridden virtual methods
	virtual void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

	//sets string outputs when user presses "Test Network"
	void setTestOutputs(const std::vector<sf::String>& outputs);

	//create the GUI representation of the neural network on the testing screen
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