package wordCount.util;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.List;


/** Decription of Driver Class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description performs file operations
 */
public class FileProcessor {
	BufferedReader br=null;
	BufferedWriter wr=null;
	String fileName="";
	public FileProcessor(BufferedReader readerIn,BufferedWriter writerIn,String fileNameIn) {
		this.br=readerIn;
		this.wr=writerIn;
		this.fileName=fileNameIn;
	}
	
	/**
	 * @param String filename
	 * @description Accepts the input file name and create input stream 
	 */
	
	public List<String> readLines() throws IOException{
		return Files.readAllLines(new File(fileName).toPath(),Charset.defaultCharset());

	}
	/**
	 * @param String output filename
	 * @description Accepts the output file name and writes the file 
	 */
	public void writeLineToFile(String line) throws IOException{
		wr.write(line);
	}
}
