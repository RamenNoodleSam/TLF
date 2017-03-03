#ifndef COMMAND_H
#define COMMAND_H

/* Filename: Command.h
 * Description: Abstract base class used to implement the Command pattern.
 *				Used to add a layer of indirection where needed, specifically Button clicks.
 */

#include <string>

class Command {
public:
	virtual ~Command() {};

	virtual void operator()() = 0;

	//necessary for deep copy of polymorphic instance
	virtual Command* clone() const = 0;
};

#endif