#include "Arrow.h"

const float radToDeg = 180 / 3.141592f;

Arrow::Arrow() :
	m_arrowHead(10.0f, 3),
	m_arrowStart({50, 50}),
	m_arrowEnd({150, 50})
{
	setWidth(5.0f);
	constructArrow();
}

Arrow::Arrow(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float width) :
	m_arrowHead(width * 2.0f, 3),
	m_arrowStart(startPoint),
	m_arrowEnd(endPoint)
{
	setWidth(width);
	constructArrow();
}

void Arrow::draw(sf::RenderWindow& window) {
	window.draw(m_arrowBody);
	window.draw(m_arrowHead);
}

void Arrow::setStartPoint(const sf::Vector2f& startPoint) {
	m_arrowStart = startPoint;
	constructArrow();
}

void Arrow::setEndPoint(const sf::Vector2f& endPoint) {
	m_arrowEnd = endPoint;
	constructArrow();
}

void Arrow::setWidth(float width) {
	m_arrowBody.setSize({ m_arrowBody.getSize().x, width });
	m_arrowHead.setRadius(width * 2.0f);
	constructArrow();
}

void Arrow::constructArrow() {
	//calculate how long the arrow should be to connect 2 points
	float length = sqrtf((m_arrowEnd.x - m_arrowStart.x) * (m_arrowEnd.x - m_arrowStart.x) +
						 (m_arrowEnd.y - m_arrowStart.y) * (m_arrowEnd.y - m_arrowStart.y));

	//rotate and position the body of the arrow first
	m_arrowBody.setRotation(radToDeg * atan2f((m_arrowEnd.y - m_arrowStart.y), (m_arrowEnd.x - m_arrowStart.x)));
	m_arrowBody.setPosition(m_arrowStart);

	//set the length of the arrow
	m_arrowBody.setSize({ length, m_arrowBody.getSize().y });

	//set origin of arrow head based on radius
	m_arrowHead.setOrigin(m_arrowHead.getRadius(), m_arrowHead.getRadius());

	//position arrow head based on which way the arrow is pointing and the width of the arrow body, before rotation
	float width = m_arrowBody.getSize().y;
	if (m_arrowStart.x < m_arrowEnd.x) {
		m_arrowHead.setPosition(m_arrowEnd + sf::Vector2f(0.f, width / 2.0f));
	}
	else {
		m_arrowHead.setPosition(m_arrowEnd - sf::Vector2f(0.f, width / 2.0f));
	}

	//finally, rotate the arrow head (+90 so the "tip" of the arrow head is originally facing right)
	m_arrowHead.setRotation(m_arrowBody.getRotation() + 90.0f);
}