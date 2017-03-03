#include <iostream>
#include "ChangeStateCommand.h"

ChangeState::ChangeState(StateManager* pStateManager, StateID id) :
	m_pStateManager(pStateManager),
	m_targetStateID(id)
{}

void ChangeState::operator()() {
	m_pStateManager->changeState(m_targetStateID);
}

Command* ChangeState::clone() const {
	return new ChangeState(*this);
}