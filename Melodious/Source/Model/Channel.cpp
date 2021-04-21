#include "Channel.h"

#include "../Exceptions/InvalidArgumentException.h"
#include "../Exceptions/InvalidChannelTreeException.h"

void Channel::setParent(Channel *newParent)
{
	if (newParent == this)
		throw InvalidChannelTreeException();
	
	if (newParent == parent)
		return;

	if (!newParent)
	{
		if (parent)
		{
			auto *tempPtr = parent;
			parent = nullptr;	// ensure bad ref is removed in case of exception
			
			try
			{
				tempPtr->removeChild(this);
			}
			catch (InvalidChannelTreeException& e)
			{
				throw e;
			}
			catch (InvalidArgumentException& e)
			{
				// this either wasn't found or doesn't exist
				printf("Found orphaned node in Channel tree.\n");
			}
		}
	}
	else if (this->hasChild(newParent))
	{
		throw InvalidChannelTreeException();
	}
	else
	{
		if (parent) parent->removeChild(this);
		try
		{
			newParent->addChild(this);
		}
		catch (InvalidChannelTreeException& e)
		{
			throw e;
		}
		catch (InvalidArgumentException& e)
		{
			// this was already a child
			printf("Tried to add duplicate connection in Channel tree.\n");
		}
		parent = newParent;
	}
}

void Channel::removeParent()
{
	try
	{
		setParent(nullptr);
	}
	catch (std::exception& e)
	{
		throw e;
	}
}

Channel* Channel::getParent()
{
	return parent;
}

bool Channel::hasParent()
{
	return parent != nullptr;
}