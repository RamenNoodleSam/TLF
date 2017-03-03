#ifndef STATE_H
#define STATE_H

/* Filename: State.h
 * Description: Abstract base class for all concrete States in the application.
 *				Handled by StateManager.
 */

//prototypes
class StateManager;

namespace sf {
	class RenderWindow;
	class Event;
}

class State {
public:
	State(StateManager* pStateManager) : m_pStateManager(pStateManager) {}
	virtual ~State() {}
	
	virtual void handleEvents(const sf::Event&, sf::RenderWindow&) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow&) = 0;

protected:
	StateManager* m_pStateManager;
};

#endif