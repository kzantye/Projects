package studentRecordsBackup.util;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

import studentRecordsBackup.bst.BST;
import studentRecordsBackup.bst.Node;

/** Description of BSTBuilder Class
 * @author KUNAL ZANTYE
 * @description performs file operations and creating tree operations
 */
public class BSTBuilder {
	
	BST tree = new BST();
	BST b1 = new BST();
	BST b2 = new BST();
	
	Node treeRoot,b1Root,b2Root;
	
	 /**
	  * @name readLineFromFile
	 * @description read a line from the file and insert the node in three trees
	 * @param file name 
	 */
	public void readLineFromFile(String filename) {
		String line;
			try {
				BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(filename)));
				OddEvenFilterI even=new EvenFilterImpl();
				OddEvenFilterI odd=new OddFilterImpl();
				Node node=null;
				Node node1=null;
				Node node2=null;
				if((line = br.readLine()) != null)
				{
					treeRoot=node=tree.insert(node,Integer.valueOf(line));	
					
					b1Root=node1=b1.insert(node1,Integer.valueOf(line));
					treeRoot.registerNode(node1,even);
					
					b2Root=node2=b2.insert(node2,Integer.valueOf(line));
					treeRoot.registerNode(node2,odd);
				}
				while((line = br.readLine()) != null) 
				{
					node=tree.insert(node,Integer.valueOf(line));
					
					node1=b1.insert(node1,Integer.valueOf(line));
					node.registerNode(node1,even);
					
					node2=b2.insert(node2,Integer.valueOf(line));
					node.registerNode(node2,odd);
					
				
				}
				br.close();	
			}catch (FileNotFoundException e) {
				System.out.println("File Doesn't Exist");
				System.exit(1);
			} catch (NumberFormatException e) {
				System.out.println("Improper contents of the file: File must Contain numbers");
				System.exit(1);
			} catch (IOException e) {
				System.out.println("Error in reading file: " + filename);    
				System.exit(1);
			}	
			catch (Exception e) {
				System.out.println("Error in executing program " + filename);    
				System.exit(1);
			}	
	}
	/**
	 * @name display
	 * @description display the three bst
	 * @param void 
	 */
	
	public void display()
	{
		System.out.print("\nPrinting Tree Inorder:\n ");
		System.out.println("\nOrignal Tree: ");
		tree.printInorder(treeRoot,0);
		System.out.println("\nBackup1 Tree: ");
		b1.printInorder(b1Root,0);
		System.out.println("\nBackup2 Tree: ");
		b2.printInorder(b2Root,0);
		System.out.println();
	}
	/**
	 * @name sumNode
	 * @description calculate the sum of individual tree
	 * @param void 
	 */
	public void sumNode()
	{
		System.out.print("\nPrinting SUM:\n ");
		System.out.print("\nSum of Orignal Tree: ");
		tree.printBSum(treeRoot);
		System.out.print("\nSum of Backup1 Tree: ");
		b1.printBSum(b1Root);
		System.out.print("\nSum of Backup2 Tree: ");
		b2.printBSum(b2Root);
	}
	/**
	 * @name updateBST
	 * @description Update the three tree with update value on the max node and depending on filter
	 * @param Update value from the user
	 */
	public void updateBST(int UPDATE_VALUE)
	{
		tree.update(treeRoot,UPDATE_VALUE);
	}
}
