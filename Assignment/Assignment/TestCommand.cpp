#include <iostream>
#include "TestCommand.h"
#include "NeuralNetwork.h"

TestCommand::TestCommand() {
	m_pNeuralNetwork = NeuralNetwork::getInstance();
}

void TestCommand::operator()() {
	std::cout << "Starting network testing..." << std::endl;
	m_pNeuralNetwork->test();
}

Command* TestCommand::clone() const {
	return new TestCommand(*this);
}