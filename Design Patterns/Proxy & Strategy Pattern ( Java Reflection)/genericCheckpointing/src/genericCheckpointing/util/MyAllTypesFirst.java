package genericCheckpointing.util;

public class MyAllTypesFirst extends SerializableObject{
	private int myInt ;
	private long myLong ;
	private String myString;
	private boolean myBool ;
	
	public int getMyInt() {
		return myInt;
	}
	public void setMyInt(int myInt) {
		this.myInt = myInt;
	}
	public long getMyLong() {
		return myLong;
	}
	public void setMyLong(long myLong) {
		this.myLong = myLong;
	}
	public String getMyString() {
		return myString;
	}
	public void setMyString(String myString) {
		this.myString = myString;
	}
	public boolean getMyBool() {
		return myBool;
	}
	public void setMyBool(boolean myBool) {
		this.myBool = myBool;
	}
	
	public MyAllTypesFirst() {
		// TODO Auto-generated constructor stub
	}
	
	public MyAllTypesFirst(int myIntIn ,	long myLongIn ,	String myStringIn,	boolean myBoolIn ) {
		// TODO Auto-generated constructor stub
		myInt=myIntIn;
		myLong=myLongIn;
		myString=myStringIn;
		myBool=myBoolIn;
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "Class Name:MyAllTypesFirst \n myInt:"+myInt+"\n myLong:"+myLong+"\n myString:"+myString+"\n myBool:"+myBool;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		
		MyAllTypesFirst o=(MyAllTypesFirst) obj;
		boolean flag=true;
		if(getMyInt() != o.getMyInt())
			return false;
		else if(getMyLong() != o.getMyLong())
			return false;
		else if(!getMyString().equals(o.getMyString()))
			return false;
		else if(getMyBool() != o.getMyBool())
			return false;
		
		return flag;
			
	
	}
	
	@Override
	public int hashCode() {
		// TODO Auto-generated method stub
		return super.hashCode();
	}
	
	
	
}
