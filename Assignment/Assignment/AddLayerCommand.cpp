#include <iostream>
#include <numeric>
#include "AddLayerCommand.h"

AddLayerCommand::AddLayerCommand(std::vector<unsigned int>* pLayers, TextField* pTextField) {
	m_pLayers = pLayers;
	m_pTextField = pTextField;
}

void AddLayerCommand::operator()() {
	std::string str = m_pTextField->getString().toAnsiString();

	//check string isn't empty and all characters are digits for safety
	if (str.empty() || !std::all_of(str.begin(), str.end(), ::isdigit)){
		return;
	}

	//cast string to integer value
	unsigned int numNeurons = std::stoi(str);

	//push current contents of the TextField into a new layer of the structure
	m_pLayers->push_back(numNeurons);

	std::cout << "Added layer with " << numNeurons << " neurons. Number of layers: " <<m_pLayers->size() << std::endl;
}

Command* AddLayerCommand::clone() const {
	return new AddLayerCommand(*this);
}