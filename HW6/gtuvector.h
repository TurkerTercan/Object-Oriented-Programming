//Decleations for GTUVector class

#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include "gtucontainer.h"
#include <memory>

namespace TurkerTercanHW6
{
	template<class T>
	class GTUVector : public GTUContainer<T>
	{
	public:
		GTUVector();								//Default constructor
		GTUVector(int newSize);						//Basic constructor
		GTUVector(int newSize, T value);			//Basic constructor with fill the container with a value
		bool empty() const noexcept;				//Is empty
		int size() const noexcept;					//Return used
		int max_size() const noexcept;				//Return container
		void insert(const T&) noexcept;				//Add a new element to the container
		void erase(const T&) noexcept;				//Erase that element
		void erase(GTUIterator<T> pos) noexcept;	//Erase the element in that position
		void clear() noexcept;						//Delete all elements
		T operator [](int) const;					//Return the index's corresponding value
		
		GTUIterator<T> begin() const noexcept 	//Return iterator to beginning
		{
			return (this->data).get();  		//shared_ptr.get() function
		}
		GTUIterator<T> end() const noexcept 	//Return iterator to ending
		{
			GTUIterator<T> iter((this->data).get() + this->used);
			return iter;
		}
		GTUIteratorConst<T> cbegin() const noexcept
		{
			return (this->data).get();
		}
		GTUIteratorConst<T> cend() const
		{
			GTUIteratorConst<T> iter((this->data).get() + this->used);
			return iter;
		}
		
	};
}

#endif
