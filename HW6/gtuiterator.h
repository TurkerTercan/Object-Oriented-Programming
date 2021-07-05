//Definitions and implementations for GTUIterator

#ifndef GTUITERATOR_H
#define GTUITERATOR_H
#include <memory>

namespace TurkerTercanHW6
{
	template<class T>
	class GTUIterator
	{
	public:
		//Constructor
		GTUIterator( T* object)
		{
			data = object;
		}
		//These are the operators which are needed by GTUIterator
		T& operator *() const
		{
			return *data;
		}
		T* operator ->() const
		{
			return data;
		}
		GTUIterator& operator ++()
		{
			data++;
			return *this;
		}
		GTUIterator& operator ++(int ignore)
		{
			GTUIterator temp = *this;
			data++;
			return temp;
		}
		GTUIterator& operator --()
		{
			data--;
			return *this;
		}
		GTUIterator& operator --(int ignore)
		{
			GTUIterator temp = *this;
			data--;
			return temp;
		}
		GTUIterator& operator =(const GTUIterator& object)
		{
			data = object.data;
			return *this;
		}
		GTUIterator& operator +(const int& pos)
		{
			for(int i = 0; i < pos; i++)
			{
				data++;
			}
			return *this;
		}
		bool operator ==( const GTUIterator& object ) const
		{
			return data == object.data;
		}
		bool operator !=( const GTUIterator& object ) const
		{
			return data != object.data;
		}
		T* get() const
		{
			return data;
		}
	private:
		T* data;
	};
	
	//Find the element in container with iterator
	template<class T>
	GTUIterator<T> find(GTUIterator<T> first, GTUIterator<T> last, const T& value)
	{
		while(first != last)
		{
			if(*first == value)
				return first;
			++first;
		}
		return last;
	}
	
	//Find the element which is true by given function
	template<class T, class UnaryPredicate>
	GTUIterator<T> find_if(GTUIterator<T> first, GTUIterator<T> last, UnaryPredicate F)
	{
		while(first != last)
		{
			if(F(*first))
				return first;
			first++;
		}
		return last;
	}
	
	//Apply function to all elements in container
	template<class T, class Function>
	Function for_each(GTUIterator<T> first, GTUIterator<T> last, Function fn)
	{
		while(first != last)
		{
			fn(*first);
			first++;
		}
		return fn;
	}
}
#endif
