#ifndef CORE_H
#define CORE_H

/* Filename: Core.h
 * Description: The central object of the application, ties together
 *			    the most important aspects of SFML, FANN and specifics
 *				of the application.
 */

#include <SFML/Graphics.hpp>
#include "StateManager.h"

class Core {
public:
	Core();
	~Core();

	//contains main application loop (handle events, update assets, render assets)
	bool run();

private:
	//SFML window as render target
	sf::RenderWindow m_window;

	//state manager handling specific screen logic
	StateManager m_stateManager;
};

#endif