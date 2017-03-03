#ifndef SAVENETWORKCOMMAND_H
#define SAVENETWORKCOMMAND_H

/* Filename: SaveNetworkCommand.h
 * Description: Concrete Command to save neural network data to a file.
 */

#include "Command.h"
#include "StateManager.h"

//prototypes
class NeuralNetwork;
class TextField;

class SaveNetworkCommand : public Command {
public:
	SaveNetworkCommand(TextField* pTextField);

	virtual void operator()();

	virtual Command* clone() const;
private:
	NeuralNetwork*	m_pNeuralNetwork;
	TextField*		m_pTextField;
};

#endif