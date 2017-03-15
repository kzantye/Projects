package genericCheckpointing.xmlStoreRestore;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import genericCheckpointing.util.SerializableObject;
import genericCheckpointing.util.SerializeTypes;

public class XMLSerialization implements SerStrategy {
    
	/**
	 * @name processInput
	 * @description  to process object and generate XML file using java reflection
	 * @return null
	 */
    public void processInput(Object sObject,BufferedWriter writer) throws NoSuchMethodException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, IOException {

     // all the code to create the output file with XML snippets for
     // an object
    	SerializeTypes serTypes= new SerializeTypes();
        Class<?> cls = sObject.getClass();
        Field[] fields=cls.getDeclaredFields();
        
        writer.write("<DPSerialization> \n");
        writer.write(" <complexType xsi:type=\""+cls.getCanonicalName()+"\">");
        
        
        for(int i=0;i<fields.length;i++){
        	Field fld=fields[i];
       
        
	       if (fld.getType() == int.class) {
	       	  // get field name 
	    	   String methodName = "get" + fld.getName();
	    	   Method[] methods=cls.getDeclaredMethods();
	    	   for(int j=0;j<methods.length;j++){
	    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
	    			   Object invokeRet = methods[j].invoke(sObject);
	    		          String fieldName=fld.getName();
	    		        writer.write(serTypes.processInt(fieldName, methodName, invokeRet));
	    		          	   break;
	    		   }
	    	   }
	          //Method getterMethod = cls.getMethod("getMyInt()");
	          
	       }else if (fld.getType() == long.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processLong(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }
		          
		    }else if (fld.getType() == String.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processString(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }
		          
		    }else if (fld.getType() == boolean.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processBool(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }
		          
		    }else if (fld.getType() == double.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processDouble(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }		          
		    }else if (fld.getType() == float.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processFloat(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }
		          
		    }else if (fld.getType() == short.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processShort(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }
		          
		    }else if (fld.getType() == char.class) {
		       	  // get field name 
		    	   String methodName = "get" + fld.getName();
		    	   Method[] methods=cls.getDeclaredMethods();
		    	   for(int j=0;j<methods.length;j++){
		    		   if(methods[j].getName().toLowerCase().equals(methodName.toLowerCase())){
		    			   Object invokeRet = methods[j].invoke(sObject);
		    		          String fieldName=fld.getName();
		    		        writer.write(  serTypes.processChar(fieldName, methodName, invokeRet));
		    		          	   break;
		    		   }
		    	   }
		          
		    }
    	
        }
        
        writer.write("\n </complexType>");
        writer.write("\n");
        writer.write("</DPSerialization>");
        writer.write("\n");
    }

	@Override
	public SerializableObject processInput(BufferedReader writer)
			throws IOException, ClassNotFoundException, InstantiationException, IllegalAccessException {
		// TODO Auto-generated method stub
		return null;
	}

	

	
}