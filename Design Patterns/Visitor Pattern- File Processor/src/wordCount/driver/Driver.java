package wordCount.driver;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import wordCount.treesForStrings.BST;
import wordCount.util.FileProcessor;
import wordCount.visitors.GrepVisitor;
import wordCount.visitors.PopulateTreeVisitor;
import wordCount.visitors.WordCountVisitor;

/**
 * Driver     Main file also contain main(..)
 * @author    PRASHANT KOLHE, KUNAL ZANTYE
 */
public class Driver {
	
	String inputFile="";
	String outputFile="";
	int numIteration;
	String searchString="";
	
	public static void main(String[] args) {
		FileProcessor fpObj=null;
		BufferedReader br=null;
		BufferedWriter bw=null;
	try{
		Driver d=new Driver();
		d.validateArguments(args);
		d.populateInfo(args);
	
		long startTime = System.currentTimeMillis();
		for(int i=0;i<d.getNumIteration();i++){
			try{
			br=new BufferedReader(new FileReader(d.getInputFile()));
			bw=new BufferedWriter(new FileWriter(d.getOutputFile()));
			fpObj=new FileProcessor(br,bw,d.getInputFile());
			BST bst =new BST();
			
			PopulateTreeVisitor populateVisitor = new PopulateTreeVisitor(fpObj);
			WordCountVisitor countVisitor= new WordCountVisitor(fpObj);
			GrepVisitor grepVisitor = new GrepVisitor(d.getSearchString(),fpObj);
			
			bst.accept(populateVisitor);
			
			
			bst.accept(countVisitor);
			bst.accept(grepVisitor);
			}catch(FileNotFoundException e){
				System.err.println("File not found or can not be opened.");
				System.exit(1);
			}catch(IOException e){
				System.err.println("Error while parsing/writing input/output file.");
				System.exit(1);
			}catch(Exception e){
				System.err.println("Error occured while applying visitor pattern to node or File is empty or invalid number of arguments.");
				System.exit(1);
			}finally {
				try {
					if(br!=null)
					br.close();
					if(bw!=null)
					bw.close();
				} catch (IOException e) {
					System.err.println("Error occured while closing file");
					System.exit(1);
				}
			}		
		}
		
		
		


		long finishTime = System.currentTimeMillis();
		System.out.println();
		System.out.println((finishTime-startTime)/d.getNumIteration());
		
		
		
	}catch(Exception e){
		System.err.println("Error occured while applying visitor pattern to node.");
		System.exit(1);
	}
		
	}

	private  void validateArguments(String args[]) {
		// TODO Auto-generated method stub
		
		if(args == null || args.length!=4){
			System.out.println("Invalid number of arguments.");
			System.out.println("4 Argments should be Input file name, output file name, Number of iteration and search-string.");
			System.exit(1);
		}
		try{
			if(Integer.parseInt(args[2]) <=0 ){
				System.out.println("Number of iteration should be greater than 0.");
				System.exit(1);
			}
		}catch(NumberFormatException e){
			System.err.println("Number of iteration should be integer.");
			System.exit(1);
		}
		
		File file = new File(args[1]);
		if(!file.exists()){
			try {
				file.createNewFile();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				System.err.println("Output file can not be created.");
				System.exit(1);
			}
			
		}
	}
	/**
	 * @param input command line arguments
	 * @description populate the tree data structure 
	 */
	private void populateInfo(String args[]){
		inputFile=args[0];
		outputFile=args[1];
		numIteration=Integer.valueOf(args[2]);
		searchString=args[3];
		
	
	}

	public String getInputFile() {
		return inputFile;
	}

	public void setInputFile(String inputFile) {
		this.inputFile = inputFile;
	}

	public String getOutputFile() {
		return outputFile;
	}

	public void setOutputFile(String outputFile) {
		this.outputFile = outputFile;
	}

	public int getNumIteration() {
		return numIteration;
	}

	public void setNumIteration(int numIteration) {
		this.numIteration = numIteration;
	}

	public String getSearchString() {
		return searchString;
	}

	public void setSearchString(String searchString) {
		this.searchString = searchString;
	}
	
	
	
	
	

}
