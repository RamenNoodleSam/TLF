#include <iostream>
#include "ResetLayersCommand.h"

ResetLayersCommand::ResetLayersCommand(std::vector<unsigned int>* pLayers) {
	m_pLayers = pLayers;
}

void ResetLayersCommand::operator()() {
	//remove any layers in vector
	m_pLayers->clear();

	std::cout << "Reset layers." << std::endl;
}

Command* ResetLayersCommand::clone() const {
	return new ResetLayersCommand(*this);
}