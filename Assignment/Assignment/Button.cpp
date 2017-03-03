#include <iostream>
#include "Button.h"
#include "GlobalAssetPool.h"

Button::Button() :
	m_background({ 200, 200 }),
	m_pCommandOnClick(nullptr)
{
	//initialise text
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString("<DEFAULT TEXT>");
	m_text.setCharacterSize(16);
	m_text.setStyle(m_text.Bold);
	m_text.setFillColor({ 255, 140, 0 });

	//initialise background of button
	m_background.setFillColor({ 20, 20, 20 });
}

Button::Button(Command* pCommandOnClick, const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& textString) :
	m_pCommandOnClick(pCommandOnClick)
{
	//initialise text
	m_text.setFont(GlobalAssetPool::getInstance()->m_font);
	m_text.setString(textString);
	m_text.setCharacterSize(24);
	m_text.setStyle(m_text.Bold);
	m_text.setFillColor({ 255, 140, 0 });

	//initialise background of button
	m_background.setSize(size);
	m_background.setPosition(position);
	m_background.setFillColor({ 20, 20, 20 });

	//reposition the text
	repositionText();
}

//copy constructor
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

//move constructor
Button::Button(Button&& rhs) :
	m_background(rhs.m_background),
	m_pCommandOnClick(rhs.m_pCommandOnClick),
	m_text(rhs.m_text)
{
	rhs.m_pCommandOnClick = nullptr;
}

//copy assignment operator
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

//move assignment operator
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

void Button::setBackgroundColour(const sf::Color& colour) {
	m_background.setFillColor(colour);
}

void Button::setTextColour(const sf::Color& colour) {
	m_text.setFillColor(colour);
}

bool Button::click(int x, int y, sf::RenderWindow& window) {
	//convert the (x,y) coords to world coordinates (in case of window scaling)
	sf::Vector2f realCoords = window.mapPixelToCoords({ x, y });

	//if not in bounds, we don't care about this Button
	if (!m_background.getGlobalBounds().contains(realCoords)) {
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
	//set the origin based on text boundaries
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
					 textRect.top + textRect.height / 2.0f);

	//set position based on text boundaries AND Button boundaries
	m_text.setPosition(m_background.getPosition() +
					   sf::Vector2f(m_background.getSize().x / 2.0f, m_background.getSize().y / 2.0f));
}