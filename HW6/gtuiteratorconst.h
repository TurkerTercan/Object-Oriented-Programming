//Definitions and implementations for GTUIteratorConst

#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include <memory>

namespace TurkerTercanHW6
{
	template<class T>
	class GTUIteratorConst
	{
	public:
		//Basic const
		GTUIteratorConst( T* object)
		{
			data = object;
		}
		
		//These are the operators that which are needed by Iterators
		const T& operator *() const
		{
			return *data;
		}
		const T* operator ->() const
		{
			return data;
		}
		const GTUIteratorConst& operator ++()
		{
			data++;
			return *this;
		}
		GTUIteratorConst& operator ++(int ignore)
		{
			GTUIteratorConst temp = *this;
			data++;
			return temp;
		}
		GTUIteratorConst& operator --()
		{
			data--;
			return *this;
		}
		GTUIteratorConst& operator --(int ignore)
		{
			GTUIteratorConst temp = *this;
			data--;
			return temp;
		}
		GTUIteratorConst& operator = ( const GTUIteratorConst& object)
		{
			data = object.data;
			return *this;
		}
		bool operator ==( const GTUIteratorConst& object ) const
		{
			return data == object.data;
		}
		bool operator !=( const GTUIteratorConst& object ) const
		{
			return data != object.data;
		}
	private:
		T* data;
	};
}
#endif
