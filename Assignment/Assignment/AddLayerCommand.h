#ifndef ADDLAYERCOMMAND_H
#define ADDLAYERCOMMAND_H

/* Filename: AddLayerCommand.h
 * Description: Concrete Command to add a layer to the NetworkEditor
 *				local layer structure.
 */

#include "Command.h"
#include "StateManager.h"
#include "TextField.h"

class AddLayerCommand : public Command {
public:
	AddLayerCommand(std::vector<unsigned int>* pLayers, TextField* pTextField);

	virtual void operator()();

	virtual Command* clone() const;
private:
	std::vector<unsigned int>*	m_pLayers;
	TextField*					m_pTextField;
};

#endif