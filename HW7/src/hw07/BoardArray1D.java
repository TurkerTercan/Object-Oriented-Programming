package hw07;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class BoardArray1D extends AbstractBoard{
	
	/**
	 * One dimensional array
	 */
	private int[] board;

	/*
	 * When i tried to use two different scanners for write and read functions, i'd received NoSuchElementException
	 * to avoid that i used one scanner for both.
	 */
	private Scanner terminal = new Scanner(System.in);
	
	/**
	 * Swaps BB to that tile
	 * @param x is tile's x coordinate
	 * @param y is tile's y coordinate
	 */
	private void swapBlank( int x, int y ) 
	{
		board[this.getLocationX() * this.getWidth() + this.getLocationY()] = this.cell(x, y);
		board[x * getWidth() + y] = -1;
		this.setLocationX( x );
		this.setLocationY( y );
	}
	
	/**
	 * BB's move down method
	 * It will not allow used to moveDown if there is a wall or empty
	 */
	private void moveDown() 
	{
		if( this.getLocationX() != this.getSize() - 1 && this.cell( this.getLocationX( ) + 1, this.getLocationY( ) ) != 0 )
		{	
			this.swapBlank( this.getLocationX( ) + 1, this.getLocationY( ) );
			this.increaseMoves();
			this.setLast('D');
			this.checkIsFinal();
		}
		else if( this.getLocationX() == this.getSize() - 1 )
			System.out.println("Unavailable to move: Down side is empty");
		else if( this.cell( getLocationX( ) + 1, getLocationY( ) ) == 0 )
			System.out.println("Unavailable to move: Down side is a wall");
	}
	
	/**
	 * BB's move up method
	 * It will not allow used to moveUp if there is a wall or empty
	 */
	private void moveUp() 
	{
		if( this.getLocationX() != 0 && this.cell( this.getLocationX( ) - 1, this.getLocationY( ) ) != 0)
		{
			this.swapBlank(getLocationX() -1, getLocationY());
			this.increaseMoves();
			this.setLast('U');
			this.checkIsFinal();
		}
		else if( this.getLocationX() == 0 )
			System.out.println("Unavailable to move: Up side is empty");
		else if( this.cell(getLocationX() -1, getLocationY()) == 0)
			System.out.println("Unavailable to move: Up side is a wall");
	}
	
	/**
	 * BB's move right method
	 * It will not allow used to moveRight if there is a wall or empty
	 */
	private void moveRight() 
	{
		if( this.getLocationY() != this.getWidth() - 1 && this.cell(getLocationX(), getLocationY() + 1) != 0 )
		{
			this.swapBlank(getLocationX(), getLocationY() + 1);
			this.increaseMoves();
			this.setLast('R');
			this.checkIsFinal();
		}
		else if( this.getLocationY() == this.getWidth() - 1 )
			System.out.println("Unavailable to move: Right side is empty");
		else if( this.cell(getLocationX(), getLocationY() + 1) == 0 )
			System.out.println("Unavailable to move: Right side is a wall");
	}
	
	/**
	 * BB's move left method
	 * It will not allow used to moveLeft if there is a wall or empty
	 */
	private void moveLeft() 
	{
		if( this.getLocationY() != 0 && this.cell(getLocationX(), getLocationY() - 1) != 0 )
		{
			this.swapBlank(getLocationX(), getLocationY() - 1);
			this.increaseMoves();
			this.setLast('L');
			this.checkIsFinal();
		}
		else if( this.getLocationY() == 0 )
			System.out.println("Unavailable to move: Left side is empty");
		else if( this.cell(getLocationX(), getLocationY() - 1) == 0 )
			System.out.println("Unavailable to move: Left side is a wall");
	}
	
	/**
	 * Basic constructor
	 * @param newX size of x coordinates
	 * @param newY size of y coordinates
	 */
	public BoardArray1D( int newX, int newY )
	{
		super( newX, newY );
		this.randomMoves( );
	}
	
	/**
	 * I used this constructor to get clone of the current board
	 * @param clone clone is the current board
	 */
	public BoardArray1D( AbstractBoard clone )
	{
		super( clone );
	}
	
	/**
	 * it makes 5 random moves
	 */
	public void randomMoves( ) 
	{
		Random rand = new Random( );
		int n;
		for( int i = 0; i < 5 ; i++)
		{
			int x = this.getLocationX();
			int y = this.getLocationY();
			n = rand.nextInt( 4 );
			if( n == 0 & this.lastMove( ) != 'D' && this.getLocationX( ) != 0 )
				this.move( 'U' );
			else if( n == 1 && this.lastMove( ) != 'R' && this.getLocationY() != 0 )
				this.move( 'L' );
			else if( n == 2 && this.lastMove( ) != 'L' && this.getLocationY() != this.getWidth() - 1 )
				this.move( 'R' );
			else if( n == 3 && this.lastMove( ) != 'U' && this.getLocationX() != this.getSize() - 1 )
				this.move( 'D' );
			if( x != this.getLocationX() || y != this.getLocationY() )
				this.setMoves( this.numberOfMoves() - 1);
		}
	}
	
	/**
	 * Initialize one dimensional board
	 */
	public void createBoard( )
	{
		board = new int[ this.getSize( ) * this.getWidth( ) ];
		this.setLocationX( this.getSize( ) - 1 );
		this.setLocationY( this.getWidth( ) - 1 );
	}
	
	/**
	 * This method finds and returns integer in that positon
	 * @param x is x coordinate
	 * @param y is y coordinate
	 * @return integer in that position
	 */
	public int getTile( int x, int y )
	{
		return board[x * getWidth() + y];
	}
	
	@Override
	protected void setTile( int tile, int x, int y )
	{
		board[x * getWidth() + y] = tile;
	}
	
	@Override
	public void move( char direction )
	{
		switch( direction )
		{ 
			case 'L': this.moveLeft( );
			break;
			case 'R': this.moveRight( );
			break;
			case 'U': this.moveUp( );
			break;
			case 'D': this.moveDown( );
			break;
			default: System.out.printf("Wrong Decision!\n");
		}
	}
	
	@Override
	public void writeToFile( )
	{
		System.out.println("Enter your file's \\path\\fileName:");
		String fileName = new String(terminal.nextLine());
		File text = new File(fileName);
		
		try
		{
			if(text.createNewFile())
				System.out.println("File created: " + text.getName());
			else
				System.out.println("File already exist in that location");
			FileWriter writer = new FileWriter(text);
			
			for( int i = 0; i < this.getSize(); i++ )
			{
				for( int j = 0; j < this.getWidth(); j++ )
				{
					if(this.cell(i, j) == -1)
					{
						writer.write("bb ");
					}
					else if( this.cell(i, j) < 10 )
						writer.write("0" + this.cell(i, j) + " ");
					else if( this.cell(i, j) >= 10 )
						writer.write(this.cell(i, j) + " ");
				}
				if( i != this.getSize() - 1)
					writer.write("\n");
			}
			writer.close();
		}
		catch( IOException e )
		{
			System.out.println(e.getMessage() + " writeToFile closes..\n");
		}	
	}
	
	@Override
	public void readFromFile( ) throws FileNotFoundException
	{
		System.out.println("Enter your file's path: ");
		String fileName = new String(terminal.nextLine());
		File text = new File(fileName);
		Scanner reader = new Scanner(text);
		
		int x = 0, y = 0;
		String temp;
		while( reader.hasNext() )
		{
			temp = new String(reader.nextLine());
			x++;
			y = (temp.length() + 1) / 3;
		}
		this.setSize(x, y);
		
		reader.close();
		reader = new Scanner(text);
		x = 0;
		y = 0;
		char c1, c2;
		int val;
		while( reader.hasNext() )
		{
			String read = new String(reader.nextLine());
			y = 0;
			for( int i = 0; i < read.length(); i+=3)
			{
				c1 = read.charAt( i );
				c2 = read.charAt( i + 1 );
				if( c1 == 'b' && c2 == 'b' ) {
					this.setTile( -1, x, y );
					this.setLocationX(x);
					this.setLocationY(y);
				}
				else
				{
					val = Character.getNumericValue(c1) * 10 + Character.getNumericValue(c2);
					this.setTile(val, x, y);
				}
				y++;	
			}
			x++;
		}
		reader.close();
	}
	
	@Override
	public String toString()
	{
		StringBuilder build = new StringBuilder();
		build.append(super.toString());
		
		for( int i = 0; i < this.getSize(); i++ )
		{
			for( int j = 0; j < this.getWidth(); j++ )
			{
				if( this.cell(i, j) == -1 )
					build.append("bb ");
				else if( this.cell(i, j) < 10)
					build.append("0" + this.cell(i, j) + " ");
				else if( this.cell(i, j) >= 10 )
					build.append(this.cell(i, j) + " ");
			}
			build.append("\n");
		}	
		
		return build.toString();
	}
}
