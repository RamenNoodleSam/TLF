#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

/* Filename: TestCommand.h
 * Description: Concrete Command to initiate testing of the neural network.
 */

#include "Command.h"
#include "StateManager.h"

//prototype
class NeuralNetwork;

class TestCommand : public Command {
public:
	TestCommand();

	virtual void operator()();

	virtual Command* clone() const;
private:
	NeuralNetwork*	m_pNeuralNetwork;
};

#endif