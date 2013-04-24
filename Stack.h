#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <typename T>
class Stack : private LinkedList<T>
{
public:
	bool push(const T &data)
	{
		return insertAtFront(data);
	}

	bool pop(void)
	{
		bool success = false;
		LinkedList::removeFromFront(&success);
		return success;
	}

	T peek(bool *success = NULL) const
	{
		T retval;

		if (LinkedList::isEmpty())
		{
			if (success != NULL)
				*success = false;

			return retval;
		}
		else
		{
			if (success != NULL)
				*success = true;
			retval = LinkedList::headPtr->getData();
		}

		return retval;
	}

	bool isEmpty() const
	{
		return LinkedList::isEmpty();
	}

	void print() const
	{
		LinkedList::print();
	}
};

#endif