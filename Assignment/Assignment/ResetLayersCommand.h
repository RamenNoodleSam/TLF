#ifndef RESETLAYERSCOMMAND_H
#define RESETLAYERSCOMMAND_H

/* Filename: ResetLayersCommand.h
 * Description: Concrete Command to remove any existing layers of the NetworkEditor
 *				local layer structure.
 */

#include "Command.h"
#include "StateManager.h"
#include "TextField.h"

class ResetLayersCommand : public Command {
public:
	ResetLayersCommand(std::vector<unsigned int>* pLayers);

	virtual void operator()();

	virtual Command* clone() const;
private:
	std::vector<unsigned int>*	m_pLayers;
};

#endif