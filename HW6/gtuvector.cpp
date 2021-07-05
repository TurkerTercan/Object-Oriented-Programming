//Implementations for GTUVector

#include "gtuvector.h"

#include <memory>

namespace TurkerTercanHW6
{
	template<class T>
	//Default Constructor
	GTUVector<T>::GTUVector()
	{
		this->capacity = 1;
		this->used = 0;
		std::shared_ptr<T> temp(new T[this->capacity]);
		this->data = temp;
	}
	//Constructor for v(10)
	template<class T>
	GTUVector<T>::GTUVector(int newsize)
	{
		this->capacity = newsize;
		this->used = 0;
		std::shared_ptr<T> temp(new T[this->capacity]);
		this->data = temp;
	}
	//Constructor for v(10,5)
	template<class T>
	GTUVector<T>::GTUVector(int newsize, T value)
	{
		this->capacity = newsize;
		this->used = 0;
		std::shared_ptr<T> temp(new T[this->capacity]);
		this->data = temp;
		
		for(auto p = this->begin(); p != this->end(); p++)
		{
			*p = value;
		}
	}
	//Returns true if it is empty
	template<class T>
	bool GTUVector<T>::empty() const noexcept
	{
		if(this->used != 0)
			return false;
		else
			return true;
	}
	//Returns used
	template<class T>
	int GTUVector<T>::size() const noexcept
	{
		return this->used;
	}
	
	//Returns capacity
	template<class T>
	int GTUVector<T>::max_size() const noexcept
	{
		return this->capacity;
	}
	
	template<class T>
	//Insert an element to container if it not already in the container.
	void GTUVector<T>::insert(const T& object) noexcept
	{
		//If the capacity is not reached, attach the element to the end()
		if(this->size() != this->max_size())
		{
			*(this->end()) = object;
			this->used++;
		}
		//If the capacity is reached, double the capacity and attach the element to the end()
		else if(this->size() >= this->max_size())
		{
			this->capacity = this->capacity * 2;
			std::shared_ptr<T> temp(new T[this->capacity]);
			int i = 0;
			for(auto iter = this->begin(); iter != this->end(); ++iter, ++i)
				temp.get()[i] = *iter;
			this->data = temp;
			*(this->end()) = object;
			this->used++;
		}
	}
	
	//Erase the first element if there is one 
	template<class T>
	void GTUVector<T>::erase(const T& object) noexcept
	{
		bool inVector = false;
		for( auto i = this->begin(); i != this->end(); i++ )
		{
			if(*i == object )
			{
				for( auto j = i; j != this->end(); j++ )
				{
					*j = *(j.get() + 1);
				}
				inVector = true;
			}
			break;
		}
		if(inVector == 1)
			this->used--;
	}
		
	//Erase the element in that position 
	template<class T>
	void GTUVector<T>::erase(const GTUIterator<T> pos) noexcept
	{
		for(auto p = pos; p != this->end(); p++)
		{
			*p = *(p.get() + 1);
		}
		this->used--;
	}
	
	//Delete all elements in container
	template<class T>
	void GTUVector<T>::clear() noexcept
	{
		this->used = 0;
		this->capacity = 1;
		std::shared_ptr<T> temp(new T[this->capacity]);
		this->data = temp;
	}
	
	//[] operator which is returns that value in the index
	template<class T>
	T GTUVector<T>::operator [](int index) const
	{
		auto iter = this->begin();
		for(int i = 0; i < index; i++)
		{
			++iter;
		}
		return *iter;
	}
}
