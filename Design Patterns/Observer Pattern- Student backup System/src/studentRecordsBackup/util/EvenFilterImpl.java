package studentRecordsBackup.util;
/** Description of EvenFilterImpl
 * @author KUNAL ZANTYE
 * @description implementation of even filter 
 */
public class EvenFilterImpl implements OddEvenFilterI {

	@Override
	public Boolean checkOddEven(int num) {
		if(num%2==0)
			return true;
		else
		return false;
	}
	
}
