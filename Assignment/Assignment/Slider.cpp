#include "Slider.h"

Slider::Slider() :
	m_background({150, 5}),
	m_handle(10.f),
	m_minimumValue(0.f),
	m_maximumValue(1.f),
	m_currentValue(0.5f),
	m_sliding(false)
{
	//set origins of components
	m_background.setOrigin(0.f, -10.f);
	m_handle.setOrigin(10.f, 0.f);

	//set background colours
	m_background.setFillColor({ 20, 20, 20 });
	m_handle.setFillColor({ 255, 140, 0 });
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_handle);
}

void Slider::setPosition(const sf::Vector2f& position) {
	m_background.setPosition(position);
	m_handle.setPosition(position + m_background.getSize() * 0.5f);
}

void Slider::setValue(float value) {
	m_currentValue = value;
	m_handle.setPosition(m_background.getPosition() + sf::Vector2f((value - m_minimumValue) / (m_maximumValue - m_minimumValue) * m_background.getSize().x, m_background.getSize().y * 0.5f));
}

float Slider::getValue() const {
	return m_currentValue;
}

bool Slider::click(int x, int y, sf::RenderWindow& window) {
	//convert the (x,y) coords to world coordinates (in case of window scaling)
	sf::Vector2f realCoords = window.mapPixelToCoords({ x, y });

	//if not in bounds, we don't care about this Slider
	if (!m_handle.getGlobalBounds().contains(realCoords)) {
		return false;
	}

	return true;
}

bool Slider::handleEvents(const sf::Event& event, sf::RenderWindow& window) {
	if (m_sliding) {
		if (event.type == sf::Event::MouseButtonReleased) {
			m_sliding = false;
			return true;
		}
		else if (event.type == sf::Event::MouseMoved) {
			//convert the (x,y) coords to world coordinates (in case of window scaling)
			float mouseX = window.mapPixelToCoords({ event.mouseMove.x, 0 }).x;

			//if too far to the right, set to the maximum X value allowed
			if (mouseX > m_background.getPosition().x + m_background.getSize().x) {
				m_handle.setPosition(m_background.getPosition().x + m_background.getSize().x, m_background.getPosition().y + m_background.getSize().y * 0.5f);
			}

			//if too far left, set to the minimum X value allowed
			else if (mouseX < m_background.getPosition().x) {
				m_handle.setPosition(m_background.getPosition().x, m_background.getPosition().y + m_background.getSize().y * 0.5f);
			}
			else {
				m_handle.setPosition({ mouseX, m_background.getPosition().y + m_background.getSize().y * 0.5f });
			}

			calculateValue();
		}
	}
	else {//Left click event
		if (event.mouseButton.button == sf::Mouse::Left) {
			m_sliding = click(event.mouseButton.x, event.mouseButton.y, window);
		}
	}

	return false;
}

void Slider::calculateValue() {
	float distance = m_background.getSize().x;
	float progress = m_handle.getPosition().x - m_background.getPosition().x;

	m_currentValue = progress / distance * (m_maximumValue - m_minimumValue);
}