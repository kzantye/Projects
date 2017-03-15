
package genericCheckpointing.driver;

import java.util.Vector;

import genericCheckpointing.server.RestoreI;
import genericCheckpointing.server.StoreI;
import genericCheckpointing.server.StoreRestoreI;
import genericCheckpointing.util.MyAllTypesFirst;
import genericCheckpointing.util.MyAllTypesSecond;
import genericCheckpointing.util.ProxyCreator;
import genericCheckpointing.util.SerializableObject;
import genericCheckpointing.xmlStoreRestore.StoreRestoreHandler;

// import the other types used in this file

/** Description of Driver Class
* @author KUNAL ZANTYE
* @description Main file also contain main(..)
* @args reads the command line argument, input file and update value
*/
public class Driver {
    
    public static void main(String[] args) {
    	
    	try {
				
			if(args.length < 3 || args.length > 3)
			{System.out.println("Enter mode,N and output file name values");
				System.exit(1);
			}
			
			String mode=args[0];
			int n=Integer.parseInt(args[1]);
			String fileName=args[2];
		
			/*String mode="deser";
			int n=2;
			String fileName="src/output.txt";*/
		
			

	
	ProxyCreator pc = new ProxyCreator();
	
	StoreRestoreHandler handle=new StoreRestoreHandler();
	
	StoreRestoreI cpointRef = (StoreRestoreI) pc.createProxy(
								 new Class[] {
								     StoreI.class, RestoreI.class
								 }, 
								 handle
								 );
		
	

	MyAllTypesFirst myFirst;
	MyAllTypesSecond  mySecond;
	
	Vector<SerializableObject> ser=new Vector<>();
	handle.setFile(fileName);
	if(mode.equals("serdeser")){
		handle.openToWrite();
		for (int i=0; i<n; i++) {

		    
			String str=String.valueOf(i+n);
		    myFirst = new MyAllTypesFirst(i+n, i+n, str, true);
		    mySecond = new MyAllTypesSecond(i+n, i+n, Short.valueOf((i+n)+""), 'a');

		    ((StoreI) cpointRef).writeObj(myFirst, "XML");
		    ((StoreI) cpointRef).writeObj(mySecond, "XML");

		    ser.add(myFirst);
		    ser.add(mySecond);
		    

		}
		handle.closeFile();
		
		handle.openToRead();
		SerializableObject obj=null;
		

		Vector<SerializableObject> deser=new Vector<>();
		for (int j=0; j<2*n; j++) {

			obj = ((RestoreI) cpointRef).readObj("XML");
			deser.add(obj);
		}
		
		handle.closeFile();
		
		int count=0;
		for(int i=0;i<2*n;i++){
			if(!ser.get(i).equals(deser.get(i))){
				count++;
			}
		}
		
		System.out.println(count+" mismatched objects");
	}else if(mode.equals("deser")){
		handle.openToRead();
		
		SerializableObject obj=null;

		Vector<SerializableObject> deser=new Vector<>();
		for (int j=0; j<2*n; j++) {

			obj = ((RestoreI) cpointRef).readObj("XML");
		    // FIXME: store myRecordRet in the vector
			deser.add(obj);
		}
		
		handle.closeFile();
		
		
		for(int i=0;i<2*n;i++){
			System.out.println(deser.get(i));
		}
	}

	
    	}catch(Exception e){
    		System.out.println("Error occured while serializing or deserializing");
    		System.exit(1);
    	}
    }
}