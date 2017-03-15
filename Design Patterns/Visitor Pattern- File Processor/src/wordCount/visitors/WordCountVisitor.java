package wordCount.visitors;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import wordCount.treesForStrings.BST;
import wordCount.treesForStrings.Node;
import wordCount.util.FileProcessor;

/** Decription of WordCountVisitor Class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description Visitor that determines the total number of words, etc.
 */
public class WordCountVisitor implements TreeProcessingVisitorI {
	
	private long wordCount;
	private int noOfCharacters;	
	private FileProcessor fpObj;
	private Map<String,Long> frequencyMap= new HashMap<String,Long>();
	public WordCountVisitor(FileProcessor fpObjIn) {
		// TODO Auto-generated constructor stub
		fpObj=fpObjIn;
	}
	long maxFrequency=0;

	
	/**
	 * @param nodes of the tree
	 * @description To determine the total words, max frequency and max word 
	 */
	private void performComputations(Node node){
		noOfCharacters +=(node.getWord().length() *node.getFrequency());
		wordCount+=node.getFrequency();
		
		
		if(node.getFrequency()>maxFrequency){
			maxFrequency =node.getFrequency();
			frequencyMap.clear();
			frequencyMap.put(node.getWord(), node.getFrequency());
		}else if(node.getFrequency()== maxFrequency){
			frequencyMap.put(node.getWord(), node.getFrequency());
		}
		
		

	}
	/**
	 * @param nodes of the tree
	 * @description Visitor that determines the total number of words, etc. 
	 */
	@Override
	public void visit(BST bst) throws IOException {
		// TODO Auto-generated method stub
		traverseTree(bst.getRoot());
		writeToFile();
			}

	/**
	 * @param nodes of the tree
	 * @description traverse tree in order 
	 */
	public void traverseTree(Node node){
		if(node!=null){
			traverseTree(node.getLeft());
			performComputations(node);
			traverseTree(node.getRight());
		}

	}
	
	/**
	 * @param 
	 * @description writes the data to a file 
	 */
	public void writeToFile() throws IOException{
		
		for(String word:frequencyMap.keySet()){
			fpObj.writeLineToFile("The most frequently used word is: "+word+"\n");
			fpObj.writeLineToFile("The frequency of the most frequently used word is: "+frequencyMap.get(word)+"\n");	
		}
		
		fpObj.writeLineToFile("The total number of words is: "+wordCount+"\n");
	
		fpObj.writeLineToFile("The number of characters (without whitespaces) is: "+noOfCharacters+"\n");

		
	}
	
	

	public int getNoOfCharacters() {
		return noOfCharacters;
	}

	public void setNoOfCharacters(int noOfCharacters) {
		this.noOfCharacters = noOfCharacters;
	}

		
	
}
