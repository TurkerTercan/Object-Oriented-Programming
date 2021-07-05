//This is the abstract base class for my set and vector class

#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include "gtuiterator.h"
#include "gtuiteratorconst.h"
#include "gtuiterator.cpp"
#include "gtuiteratorconst.cpp"
#include <exception>

namespace TurkerTercanHW6
{
	template<class T>
	class GTUContainer
	{
	public:
		virtual bool empty() const noexcept = 0; 
		//is the container empty
		virtual int size() const noexcept = 0;	
		//returns an int that the container holds
		virtual int max_size() const noexcept = 0;
		//return max size
		virtual void insert(const T& ) noexcept(false)= 0;
		//Insert element, throws exception std::bad_pafram 
		//if there is a problem with insersion
		virtual void erase(const T&) noexcept = 0;
		//Erase element
		virtual void clear() noexcept = 0;
		//Clear all content
		virtual GTUIterator<T> begin() const noexcept = 0;
		//Return iterator to beginning
		virtual GTUIterator<T> end() const noexcept = 0;
		//Return iterator to ending
	protected:
		int used;			//the capacity that is using
		int capacity;		//max capacity
		std::shared_ptr<T> data;	//data
	};
}
#endif