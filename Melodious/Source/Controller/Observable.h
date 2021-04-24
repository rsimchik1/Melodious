#pragma once
#include <memory>
#include <vector>

#include "Observer.h"

template<class T>
class Observable
{
public:
	void addObserver(std::shared_ptr<Observer<T>> toAdd)
	{
		if (std::find(observers.begin(), observers.end(), toAdd) == observers.end())
			observers.push_back(std::shared_ptr<Observer<T>>(toAdd));
	}

	void removeObserver(std::shared_ptr<Observer<T>> toRemove)
	{
		const auto index = std::find(observers.begin(), observers.end(), toRemove);
		if (index != observers.end())
			observers.erase(index);
	}

	void notifyObservers()
	{
		for (const auto& observer : observers)
			observer->notify(static_cast<T*>(this));
	}

private:
	std::vector<std::shared_ptr<Observer<T>>> observers;
};
