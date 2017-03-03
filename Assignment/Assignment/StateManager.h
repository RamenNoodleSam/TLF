#ifndef STATEMANAGER_H
#define STATEMANAGER_H

/* Filename: StateManager.h
* Description: Stores and manages the various states of the application.
*/

#include <unordered_map>
#include "State.h"

//enum of all concrete States
enum StateID { e_NetworkEditor, e_Training, e_Testing };

class StateManager {
	typedef std::unordered_map<StateID, State*> States;
public:
	StateManager();
	~StateManager();

	//initialise the States
	void init();

	//change to State associated with enumerated ID
	void changeState(StateID id);

	//accessors
	State* currentState() const;

private:
	States m_states;
	State* m_pCurrentState;
};

#endif