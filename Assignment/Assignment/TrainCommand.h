#ifndef TRAINCOMMAND_H
#define TRAINCOMMAND_H

/* Filename: TrainCommand.h
 * Description: Concrete Command to initiate training for neural network.
 *				A reference to a Graph is passed so that it can be updated
 *				with points as training continues (1 point per report).
 */

#include "Command.h"
#include "StateManager.h"

//prototypes
class Graph;
class NeuralNetwork;

class TrainCommand : public Command {
public:
	TrainCommand(Graph* pGraph);

	virtual void operator()();

	virtual Command* clone() const;
private:
	NeuralNetwork*	m_pNeuralNetwork;
	Graph*			m_pGraph;
};

#endif