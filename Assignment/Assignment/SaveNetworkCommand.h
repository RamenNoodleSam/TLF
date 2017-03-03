#ifndef SAVENETWORKCOMMAND_H
#define SAVENETWORKCOMMAND_H

/* Filename: SaveNetworkCommand.h
 * Description: Concrete Command to save neural network data to a file.
 */

#include "Command.h"
#include "StateManager.h"

//prototype
class NeuralNetwork;

class SaveNetworkCommand : public Command {
public:
	SaveNetworkCommand();

	virtual void operator()();

	virtual Command* clone() const;
private:
	NeuralNetwork*	m_pNeuralNetwork;
};

#endif