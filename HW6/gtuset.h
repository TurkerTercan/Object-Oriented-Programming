//Definitions for GTUSet

#ifndef GTUSET_H
#define GTUSET_H

#include "gtucontainer.h"
#include <memory>

namespace TurkerTercanHW6
{
	template<class T>
	class GTUSet : public GTUContainer<T>
	{
	public:
		GTUSet(); 								//Default constructor
		bool empty() const noexcept; 			//Is empty 
		int size() const noexcept;				//Return used
		int max_size() const noexcept;			//Return container
		void insert(const T& ) noexcept(false);	//If new element isn't in the container then add it. Otherwise throw an exception
		void erase(const T& ) noexcept;			//Erase an element
		void clear() noexcept;					//Clear all content
		GTUIterator<T> begin() const noexcept	//Return iterator to beginning
		{
			return (this->data).get();			//shared_ptr.get() function
		}
		GTUIterator<T> end() const noexcept		//Return iterator to ending
		{
			auto iter((this->data).get() + this->used);	
			return iter;
		}
		GTUIteratorConst<T> cbegin() const noexcept //Return IteratorConst to beginning
		{
			return (this->data).get();
		}
		GTUIteratorConst<T> cend() const noexcept	//Return IteratorConst to ending
		{
			auto iter((this->data).get() + this->used);
			return iter;
		}
	};
}
#endif
