#ifndef LOADNETWORKCOMMAND_H
#define LOADNETWORKCOMMAND_H

/* Filename: LoadNetworkCommand.h
 * Description: Concrete Command to load neural network data from a file.
 */

#include "Command.h"
#include "StateManager.h"

//prototypes
class NeuralNetwork;
class TextField;

class LoadNetworkCommand : public Command {
public:
	LoadNetworkCommand(TextField* pTextField);

	virtual void operator()();

	virtual Command* clone() const;
private:
	NeuralNetwork*	m_pNeuralNetwork;
	TextField*		m_pTextField;
};

#endif