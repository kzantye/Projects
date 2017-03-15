package wordCount.treesForStrings;

import java.io.IOException;

import wordCount.visitors.TreeProcessingVisitorI;
/** Description of Node class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description each node of the the tree
 */
public class Node {
	
	private String word="";
	private long hash;
	private Node right=null;
	private Node left=null;
	private long frequency=1;
	private long charCount;
	
	public Node(String wordIn){
		this.word=wordIn;
		this.hash=wordIn.hashCode();
	}
	
	/**
	 * @param 
	 * @description getter setter for node 
	 */
	public String getWord() {
		return word;
	}

	public void setWord(String word) {
		this.word = word;
	}

	/**
	 * @param 
	 * @description getter setter for hash code 
	 */

	public long getHash() {
		return hash;
	}

	public void setHash(long hash) {
		this.hash = hash;
	}
	
	/**
	 * @param 
	 * @description getter setter for word frequency 
	 */
	public long getFrequency() {
		return frequency;
	}
	public void setFrequency(long frequency) {
		this.frequency = frequency;
	}

	/**
	 * @param 
	 * @description getter setter for character count
	 */
	public long getCharCount() {
		return charCount;
	}

	public void setCharCount(long charCount) {
		this.charCount = charCount;
	}

	/**
	 * @param 
	 * @description getter setter for right child 
	 */

	public Node getRight() {
		return right;
	}

	public void setRight(Node right) {
		this.right = right;
	}

	/**
	 * @param 
	 * @description getter setter for left child
	 */
	public Node getLeft() {
		return left;
	}

	public void setLeft(Node left) {
		this.left = left;
	}

}
