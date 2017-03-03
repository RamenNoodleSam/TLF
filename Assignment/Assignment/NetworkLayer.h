#ifndef NETWORKLAYER_H
#define NETWORKLAYER_H

/* Filename: NetworkLayer.h
 * Description: Encapsulates a column of Neurons, and handles their
 *				positioning and rendering
 */

#include <SFML/Graphics.hpp>
#include "Neuron.h"

class NetworkLayer {
public:
	NetworkLayer();
	NetworkLayer(const sf::Vector2f& position);

	//draw assets to provided RenderWindow
	void draw(sf::RenderWindow& window);

	//mutators
	void setPosition(const sf::Vector2f& position);
	unsigned int setIDs(unsigned int startingID);
	void addNeuron(const sf::String& data, bool isBias);

	//accessors
	Neuron* getNeuronWithID(unsigned int id);
private:
	std::vector<Neuron>	m_neurons;
	sf::Vector2f		m_position;

	//repositions the neurons in th eLayer based on how many Neurons are in it
	void repositionNeurons();
};

#endif