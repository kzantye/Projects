package wordCount.visitors;

import java.io.IOException;


import wordCount.treesForStrings.BST;
import wordCount.treesForStrings.Node;
import wordCount.util.FileProcessor;

/** Decription of GrepVisitor Class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description Visitor that determines the total number of times a "search-string" occurs
 */
public class GrepVisitor implements TreeProcessingVisitorI {

	private Node node=null;
	private String searchString="";
	private FileProcessor fpObj;
	long hash;
	public GrepVisitor(String searchStringIn,FileProcessor fpObjIn) {
		// TODO Auto-generated constructor stub
		searchString=searchStringIn;
		fpObj=fpObjIn;
	}

	/**
	 * @param bst object
	 * @description grep visitor to traverse tree 
	 */
	@Override
	public void visit(BST bst) throws IOException {
		// TODO Auto-generated method stub
		hash=searchString.hashCode();
	
			traverseTree(bst.getRoot());

		writeToFile();
		
	}

	/**
	 * @param nodes of the tree
	 * @description find the word to be grep 
	 */
	public void traverseTree(Node nodeIn){
		if(nodeIn!=null){
			traverseTree(nodeIn.getLeft());
			if(nodeIn.getHash() == hash){
				node=nodeIn;
				return;
			}
			traverseTree(nodeIn.getRight());
		}

	}
	
	/**
	 * @param 
	 * @description writes the data to a file 
	 */
	public void writeToFile() throws IOException{
		if(node !=null)
			fpObj.writeLineToFile("The word <"+ searchString+"> occurs the following times: "+node.getFrequency()+"\n");
		else
			fpObj.writeLineToFile("The word <"+ searchString+"> occurs the following times: 0"+"\n");
	}

	
}
