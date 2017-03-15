
package primeThreads.driver;


import primeThreads.store.Results;

import primeThreads.store.StdoutDisplayInterface;
import primeThreads.threadMgmt.CreateWorkers;
import primeThreads.util.FileProcessor;
import primeThreads.util.IsPrime;
import primeThreads.util.Logger;

/** Decription of Driver Class
* @author KUNAL ZANTYE
* @description Main file also contain main(..)
*/

public class Driver{
	/**
	 * @param args
	 */
	public static void main(String args[]) {
		try {
			if(args.length < 3 || args.length > 3)
			{
				System.out.println("Enter Filename, no of threads and debug values");
				System.exit(1);
			}
			//System.out.println("Enter the name of the input file");
			
			FileProcessor fp =new FileProcessor(args[0]);
	
			StdoutDisplayInterface res= new Results();
			IsPrime prime = new IsPrime();
			
			CreateWorkers workers=new CreateWorkers(fp, res, prime);
			//System.out.println("Enter the number of threads to create");
			Logger.setDebugValue(Integer.parseInt(args[2]));	
			if(Integer.parseInt(args[1]) < 1 || Integer.parseInt(args[1]) > 5) 
				System.out.println("Enter no of threads between 1 and 5");
			else workers.startWorkers(args[1]);
			
			if(Integer.parseInt(args[2]) < 0 || Integer.parseInt(args[2]) > 4) 
				System.out.println("Enter Debug Value between 0 and 4");
			
			
			
			//workers.startWorkers("3");
				res.writeSumToScreen();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		

	} // end main(...)

} // end public class Driver

