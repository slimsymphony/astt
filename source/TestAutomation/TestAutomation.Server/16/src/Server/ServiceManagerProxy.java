package Server;

import java.lang.reflect.Method;
import android.os.IBinder;

/***
 * Class for digging out the services
 * 
 * @author 		Sami Utriainen
 * @since		1.0.1.0
 */
public class ServiceManagerProxy {
	
	private static ServiceManagerProxy mInstance;
	
	private Method mServiceGetter;
	
	/***
	 * 
	 * @return
	 * @since		1.0.1.0
	 */
	public static ServiceManagerProxy getInstance() {
		
		if (mInstance == null) {
			mInstance = new ServiceManagerProxy();
		}
		return mInstance;
	}
	
	/***
	 * 
	 * @since		1.0.1.0
	 */
	private ServiceManagerProxy() {
		createManagerProxy();
	}
	
	/***
	 * 
	 * @since		1.0.1.0
	 */
	private void createManagerProxy() {
		try {
			Class<?> cServiceManager = Class.forName("android.os.ServiceManager");
			mServiceGetter = cServiceManager.getMethod("getService", new Class[] { String.class });
		} catch (Exception e) {
			Trace.writeLine(e);
		}
	}
	
	/***
	 * 
	 * @param serviceName
	 * @param serviceTypeName
	 * @return
	 * @since		1.0.1.0
	 */
	public Object createProxy(String serviceName, String serviceTypeName) {
		
		if (mServiceGetter == null) {
			return null;
		}
		
		if (!serviceTypeName.endsWith("$Stub")) {
			serviceTypeName += "$Stub";
		}
		
		try {
			
			IBinder manager = (IBinder)mServiceGetter.invoke(null, serviceName);
		    Class<?> cIManager_Stub = Class.forName(serviceTypeName);
		    Method IManager_Stub_asInterface = cIManager_Stub.getMethod("asInterface", IBinder.class);
		    return IManager_Stub_asInterface.invoke(null, manager);
			
		} catch(Exception e) {
			Trace.writeLine(e);
			return null;
		}
	}
}