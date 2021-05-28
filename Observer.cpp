#include "Observer.h"

void Observable::addObserver(Observer* obs) {
	observers.push_back(obs);
}

void Observable::removeObserver(Observer* obs) {
	observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Observable::notify() {
	for (auto obs : observers) {
		obs->update();
	}
}

