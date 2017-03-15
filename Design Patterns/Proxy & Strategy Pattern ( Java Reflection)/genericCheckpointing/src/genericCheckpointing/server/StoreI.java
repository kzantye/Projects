package genericCheckpointing.server;


import genericCheckpointing.util.MyAllTypesSecond;
import genericCheckpointing.util.MyAllTypesFirst;

/** Description of StoreI
 * @author KUNAL ZANTYE
 * @description interface for serializtion, contain write method 
 */
public interface StoreI extends StoreRestoreI {
    void writeObj(MyAllTypesFirst myFirst, String wireFormat);
    void writeObj(MyAllTypesSecond mySecond, String wireFormat);

}
