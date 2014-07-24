package Server;

import java.lang.reflect.Constructor;

import android.content.Context;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationManager;
import android.location.LocationProvider;
import android.os.Bundle;

/***
 * 
 * 
 * @author 		Sami Utriainen
 * @since		1.0.1.0
 */
public class LocationManagerProxy {

	private Object mLocationProxy;
	
	private String mTestProviderName = LocationManager.GPS_PROVIDER;
	
	private static LocationManagerProxy mInstance;
	
	/***
	 * 
	 * 
	 * @return
	 * @since		1.0.1.0
	 */
	public static LocationManagerProxy getInstance() {
		
		if (mInstance == null) {
			mInstance = new LocationManagerProxy();
		}
		return mInstance;
	}
	
	/***
	 * 
	 * 
	 * @since		1.0.1.0
	 */
	private LocationManagerProxy() {
		mLocationProxy = ServiceManagerProxy.getInstance().createProxy(
				Context.LOCATION_SERVICE, "android.location.ILocationManager");
	}
	
	/***
	 * 
	 * 
	 * @return
	 * @since		1.0.1.0
	 */
	public boolean enableTestProvider() {
		if (createTestProvider()) {
			return setTestProviderEnabled(true);
		}
		return false;
	}
	
	/***
	 * 
	 * 
	 * @since		1.0.1.0
	 */
	public void disableTestProvider() {
		removeTestProvider();
	}
	
	/***
	 * 
	 * 
	 * @param 		latitude
	 * @param 		longitude
	 * @return
	 * @since		1.0.1.0
	 */
	public boolean setLocation(double latitude, double longitude) {
		return setTestProviderLocation(createLocation(latitude, longitude));
	}
	
	/***
	 * 
	 * @param 		latitude
	 * @param 		longitude
	 * @return		
	 * @since		1.0.1.0
	 */
	private Location createLocation(double latitude, double longitude) {
		
		Location l = new Location(mTestProviderName);
		l.setLatitude(latitude);
		l.setLongitude(longitude);
		l.setAccuracy(90);
		l.setTime(System.currentTimeMillis());
		
		if (AutomatorBridge.getInstance().isApi18OrLater()) {
			try {
				l.getClass().getMethod("setElapsedRealtimeNanos", long.class).invoke(l, l.getTime());
			} catch (Exception e) {
				Trace.writeLine(e);
			}
		}
		
		return l;
	}
	
	/***
	 * 
	 * @param 		location
	 * @return		
	 * @since		1.0.1.0
	 */
	private boolean setTestProviderLocation(Location location) {
		
		try {
					
			mLocationProxy.getClass().getMethod("setTestProviderLocation", String.class, Location.class)
            	.invoke(mLocationProxy, mTestProviderName, location);
			
			return true;
			
			
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}
	
	/***
	 * 
	 * 
	 * @since		1.0.1.0
	 */
	private void removeTestProvider() {
		
		try {
			
			if (mLocationProxy.getClass().getMethod("getProviderProperties", String.class).
				invoke(mLocationProxy, mTestProviderName) == null) {
				return;
			}
			
			//setTestProviderEnabled(false);
			
			mLocationProxy.getClass().getMethod("removeTestProvider", String.class).
				invoke(mLocationProxy, mTestProviderName);
		
		} catch (Exception e) {
			Trace.writeLine(e);
		}
	}
	
	/***
	 * 
	 * @return
	 * @since		1.0.1.0
	 */
	private boolean createTestProvider() {
		
		removeTestProvider();
		
		try {
		
			if (AutomatorBridge.getInstance().isApi18OrLater()) {
				
	            Class<?> props = Class.forName("com.android.internal.location.ProviderProperties");
	            Constructor<?> ctor = props.getConstructor(boolean.class, boolean.class, boolean.class, boolean.class, boolean.class, boolean.class, boolean.class, int.class, int.class);                    
	            Object provider_props = ctor.newInstance(false, false, false, false, false, false, false, Criteria.POWER_LOW, Criteria.ACCURACY_FINE);
				
	            mLocationProxy.getClass().getMethod("addTestProvider", String.class, props)
	            	.invoke(mLocationProxy, mTestProviderName, provider_props);
	
	            return true;
			}
			else {
				
	            mLocationProxy.getClass().getMethod("addTestProvider", String.class, boolean.class, boolean.class, boolean.class, boolean.class, boolean.class, boolean.class, boolean.class, int.class, int.class)
	        		.invoke(mLocationProxy, mTestProviderName, false, false, false, false, false, false, false, Criteria.POWER_LOW, Criteria.ACCURACY_FINE);
				
				return true;
				
			}
		
		}
		catch (Exception e) {
			Trace.writeLine(e);
		}
		return false;
		
	}
	
	/***
	 * 
	 * @param 		enabled
	 * @return
	 * @since		1.0.1.0
	 */
	private boolean setTestProviderEnabled(boolean enabled) {
		
		try {
			
			mLocationProxy.getClass().getMethod("setTestProviderEnabled", String.class, boolean.class)
				.invoke(mLocationProxy, mTestProviderName, enabled);
			
			mLocationProxy.getClass().getMethod("setTestProviderStatus", String.class, int.class, Bundle.class, long.class)
        		.invoke(mLocationProxy, mTestProviderName, enabled ? LocationProvider.AVAILABLE : LocationProvider.OUT_OF_SERVICE , null, System.currentTimeMillis());
			
			return true;
			
		} catch (Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}
}