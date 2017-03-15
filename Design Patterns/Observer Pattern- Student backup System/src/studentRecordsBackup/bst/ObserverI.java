package studentRecordsBackup.bst;
/** Description of ObserverI
 * @author KUNAL ZANTYE
 * @description Observer Interface 
 */

public interface ObserverI {
	
	public void setBNumber(int BNumber);
	public int getBNumber();
	void updateNode(ObserverI root, int UPDATE_VALUE);
}
