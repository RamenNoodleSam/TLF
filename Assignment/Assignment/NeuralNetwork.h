#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "floatfann.h"
#include "fann_cpp.h"

//prototypes
class TrainingState;
class TestingState;

class NeuralNetwork {
public:
	~NeuralNetwork();

	void addLayer(unsigned int numNeurons);
	void resetLayers();
	bool createNetwork();

	void setMaxEpochs(unsigned int maxEpochs);
	void setReportFrequency(unsigned int frequency);
	void setDesiredError(float desiredError);
	void setLearningRate(float learningRate);
	void loadTrainingFile(const sf::String&); 
	void setNetworkFile(const sf::String&);
	void setLinkToTrainingState(TrainingState* pTrainingState);
	void setLinkToTestingState(TestingState* pTestingState);

	unsigned int getMaxEpochs() const;
	unsigned int getReportFrequency() const;
	float getDesiredError() const;
	float getLearningRate() const;

	const std::vector<unsigned int>& getNeuronsInLayers() const;
	std::vector<unsigned int> getBiasInLayers();
	std::vector<FANN::connection> getConnections();
	FANN::training_data& getTrainingData();

	void train();
	void test();
	void resetWeights();

	void load();
	void save();

	friend int training_callback(FANN::neural_net &net, FANN::training_data &train,
								 unsigned int max_epochs, unsigned int epochs_between_reports,
								 float desired_error, unsigned int epochs, void *user_data);
private:
	FANN::neural_net			m_network;

	std::vector<unsigned int>	m_neuronsInLayers;
	unsigned int*				m_pBiasInLayers;
	FANN::connection*			m_pConnections;

	FANN::training_data			m_trainingData;
	unsigned int				m_maxEpochs;
	unsigned int				m_epochsBetweenReports;
	float						m_desiredError;
	float						m_learningRate;
	bool						m_trainingFileLoaded;
	sf::String					m_networkFile;

	TrainingState*				m_pTrainingState;
	TestingState*				m_pTestingState;

	//***SINGLETON IMPLEMENTATION***//
public:
	static NeuralNetwork* getInstance();
private:
	NeuralNetwork();
	NeuralNetwork(const NeuralNetwork&) = delete;
	NeuralNetwork(NeuralNetwork&&) = delete;

	static NeuralNetwork*		m_pSelf;
	//***SINGLETON IMPLEMENTATION***//
};

#endif