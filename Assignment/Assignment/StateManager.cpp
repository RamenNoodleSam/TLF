#include "StateManager.h"
#include "NetworkEditorState.h"
#include "TrainingState.h"
#include "TestingState.h"

StateManager::StateManager() :
	m_pCurrentState(nullptr)
{}

StateManager::~StateManager() {
	for (auto& iter : m_states) {
		if (iter.second != nullptr) {
			delete iter.second;
		}
	}
}

void StateManager::init() {
	//add all unique states to the map
	m_states[e_NetworkEditor] = new NetworkEditorState(this);
	m_states[e_Training] = new TrainingState(this);
	m_states[e_Testing] = new TestingState(this);

	//set the current state to the IntroState
	m_pCurrentState = m_states[e_NetworkEditor];
}

void StateManager::changeState(StateID id) {
	m_pCurrentState = m_states[id];
}

State* StateManager::currentState() const {
	return m_pCurrentState;
}