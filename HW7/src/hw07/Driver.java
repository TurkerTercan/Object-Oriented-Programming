package hw07;

import java.util.Scanner;

public class Driver {

	/**
	 * This is my driver main class
	 * I tested my methods and classes here
	 */
	public static void main(String[] args) {
		
		boolean check = false;
		boolean goBack = true;
		boolean is2D = false, is1D = false;
		int choice = -1;
		int size = -1, width = -1;
		AbstractBoard board;
		int sizeBoard = 0;
		BoardArray2D boards2D[] = new BoardArray2D[100];
		BoardArray1D boards1D[] = new BoardArray1D[100];
		
		Scanner getter = new Scanner(System.in);
		char ch;

		System.out.println("Welcome to the board game");
		while( !check )
		{	
			while( size < 0 )
			{
				System.out.println("Enter your board's size: ");
				size = getter.nextInt();
				if( size < 0 )
					System.out.println("Size can not be non positive integer");
			}
			while( width < 0 )
			{
				System.out.println("Enter your board's width: ");
				width = getter.nextInt();
				if( width < 0 )
					System.out.println("Width can not be non positive integer");
			}
			
			System.out.printf("1- Create BoardArray2D\n2- Create BoardArray1D\n");
			while( choice < 1 || choice > 2)
			{
				choice = getter.nextInt();
				if( choice < 1 || choice > 2)
					System.out.println("You can enter 1 or 2. Try Again!");
			}
			if( choice == 1 ) {
				board = new BoardArray2D(size, width);
				boards2D[sizeBoard] = new BoardArray2D( board );
				sizeBoard++;
				is2D = true;
				goBack = false;
			}
			else {
				board = new BoardArray1D(size, width);
				boards1D[sizeBoard] = new BoardArray1D( board );
				goBack = false;
				is1D = true;
				sizeBoard++;
			}
			
			while( !goBack )
			{
				System.out.printf("Your Board:\n%s", board);
				System.out.printf("Choices:\n"
						+ "L: LeftMove\t"
						+ "R: RightMove\t"
						+ "U: UpMove\t"
						+ "D: DownMove\n"
						+ "S: Shufle\t"
						+ "E: Read from file\t"
						+ "V: Check if your moves valid or not\n"
						+ "W: Write to file\t"
						+ "P: Print board again\n"
						+ "C: Go back and choice board again\n"
						+ "Q: Close the program\n");
				
				ch = getter.next().charAt(0);
				switch( ch )
				{
					case 'L': board.move( ch ); 
						if( is2D )
							boards2D[sizeBoard] = new BoardArray2D( board );
						if( is1D )
							boards1D[sizeBoard] = new BoardArray1D( board );
						sizeBoard++;
						break;
					case 'R': board.move( ch );
						if( is2D )
							boards2D[sizeBoard] = new BoardArray2D( board );
						if( is1D )
							boards1D[sizeBoard] = new BoardArray1D( board );
						sizeBoard++;
						break;
					case 'U': board.move( ch ); 
						if( is2D )
							boards2D[sizeBoard] = new BoardArray2D( board );
						if( is1D )
							boards1D[sizeBoard] = new BoardArray1D( board );
						sizeBoard++;
						break;
					case 'D': board.move( ch );
						if( is2D )
							boards2D[sizeBoard] = new BoardArray2D( board );
						if( is1D )
							boards1D[sizeBoard] = new BoardArray1D( board );
						sizeBoard++;
						break;
					case 'S': board.reset(); board.randomMoves(); sizeBoard = 0;
						break;
					case 'E':
						try
						{
							board.readFromFile(); 
							sizeBoard = 0;
						}
						catch( Exception e )
						{
							System.out.println(e.getMessage());
						}
						break;
					case 'V':
						AbstractBoard boards[] = new AbstractBoard[sizeBoard];
						for( int i = 0; i < sizeBoard; i++ )
						{
							if( is2D )
								boards[i] = boards2D[i];
							if( is1D )
								boards[i] = boards1D[i];
						}
						if(AbstractBoard.validMoves( boards ))
							System.out.println("Your moves are valid");
						else
							System.out.println("Your moves are not valid");
						break;
					case 'W': board.writeToFile();
						break;
					case 'P': System.out.println(board.toString());
						break;
					case 'C': goBack = true;
						break;
					case 'Q': goBack = true; check = true;
						break;
					default: System.out.println("Wrong Choice! Try Again");
				}
				
			}
			size = -1;
			width = -1;
			choice = -1;
			sizeBoard = 0;
		}
		getter.close();
	}
}
