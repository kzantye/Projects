package genericCheckpointing.util;

import genericCheckpointing.server.StoreRestoreI;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;
/** Description of ProxyCreator Class
* @author KUNAL ZANTYE
* @description this class is used to create dynamic proxy reference
* 
*/
public class ProxyCreator
{

	public StoreRestoreI createProxy(Class<?>[] interfaceArray, InvocationHandler handler){
		StoreRestoreI storeRestoreRef =
            (StoreRestoreI)
            Proxy.newProxyInstance(
                                   getClass().getClassLoader(),
                                   interfaceArray,
                                   handler
                                   );

		return storeRestoreRef;
	}
}