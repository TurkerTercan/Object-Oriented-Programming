//Implementations for GTUSET class
#include "gtuset.h"

#include <memory>

namespace TurkerTercanHW6
{
	template<class T>
	//Default Constructor
	GTUSet<T>::GTUSet()
	{
		this->capacity = 1;
		std::shared_ptr<T> temp(new T[this->capacity]);
		this->data = temp;
		this->used = 0;
	}
	
	//Returns true if it is empty
	template<class T>
	bool GTUSet<T>::empty() const noexcept
	{
		if(this->used != 0)
			return false;
		else
			return true;
	}
	
	//Returns used
	template<class T>
	int GTUSet<T>::size() const noexcept
	{
		return this->used;
	}
	
	//Returns capacity
	template<class T>
	int GTUSet<T>::max_size() const noexcept
	{
		return this->capacity;
	}
	
	//Insert an element to container if it not already in the container.
	template<class T>
	void GTUSet<T>::insert(const T& object) noexcept(false)
	{
		bool inSet = false;
		for(auto i = this->begin(); i != this->end(); ++i)
		{
			if(*i == object)
			{
				throw std::invalid_argument("Error: You can not insert an element which is already in the set!");
				inSet = true;
			}
		}
		//If the capacity is not reached, attach the element to the end()
		if(this->size() != this->max_size() && !inSet)
		{
			*(this->end()) = object;
			this->used++;
		}
		
		//If the capacity is reached, double the capacity and attach the element to the end()
		else if(this->size() >= this->max_size() && !inSet)
		{
			this->capacity = this->capacity * 2;
			std::shared_ptr<T> temp(new T[this->capacity]);
			int i = 0;
			for( auto iter = this->begin(); iter != this->end(); ++iter, ++i) //Transferring all elements in shared_ptr to new one
			{
				temp.get()[i] = *(iter);
			}
			this->data = temp;
			*(this->end()) = object;
			this->used++;
		}
	}
	//Erase the first element if there is one 
	template<class T>
	void GTUSet<T>::erase(const T& object) noexcept
	{
		bool inSet = false;
		for( auto i = this->begin(); i != this->end(); i++ )
		{
			if(*i == object)
			{
				for( auto j = i; j != this->end(); j++ )
				{
					*j = *(j.get() + 1);
				}
				inSet = true;
			}
		}
		if(inSet == 1)
			this->used--;
	}
	
	//Delete all elements in container
	template<class T>
	void GTUSet<T>::clear() noexcept
	{
		this->used = 0;
		this->capacity = 1;
		std::shared_ptr<T> temp(new T[this->capacity]);
		this->data = temp;
	}
	
}