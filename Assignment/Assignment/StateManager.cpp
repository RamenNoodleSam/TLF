#include "StateManager.h"

StateManager::StateManager() :
	m_pCurrentState(nullptr)
{}

StateManager::~StateManager() {
	for (auto iter : m_states) {
		if (iter != nullptr) {
			delete iter;
		}
	}
}

void StateManager::init() {
	m_states.push_back(new IntroState);
	m_states[0]->init();
}

State* StateManager::currentState() const {
	return m_states[0];
}