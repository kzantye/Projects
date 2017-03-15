package genericCheckpointing.util;

/** Description of MyAllTypesSecon Class
* @author KUNAL ZANTYE
* @description this class is a POJO class
*/
public class MyAllTypesSecond extends SerializableObject {
	private double myDoubleT; 
	private float myFloatT; 
	private short myShortT; 
	private char myCharT;
	
	public double getMyDoubleT() {
		return myDoubleT;
	}
	public void setMyDoubleT(double myDoubleT) {
		this.myDoubleT = myDoubleT;
	}
	public float getMyFloatT() {
		return myFloatT;
	}
	public void setMyFloatT(float myFloatT) {
		this.myFloatT = myFloatT;
	}
	public short getMyShortT() {
		return myShortT;
	}
	public void setMyShortT(short myShortT) {
		this.myShortT = myShortT;
	}
	public char getMyCharT() {
		return myCharT;
	}
	public void setMyCharT(char myCharT) {
		this.myCharT = myCharT;
	}
	
	public MyAllTypesSecond() {
		// TODO Auto-generated constructor stub
	}
	
	public MyAllTypesSecond(double myDoubleTIn ,	float myFloatTIn ,	short myShortTIn,	char myCharTIn ) {
		// TODO Auto-generated constructor stub
		myDoubleT=myDoubleTIn;
		myFloatT=myFloatTIn;
		myShortT=myShortTIn;
		myCharT=myCharTIn;
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "Class Name:MyAllTypesSecond \n myDoubleT:"+myDoubleT+"\n myFloatT:"+myFloatT+"\n myShortT:"+myShortT+"\n myCharT:"+myCharT;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		MyAllTypesSecond o=(MyAllTypesSecond) obj;
		boolean flag=true;
		if(getMyDoubleT() != o.getMyDoubleT())
			return false;
		else if(getMyFloatT() != o.getMyFloatT())
			return false;
		else if(getMyShortT() != o.getMyShortT())
			return false;
		else if(getMyCharT() != o.getMyCharT())
			return false;
		
	return flag;
	}
	
	@Override
	public int hashCode() {
		// TODO Auto-generated method stub
		return super.hashCode();
	}
	
}
