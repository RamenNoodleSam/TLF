#include <iostream>
#include "TrainCommand.h"
#include "NeuralNetwork.h"
#include "Graph.h"

TrainCommand::TrainCommand(Graph* pGraph) {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pGraph = pGraph;
}

void TrainCommand::operator()() {
	std::cout << "Resetting MSE and fail bits." << std::endl;
	m_pGraph->resetPoints();
	m_pNeuralNetwork->resetWeights();
	std::cout << "Starting network training..." << std::endl;
	m_pNeuralNetwork->train();
}

Command* TrainCommand::clone() const {
	return new TrainCommand(*this);
}