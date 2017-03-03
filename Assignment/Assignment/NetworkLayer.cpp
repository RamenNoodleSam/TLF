#include "NetworkLayer.h"

NetworkLayer::NetworkLayer() {

}

NetworkLayer::NetworkLayer(const sf::Vector2f& position) :
	m_position(position)
{
}

void NetworkLayer::draw(sf::RenderWindow& window) {
	for (auto& iter : m_neurons) {
		iter.draw(window);
	}
}

void NetworkLayer::setPosition(const sf::Vector2f& position) {
	m_position = position;
}

unsigned int NetworkLayer::setIDs(unsigned int startingID) {
	for (int i = 0; i < m_neurons.size(); ++i) {
		m_neurons[i].setID(startingID + i);
	}

	return startingID + m_neurons.size();
}

void NetworkLayer::addNeuron(const sf::String& data, bool isBias) {
	Neuron neuron;
	neuron.setString(data);
	neuron.setIsBias(isBias);
	m_neurons.push_back(neuron);

	repositionNeurons();
}

Neuron* NetworkLayer::getNeuronWithID(unsigned int id) {
	for (auto& iter : m_neurons) {
		if (iter.getID() == id) {
			return &iter;
		}
	}

	return nullptr;
}

void NetworkLayer::repositionNeurons() {
	size_t numberOfNeurons = m_neurons.size();
	float spacing = 340.f / numberOfNeurons;

	for (size_t i = 0; i < numberOfNeurons; ++i) {
		m_neurons[i].setPosition(m_position + sf::Vector2f(0.f, spacing * i + spacing * 0.5f));
	}
}