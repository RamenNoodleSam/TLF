#ifndef INTROSTATE_H
#define INTROSTATE_H

/* Filename: IntroState.h
 * Description: The concrete State the user first sees.				
 */


#include "State.h"
#include "Arrow.h"
#include "Button.h"
#include "TextField.h"

class IntroState : public State {
public:
	virtual void init();	
	virtual void cleanup();

	virtual void handleEvents(const sf::Event& event);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

private:
	std::vector<Button> m_buttons;

	Arrow m_arrow1;

	TextField m_textField1;
	TextField m_textField2;
};

#endif