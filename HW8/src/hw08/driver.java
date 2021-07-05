package hw08;

/**
 * This is my driver test class for my GTUVector and GTUSet classes
 */
public class driver {

	public static void main(String[] args) {
	
		GTUSet<Integer> tempSet = new GTUSet<Integer>(Integer[].class);
		
		tempSet.insert( 0 );
		tempSet.insert( 5 );
		tempSet.insert( 10 );
		tempSet.insert( 15 );
		tempSet.insert( 20 );
		tempSet.insert( 25 );
		tempSet.insert( 30 );
		tempSet.insert( 35 );
		
		System.out.printf("tempSet:\n%s", tempSet);
		
		try
		{
			System.out.printf("Trying to insert 20 and 35 to tempSet \n");
			tempSet.insert( 20 );
			tempSet.insert( 35 );
		}
		catch( Exception e )
		{
			System.err.printf("%s\n", e.getMessage());
		}
		System.out.printf("Trying to erase 10, 17 and 25 to tempSet \n");
		tempSet.erase( 10 );
		tempSet.erase( 17 );
		tempSet.erase( 25 );
		
		System.out.printf("\nAfter erasing 10 and 25\ntempSet: \n%stempSet.contains( 15 ) = %s, tempSet.contains( 10 ) = %s\n\n"
				, tempSet, tempSet.contains( 15 ), tempSet.contains( 10 ));
		
		tempSet.clear();
		System.out.printf("After tempSet.clear()\ntempSet:\n%s\n", tempSet);
		
		GTUVector<String> tempVector = new GTUVector<String>(String[].class);
		
		tempVector.insert("Türker");
		tempVector.insert("Naime");
		tempVector.insert("Çaðla");
		tempVector.insert("Ege");
		tempVector.insert("Mert");
		tempVector.insert("Görkem");
		tempVector.insert("Alper");
		tempVector.insert("Sevgi");
		tempVector.insert("Ali");
		System.out.printf("tempVector:\n%s", tempVector);
		
		System.out.printf("Trying to erase \"Türker\", \"Naime\" and \"Jacob\" to tempSet \n");
		tempVector.erase("Türker");
		tempVector.erase("Naime");
		tempVector.erase("Jacob");
		System.out.printf("\nAfter erasing \"Türker\" and \"Naime\"\ntempVector:\n%stempVector.contains( \"Çaðla\" ) = %s, tempVector.contains( \"Türker\" ) = %s\n\n",
				tempVector, tempVector.contains("Çaðla"), tempVector.contains("Türker"));
		
		tempVector.clear();
		System.out.printf("After tempVector.clear()\ntempVector: \n%s\n", tempVector);
		
	}

}
