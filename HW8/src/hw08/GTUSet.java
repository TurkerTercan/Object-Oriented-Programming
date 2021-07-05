package hw08;

import java.lang.reflect.Array;

/**
 * This is a simple set class which is extends from GTUContainer abstract class
 * 
 * @author Türker Tercan
 */
public class GTUSet<T> extends GTUContainer<T>{

	/**
	 * Set constructor to sets the its capacity to 1 
	 * and creates a empty array of capacity's size
	 * 
	 * @param _type is the type of array that is needed to be instantiated
	 */
	public GTUSet(Class<T[]> _type)
	{
		used = 0;
		capacity = 1;
		genericType = _type;
		T[] temp =  genericType.cast(Array.newInstance(genericType.getComponentType(), capacity));
		this.data = temp;
	}
	
	@Override
	public boolean empty()
	{
		if( used == 0 )
			return true;
		else
			return false;
	}
	
	@Override
	public int size()
	{
		return used;
	}
	
	@Override
	public int max_size()
	{
		return capacity;
	}
	
	@Override
	public void insert( T element ) throws IllegalArgumentException
	{
		if( this.contains(element) )
		{
			throw new IllegalArgumentException("Error : You can not insert an element which is already in the set!\n");
		}
		
		else
		{
			if( used < capacity )
			{
				data[used++] = element;
			}
			else
			{
				capacity = capacity * 2;
				GTUIterator<T> p = this.iterator();
				T[] temp = genericType.cast(Array.newInstance(genericType.getComponentType(), capacity));
				for( int i = 0; i < used; i++ )
				{
					temp[i] = p.next();
				}
				this.data = temp;
				this.data[used++] = element;
			}
		}
	}
	
	@Override
	public void erase( T element )
	{
		if(this.contains( element ))
		{
			GTUIterator<T> p = this.iterator();
			while( p.hasNext() )
			{
				if( p.next() == element)
				{
					int i = p.getPosition() - 1;
					while( p.hasNext() )
					{
						data[i++] = p.next();
					}
				}
			}
			used--;
		}
		else
			System.err.printf("%s could not be found in the set\n", element);
	}
	
	@Override
	public void clear()
	{
		used = 0;
		capacity = 1;
		T[] temp = genericType.cast(Array.newInstance(genericType.getComponentType(), capacity));
		this.data = temp;
	}
	
	@Override
	public GTUIterator<T> iterator()
	{
		return new GTUIterator<T>(data);
	}
	
	@Override
	public boolean contains( Object o )
	{
		GTUIterator<T> temp = this.iterator();
		while( temp.hasNext() )
		{
			if( temp.next() == o)
				return true;
		}
		return false;
	}
	
	@Override
	public String toString()
	{
		GTUIterator<T> p = this.iterator();
		String[] totalSet = new String[used+1];
		totalSet[0] = String.format("Printing %s size = %d, max_size = %d\n", this.getClass(), used, capacity);
		
		for(int i = 1; i < totalSet.length; i++)
		{
			totalSet[i] = String.format("%d. element: %s\n", i, p.next());
		}
		
		StringBuilder build = new StringBuilder();
		for(int i = 0; i < totalSet.length; i++)
		{	
			build.append(totalSet[i]);
		}
		return build.toString();
	}
}
