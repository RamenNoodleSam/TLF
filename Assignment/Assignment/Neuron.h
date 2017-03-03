#ifndef NEURON_H
#define NEURON_H

/* Filename: Neuron.h
 * Description: Graphical representation of a neuron as part of the neural network.
 */

#include <SFML/Graphics.hpp>

class Neuron {
public:
	Neuron();
	Neuron(const sf::Vector2f& position, float radius = 40.0f, const sf::String& textString = "");

	//draw assets to provided RenderWindow
	void draw(sf::RenderWindow& window);

	//mutators
	void setPosition(const sf::Vector2f& position);
	void setRadius(float radius);
	void setString(const sf::String& textString);
	void setID(unsigned int id);
	void setIsBias(bool isBias);

	//accessors
	sf::Vector2f getLeftPoint() const;
	sf::Vector2f getRightPoint() const;
	unsigned int getID() const;
private:
	sf::CircleShape m_background;
	sf::Text		m_text;
	unsigned int	m_id;

	//repositions the text on the Neuron based on size of the Neuron and text
	void repositionText();
};

#endif