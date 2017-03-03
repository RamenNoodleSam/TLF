#include <iostream>
#include "TrainCommand.h"
#include "NeuralNetwork.h"
#include "Graph.h"

TrainCommand::TrainCommand(Graph* pGraph) {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pGraph = pGraph;
}

void TrainCommand::operator()() {
	//reset points in the graph each time training starts
	m_pGraph->resetPoints();

	//reset weights of the network to start training fresh
	m_pNeuralNetwork->resetWeights();
	std::cout << "Starting network training..." << std::endl;
	m_pNeuralNetwork->train();
}

Command* TrainCommand::clone() const {
	return new TrainCommand(*this);
}