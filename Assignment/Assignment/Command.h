#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
public:
	virtual ~Command() {};

	virtual void operator()() = 0;

	virtual Command* clone() const = 0;
};

class ChangeState : public Command{
public:
	ChangeState(std::string s) { m_s = s; }

	virtual void operator()();

	virtual Command* clone() const {
		return new ChangeState(*this);
	}
private:
	std::string m_s;
};

#endif