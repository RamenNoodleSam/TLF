#ifndef NETWORKEDITORSTATE_H
#define NETWORKEDITORSTATE_H

/* Filename: NetworkEditorState.h
 * Description: Concrete State representing the Network Editor Screen.
 *				Allows user to load and save the network, as well as modify the structure.
 */

#include "State.h"
#include "Button.h"
#include "TextField.h"
#include "Neuron.h"

//prototype
class NeuralNetwork;

class NetworkEditorState : public State {
public:
	NetworkEditorState(StateManager* pStateManager);
	~NetworkEditorState();

	//overridden virtual methods
	virtual void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

private:
	//layers storing the number of Neurons in each
	std::vector<unsigned int>	m_layers;

	//visual assets
	std::vector<Button>			m_buttons;
	std::vector<sf::Text>		m_text;

	TextField					m_networkFile;
	TextField					m_numberOfNeurons;

	//link to neural network
	NeuralNetwork*				m_pNeuralNetwork;
};

#endif