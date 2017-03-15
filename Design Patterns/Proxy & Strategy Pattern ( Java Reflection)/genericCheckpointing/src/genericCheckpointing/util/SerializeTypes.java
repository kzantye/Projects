package genericCheckpointing.util;
/** Description of DeserializeTypes Class
* @author KUNAL ZANTYE
* @description this class is used to serialized according to type
*/
public class SerializeTypes {
	
	
	public String processInt(  String fieldName,String methodName , Object invokeRet ){
		int value=Integer.parseInt(invokeRet.toString());
		return "\n <"+fieldName+" xsi:type=\"xsd:int\">"+value+"</"+fieldName+">";
	}
	
	public String processLong(  String fieldName,String methodName , Object invokeRet ){
		long value=Long.parseLong(invokeRet.toString());
		return "\n <"+fieldName+" xsi:type=\"xsd:long\">"+value+"</"+fieldName+">";
	}
	
	public String processShort(  String fieldName,String methodName , Object invokeRet ){
		short value=Short.parseShort(invokeRet.toString());
		return "\n <"+fieldName+" xsi:type=\"xsd:short\">"+value+"</"+fieldName+">";
	}
	
	public String processBool(  String fieldName,String methodName , Object invokeRet ){
		boolean value=Boolean.parseBoolean(invokeRet.toString());
		return "\n <"+fieldName+" xsi:type=\"xsd:boolean\">"+value+"</"+fieldName+">";
	}
	
	public String processDouble(  String fieldName,String methodName , Object invokeRet ){
		double value=Double.parseDouble(invokeRet.toString());
		return "\n <"+fieldName+" xsi:type=\"xsd:double\">"+value+"</"+fieldName+">";
	}
	
	public String processFloat(  String fieldName,String methodName , Object invokeRet ){
		float value=Float.parseFloat(invokeRet.toString());
		return "\n <"+fieldName+" xsi:type=\"xsd:float\">"+value+"</"+fieldName+">";
	}
	
	public String processString(  String fieldName,String methodName , Object invokeRet ){
		String value=invokeRet.toString();
		return "\n <"+fieldName+" xsi:type=\"xsd:string\">"+value+"</"+fieldName+">";
	}
	
	public String processChar(  String fieldName,String methodName , Object invokeRet ){
		char value=invokeRet.toString().charAt(0);
		return "\n <"+fieldName+" xsi:type=\"xsd:char\">"+value+"</"+fieldName+">";
	}
	
	

}
