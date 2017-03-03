#include "TextField.h"
#include "GlobalAssetPool.h"

TextField* TextField::m_pFocussed = nullptr;
const sf::Uint32 BACKSPACE = 8;
const sf::Uint32 RETURN = 13;

TextField::TextField() :
	m_background({ 150, 20 }),
	m_hasFocus(false)
{
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString("Enter text...");
	m_text.setCharacterSize(16);
	m_text.setStyle(m_text.Bold);
	m_text.setFillColor({ 255, 140, 0 });

	m_background.setFillColor({ 20, 20, 20 });
}

void TextField::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_text);
}

void TextField::setPosition(const sf::Vector2f& position) {
	m_background.setPosition(position);
	m_text.setPosition(position);
}

void TextField::setSize(const sf::Vector2f& size) {
	m_background.setSize(size);
}

void TextField::setString(const sf::String& textString) {
	m_text.setString(textString);
}

sf::String TextField::getString() const {
	return m_text.getString();
}

bool TextField::click(int x, int y, sf::RenderWindow& window) {
	//convert the (x,y) coords to world coordinates (in case of window scaling)
	sf::Vector2f realCoords = window.mapPixelToCoords({ x, y });

	//if not in bounds, we don't care about this TextField
	if (!m_background.getGlobalBounds().contains(realCoords)) {
		return false;
	}

	//handle defocus of other TextField
	if (m_pFocussed != nullptr) {
		m_pFocussed->defocus();
	}

	//set the focus to this TextField
	m_pFocussed = this;
	focus();

	return true;
}

void TextField::focus() {
	if (m_text.getString() == "Enter text...") {
		m_text.setString("");
	}

	m_text.setFillColor({ 20, 20, 20 });

	m_background.setFillColor({ 255, 140, 0 });
}

void TextField::defocus() {
	if (m_text.getString().isEmpty()) {
		m_text.setString("Enter text...");
	}

	m_pFocussed = nullptr;

	m_text.setFillColor({ 255, 140, 0 });

	m_background.setFillColor({ 20, 20, 20 });
}

bool TextField::handleEvents(const sf::Event& event, sf::RenderWindow& window) {
	if (m_pFocussed == this) {
		//Text entered event
		if (event.type == sf::Event::TextEntered) {
			//alphanumeric characters accepted, as well as '.' for decimal values
			if (event.text.unicode >= '0' && event.text.unicode <= '9' || 
				event.text.unicode == '.'							   ||
				event.text.unicode >= 'a' && event.text.unicode <= 'z' ||
				event.text.unicode >= 'A' && event.text.unicode <= 'Z') 
			{
				m_text.setString(m_text.getString() + static_cast<char>(event.text.unicode));
			}
			//check for backspace to delete last character
			else if (event.text.unicode == BACKSPACE) {
				m_text.setString(m_text.getString().substring(0, m_text.getString().getSize() - 1));
			}
			//check for return to submit string
			else if (event.text.unicode == RETURN) {
				defocus();
				return true;
			}
		}
	}
	else {
		//Left click event
		if (event.mouseButton.button == sf::Mouse::Left) {
			click(event.mouseButton.x, event.mouseButton.y, window);
		}
	}

	return false;
}