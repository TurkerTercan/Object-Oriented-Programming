package hw07;
/**
 * 
 */

/**
 * This is my AbstractBoard super class 
 * it contains all functions to be implemented
 * @author Turker Tercan
 */
public abstract class AbstractBoard {
	
	/**
	 * Board's x coordinate size
	 */
	private int size;
	
	/**
	 * Board's y coordinate size
	 */
	private int width;
	
	/**
	 * How many moves user played
	 */
	private int moves;
	
	/**
	 * BB's x coordinate
	 */
	private int locationX;
	
	/**
	 * BB's y coordinate
	 */
	private int locationY;
	
	/**
	 * How many boards have been created
	 */
	private static int num = 0;
	
	/**
	 * Current boards is solution
	 */
	private boolean solved;
	
	/**
	 * Last move that the user is played
	 */
	private char last;
	
	/**
	 * Basic constructor for AbstractBoard
	 * @param newSize is the size of x coordinates
	 * @param newWidth is the size of y coordinates
	 */
	public AbstractBoard( int newSize, int newWidth )
	{
		this.setMoves( 0 );
		this.setSolved( false );
		this.setLast( 'S' );
		this.setSize(newSize, newWidth);
		num++;
	}
	
	/**
	 * I used this constructor to make the clone of the current board
	 * @param clone is the current board
	 */
	public AbstractBoard( AbstractBoard clone )
	{
		this.setMoves( clone.numberOfMoves());
		this.setSolved( clone.isSolved() );
		this.setLast( clone.lastMove() );
		this.setSize(clone.getSize(), clone.getWidth());
		
		for( int i = 0; i < clone.getSize(); i++ )
		{
			for( int j = 0; j < clone.getWidth(); j++)
			{
				this.setTile( clone.cell(i, j), i, j);
			}
		}
	}
	
	/**
	 * Initialize one and two dimensinal arrays
	 */
	public abstract void createBoard();
	
	/**
	 * This method takes an AbstractBoard and checks it is equal to current board
	 * @param other is the board that will compared
	 * @return if it is equal or not
	 */
	public boolean Equals( AbstractBoard other )
	{
		if( this.getSize( ) != other.getSize( ) || this.getWidth( ) != other.getWidth( ) )
			return false;
		
		for( int i = 0; i < this.getSize( ); i++ )
		{
			for( int j = 0; j < this.getWidth( ); j++ )
			{
				if( this.cell( i, j ) != other.cell( i, j ) )
					return false;
			}
		}
		return true;
	}
	
	/**
	 * Finds board[x][y]
	 * @param x is x coordinate
	 * @param y is y coordinate
	 * @return tile in that position
	 */
	public int cell( int x, int y )
	{
		return this.getTile( x, y );
	}
	
	/**
	 * Finds board[x][y]
	 * @param x is x coordinate
	 * @param y is y coordinate
	 * @return tile in that position
	 */
	protected abstract int getTile(int x, int y);

	/**
	 * Move method for board
	 * @param direction is which direction will the board go
	 */
	public abstract void move( char direction );
	
	/**
	 * it makes 5 random moves
	 */
	public abstract void randomMoves();
	
	/**
	 * Checks the current board is solution
	 */
	public void checkIsFinal( )
	{
		int count = 1;
		boolean check = true;
		
		for( int i = 0; i < this.getSize( ); i++ )
		{
			for( int j = 0; j < this.getWidth( ); j++ )
			{
				if( i == this.getSize() - 1 && j == this.getWidth() - 1 && this.cell(i, j) == -1 )
					check = true;
				else if( this.cell(i, j) != count++)
					check = false;
			}
		}
		this.setSolved( check );
	}
	
	/**
	 * Resets the current board
	 */
	public void reset( )
	{
		int count = 1;
		this.setMoves( 0 );
		for( int i = 0; i < this.getSize(); i++ )
		{
			for( int j = 0; j < this.getWidth(); j++ )
			{
				this.setTile( count++, i, j );
				if( i == getSize( ) - 1 && j == getWidth( ) - 1 ) {
					this.setTile( -1, i, j );
					locationX = i;
					locationY = j;
				}
					
			}
		}
	}
	
	/**
	 * Sets the tile in that position to given integer
	 * @param tile is the integer that will be replaced
	 * @param x is x coordinate
	 * @param y is y coordinate
	 */
	protected abstract void setTile( int tile, int x, int y );

	/**
	 * Method for writing to file
	 */
	public abstract void writeToFile( );
	
	/**
	 * Read method from file
	 * @throws Exception throws if there is no such file
	 */
	public abstract void readFromFile( ) throws Exception;
	
	/**
	 * Sets the x and y sizes
	 * @param newSize x size
	 * @param newWidth y size
	 */
	public void setSize( int newSize, int newWidth )
	{
		if( newSize > 0 )
			size = newSize;
		else
		{
			size = 0;
			System.err.printf("Board's parameter values can not be negative!");
		}
		if( newWidth > 0 )
			width = newWidth;
		else
		{
			width = 0;
			System.err.printf("Board's parameter values can not be negative!");
		}
		this.createBoard();
		this.reset();
	}
	
	/**
	 * toString method
	 */
	public String toString( )
	{
		return String.format( "Size = %d, Width = %d\nCreated board objects count = %d"
				+ "\nMoves count = %d, Is it solved = %s\n"
				, this.getSize( ), this.getWidth( ), this.NumberOfBoards( ), this.numberOfMoves( ), this.isSolved() );
	}
	
	/**
	 * Getter for size
	 * @return size
	 */
	public int getSize( )
	{
		return size;
	}
	
	/**
	 * Getter for width
	 * @return width
	 */
	public int getWidth( )
	{
		return width;
	}
	
	/**
	 * Getter for moves
	 * @return moves
	 */
	public int numberOfMoves( )
	{
		return moves;
	}
	
	/**
	 * Setter for moves
	 * @param newMoves is move
	 */
	public void setMoves( int newMoves ) 
	{
		moves = newMoves;
	}
	
	/**
	 * Increase moves one
	 */
	public void increaseMoves( )
	{
		moves++;
	}
	
	/**
	 * Getter for x coordinate of BB
	 * @return locationX
	 */
	public int getLocationX( )
	{
		return locationX;
	}
	
	/**
	 * Setter for x coordinate of BB
	 * @param newLocationX is the current x position of BB
	 */
	public void setLocationX( int newLocationX )
	{
		locationX = newLocationX;
	}
	
	/**
	  * Getter for y coordinate of BB
	 * @return locationY
	 */
	public int getLocationY( )
	{
		return locationY;
	}
	
	/**
	 * Setter for y coordinate of BB
	 * @param newLocationY is the current y position of BB
	 */
	public void setLocationY( int newLocationY )
	{
		locationY = newLocationY;
	}
	
	/**
	 * Getter for solved
	 * @return solved
	 */
	private boolean isSolved( )
	{
		return solved;
	}
	
	/**
	 * Setter for solved
	 * @param newSolved is boolean for solved
	 */
	private void setSolved( boolean newSolved )
	{
		solved = newSolved;
	}
	
	/**
	 * Getter for last
	 * @return last
	 */
	public char lastMove( )
	{
		return last;
	}
	
	/**
	 * Setter for last
	 * @param newLast is char for last
	 */
	public void setLast( char newLast )
	{
		last = newLast;
	}
	
	/**
	 * Getter for num
	 * @return num
	 */
	private int NumberOfBoards( )
	{
		return num;
	}
	
	
	/**
	 * This the method for all the moves that the user played is valid for solution
	 * @param boards all the moves that user played
	 * @return if it valid or not
	 */
	public static boolean validMoves(AbstractBoard[] boards )
	{
		int x = boards[0].getSize();
		int y = boards[0].getWidth();
		int count = 1;
		int[][] Final = new int[x][y];
		
		for( int i = 0; i < x; i++ )
		{
			for( int j = 0; j < y; j++ )
			{
				if( i == x - 1 && j == y - 1)
					Final[i][j] = -1;
				else
					Final[i][j] = count++;
			}
		}
		AbstractBoard temp = boards[boards.length - 1];
		
		for( int i = 0; i < x; i++ )
		{
			for( int j = 0; j < y; j++ )
			{
				if( temp.cell(i, j) != Final[i][j] )
					return false;
			}
		}
		if( boards.length >= 2) {
			int compareX, compareY;
			for( int i = 0; i < boards.length - 1; i++)
			{
				x = boards[i].getLocationX();
				y = boards[i].getLocationY();
				
				compareX = boards[i + 1].getLocationX();
				compareY = boards[i + 1].getLocationY();
				
				if( Math.abs( x - compareX ) != 1 && Math.abs( x - compareX ) != 1)
				{
					if( x != compareX || y != compareY )
						return false;
				}
			}
		}
		return true;
	}
}
