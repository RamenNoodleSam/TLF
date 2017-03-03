#include "Arrow.h"
#include "GlobalAssetPool.h"

const float radToDeg = 180 / 3.141592f;

Arrow::Arrow() :
	m_arrowHead(10.0f, 3),
	m_arrowStart({50, 50}),
	m_arrowEnd({150, 50})
{
	//set colour of the arrow components
	setColour({ 80, 80, 80 });

	//initialise text
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setCharacterSize(16);
	m_text.setStyle(m_text.Bold);
	m_text.setFillColor({ 255, 140, 0 });

	//construct arrow using default information
	setWidth(5.0f);
	constructArrow();
}

Arrow::Arrow(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float width) :
	m_arrowHead(width * 2.0f, 3),
	m_arrowStart(startPoint),
	m_arrowEnd(endPoint)
{
	//set colour of the arrow components
	setColour({80, 80, 80});

	//initialise text
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setCharacterSize(16);
	m_text.setStyle(m_text.Bold);
	m_text.setFillColor({ 255, 140, 0 });

	//construct arrow using passed information
	setWidth(width);
	constructArrow();
}

void Arrow::drawArrow(sf::RenderWindow& window) {
	window.draw(m_arrowBody);

	//removed arrow head for clarify of diagrams on the Testing screen
	//window.draw(m_arrowHead);
}

void Arrow::drawText(sf::RenderWindow& window) {
	window.draw(m_text);
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

void Arrow::setColour(const sf::Color& colour) {
	m_arrowBody.setFillColor(colour);
	m_arrowHead.setFillColor(colour);
}

void Arrow::setString(const sf::String& textString) {
	m_text.setString(textString);
	constructArrow();
}

void Arrow::constructArrow() {
	//calculate how long the arrow should be to connect 2 points
	float length = sqrtf((m_arrowEnd.x - m_arrowStart.x) * (m_arrowEnd.x - m_arrowStart.x) +
						 (m_arrowEnd.y - m_arrowStart.y) * (m_arrowEnd.y - m_arrowStart.y));

	//rotate and position the body of the arrow first
	m_arrowBody.setOrigin({ 0.f, m_arrowBody.getSize().y / 2.0f });
	m_arrowBody.setRotation(radToDeg * atan2f((m_arrowEnd.y - m_arrowStart.y), (m_arrowEnd.x - m_arrowStart.x)));
	m_arrowBody.setPosition(m_arrowStart);

	//set the length of the arrow
	m_arrowBody.setSize({ length, m_arrowBody.getSize().y });

	/****************ARROW HEAD****************/

	//rotate arrow head 90 degrees about it's centre so it starts off by "facing" right
	m_arrowHead.setOrigin(m_arrowHead.getRadius(), m_arrowHead.getRadius());
	m_arrowHead.setRotation(90.0f);

	//position arrow head based on which way the arrow is pointing and the width of the arrow body, before rotation
	float width = m_arrowBody.getSize().y;
	if (m_arrowStart.x < m_arrowEnd.x) {
		m_arrowHead.setPosition(m_arrowEnd + sf::Vector2f(0.f, width / 2.0f - m_arrowHead.getRadius()));
	}
	else {
		m_arrowHead.setPosition(m_arrowEnd - sf::Vector2f(0.f, width / 2.0f - m_arrowHead.getRadius()));
	}

	//set origin of arrow head to be the same as the body so their rotations are uniform
	m_arrowHead.setOrigin(m_arrowBody.getOrigin());

	//match rotation about the same origin
	m_arrowHead.rotate(m_arrowBody.getRotation());

	/****************TEXT****************/

	m_text.setRotation(m_arrowBody.getRotation());

	m_text.setPosition(m_arrowStart + sf::Vector2f((m_arrowEnd.x - m_arrowStart.x) * 0.2f, (m_arrowEnd.y - m_arrowStart.y) * 0.2f));
}