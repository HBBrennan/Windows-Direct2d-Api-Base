#pragma once

class MinionList
{
	friend class Minion;
	Minion** arr;
	int size;
public:
	MinionList();
	~MinionList();

	Minion* addObject(Minion* obj);
	bool removeObject(Minion* obj);
	void removeObject(int index);
	int findObject(Minion* obj) const;
	Minion* getObject(int index) const;
	int getSize() const;
};

