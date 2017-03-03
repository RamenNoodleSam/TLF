#ifndef CHANGESTATECOMMAND_H
#define CHANGESTATECOMMAND_H

/* Filename: ChangeStateCommand.h
 * Description: Concrete Command to switch from one State to another.
 *				StateID defined in "StateManager.h"
 */

#include "Command.h"
#include "StateManager.h"

class ChangeState : public Command {
public:
	ChangeState(StateManager* pStateManager, StateID id);

	virtual void operator()();

	virtual Command* clone() const;
private:
	StateManager*	m_pStateManager;
	StateID			m_targetStateID;
};

#endif