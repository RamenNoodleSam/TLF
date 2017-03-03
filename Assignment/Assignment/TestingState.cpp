#include <sstream>
#include <iomanip>
#include "TestingState.h"
#include "ChangeStateCommand.h"
#include "GlobalAssetPool.h"
#include "NeuralNetwork.h"
#include "TestCommand.h"

TestingState::TestingState(StateManager* pStateManager) :
	State(pStateManager)
{
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pNeuralNetwork->setLinkToTestingState(this);

	Button button1;
	button1.setPosition({ 0, 0 });
	button1.setSize({ 267, 40 });
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
	button3.setBackgroundColour({ 255, 140, 0 });
	button3.setTextColour({ 20, 20, 20 });
	button3.setString({ "Network Testing" });
	button3.setCommand(new ChangeState(m_pStateManager, e_Testing));
	m_buttons.push_back(button3);

	Button button4;
	button4.setPosition({ 20, 460 });
	button4.setSize({ 120, 40.f });
	button2.setPosition({ 267, 0 });
	button2.setSize({ 267, 40.f });
	button4.setString({ "Test Network" });
	button4.setCommand(new TestCommand);
	m_buttons.push_back(button4);

	createNetworkStructure();
}

TestingState::~TestingState() {

}

void TestingState::handleEvents(const sf::Event& event, sf::RenderWindow& window) {
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
}

void TestingState::update() {

}

void TestingState::draw(sf::RenderWindow& window) {
	for (auto& iter : m_buttons) {
		iter.draw(window);
	}

	for (auto& iter : m_connections) {
		iter.drawArrow(window);
	}

	for (auto& iter : m_connections) {
		iter.drawText(window);
	}

	for (auto& iter : m_layers) {
		iter.draw(window);
	}

	for (auto& iter : m_text) {
		window.draw(iter);
	}
}

void TestingState::setTestOutputs(const std::vector<sf::String>& outputs) {
	m_text.clear();

	for (size_t i = 0; i < outputs.size(); ++i) {
		sf::Text text;
		text.setFont(GlobalAssetPool::getInstance()->m_font);
		text.setString(outputs[i]);
		text.setCharacterSize(16);
		text.setStyle(text.Bold);
		text.setFillColor({ 255, 140, 0 });
		text.setPosition({ 160, 460 + 20 * (float)i });
		m_text.push_back(text);
	}
}

void TestingState::createNetworkStructure() {
	std::vector<unsigned int> layerConfiguration = m_pNeuralNetwork->getNeuronsInLayers();
	std::vector<unsigned int> biasInLayers = m_pNeuralNetwork->getBiasInLayers();

	m_layers.clear();

	float layerSpacing = 800.f / layerConfiguration.size();

	//create layers and add neurons to them
	for (unsigned int layer = 0; layer < layerConfiguration.size(); ++layer) {
		//create a layer
		NetworkLayer networkLayer;
		networkLayer.setPosition({ layerSpacing * layer + layerSpacing * 0.5f, 60.f } );
		m_layers.push_back(networkLayer);

		for (unsigned int neuron = 0; neuron < layerConfiguration[layer]; ++neuron) {
			sf::String stringValue("");
			std::ostringstream oss;
			if (layer == 0) {
				oss << std::setprecision(2) << std::fixed << m_pNeuralNetwork->getTrainingData().get_input()[neuron][0];
				stringValue = oss.str();
			}
			else if (layer == layerConfiguration.size() - 1) {
				oss << std::setprecision(2) << std::fixed << m_pNeuralNetwork->getTrainingData().get_output()[neuron][0];
				stringValue = oss.str();
			}
			m_layers[layer].addNeuron(stringValue, false);
		}
	}

	//add biases to layers if any
	for (unsigned int layer = 0; layer < biasInLayers.size(); ++layer) {

		//for every bias in that layer
		for (unsigned int y = 0; y < biasInLayers[layer]; ++y) {
			std::ostringstream oss; 
			oss << std::setprecision(2) << std::fixed << 1.0f;
			m_layers[layer].addNeuron(oss.str(), true);
		}
	}

	std::vector<FANN::connection> connections = m_pNeuralNetwork->getConnections();
	m_connections.clear();

	unsigned int startingID = 0;
	for (unsigned int i = 0; i < m_layers.size(); ++i) {
		startingID = m_layers[i].setIDs(startingID);
	}

	for (const auto& iter : connections) {
		Neuron* pFromNeuron = nullptr;
		Neuron* pToNeuron = nullptr;

		for (unsigned int i = 0; i < m_layers.size(); ++i) {
			if (pFromNeuron == nullptr) 
				pFromNeuron = m_layers[i].getNeuronWithID(iter.from_neuron);
			if (pToNeuron == nullptr)
				pToNeuron = m_layers[i].getNeuronWithID(iter.to_neuron);
		}

		Arrow arrow(pFromNeuron->getRightPoint(), pToNeuron->getLeftPoint(), 3.f);

		std::ostringstream oss;
		oss << std::setprecision(3) << std::fixed << iter.weight;
		arrow.setString(oss.str());
		if (fann_abs(iter.weight) > 2.0f)
			arrow.setColour({ 255, 140, 0 });
		else
			arrow.setColour({ 80, 80, 80 });
		m_connections.push_back(arrow);
	}
}