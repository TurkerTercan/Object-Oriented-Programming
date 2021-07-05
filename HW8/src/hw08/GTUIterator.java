package hw08;

/**
 * This class implements the basic of Iterator
 * that can be used for any GTUContainer classes
 * 
 * @author Türker Tercan
 *
 * @param <T> type of Iterator to be constructed
 */

public class GTUIterator<T> 
{
	/**
	 * 
	 */
	private T data[];
	
	/**
	 * Index count of iterator
	 */
	private int pos = 0;
	
	
	/**
	 * Basic constructor for GTUIterator
	 * 
	 * @param object is the needed data to be controlled in Iterator
	 */
	public GTUIterator( T[] object )
	{
		data = object;
	}
	
	/**
	 * Returns a boolean depending on array is reached to its end or not
	 */
	public boolean hasNext( )
	{
		if( data.length == pos)
			return false;
		else
			return true;
	}
	
	/**
	 * Returns the value of element and increase its position
	 */
	public T next( )
	{
		return data[pos++];
	}
	
	
	/**
	 * Returns the integer of the position
	 */
	public int getPosition( )
	{
		return pos;
	}
}
