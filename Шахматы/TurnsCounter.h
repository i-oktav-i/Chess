#pragma once
class TurnsCounter
{
public:

	TurnsCounter() { count = 0; }
	int getCount() const { return count; }
	int operator++() { return ++count; }
	int operator--() { return --count; }
	void setZero() { count = 0; }
private:

	int count;
};

