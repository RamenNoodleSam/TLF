#include "Neuron.h"
#include "GlobalAssetPool.h"

Neuron::Neuron() :
	m_background(40.f)
{
	m_background.setOrigin({40.0f, 40.0f});

	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setCharacterSize(16);
	m_text.setFillColor({ 255, 140, 0 });
	m_text.setStyle(m_text.Bold);

	m_background.setFillColor({ 20, 20, 20 });
}

Neuron::Neuron(const sf::Vector2f& position, float radius, const sf::String& textString) :
	m_background(radius)
{
	m_background.setOrigin(radius, radius);
	m_background.setPosition(position);

	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString(textString);
	m_text.setCharacterSize(16);
	m_text.setFillColor({ 255, 140, 0 });
	m_text.setStyle(m_text.Bold);

	repositionText();

	m_background.setFillColor({20, 20, 20});
}

void Neuron::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_text);
}

void Neuron::setPosition(const sf::Vector2f& position) {
	m_background.setPosition(position);
	repositionText();
}

void Neuron::setRadius(float radius) {
	m_background.setRadius(radius);
	m_background.setOrigin(radius, radius);
}

void Neuron::setString(const sf::String& textString) {
	m_text.setString(textString);
	repositionText();
}

void Neuron::setID(unsigned int id) {
	m_id = id;
}

void Neuron::setIsBias(bool isBias) {
	if (isBias) {
		m_text.setFillColor({ 20, 20, 20 });
		m_background.setFillColor({ 255, 140, 0 } );
	}
	else {
		m_text.setFillColor({ 255, 140, 0 });
		m_background.setFillColor({ 20, 20, 20 });
	}
}

sf::Vector2f Neuron::getLeftPoint() const {
	return m_background.getPosition() - sf::Vector2f(m_background.getRadius(), 0.f);
}

sf::Vector2f Neuron::getRightPoint() const {
	return m_background.getPosition() + sf::Vector2f(m_background.getRadius(), 0.f);
}

unsigned int Neuron::getID() const {
	return m_id;
}

void Neuron::repositionText() {
	//set the origin based on text boundaries
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
					 textRect.top + textRect.height / 2.0f);

	//set position based on text boundaries AND Neuron position
	m_text.setPosition(m_background.getPosition());
}