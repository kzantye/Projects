package genericCheckpointing.xmlStoreRestore;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;


import genericCheckpointing.util.DeserializeTypes;
import genericCheckpointing.util.SerializableObject;

/** Description of XMLDeSerialization Class
* @author KUNAL ZANTYE
* @description this class is used to parse the XML and generate object
*/
public class XMLDeSerialization implements SerStrategy {

	public XMLDeSerialization() {
		// TODO Auto-generated constructor stub
	}
	
	/**
	 * @name processInput
	 * @description  to parse the XML and generate object
	 * @return null
	 */
	@Override
	public SerializableObject processInput(BufferedReader reader) throws IOException, ClassNotFoundException, InstantiationException, IllegalAccessException, NumberFormatException, IllegalArgumentException, InvocationTargetException {
		// TODO Auto-generated method stub
		
		Class obj=null;
		String line=reader.readLine();
		
		line=line.trim();
		String className="";
		SerializableObject serObject=null;
		DeserializeTypes types=new DeserializeTypes();
		while(line!=null){
			line=line.trim();
			if(line.equals("</DPSerialization>"))
				break;
				
	
		while(!line.equals("</DPSerialization>")){
			line=line.trim();
			if(line.equals("<DPSerialization>")){
				
				line=reader.readLine();
			}else{
				if(line.startsWith("<complexType")){
					int indexStart=line.indexOf("\"");
					int indexLast=line.indexOf("\">");
					className=line.substring(indexStart+1, indexLast);
					 obj=Class.forName(className);
					 serObject=(SerializableObject) obj.newInstance();
					 
					 
					
				}else if(!line.startsWith("</complexType")){
					int indexStart=line.indexOf("<");
					int indexLast=line.indexOf(" ");
					String fieldName=line.substring(indexStart+1, indexLast);
					
					String[] arr=line.split(">");
					if(arr[0].endsWith("int\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processInt(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					}else if(arr[0].endsWith("long\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processLong(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					} else if(arr[0].endsWith("short\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processShort(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					}  else if(arr[0].endsWith("double\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processDouble(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					}  else if(arr[0].endsWith("float\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processFloat(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					}  else if(arr[0].endsWith("boolean\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processBool(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					} else if(arr[0].endsWith("char\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processChar(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					} else if(arr[0].endsWith("string\"")){
						String methodName = "set" + fieldName;
				    	   Method[] methods=obj.getDeclaredMethods();
				    	   for(int j=0;j<methods.length;j++){
				    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
				    		         
				    				types.processString(methods[j], arr[1].substring(0, arr[1].indexOf("<")), serObject);
				    		          	   break;
				    		   }
				    	   }
						//call method for set
					} 
					
					
				}	
				line=null;
				line=reader.readLine();
			}
			
			
			
			
			
			
		}
			
			
			
		}
		
				
		return serObject;
	}

	@Override
	public void processInput(Object sObject, BufferedWriter writer) throws NoSuchMethodException, SecurityException,
			IllegalAccessException, IllegalArgumentException, InvocationTargetException, IOException {
		// TODO Auto-generated method stub
		
	}
    
    

	
}