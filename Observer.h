#pragma once

class Observer {
public:
	virtual void update() = 0;
};

#include <vector>
#include <algorithm>

class Observable {
private:
	/*Non owning pointers to observer instances*/
	std::vector<Observer*> observers;

public:

	void addObserver(Observer* obs);

	void removeObserver(Observer* obs);

	void notify();
};
