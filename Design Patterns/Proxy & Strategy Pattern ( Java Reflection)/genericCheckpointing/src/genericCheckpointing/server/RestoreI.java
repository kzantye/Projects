package genericCheckpointing.server;


import genericCheckpointing.util.SerializableObject;
/** Description of RestoreI
 * @author KUNAL ZANTYE
 * @description interface for deserializtion, contain read method 
 */

public interface RestoreI extends StoreRestoreI {
	
	SerializableObject readObj(String string);


}
