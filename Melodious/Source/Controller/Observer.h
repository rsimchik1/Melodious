#pragma once
#include <memory>

template<class T>
class Observer
{
protected:
	~Observer() = default;
public:
	virtual void notify(T* caller) = 0;
};
