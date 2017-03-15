package primeThreads.util;

import java.io.*;
import java.lang.String;

/** Decription of Driver Class
 * @author KUNAL ZANTYE
 * @description performs file operations
 */
public class FileProcessor {
	BufferedReader br;
	/**
	 * @param String filename
	 * @description Accepts the input file name and create input stream 
	 */
	public FileProcessor(String filename){
		try {
			 br = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			System.out.println("File Doesn't Exist");
			e.printStackTrace();
			System.exit(1);
		}
		
	
	}
	  /**
	 * @return one line as a String 
	 */
	public synchronized String readLineFromFile() {
			String line;
				try {
					if((line = br.readLine()) != null) 
						return line;
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}			
			return null;
	}

}
