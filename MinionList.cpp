#include "MinionList.h"

MinionList::MinionList()
{
	size = 0;
}


MinionList::~MinionList()
{
	for (int i = 0; i < size; i++)
	{
		delete arr[i];
	}

	delete[] arr;
	arr = nullptr;
}


Minion* MinionList::addObject(Minion* obj)
{
	Minion** newList = new Minion*[size + 1];
	
	for (int i = 0; i < size; i++)
	{
		newList[i] = arr[i];
	}
	newList[size] = obj;
	size++;
	delete[] arr;
	arr = newList;
	newList = nullptr;
	return obj;
}

void MinionList::removeObject(int index)
{
	int i = 0;
	delete arr[index];
	Minion** newList = new Minion*[size - 1];
	while (i < size - 1)
	{
		if (i < index)
			newList[i] = arr[i];
		else
			newList[i] = arr[i + 1];

		i++;
	}
	size--;
	delete[] arr;
	arr = newList;
}

bool MinionList::removeObject(Minion* obj)
{
	int index = findObject(obj);
	bool found = index >= 0;

	if (found)
		removeObject(index);

	return found;
}

int MinionList::findObject(Minion* obj) const
{
	for (int i = 0; i < size; i++)
	{
		Minion* m = arr[i];
		if (m == obj)
			return i;
	}

	return -1;
}

Minion* MinionList::getObject(int index) const
{
	return arr[index];
}

int MinionList::getSize() const
{
	return size;
}