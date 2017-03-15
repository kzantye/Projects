package wordCount.visitors;

import java.io.IOException;

import wordCount.treesForStrings.BST;

/** Decription of TreeProcessingVisitorI Class
 * @author PRASHANT KOLHE, KUNAL ZANTYE
 * @description visitor interface
 */

public interface TreeProcessingVisitorI {
	public void visit(BST bst) throws IOException;
	}

