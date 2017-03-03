#ifndef NETWORKLAYER_H
#define NETWORKLAYER_H

#include <SFML/Graphics.hpp>
#include "Neuron.h"

class NetworkLayer {
public:
	NetworkLayer();
	NetworkLayer(const sf::Vector2f& position);

	void draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	unsigned int setIDs(unsigned int startingID);
	void addNeuron(const sf::String& data, bool isBias);

	Neuron* getNeuronWithID(unsigned int id);
private:
	std::vector<Neuron>	m_neurons;
	sf::Vector2f		m_position;

	void repositionNeurons();
};

#endif