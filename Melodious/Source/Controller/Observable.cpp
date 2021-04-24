#include "Observable.h"

template<class T>
void Observable<T>::addObserver(Observer<T> *toAdd)
{
	if (std::find(observers.begin(), observers.end(), toAdd) != observers.end())
		observers.push_back(std::shared_ptr<Observer<T>>(toAdd));
}

template<class T>
void Observable<T>::removeObserver(Observer<T> *toRemove)
{
	const auto index = std::find(observers.begin(), observers.end(), toRemove);
	if (index != observers.end())
		observers.erase(index);
}

template<class T>
void Observable<T>::notifyObservers()
{
	for (const auto& observer : observers)
		observer->notify(static_case<T>(this));
}
