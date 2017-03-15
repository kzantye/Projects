package studentRecordsBackup.bst;

import studentRecordsBackup.util.OddEvenFilterI;

/** Description of SubjectI
 * @author KUNAL ZANTYE
 * @description Subject Interface 
 */
public interface SubjectI {
	public void registerNode(ObserverI o,OddEvenFilterI f);
	public void removeNode(ObserverI o);
	
	void notifyAllNode(int UPDATE_VALUE);
	
}
