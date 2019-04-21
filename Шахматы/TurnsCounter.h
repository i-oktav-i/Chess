#pragma once
class TurnsCounter
{
public:

	TurnsCounter() { count = 0; }
	int getCount() const { return count; }
	int operator++() { return ++count; }
	int operator--() { return --count; }
private:

	int count;
};

