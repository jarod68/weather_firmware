#pragma once
#ifndef SLIDINGHISTORY_H
#define SLIDINGHISTORY_H

template<typename T>
class SlidingHistory
{

public:
	SlidingHistory(size_t allocatedSize) :
		_allocatedSize(allocatedSize), _current(-1), _history(new T[allocatedSize]), _historySize(0)
	{
	}
	size_t getSize()
	{
		return _historySize;
	}

	void addToHistory(T value)
	{
		if (_current + 1 == _allocatedSize)
			_current = -1;

		if (_historySize < _allocatedSize)
			_historySize++;

		_current++;
		_history[_current] = value;

	}
	T mean()
	{
		T mean = 0;
		for (int i = 0; i < _historySize; ++i){

			mean += _history[i];

		}
		return mean / _historySize;
	}
	T getLast()
	{
		return _history[_current];
	}
	void reset()
	{
		_current = -1;
		_historySize = 0;
	}
private:
	size_t _allocatedSize;
	size_t _historySize;
	int _current;

	T * _history;

};

#endif