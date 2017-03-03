#include <sstream>
#include <iomanip>
#include "TrainingState.h"
#include "ChangeStateCommand.h"
#include "TrainCommand.h"
#include "GlobalAssetPool.h"
#include "NeuralNetwork.h"

TrainingState::TrainingState(StateManager* pStateManager) :
	State(pStateManager)
{
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pNeuralNetwork->setLinkToTrainingState(this);

	//initialise the graphical components of the screen

	Button button1;
	button1.setPosition({ 0, 0 });
	button1.setSize({ 267, 40 });
	button1.setString({ "Network Editor" });
	button1.setCommand(new ChangeState(m_pStateManager, e_NetworkEditor));
	m_buttons.push_back(button1);

	Button button2;
	button2.setPosition({ 267, 0 });
	button2.setSize({ 267, 40.f });
	button2.setBackgroundColour({ 255, 140, 0 });
	button2.setTextColour({ 20, 20, 20 });
	button2.setString({ "Network Training" });
	button2.setCommand(new ChangeState(m_pStateManager, e_Training));
	m_buttons.push_back(button2);

	Button button3;
	button3.setPosition({ 534, 0 });
	button3.setSize({ 267, 40.f });
	button3.setString({ "Network Testing" });
	button3.setCommand(new ChangeState(m_pStateManager, e_Testing));
	m_buttons.push_back(button3);

	Button button4;
	button4.setPosition({ 20, 460 });
	button4.setSize({ 60, 30 });
	button4.setString({ "Train" });
	button4.setCommand(new TrainCommand(&m_graph));
	m_buttons.push_back(button4);

	sf::Text text1;
	text1.setFont(GlobalAssetPool::getInstance()->m_font);
	text1.setString("Max Epochs");
	text1.setCharacterSize(16);
	text1.setStyle(text1.Bold);
	text1.setFillColor({ 255, 140, 0 });
	text1.setPosition({ 20, 60 });
	m_text.push_back(text1);

	sf::Text text4;
	text4.setFont(GlobalAssetPool::getInstance()->m_font);
	text4.setString("Report Freq.");
	text4.setCharacterSize(16);
	text4.setStyle(text4.Bold);
	text4.setFillColor({ 255, 140, 0 });
	text4.setPosition({ 20, 140 });
	m_text.push_back(text4);

	sf::Text text2;
	text2.setFont(GlobalAssetPool::getInstance()->m_font);
	text2.setString("Desired Error");
	text2.setCharacterSize(16);
	text2.setStyle(text2.Bold);
	text2.setFillColor({ 255, 140, 0 });
	text2.setPosition({ 20, 220 });
	m_text.push_back(text2);

	sf::Text text3;
	text3.setFont(GlobalAssetPool::getInstance()->m_font);
	text3.setString("Training File");
	text3.setCharacterSize(16);
	text3.setStyle(text3.Bold);
	text3.setFillColor({ 255, 140, 0 });
	text3.setPosition({ 20, 300 });
	m_text.push_back(text3);

	m_meanSquaredErrorText.setFont(GlobalAssetPool::getInstance()->m_font);
	m_meanSquaredErrorText.setString("Mean Square Error calculated after training.");
	m_meanSquaredErrorText.setCharacterSize(16);
	m_meanSquaredErrorText.setStyle(m_meanSquaredErrorText.Bold);
	m_meanSquaredErrorText.setFillColor({ 255, 140, 0 });
	m_meanSquaredErrorText.setPosition({ 20, 540 });

	m_maxEpochs.setPosition({ 150, 60});
	m_maxEpochs.setString(std::to_string(m_pNeuralNetwork->getMaxEpochs()));
	m_reportFrequency.setPosition({ 150, 140 });
	m_reportFrequency.setString(std::to_string(m_pNeuralNetwork->getReportFrequency()));
	m_desiredError.setPosition({ 150, 220});
	m_desiredError.setString(std::to_string(m_pNeuralNetwork->getDesiredError()));
	m_trainingFile.setPosition({ 150, 300 }); 
	m_learningRate.setPosition({ 200, 380 });
	m_learningRate.setValue(m_pNeuralNetwork->getLearningRate());

	m_learningRateText.setFont(GlobalAssetPool::getInstance()->m_font);
	m_learningRateText.setString("Learning rate: " + std::to_string(m_learningRate.getValue()));
	m_learningRateText.setCharacterSize(16);
	m_learningRateText.setStyle(m_learningRateText.Bold);
	m_learningRateText.setFillColor({ 255, 140, 0 });
	m_learningRateText.setPosition({ 20, 380 });

	m_graph.setPosition({ 380, 60 });
	m_graph.setLabelX("Epochs");
	m_graph.setLabelY("Mean Square Error");
}

TrainingState::~TrainingState() {

}

void TrainingState::handleEvents(const sf::Event& event, sf::RenderWindow& window) {
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

	//handle events for the TextField representing max epochs
	if (m_maxEpochs.handleEvents(event, window)) {
		m_pNeuralNetwork->setMaxEpochs(std::stoi(m_maxEpochs.getString().toAnsiString()));
	}

	//handle events for the TextField representing report frequency
	if (m_reportFrequency.handleEvents(event, window)) {
		m_pNeuralNetwork->setReportFrequency(std::stoi(m_reportFrequency.getString().toAnsiString()));
	}

	//handle events for the TextField representing desired error
	if (m_desiredError.handleEvents(event, window)) {
		m_pNeuralNetwork->setDesiredError(std::stof(m_desiredError.getString().toAnsiString()));
	}

	//handle events for the TextField representing training file name
	if (m_trainingFile.handleEvents(event, window)) {
		m_pNeuralNetwork->loadTrainingFile(m_trainingFile.getString());
	}

	//handle events for the TextField representing learning rate
	if (m_learningRate.handleEvents(event, window)) {
		m_pNeuralNetwork->setLearningRate(m_learningRate.getValue());
	}
}

void TrainingState::update() {
	//update the learning rate
	std::ostringstream oss;
	oss << std::setprecision(2) << std::fixed << m_learningRate.getValue();
	m_learningRateText.setString("Learning Rate: " + oss.str());
}

void TrainingState::draw(sf::RenderWindow& window) {
	for (auto& iter : m_buttons) {
		iter.draw(window);
	}

	for (auto& iter : m_text) {
		window.draw(iter);
	}

	m_maxEpochs.draw(window);
	m_reportFrequency.draw(window);
	m_desiredError.draw(window);
	m_trainingFile.draw(window);
	m_learningRate.draw(window);
	m_graph.draw(window);
	window.draw(m_learningRateText);
	window.draw(m_meanSquaredErrorText);
}

void TrainingState::setMeanSquaredError(const sf::String& MSE) {
	m_meanSquaredErrorText.setString(MSE);
}

void TrainingState::addPointToGraph(unsigned int epoch, float MSE) {
	m_graph.addPoint(sf::Vector2f((float)epoch, MSE));
}