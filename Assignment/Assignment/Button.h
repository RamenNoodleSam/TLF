#ifndef BUTTON_H
#define BUTTON_H

/* Filename: Button.h
 * Description: Encapsulates the assets and functionality of a clickable button component,
 *				and accepts a Command to invoke when clicked.
 */

#include <SFML/Graphics.hpp>
#include "Command.h"

class Button {
public:
	Button();
	Button(Command* pCommandOnClick, const sf::Vector2f& position = { 0.f, 0.f }, const sf::Vector2f& size = { 200.f, 200.f }, const sf::String& textString = "");
	Button(const Button& rhs);
	Button(Button&& rhs);
	Button& operator=(const Button& rhs);
	Button& operator=(Button&& rhs);
	~Button();

	//draw assets to provided RenderWindow
	void draw(sf::RenderWindow& window);

	//mutators
	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setString(const sf::String& textString);
	void setCommand(Command* pCommandOnClick);
	void setBackgroundColour(const sf::Color& colour);
	void setTextColour(const sf::Color& colour);

	//returns true if coordinates are in Button bounds,
	//also invokes the linked Command
	bool click(int x, int y, sf::RenderWindow& window);

private:
	sf::RectangleShape	m_background;
	sf::Text			m_text;
	Command*			m_pCommandOnClick;

	//repositions the text on the Button based on size of the button and text
	void repositionText();
};

#endif