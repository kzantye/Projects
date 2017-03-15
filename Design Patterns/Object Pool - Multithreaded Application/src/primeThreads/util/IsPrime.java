
package primeThreads.util;
/** Decription of Driver Class
* @author KUNAL ZANTYE
* @description Check whether the input number is prime.
*/

public class IsPrime {

	/**
	 * @param Integer as input
	 * @description Check whether the input number is prime. Returns true if the the input is true 
	 */
	public boolean isPrime(int input){
		if(input%2 ==0){
			return false;
		}
		
		return true;
		
	}

}
