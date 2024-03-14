#pragma once
#include "Observer.h"

class Subject
{
public:
	void addObserver(Observer* observer);
	void notify(Events event);

private:
	Observer* observer;
};