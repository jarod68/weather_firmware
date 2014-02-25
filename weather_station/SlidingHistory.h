#pragma once
#ifndef SLIDINGHISTORY_H
#define SLIDINGHISTORY_H

/**
* This class is a circular array to store T values and compute mean of stored values
*/
template<typename T>
class SlidingHistory
{

public:

	/**
	* Constructor using allocatedSize argument : the size to allocate to store values, when size reachs allocatedSize, insert index goes back to 0, erasing old values.
	*/
	SlidingHistory		(size_t allocatedSize) :
												_allocatedSize(allocatedSize), 
												_current(-1), 
												_history(new T[allocatedSize]),
												_historySize(0)
	{}

	/**
	* Returns the amount of values
	*/
	size_t	 getSize		()
	{
		return _historySize;
	}

	/**
	* Adds the specified value
	*/
	void	addToHistory	(T value)
	{
		if (_current + 1 == _allocatedSize)
			_current = -1;

		if (_historySize < _allocatedSize)
			_historySize++;

		_current++;
		_history[_current] = value;

	}

	/**
	* Returns the mean value of all stored values
	*/
	T	 mean	()
	{
		T mean = 0;
		for (int i = 0; i < _historySize; ++i)
			mean += _history[i];

		return mean / _historySize;
	}

	/**
	* Returns the last inserted value
	*/
	T	getLast	()
	{
		return _history[_current];
	}

	/**
	* Clears all values
	*/
	void	reset	()
	{
		_current = -1;
		_historySize = 0;
	}

private:
	T		*		_history;

	size_t		_allocatedSize;
	size_t		_historySize;
	int			_current;

};

#endif