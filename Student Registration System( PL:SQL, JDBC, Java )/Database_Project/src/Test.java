
public class Test {

	public static void main(String[] args) {
		String test="ORA-20000: The classid is invalid.ORA-06512: at SYSTEM.PROJECT3, line 106ORA-06512: at line 1";
		String[] error=test.split(":");
		String errorString=error[1];
		String[] error1=errorString.split("\\.");
		System.out.println(error1[0]);
		
	}
}
