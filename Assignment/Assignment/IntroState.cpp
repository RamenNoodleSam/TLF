#include "IntroState.h"

void IntroState::init() {

	Button button1;
	button1.setPosition({ 100, 100 });
	button1.setSize({ 100, 100 });
	button1.setString({ "Button 1" });
	button1.setCommand(new ChangeState("Left click on Button 1"));
	m_buttons.push_back(button1);

	Button button2;
	button2.setPosition({ 300, 100 });
	button2.setSize({ 100, 100 });
	button2.setString({ "Button 2" });
	button2.setCommand(new ChangeState("Left click on Button 2"));
	m_buttons.push_back(button2);

	Button button3;
	button3.setPosition({ 500, 100 });
	button3.setSize({ 100, 100 });
	button3.setString({ "Button 3" });
	//button3.setCommand(new ChangeState("Left click on Button 3"));
	m_buttons.push_back(button3);
	
	m_textField1.setPosition({ 450, 400 });
	m_textField2.setPosition({ 450, 500 });
};

void IntroState::cleanup() {

}

void IntroState::handleEvents(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {

		//Left click event
		if (event.mouseButton.button == sf::Mouse::Left) {
			//checking for bounds stops as soon as one returns true
			for (auto& iter : m_buttons) {
				if (iter.click(event.mouseButton.x, event.mouseButton.y))
					break;
			}

		}
	}

	m_textField1.handleEvents(event);
	m_textField2.handleEvents(event);
}

void IntroState::update() {

}

void IntroState::draw(sf::RenderWindow& window) {
	m_arrow1.draw(window);
	for (auto& iter : m_buttons) {
		iter.draw(window);
	}
	m_textField1.draw(window);
	m_textField2.draw(window);
}