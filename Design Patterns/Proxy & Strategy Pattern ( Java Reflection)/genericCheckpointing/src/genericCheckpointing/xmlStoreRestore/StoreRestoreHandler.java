package genericCheckpointing.xmlStoreRestore;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import genericCheckpointing.util.SerializableObject;


/** Description of XMLDeSerialization Class
* @author KUNAL ZANTYE
* @description this class is used for selecting serialization & deserialization
*/
public class StoreRestoreHandler implements InvocationHandler {

	private String file;
	BufferedWriter writer=null;
	BufferedReader reader=null;
	
	/**
	 * @name invoke
	 * @description invoke serialization or deserialization depending on strategy
	 * @return null
	 */
	@Override
	public Object invoke(Object arg0, Method arg1, Object[] arg2) throws Throwable {
		// TODO Auto-generated method stub
		
		
		
		if(arg1.getName().equals("writeObj")){
			if(arg2[1].equals("XML")){
				serializeData(arg2[0], new XMLSerialization());
				
			}
		}else if(arg1.getName().equals("readObj")){
			if(arg2[0].equals("XML")){
				return deserializeData(new XMLDeSerialization());
			}
		}

		return null;
	}
	
	/**
	 * @name openToRead
	 * @description open the file in read mode
	 * @return null
	 */
	public void openToRead() throws IOException{
		
		reader=new BufferedReader(new FileReader(file));

	}
	
	/**
	 * @name openToWrite
	 * @description open the file in write mode
	 * @return null
	 */
	public void openToWrite() throws IOException{
		
		writer=new BufferedWriter(new FileWriter(file));

	}	
		
	/**
	 * @name closeFile
	 * @description close file
	 * @return null
	 */

	public void closeFile(){
		try {
			
			if(writer!=null)
				writer.close();
			if(reader!=null)
				reader.close();
		} catch (IOException e) {
			System.err.println("Error occured while doing file operation.");
			System.exit(1);
		}
	}
	
	
	public void setFile(String nameIn){
		file=nameIn;
	}
	
	public void serializeData(Object sObject, SerStrategy sStrategy) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, IOException {
        sStrategy.processInput(sObject,writer);
	}
	
	public SerializableObject deserializeData( SerStrategy sStrategy) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, IOException, ClassNotFoundException, InstantiationException {
      return  sStrategy.processInput( reader);
	}

}
