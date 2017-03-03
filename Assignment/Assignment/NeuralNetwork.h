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

	//adds a new layer to the network, with numNeurons neurons in the layer
	void addLayer(unsigned int numNeurons);

	//removes all layers from the network
	void resetLayers();

	//creates the network using the provided information for layers and neurons
	bool createNetwork();

	//attempts to load training data from file with the name provided
	void loadTrainingFile(const sf::String& fileName);

	//applies layers provided to structure instead of adding them individually
	void applyStructureToNetwork(const std::vector<unsigned int>& layers);

	void setMaxEpochs(unsigned int maxEpochs);
	void setReportFrequency(unsigned int frequency);
	void setDesiredError(float desiredError);
	void setLearningRate(float learningRate);
	void setNetworkFile(const sf::String& fileName);
	void setLinkToTrainingState(TrainingState* pTrainingState);
	void setLinkToTestingState(TestingState* pTestingState);

	//accessors
	unsigned int getMaxEpochs() const;
	unsigned int getReportFrequency() const;
	float getDesiredError() const;
	float getLearningRate() const;
	const sf::String& getNetworkFile() const; 
	const sf::String& getTrainingFile() const;

	const std::vector<unsigned int>& getNeuronsInLayers() const;
	std::vector<unsigned int> getBiasInLayers();
	std::vector<FANN::connection> getConnections();
	FANN::training_data* getTrainingData();

	void train();
	void test();
	void resetWeights();

	//save/load the network to/from file at "Data/[m_networkFile]"
	void load();
	void save();

	//callback for reports while training the network, declared as a friend function of NeuralNetwork
	//defined in NeuralNetwork.cpp
	friend int training_callback(FANN::neural_net& network, FANN::training_data& trainingData,
								 unsigned int maxEpochs, unsigned int epochsBetweenReports,
								 float desiredError, unsigned int currentEpoch, void *userData);

private:
	//the artificial neural network provided by the FANN library
	FANN::neural_net			m_network;

	//network information
	std::vector<unsigned int>	m_neuronsInLayers;
	unsigned int*				m_pBiasInLayers;
	FANN::connection*			m_pConnections;
	sf::String					m_networkFile;

	//training information
	FANN::training_data			m_trainingData;
	unsigned int				m_maxEpochs;
	unsigned int				m_epochsBetweenReports;
	float						m_desiredError;
	float						m_learningRate;
	bool						m_trainingFileLoaded;
	sf::String					m_trainingFile;

	//links to states that need information from the network
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