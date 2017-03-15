
package primeThreads.store;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

import primeThreads.util.Logger;

/** Decription of Driver Class
* @author KUNAL ZANTYE
* @description Calculates the sum of the prime numbers
*/

public class Results implements StdoutDisplayInterface {
    // appropriate data structure as private data member
	//private List<Integer> list=new ArrayList<Integer>();
	private Vector<Integer> list= new Vector<Integer>(); 
    
	/**
	 * @param 
	 * @description Calculates the sum and prints the out put
	 */	
    public void writeSumToScreen() {
	// ..
    	int sumOfPrime=0;
    	for(int i:list){
    		sumOfPrime=sumOfPrime+i;
    	}
    	System.out.println("The sum of all the prime numbers is: "+sumOfPrime);

    }
    
 // appropriate method to save prime number to the data structure

	@Override
	public void savePrime(int input) {
		Logger.writeMessage("Prime number added to the the Arraylist : "+input, Logger.DebugLevel.STOREPRIME);
		list.add(input);
		
		
	}
} 


