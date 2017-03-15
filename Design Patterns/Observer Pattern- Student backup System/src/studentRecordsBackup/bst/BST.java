package studentRecordsBackup.bst;

/** Description of BST Class
 * @author KUNAL ZANTYE
 * @description insert the node in a BST tree, 
 * 				Method to print the tree inOrder
 * 				Print the Sum of the tree
 */
public class BST {
	
	/**
	 * @name insert
	 * @param Integer bnum
	 * @description Recursively call insert, to insert the node in the tree 
	 */
	Node newNode =null;
	public  Node insert(Node root, int bnum)
	{
		if(root==null)
		{
			newNode=root=new Node(bnum);
			//list.add(data);
		}
		else 
		{
			if (Integer.compare(bnum,root.BNumber)<0)
			root.left=insert(root.left,bnum);
				else if(Integer.compare(bnum,root.BNumber)>0)
			root.right=insert(root.right,bnum);
		}
		return newNode;
	}
	
	/**
	 * @name printInorder
	 * @param -
	 * @description Prints the tree inOrder 
	 */
	int sum=0;
	public void printInorder(Node root,int i)
	{
		if(root!=null)
		{
			printInorder(root.left,i);
			if(i==0)
			{System.out.print(" " +root.BNumber);
			
			}
			sum=sum+root.BNumber;
			
			printInorder(root.right,i);
		}
	}
	/**
	 * @name incrementUpdate
	 * @description increments the tree with the update value 
	 * @param - root node and the Update value
	 */
	
	public void incrementUpdate(Node root,int UPDATE_VALUE)
	{
		if(root!=null)
		{
			incrementUpdate(root.left,UPDATE_VALUE);
			root.setBNumber(root.BNumber+UPDATE_VALUE);
			root.notifyAllNode(UPDATE_VALUE);
			incrementUpdate(root.right,UPDATE_VALUE);
		}
		
		//
	}
	/**
	 * @name getMaxNode
	 * @description Finds the Max Node and returns it
	 * @param - Root node of the tree 
	 */	
	Node m =new Node(0);
	public Node getMaxNode(Node root){
		
		if(root!=null)
		{
			if(m.BNumber<root.BNumber)
				m=root;
			
			if(root.left!=null)
			getMaxNode(root.left);
			
			if(root.right!=null)
			getMaxNode(root.right);
		}
		return m;
	}
	/**
	 * @name update
	 * @description Finds the Max Node of the orignal tree and updates the backups
	 * @param - Root Node and the Update value 
	 */
	public void update(Node root,int UPDATE_VALUE)
	{
		Node max= getMaxNode(root);
		incrementUpdate(root, UPDATE_VALUE);
		max.setBNumber(max.BNumber+UPDATE_VALUE);
		
	}
	
	/**
	 * @name printBSum
	 * @description Calculate the Sum of all Nodes values of the tree
	 * @param - root Node 
	 */
	public void printBSum(Node root) {
		sum=0;
		printInorder(root,1);
	    	System.out.print(sum);
	    }
	
	
}
