#include "TextField.h"
#include "GlobalAssetPool.h"

TextField* TextField::m_pFocussed = nullptr;
const sf::Uint32 BACKSPACE = 8;
const sf::Uint32 RETURN = 13;

TextField::TextField() :
	m_background({150, 30}),
	m_hasFocus(false)
{
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString("Enter text...");
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color(128, 128, 128));

	m_background.setFillColor(sf::Color::White);
	m_background.setOutlineColor(sf::Color::Red);
	m_background.setOutlineThickness(2.0f);
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

bool TextField::click(int x, int y) {
	//if not in bounds, we don't care about this TextField
	if (!m_background.getGlobalBounds().contains(x, y)) {
		return false;
	}

	//handle defocus of other TextField
	if (m_pFocussed != nullptr) {
		if (m_pFocussed->getString().isEmpty()) {
			m_pFocussed->setString("Enter text...");
		}
	}

	//set the focus to this TextField
	m_pFocussed = this;
	if (m_text.getString() == "Enter text...") {
		m_text.setString("");
	}
	return true;
}

void TextField::handleEvents(const sf::Event& event) {
	if (m_pFocussed == this) {
		//Text entered event
		if (event.type == sf::Event::TextEntered) {
			//0-9 are accepted characters in the string
			if (event.text.unicode >= '1' && event.text.unicode <= '9') {
				m_text.setString(m_text.getString() + static_cast<char>(event.text.unicode));
			} 
			//check for backspace to delete last character
			else if (event.text.unicode == BACKSPACE) {
				m_text.setString(m_text.getString().substring(0, m_text.getString().getSize() - 1));
			}
			//check for return to submit string
			else if (event.text.unicode == RETURN) {
				std::cout << "String entered: " << m_text.getString().toAnsiString() << std::endl;
			}
		}
	}
	else {
		//Left click event
		if (event.mouseButton.button == sf::Mouse::Left) {
			click(event.mouseButton.x, event.mouseButton.y);
		}
	}
}