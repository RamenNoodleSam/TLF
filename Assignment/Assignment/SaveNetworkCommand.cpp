#include <iostream>
#include <fstream>
#include "SaveNetworkCommand.h"
#include "NeuralNetwork.h"
#include "TextField.h"

SaveNetworkCommand::SaveNetworkCommand(TextField* pTextField) {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
	m_pTextField = pTextField;
}

void SaveNetworkCommand::operator()() {
	std::cout << "Saving network to file..." << std::endl;

	//get the string value from the TextField
	std::string networkFile = m_pTextField->getString().toAnsiString();

	//check string is not empty and has valid text in it for safety
	if (networkFile.empty() || networkFile == "Enter here..."){
		return;
	}

	//set the network file name in the neural network
	m_pNeuralNetwork->setNetworkFile(networkFile);

	//save the neural network
	m_pNeuralNetwork->save();

	//save the training filr name to a text file
	std::string fileName = "Data/" + networkFile.substr(0, networkFile.find('.'));
	std::ofstream file(fileName + ".txt");
	if (file.is_open()){
		file << m_pNeuralNetwork->getTrainingFile().toAnsiString();
		file.close();
	}
}

Command* SaveNetworkCommand::clone() const {
	return new SaveNetworkCommand(*this);
}