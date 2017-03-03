#ifndef NETWORKEDITORSTATE_H
#define NETWORKEDITORSTATE_H

#include "State.h"
#include "Button.h"
#include "TextField.h"
#include "Neuron.h"
#include "NetworkLayer.h"

//prototype
class NeuralNetwork;

class NetworkEditorState : public State {
public:
	NetworkEditorState(StateManager* pStateManager);
	~NetworkEditorState();

	virtual void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

private:
	//visual assets
	std::vector<Button>			m_buttons;
	std::vector<sf::Text>		m_text;

	TextField					m_networkFile;

	Button						m_addNeuron;
	Button						m_removeNeuron;
	std::vector<NetworkLayer>	m_layers;

	//link to neural network
	NeuralNetwork*				m_pNeuralNetwork;
};

#endif