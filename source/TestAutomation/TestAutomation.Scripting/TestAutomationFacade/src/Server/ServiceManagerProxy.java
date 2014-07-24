package Server;

import android.os.IBinder;

import java.lang.reflect.Method;

/***
 * 
 * @author Sami Utriainen
 * 
 */
public class ServiceManagerProxy {

  private static ServiceManagerProxy mInstance;

  private Method mServiceGetter;

  /***
   * 
   * @return
   */
  public static ServiceManagerProxy getInstance() {

    if (mInstance == null) {
      mInstance = new ServiceManagerProxy();
    }
    return mInstance;
  }

  /***
	 * 
	 */
  private ServiceManagerProxy() {
    createManagerProxy();
  }

  /***
	 * 
	 */
  private void createManagerProxy() {
    try {
      Class<?> cServiceManager = Class.forName("android.os.ServiceManager");
      mServiceGetter = cServiceManager.getMethod("getService", new Class[] { String.class });
    } catch (Exception e) {

    }
  }

  /***
   * 
   * @param serviceName
   * @param serviceTypeName
   * @return
   */
  public Object createProxy(String serviceName, String serviceTypeName) {

    if (mServiceGetter == null) {
      return null;
    }

    if (!serviceTypeName.endsWith("$Stub")) {
      serviceTypeName += "$Stub";
    }

    try {

      IBinder manager = (IBinder) mServiceGetter.invoke(null, serviceName);
      Class<?> cIManager_Stub = Class.forName(serviceTypeName);
      Method IManager_Stub_asInterface = cIManager_Stub.getMethod("asInterface", IBinder.class);
      Object proxy = IManager_Stub_asInterface.invoke(null, manager);
      return proxy;

    } catch (Exception e) {

      return null;
    }
  }
}