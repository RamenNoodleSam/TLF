#ifndef TEXTFIELD_H
#define TEXTFIELD_H

/* Filename: TextField.h
 * Description: Encapsulates the assets and functionality of a text field component,
 *				allowing the user to click the box, type in text using the keyboard and
 *				submit the "finished" string for whatever purpose the text field has.
 */

#include <SFML/Graphics.hpp>

class TextField {
public:
	TextField();

	void draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setString(const sf::String& textString);

	sf::String getString() const;

	bool click(int x, int y);

	void handleEvents(const sf::Event& event);


private:
	sf::RectangleShape	m_background;
	sf::Text			m_text;

	bool				m_hasFocus;

	static TextField*	m_pFocussed;
};

#endif