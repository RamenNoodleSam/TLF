#include <iostream>
#include "SaveNetworkCommand.h"
#include "NeuralNetwork.h"

SaveNetworkCommand::SaveNetworkCommand() {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
}

void SaveNetworkCommand::operator()() {
	m_pNeuralNetwork->save();
}

Command* SaveNetworkCommand::clone() const {
	return new SaveNetworkCommand(*this);
}