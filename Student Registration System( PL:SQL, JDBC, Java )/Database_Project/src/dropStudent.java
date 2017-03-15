import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public class dropStudent {
	
	Connection conn = Util.getDBConnection();
	ResultSet rs;

	
	public String doOperation(){
	
	
	try {
		BufferedReader readKeyBoard;
		readKeyBoard = new BufferedReader(new InputStreamReader(System.in));
		System.out.print("Please Enter B#: ");
		String student_id = readKeyBoard.readLine();
		
		
		CallableStatement cs = conn.prepareCall("begin PROJECT2.deleteStudent(:1); end;");

		// set the in parameter (the first parameter)
		cs.setString(1, student_id);

		

		// execute the stored procedure
		ResultSet s = cs.executeQuery();

		// get the out parameter result.

		System.out.println("Deleted Successfully");

		// close the result set, statement, and the connection
		cs.close();
		conn.close();

	} catch (Exception e) {
		e.getMessage();
		System.out.println(e.getMessage().split(":")[1].split("\\.")[0]);
	} 
	
	
	return null;
	}
	

}
