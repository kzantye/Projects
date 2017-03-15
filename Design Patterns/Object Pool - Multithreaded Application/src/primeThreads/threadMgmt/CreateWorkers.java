
package primeThreads.threadMgmt;


import primeThreads.store.StdoutDisplayInterface;
import primeThreads.util.FileProcessor;
import primeThreads.util.IsPrime;
import primeThreads.util.Logger;

/** Decription of Driver Class
 * @author KUNAL ZANTYE
 * @description Creates number of thread
 */
public class CreateWorkers  {
	
	FileProcessor fp;
	StdoutDisplayInterface res;
	IsPrime prime;
	
	/**
	 * @param 
	 * @description Constructor to instanciate FileProcessor, Results, and IsPrime
	 */
	public CreateWorkers(FileProcessor fpIn, StdoutDisplayInterface resObjIn, IsPrime primeObjIn) {
		// TODO Auto-generated constructor stub
		Logger.writeMessage("CreateWorker Constructor", Logger.DebugLevel.CONSTRUCTOR);
		fp=fpIn;
		res=resObjIn;
		prime=primeObjIn;
	}
	/**
	 * @param 
	 * @description Creates numbers of threads by the user
	 */
	public void startWorkers(String string) throws InterruptedException {
		// TODO Auto-generated method stub
		int noOfThreads=Integer.parseInt(string);
		WorkerThread w= new WorkerThread(fp,res,prime);
		Thread[] threads=new Thread[noOfThreads];
		
		for(int i=0;i<noOfThreads;i++){
			threads[i] = new Thread(w);
			threads[i].start();
		}
		for(int i=0;i<noOfThreads;i++){
			threads[i].join();
		}
		
	}

    // this class has the method startWokers(...)

}