#include <iostream>
#include "Button.h"
#include "GlobalAssetPool.h"

Button::Button() :
	m_background({200, 200}),
	m_pCommandOnClick(nullptr)
{
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString("<DEFAULT TEXT>");
	m_text.setCharacterSize(24);	

	m_background.setFillColor(sf::Color::Red);
}

Button::Button(Command* pCommandOnClick, const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& textString) :
	m_pCommandOnClick(pCommandOnClick)
{
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString(textString);
	m_text.setCharacterSize(24);	

	m_background.setSize(size);
	m_background.setPosition(position);
	m_background.setFillColor(sf::Color::Red);

	repositionText();
}

Button::Button(const Button& rhs) :
	m_background(rhs.m_background),
	m_text(rhs.m_text)
{
	if (rhs.m_pCommandOnClick == nullptr) {
		m_pCommandOnClick = nullptr;
	}
	else {
		m_pCommandOnClick = rhs.m_pCommandOnClick->clone();
	}
}

Button::Button(Button&& rhs) :
	m_background(rhs.m_background),
	m_pCommandOnClick(rhs.m_pCommandOnClick),
	m_text(rhs.m_text)
{
	rhs.m_pCommandOnClick = nullptr;
}

Button& Button::operator=(const Button& rhs) {
	if (&rhs != this) {
		m_background = rhs.m_background;
		m_text = rhs.m_text;

		if (rhs.m_pCommandOnClick == nullptr) {
			m_pCommandOnClick = nullptr;
		}
		else {
			m_pCommandOnClick = rhs.m_pCommandOnClick->clone();
		}
	}
	
	return *this;
}

Button& Button::operator=(Button&& rhs) {
	if (&rhs != this) {
		m_background = rhs.m_background;
		m_pCommandOnClick = rhs.m_pCommandOnClick;
		m_text = rhs.m_text;

		rhs.m_pCommandOnClick = nullptr;
	}

	return *this;
}

Button::~Button() {
	if (m_pCommandOnClick != nullptr) {
		delete m_pCommandOnClick;
	}
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(m_background);
	window.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& position) {
	m_background.setPosition(position);
	repositionText();
}

void Button::setSize(const sf::Vector2f& size) {
	m_background.setSize(size);
	repositionText();
}

void Button::setString(const sf::String& textString) {
	m_text.setString(textString);
	repositionText();
}

void Button::setCommand(Command* pCommandOnClick) {
	m_pCommandOnClick = pCommandOnClick;
}

bool Button::click(int x, int y) {
	//if not in bounds, we don't care about this Button
	if (!m_background.getGlobalBounds().contains(x, y)) {
		return false;
	}

	//if Button hasn't been assigned an action upon being clicked, we can't invoke it.
	//however we still return true because the mouse click was in the bounds of the Button
	if (m_pCommandOnClick == nullptr) {
		std::cout << "Button does not have an associated Command" << std::endl;
		return true;
	}

	//invoke linked Command
	(*m_pCommandOnClick)();
	return true;
}

void Button::repositionText() {
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
					 textRect.top + textRect.height / 2.0f);
	m_text.setPosition(m_background.getPosition() +
					   sf::Vector2f(m_background.getSize().x / 2.0f, m_background.getSize().y / 2.0f));
}