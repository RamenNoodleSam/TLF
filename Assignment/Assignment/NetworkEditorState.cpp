#include "NetworkEditorState.h"
#include "ChangeStateCommand.h"
#include "LoadNetworkCommand.h"
#include "SaveNetworkCommand.h"
#include "AddLayerCommand.h"
#include "ResetLayersCommand.h"
#include "ApplyStructureChangesCommand.h"
#include "GlobalAssetPool.h"
#include "NeuralNetwork.h"

NetworkEditorState::NetworkEditorState(StateManager* pStateManager) :
	State(pStateManager)
{
	m_pNeuralNetwork = NeuralNetwork::getInstance();

	//initialise all graphical components of the state

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
	text1.setPosition({ 20, 410 });
	m_text.push_back(text1);

	sf::Text text2;
	text2.setFont(GlobalAssetPool::getInstance()->m_font);
	text2.setString("File name: ");
	text2.setCharacterSize(16);
	text2.setStyle(text2.Bold);
	text2.setFillColor({ 255, 140, 0 });
	text2.setPosition({ 20, 450 });
	m_text.push_back(text2);

	m_networkFile.setPosition({ 160, 450 });

	Button button4;
	button4.setPosition({ 340, 445 });
	button4.setSize({ 60, 30 });
	button4.setString({ "Load" });
	button4.setCommand(new LoadNetworkCommand(&m_networkFile));
	m_buttons.push_back(button4);

	Button button5;
	button5.setPosition({ 420, 445 });
	button5.setSize({ 60, 30 });
	button5.setString({ "Save" });
	button5.setCommand(new SaveNetworkCommand(&m_networkFile));
	m_buttons.push_back(button5);

	sf::Text text3;
	text3.setFont(GlobalAssetPool::getInstance()->m_font);
	text3.setString("Number of neurons: ");
	text3.setCharacterSize(16);
	text3.setStyle(text3.Bold);
	text3.setFillColor({ 255, 140, 0 });
	text3.setPosition({ 20, 60 });
	m_text.push_back(text3);

	m_numberOfNeurons.setPosition({ 220, 60 });

	Button button6;
	button6.setPosition({ 20, 100 });
	button6.setSize({ 120, 30 });
	button6.setString({ "Add Layer" });
	button6.setCommand(new AddLayerCommand(&m_layers, &m_numberOfNeurons));
	m_buttons.push_back(button6);

	Button button7;
	button7.setPosition({ 20, 155 });
	button7.setSize({ 150, 30 });
	button7.setString({ "Reset Layers" });
	button7.setCommand(new ResetLayersCommand(&m_layers));
	m_buttons.push_back(button7);

	Button button8;
	button8.setPosition({ 20, 210 });
	button8.setSize({ 150, 30 });
	button8.setString({ "Apply Changes" });
	button8.setCommand(new ApplyStructureChangesCommand(&m_layers));
	m_buttons.push_back(button8);
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

	//handle events for the network file TextField
	if (m_networkFile.handleEvents(event, window)) {
		m_pNeuralNetwork->setNetworkFile(m_networkFile.getString());
	}


	//handle events for the number of neurons TextField
	m_numberOfNeurons.handleEvents(event, window);
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
	m_numberOfNeurons.draw(window);
}