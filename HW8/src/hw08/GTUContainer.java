package hw08;

/**
 * This is my GTUContainer abstract super class 
 * it contains which functions to be implemented
 */
public abstract class GTUContainer<T> {
	/**
	 * size of array elements which is used
	 */
	protected int used;
	
	/**
	 * max size of array elements can be stored in that variable
	 */
	protected int capacity;
	
	/**
	 * Generic array to store the values inside of it
	 * and it also dynamically increases it size
	 */
	protected T data[];
	/**
	 * It stores what type of object to be stored
	 */
	protected Class<T[]> genericType;
	
	/**
	 * Returns a boolean depending on our collection is empty or not
	 */
	public abstract boolean empty();
	
	/**
	 * Returns used
	 */
	public abstract int size();
	
	/**
	 * Returns capacity
	 */
	public abstract int max_size();
	
	/**
	 * Insert element to our collection
	 */
	public abstract void insert( T element );
	
	/**
	 * Erase an element from our collection
	 */
	public abstract void erase( T element );
	
	/**
	 * Assign capacity to 1 and used to 0
	 * Creates new empty array
	 */
	public abstract void clear();
	
	/**
	 * Creates an iterator and sets it position to its beginning
	 * and returns that iterator
	 */
	public abstract GTUIterator<T> iterator();
	
	/**
	 * Returns a boolean if that collection contains that specific element
	 */
	public abstract boolean contains(Object o);
}
