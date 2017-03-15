package genericCheckpointing.util;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
/** Description of DeserializeTypes Class
* @author KUNAL ZANTYE
* @description this class is used to deserialized according to type
*/
public class DeserializeTypes {

	public void processInt(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, Integer.parseInt(value));
	}
	public void processLong(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, Long.parseLong(value));
	}
	public void processString(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, value);
	}
	public void processShort(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, Short.parseShort(value));
	}
	public void processDouble(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, Double.parseDouble(value));
	}
	public void processFloat(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, Float.parseFloat(value));
	}
	public void processChar(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, value.charAt(0));
	}
	public void processBool(Method m,String value,SerializableObject o) throws NumberFormatException, IllegalAccessException, IllegalArgumentException, InvocationTargetException{
		m.invoke(o, Boolean.parseBoolean(value));
	}
	
}
