#ifndef STATEMANAGER_H
#define STATEMANAGER_H

/* Filename: StateManager.h
 * Description: Stores and manages the various states of the application.				
 */

#include <vector>
#include "IntroState.h"

class StateManager {
public:
	StateManager();
	~StateManager();

	void init();

	State* currentState() const;

private:
	std::vector<State*> m_states;
	State*				m_pCurrentState;
};

#endif