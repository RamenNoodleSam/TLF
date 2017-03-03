#ifndef APPLYSTRUCTURECHANGESCOMMAND_H
#define APPLYSTRUCTURECHANGESCOMMAND_H

/* Filename: ApplyStructureChangesCommand.h
 * Description: Concrete Command to apply the local layer structure
 *			    to the neural network.
 */

#include "Command.h"
#include "StateManager.h"
#include "TextField.h"

//prototype
class NeuralNetwork;

class ApplyStructureChangesCommand : public Command {
public:
	ApplyStructureChangesCommand(std::vector<unsigned int>* pLayers);

	virtual void operator()();

	virtual Command* clone() const;
private:
	NeuralNetwork*				m_pNeuralNetwork;
	std::vector<unsigned int>*	m_pLayers;
};

#endif