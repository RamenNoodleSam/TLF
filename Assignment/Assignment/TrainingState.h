#ifndef TRAININGSTATE_H
#define TRAININGSTATE_H

#include "State.h"
#include "Button.h"
#include "TextField.h"
#include "Slider.h"
#include "Graph.h"

//prototypes
class NeuralNetwork;
namespace FANN {
	class neural_net;
	class training_data;
}

class TrainingState : public State {
public:
	TrainingState(StateManager* pStateManager);
	~TrainingState();

	//overridden virtual methods
	virtual void handleEvents(const sf::Event& event, sf::RenderWindow& window);
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

	//mutators
	void setMeanSquaredError(const sf::String& MSE);
	void addPointToGraph(unsigned int epoch, float MSE);

private:
	//visual assets
	std::vector<Button>		m_buttons;
	std::vector<sf::Text>	m_text;

	TextField				m_maxEpochs;
	TextField				m_reportFrequency;
	TextField				m_desiredError;
	TextField				m_trainingFile;
	Slider					m_learningRate;
	sf::Text				m_learningRateText;
	sf::Text				m_meanSquaredErrorText;
	Graph					m_graph;

	//link to neural network
	NeuralNetwork*			m_pNeuralNetwork;
};

#endif