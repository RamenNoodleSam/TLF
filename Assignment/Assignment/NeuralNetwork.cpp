#include <iostream>
#include <sstream>
#include <iomanip>
#include "NeuralNetwork.h"
#include "TrainingState.h"
#include "TestingState.h"

NeuralNetwork* NeuralNetwork::m_pSelf = nullptr;

//training callback definition, declared as a friend in NeuralNetwork.h
int training_callback(FANN::neural_net& network, FANN::training_data& trainingData,
					  unsigned int maxEpochs, unsigned int epochsBetweenReports,
					  float desiredError, unsigned int currentEpoch, void *userData)
{
	float meanSquareError = network.get_MSE();

	//output to console
	std::cout << "Epoch " << currentEpoch << ". " << "Current Error: " << meanSquareError << std::endl;
	sf::String str("Mean Square Error: \n" + std::to_string(meanSquareError));
	str += " in " + std::to_string(currentEpoch);
	str += " epochs.";

	//pass relevant information back to the training state so user can see it on the GUI
	NeuralNetwork::getInstance()->m_pTrainingState->setMeanSquaredError(str);
	NeuralNetwork::getInstance()->m_pTrainingState->addPointToGraph(currentEpoch, meanSquareError);

	return 0;
}

NeuralNetwork::NeuralNetwork() :
	m_maxEpochs(300),
	m_desiredError(0.001f),
	m_epochsBetweenReports(1),
	m_learningRate(0.7f)
{

}

NeuralNetwork::~NeuralNetwork() {
	if (m_pBiasInLayers != nullptr) {
		delete[] m_pBiasInLayers;
	}

	if (m_pConnections != nullptr) {
		delete[] m_pConnections;
	}
}

void NeuralNetwork::addLayer(unsigned int numNeurons) {
	m_neuronsInLayers.push_back(numNeurons);
}

void NeuralNetwork::resetLayers() {
	m_neuronsInLayers.clear();
}

bool NeuralNetwork::createNetwork() {
	if (m_neuronsInLayers.size() == 0)
		return false;

	//attempt to create the neural network using information provided already
	if (m_network.create_standard_array(m_neuronsInLayers.size(), &m_neuronsInLayers[0])) {
		//get bias information
		m_pBiasInLayers = new unsigned int[m_network.get_num_layers()];
		m_network.get_bias_array(m_pBiasInLayers);

		//get connection information
		m_pConnections = new FANN::connection[m_network.get_total_connections()];
		m_network.get_connection_array(m_pConnections);

		//set learning rate
		m_network.set_learning_rate(m_learningRate);

		//set activation steepness
		m_network.set_activation_steepness_hidden(1.0);
		m_network.set_activation_steepness_output(1.0);

		//set activation function
		m_network.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
		m_network.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);

		//set callback for reports during training
		m_network.set_callback(training_callback, NULL);

		return true;
	}

	return false;
}

void NeuralNetwork::setMaxEpochs(unsigned int maxEpochs) {
	m_maxEpochs = maxEpochs;
}

void NeuralNetwork::setReportFrequency(unsigned int frequency) {
	m_epochsBetweenReports = frequency;
}

void NeuralNetwork::setDesiredError(float desiredError) {
	m_desiredError = desiredError;
}

void NeuralNetwork::setLearningRate(float learningRate) {
	m_learningRate = learningRate;
	m_network.set_learning_rate(m_learningRate);
}

void NeuralNetwork::loadTrainingFile(const sf::String& fileName) {
	//attempt to read data from file
	m_trainingFileLoaded = m_trainingData.read_train_from_file("Data/" + fileName);

	//if successful, initialise weights for the data
	if (m_trainingFileLoaded) {
		m_network.init_weights(m_trainingData);
		m_trainingFile = fileName;
		m_pTestingState->createNetworkStructure();
	}
}

void NeuralNetwork::applyStructureToNetwork(const std::vector<unsigned int>& layers) {
	m_neuronsInLayers = layers;

	createNetwork();

	m_pTestingState->createNetworkStructure();
}

void NeuralNetwork::setNetworkFile(const sf::String& fileName) {
	m_networkFile = fileName;
}

void NeuralNetwork::setLinkToTrainingState(TrainingState* pTrainingState) {
	m_pTrainingState = pTrainingState;
}

void NeuralNetwork::setLinkToTestingState(TestingState* pTestingState){
	m_pTestingState = pTestingState;
}

unsigned int NeuralNetwork::getMaxEpochs() const {
	return m_maxEpochs;
}

unsigned int NeuralNetwork::getReportFrequency() const {
	return m_epochsBetweenReports;
}

float NeuralNetwork::getDesiredError() const {
	return m_desiredError;
}

float NeuralNetwork::getLearningRate() const {
	return m_learningRate;
}

const sf::String& NeuralNetwork::getNetworkFile() const {
	return m_networkFile;
}

const sf::String& NeuralNetwork::getTrainingFile() const {
	return m_trainingFile;
}

const std::vector<unsigned int>& NeuralNetwork::getNeuronsInLayers() const {
	return m_neuronsInLayers;
}

std::vector<unsigned int> NeuralNetwork::getBiasInLayers() {
	return std::vector<unsigned int>(m_pBiasInLayers, m_pBiasInLayers + m_network.get_num_layers());
}

std::vector<FANN::connection> NeuralNetwork::getConnections() {
	return std::vector<FANN::connection>(m_pConnections, m_pConnections + m_network.get_total_connections());
}

FANN::training_data* NeuralNetwork::getTrainingData() {
	if (!m_trainingFileLoaded)
		return nullptr;
	return &m_trainingData;
}

void NeuralNetwork::train() {
	if (!m_trainingFileLoaded) {
		std::cout << "Cannot train because training data was not loaded correctly!" << std::endl;
		return;
	}

	//train the network
	m_network.train_on_data(m_trainingData, m_maxEpochs, m_epochsBetweenReports, m_desiredError);

	//get updated bias and connection information
	m_network.get_bias_array(m_pBiasInLayers);
	m_network.get_connection_array(m_pConnections);

	//create the network visuals in the testing state
	m_pTestingState->createNetworkStructure();
	m_pTestingState->setTestOutputs(std::vector<sf::String>());
}

void NeuralNetwork::test() {
	std::vector<sf::String> outputs;

	//for each set of training data in the file
	for (unsigned int i = 0; i < m_trainingData.length_train_data(); ++i) {

		//run the network on the input data
		fann_type result = *m_network.run(m_trainingData.get_input()[i]);

		//console output for ease of debugging
		std::cout << "Input: " << std::showpos << m_trainingData.get_input()[i][0] << ", " << m_trainingData.get_input()[i][1] << std::endl;
		std::cout << "Expected result: " << m_trainingData.get_output()[i][0] << std::endl;
		std::cout << "Difference: " << std::noshowpos << fann_abs(result - m_trainingData.get_output()[i][0]) << std::endl << std::endl;

		//pass the testing results to the testing state to be visualised
		std::ostringstream output;
		output << "Input: (" << std::showpos << m_trainingData.get_input()[i][0] << ", " << m_trainingData.get_input()[i][1] << ")   ";
		output << "Expected result: " << m_trainingData.get_output()[i][0] << "   ";
		output << "Difference: " << std::noshowpos << fann_abs(result - m_trainingData.get_output()[i][0]);
		outputs.push_back(output.str());
	}

	m_pTestingState->setTestOutputs(outputs);
}

void NeuralNetwork::resetWeights() {
	//reset the weights and the mean square error
	m_network.init_weights(m_trainingData);
	m_network.reset_MSE();
	m_pTrainingState->setMeanSquaredError("Mean Square Error reset.");
}

void NeuralNetwork::load() {
	//load the network from the file
	if (!m_network.create_from_file("Data/" + m_networkFile)) {
		std::cout << "Failed to load network from file." << std::endl;
		return;
	}

	if (m_pBiasInLayers == nullptr) {
		m_pBiasInLayers = new unsigned int[m_network.get_num_layers()];
	}
	if (m_pConnections == nullptr) {
		m_pConnections = new FANN::connection[m_network.get_total_connections()];
	}

	//get connection information
	m_network.get_bias_array(m_pBiasInLayers);
	m_network.get_connection_array(m_pConnections);

	//set the learning rate
	m_network.set_learning_rate(m_learningRate);

	//set the activation steepness
	m_network.set_activation_steepness_hidden(1.0);
	m_network.set_activation_steepness_output(1.0);

	//set activation function
	m_network.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
	m_network.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);

	//set callback for reports during training
	m_network.set_callback(training_callback, NULL);

	//get updated layer information
	unsigned int* pNeurons = new unsigned int[m_network.get_num_layers()];
	m_network.get_layer_array(pNeurons);

	m_neuronsInLayers.clear();
	for (unsigned int i = 0; i < m_network.get_num_layers(); ++i){
		m_neuronsInLayers.push_back(pNeurons[i]);
	}

	//create the network visuals in the testing state
	m_pTestingState->createNetworkStructure();

	delete pNeurons;
}

void NeuralNetwork::save() {
	if (!m_network.save("Data/" + m_networkFile)) {
		std::cout << "Failed to save network to file." << std::endl;
	}
}

NeuralNetwork* NeuralNetwork::getInstance() {
	if (m_pSelf == nullptr) {
		m_pSelf = new NeuralNetwork;
	}

	return m_pSelf;
}