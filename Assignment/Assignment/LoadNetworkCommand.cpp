#include <iostream>
#include "LoadNetworkCommand.h"
#include "NeuralNetwork.h"

LoadNetworkCommand::LoadNetworkCommand() {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
}

void LoadNetworkCommand::operator()() {
	m_pNeuralNetwork->load();
}

Command* LoadNetworkCommand::clone() const {
	return new LoadNetworkCommand(*this);
}