package studentRecordsBackup.util;
/** Description of OddFilterImpl
 * @author KUNAL ZANTYE
 * @description implementation of odd filter 
 */
public class OddFilterImpl implements OddEvenFilterI {
	public Boolean checkOddEven(int num) {
		if(num%2==0)
			return false;
		else
		return true;
	}

}
