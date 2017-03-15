package studentRecordsBackup.bst;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import studentRecordsBackup.util.OddEvenFilterI;

/** Description of Node class
 * @author KUNAL ZANTYE
 * @description each node of the the tree, 
 * 				implements the subject interface and observer interface
 */
public class Node implements SubjectI,ObserverI{
	
	public int BNumber;
	public Node left;
	public Node right;
	public Node(int BNumIn)
	{
		left=right=null;
		BNumber=BNumIn;
	}
	/**
	 * @name getBNumber, setBnumber
	 * @description getter setter method of BNumber
	 * @param - 
	 */
	public int getBNumber() {
		return BNumber;
	}
	public void setBNumber(int bNumber) {
		BNumber = bNumber;
	}
	Map<ObserverI, OddEvenFilterI> map= new HashMap<ObserverI, OddEvenFilterI>();
	
	/**
	 * @name updateNode
	 * @description implementation of method of ObjectI to update the nodes
	 * @param - oberver interface object and update value
	 */
	public void updateNode(ObserverI root,int UPDATE_VALUE) {
		root.setBNumber(root.getBNumber()+UPDATE_VALUE);
	}
	
	/**
	 * @name registerNode
	 * @description implementation of method of SubjectI to add the observer node.
	 * @param - oberver interface object and filter object
	 */	
	public void registerNode(ObserverI o, OddEvenFilterI f) {
		map.put(o, f);
		
	}
	/**
	 * @name removeNode
	 * @description implementation of method of SubjectI to de-register the observer node.
	 * @param - oberver interface object 
	 */	
	public void removeNode(ObserverI o) {
		if(!map.isEmpty())
		map.remove(o);
	}
	
	/**
	 * @name notifyAllNode
	 * @description implementation of method of SubjectI to notify the observer node if there is any update
	 * @param - Update Value 
	 */	
	public void notifyAllNode(int UPDATE_VALUE) {
		for(Entry<ObserverI, OddEvenFilterI> entry: map.entrySet())
		{
			if(entry.getValue().checkOddEven(UPDATE_VALUE) )//calls check on filter by passing updatevalue
				entry.getKey().updateNode(entry.getKey(), UPDATE_VALUE);
		}
		
	}
}
