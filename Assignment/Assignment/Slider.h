#ifndef SLIDER_H
#define SLIDER_H

/* Filename: Slider.h
 * Description: Encapsulates the assets and functionality of a slider component.
 */

#include <SFML/Graphics.hpp>

class Slider {
public:
	Slider();
	Slider(float min, float max);

	//draw assets to provided RenderWindow
	void draw(sf::RenderWindow& window);

	//mutators
	void setPosition(const sf::Vector2f& position);
	void setValue(float value);

	//accessors
	float getValue() const;

	bool click(int x, int y, sf::RenderWindow& window);
	bool handleEvents(const sf::Event& event, sf::RenderWindow& window);

private:
	sf::RectangleShape	m_background;
	sf::CircleShape		m_handle;

	float				m_minimumValue;
	float				m_maximumValue;
	float				m_currentValue;

	bool				m_sliding;

	void calculateValue();
};

#endif