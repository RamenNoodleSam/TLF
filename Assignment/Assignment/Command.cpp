#include "Command.h"
#include <iostream>

void ChangeState::operator()() {
	std::cout << "In ChangeState Command object: "<< m_s << std::endl;
}