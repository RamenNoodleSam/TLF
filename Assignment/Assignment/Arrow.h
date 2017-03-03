#ifndef ARROW_H
#define ARROW_H

/* Filename: Arrow.h
* Description: Encapsulates the assets and functionality of an arrow.
*				Used to graphically link neurons in the network.
*/

#include <SFML/Graphics.hpp>

class Arrow {
public:
	Arrow();
	Arrow(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float width = 5.0f);

	//draw assets to provided RenderWindow (seperated so all text is rendered on top)
	void drawArrow(sf::RenderWindow& window);
	void drawText(sf::RenderWindow& window);

	//mutators
	void setStartPoint(const sf::Vector2f& startPoint);
	void setEndPoint(const sf::Vector2f& endPoint);
	void setWidth(float width);
	void setColour(const sf::Color& colour);
	void setString(const sf::String& textString);

private:
	sf::RectangleShape	m_arrowBody;
	sf::CircleShape		m_arrowHead;
	sf::Vector2f		m_arrowStart;
	sf::Vector2f		m_arrowEnd;

	sf::Text			m_text;

	//constructs arrow based on provided start and end points, and width
	void constructArrow();
};

#endif