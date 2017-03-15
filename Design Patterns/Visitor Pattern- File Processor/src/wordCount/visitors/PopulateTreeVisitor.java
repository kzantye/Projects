package wordCount.visitors;

import java.io.IOException;

import java.util.List;

import wordCount.treesForStrings.BST;
import wordCount.treesForStrings.Node;
import wordCount.util.FileProcessor;

/** Decription of PopulateTreeVisitor Class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description Visitor class that reads words from a file and populates a tree data structure
 */
public class PopulateTreeVisitor implements TreeProcessingVisitorI{
	//private Node root=null;

	
	private FileProcessor fpObj;
	public PopulateTreeVisitor(FileProcessor fpObjIn) {
		// TODO Auto-generated constructor stub
		fpObj = fpObjIn;
	}

	/**
	 * @param bst instance
	 * @description Visitor  that reads words from a file 
	 */
	@Override
	public void visit(BST bst) {
    	try {
    		
    		List<String> lines=fpObj.readLines();
    		if(lines==null || lines.size()==0){
    			System.out.println("File is empty.");
    			return;
    			
    		}
    			
    			
    		String line1 =lines.get(0);
    		String[] words=line1.split("\\s+");
    		Node rootIn=new Node(words[0]);
    		bst.setRoot(rootIn);
    		
    		
    		parseRootLine(rootIn,words);
    		for(int i=1;i<lines.size();i++){
    		
    		
    		String line =lines.get(i);
    			line=line.trim();
    			if(!line.isEmpty()){
	    			words=null;
	    			words=line.split("\\s+");
					parseLine(rootIn,words);
				}
				
			}
    		
		} catch (IOException e) {
			System.err.println("Error while parsing/writing input/output file.");
			System.exit(1);
		}
	
	}
	
	/**
	 * @param root node, input word
	 * @description creates new node and inserts into bst 
	 */
	public void parseLine(Node rootIn,String[] words){
		for(int i=0;i<words.length;i++){
			Node node= new Node(words[i]);
			insert(rootIn, node);
		}
		
	}

	public void parseRootLine(Node rootIn,String[] words){
		for(int i=1;i<words.length;i++){
			Node node= new Node(words[i]);
			insert(rootIn, node);
		}
	}
	
	/**
	 * @param root node, data node
	 * @description populates the tree data structure
	 */
	public void insert(Node root,Node node ){
		
		if(node.getHash() < root.getHash()){
			if(root.getLeft()!=null)
				insert(root.getLeft(), node);
			else
				root.setLeft(node);
		}else if(node.getHash() > root.getHash()){
			if(root.getRight()!=null)
				insert(root.getRight(), node);
			else
				root.setRight(node);
		}else if(node.getHash() == root.getHash() ){
				root.setFrequency(root.getFrequency()+1);
		}
	}

}
