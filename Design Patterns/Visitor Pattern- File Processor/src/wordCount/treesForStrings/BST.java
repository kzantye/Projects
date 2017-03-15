package wordCount.treesForStrings;

import java.io.IOException;

import wordCount.visitors.TreeProcessingVisitorI;

/** Description of BST Class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description insert the node in a BST tree, 
*/

public class BST {
	private Node root=null;
	
	
	public BST(){
	}

	public void accept(TreeProcessingVisitorI visitor) throws IOException{
		visitor.visit(this);
		
	}
	/**
	 * @param 
	 * @description getter setter for root node 
	 */
	public Node getRoot() {
		return root;
	}

	public void setRoot(Node root) {
		this.root = root;
	}
	

}
