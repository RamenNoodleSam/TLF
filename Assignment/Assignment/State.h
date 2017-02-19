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
	virtual void init() = 0;
	virtual void cleanup() = 0;
	
	virtual void handleEvents(const sf::Event&) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow&) = 0;
};

#endif