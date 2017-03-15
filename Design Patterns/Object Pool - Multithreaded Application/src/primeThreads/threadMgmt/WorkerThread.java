
package primeThreads.threadMgmt;


import primeThreads.store.StdoutDisplayInterface;
import primeThreads.util.FileProcessor;
import primeThreads.util.IsPrime;
import primeThreads.util.Logger;

/** Decription of Driver Class
 * @author KUNAL ZANTYE
 * @description Implements Runnable.
 */
public class WorkerThread implements Runnable  {
	FileProcessor fp;
	StdoutDisplayInterface res;
	IsPrime prime;

	/**
	 * @param 
	 * @description Constructor to instanciate FileProcessor, Results, and IsPrime
	 */
    public WorkerThread(FileProcessor fpIn, StdoutDisplayInterface resObjIn, IsPrime primeObjIn) {
    	Logger.writeMessage("WorkerThread Constructor", Logger.DebugLevel.CONSTRUCTOR);
    	fp=fpIn;
		res=resObjIn;
		prime=primeObjIn;
	}
    /**
	 * @param 
	 * @description To invoke a method in the FileProcessor to read one line as a string
	 *				Checks for the prime number
	 *				Store the prime number 
	 */
	public void run() {
	// ...
		String fileData = null;
		Logger.writeMessage("Thread's run() method is called", Logger.DebugLevel.RUN);
		do{	
			fileData = fp.readLineFromFile();
			//System.out.println(fileData);
			if(fileData!=null){
				boolean isPrime=prime.isPrime(Integer.valueOf(fileData));
				if(isPrime)
					res.savePrime(Integer.valueOf(fileData));

			}		
		}while(fileData != null);
		
    }
    

}