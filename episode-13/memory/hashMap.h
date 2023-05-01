#pragma once
#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <vector>

void failure(const char* message)
{
	std::cerr << "Fatal error : " << message << std::endl;
	exit(-1);
}

template <typename FirstType, typename SecondType>
struct Pair
{
	FirstType first;
	SecondType second;
};

template <typename FirstType, typename SecondType>
Pair<FirstType, SecondType> makePair(FirstType first, SecondType second)
{
	Pair<FirstType, SecondType> pair;
	pair.first = first;
	pair.second = second;
	return pair;
}


template <typename kType, typename vType>
class HashMap
{
	std::vector<Pair<kType, vType>> elements;

public:
	void add(Pair<kType, vType> element)
	{
		elements.push_back(element);
	}
	void add(kType key, vType value)
	{
		elements.push_back(makePair<kType, vType>(key, value));
	}

	vType* get(kType key)
	{
		if(exists(key))
		{
			for(int i = 0 ; i < (int)elements.size() ; i++)
			{
				if(elements[i].first == key)
				{
					return &elements[i].second;
				}
			}
		}
		else
		{
			failure("<HashMap.get> Key doesn't exist");
			
		}
		return nullptr;
	}

	vType* operator[](kType key)
	{	
		return get(key);
		
	}
	bool exists(kType key)
	{
		for(int i = 0 ; i < (int)elements.size() ; i++)
		{
			if(elements[i].first == key)
			{
				return true;
			}
		}
		return false;
	}
	void remove(kType key)
	{
		bool found = false;
		for(int i = 0 ; i < (int)elements.size() ; i++)
		{
			if(elements[i].first == key)
			{
				elements.erase(elements.begin() + i);
				found = true;
			}
		}
		if(!found)
		{
			failure("<HashMap.remove> Key doesn't exist");
		}
		
	}
	std::vector<Pair<kType, vType>>& getKeySet()
	{
		return elements;
	}

	void clear()
	{
		if(elements.size() >= 1)
		{
			elements.clear();
		}
		
	}
};
#endif