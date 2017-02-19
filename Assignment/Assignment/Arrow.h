#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>

class Arrow {
public:
	Arrow();
	Arrow(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float width = 5.0f);

	void draw(sf::RenderWindow& window);

	void setStartPoint(const sf::Vector2f& startPoint);
	void setEndPoint(const sf::Vector2f& endPoint);
	void setWidth(float width);

private:
	sf::RectangleShape	m_arrowBody;
	sf::CircleShape		m_arrowHead;
	sf::Vector2f		m_arrowStart;
	sf::Vector2f		m_arrowEnd;

	void constructArrow();
};

#endif