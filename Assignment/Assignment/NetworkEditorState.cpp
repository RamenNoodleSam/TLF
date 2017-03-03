#include "NetworkEditorState.h"
#include "ChangeStateCommand.h"
#include "LoadNetworkCommand.h"
#include "SaveNetworkCommand.h"
#include "GlobalAssetPool.h"
#include "NeuralNetwork.h"

NetworkEditorState::NetworkEditorState(StateManager* pStateManager) :
	State(pStateManager)
{
	m_pNeuralNetwork = NeuralNetwork::getInstance();

	Button button1;
	button1.setPosition({ 0, 0 });
	button1.setSize({ 267, 40 });
	button1.setBackgroundColour({ 255, 140, 0 });
	button1.setTextColour({ 20, 20, 20 });
	button1.setString({ "Network Editor" });
	button1.setCommand(new ChangeState(m_pStateManager, e_NetworkEditor));
	m_buttons.push_back(button1);

	Button button2;
	button2.setPosition({ 267, 0 });
	button2.setSize({ 267, 40.f });
	button2.setString({ "Network Training" });
	button2.setCommand(new ChangeState(m_pStateManager, e_Training));
	m_buttons.push_back(button2);

	Button button3;
	button3.setPosition({ 534, 0 });
	button3.setSize({ 267, 40.f });
	button3.setString({ "Network Testing" });
	button3.setCommand(new ChangeState(m_pStateManager, e_Testing));
	m_buttons.push_back(button3);

	sf::Text text1;
	text1.setFont(GlobalAssetPool::getInstance()->m_font);
	text1.setString("Load / Save Neural Network");
	text1.setCharacterSize(16);
	text1.setStyle(text1.Bold);
	text1.setFillColor({ 255, 140, 0 });
	text1.setPosition({ 20, 60 });
	m_text.push_back(text1);

	sf::Text text2;
	text2.setFont(GlobalAssetPool::getInstance()->m_font);
	text2.setString("File name: ");
	text2.setCharacterSize(16);
	text2.setStyle(text2.Bold);
	text2.setFillColor({ 255, 140, 0 });
	text2.setPosition({ 20, 100 });
	m_text.push_back(text2);

	m_networkFile.setPosition({ 160, 100 });

	Button button4;
	button4.setPosition({ 340, 95 });
	button4.setSize({ 60, 30 });
	button4.setString({ "Load" });
	button4.setCommand(new LoadNetworkCommand);
	m_buttons.push_back(button4);

	Button button5;
	button5.setPosition({ 420, 95 });
	button5.setSize({ 60, 30 });
	button5.setString({ "Save" });
	button5.setCommand(new SaveNetworkCommand);
	m_buttons.push_back(button5);

	Button button6;
	button6.setPosition({ 420, 150 });
	button6.setSize({ 20, 20 });
	button6.setString({ "+" });
	button6.setCommand(new ChangeState(m_pStateManager, e_Testing));
	m_buttons.push_back(button6);

	Button button7;
	button7.setPosition({ 395, 150 });
	button7.setSize({ 20, 20 });
	button7.setString({ "-" });
	button7.setCommand(new ChangeState(m_pStateManager, e_Testing));
	m_buttons.push_back(button7);
}

NetworkEditorState::~NetworkEditorState() {

}

void NetworkEditorState::handleEvents(const sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {

		//Left click event
		if (event.mouseButton.button == sf::Mouse::Left) {
			//checking for bounds stops as soon as one returns true
			for (auto& iter : m_buttons) {
				if (iter.click(event.mouseButton.x, event.mouseButton.y, window))
					break;
			}
		}
	}

	if (m_networkFile.handleEvents(event, window)) {
		m_pNeuralNetwork->setNetworkFile(m_networkFile.getString());
	}
}

void NetworkEditorState::update() {

}

void NetworkEditorState::draw(sf::RenderWindow& window) {
	for (auto& iter : m_buttons) {
		iter.draw(window);
	}

	for (auto& iter : m_text){
		window.draw(iter);
	}

	m_networkFile.draw(window);
}