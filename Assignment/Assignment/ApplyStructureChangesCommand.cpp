#include <iostream>
#include "NeuralNetwork.h"
#include "ApplyStructureChangesCommand.h"

ApplyStructureChangesCommand::ApplyStructureChangesCommand(std::vector<unsigned int>* pLayers) {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pLayers = pLayers;
}

void ApplyStructureChangesCommand::operator()() {
	std::cout << "Applying structure to neural network." << std::endl;

	//pass layer information to the neural network
	m_pNeuralNetwork->applyStructureToNetwork(*m_pLayers);
}

Command* ApplyStructureChangesCommand::clone() const {
	return new ApplyStructureChangesCommand(*this);
}