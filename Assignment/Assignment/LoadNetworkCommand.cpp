#include <iostream>
#include <fstream>
#include "LoadNetworkCommand.h"
#include "NeuralNetwork.h"
#include "TextField.h"

LoadNetworkCommand::LoadNetworkCommand(TextField* pTextField) {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pTextField = pTextField;
}

void LoadNetworkCommand::operator()() {
	std::cout << "Loading network from file..." << std::endl;

	//get the string value from the TextField
	std::string networkFile = m_pTextField->getString().toAnsiString();

	//check string is not empty and has valid text in it for safety
	if (networkFile.empty() || networkFile == "Enter here..."){
		return;
	}

	//set the network file name in the neural network
	m_pNeuralNetwork->setNetworkFile(networkFile);

	//load the training file using the stored data in the text file
	std::string fileName = "Data/" + networkFile.substr(0, networkFile.find('.'));
	std::ifstream file(fileName + ".txt");
	std::string trainingFile;
	if (file.is_open()){
		std::getline(file, trainingFile);
		m_pNeuralNetwork->loadTrainingFile(trainingFile);
		file.close();
	}

	//load the neural network
	m_pNeuralNetwork->load();
}

Command* LoadNetworkCommand::clone() const {
	return new LoadNetworkCommand(*this);
}