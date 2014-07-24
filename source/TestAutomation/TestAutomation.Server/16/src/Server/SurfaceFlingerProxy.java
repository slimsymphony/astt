package Server;

import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;

/***
 * @author Sami Utriainen
 * 
 * Class for communicating with the native surfaceflinger
 * 
 * {@link frameworks/native/services/surfaceflinger/SurfaceFlinger.cpp}
 * 
 * @since		1.0.1.0
 */
public class SurfaceFlingerProxy {

	private static final String SERVICE_NAME = "SurfaceFlinger";
	
	private static final int TRANSACTION_showUpdates = IBinder.FIRST_CALL_TRANSACTION + 1001;
	private static final int TRANSACTION_repaintEverything = IBinder.FIRST_CALL_TRANSACTION + 1003;
	private static final int TRANSACTION_forceTransaction = IBinder.FIRST_CALL_TRANSACTION + 1004;
	private static final int TRANSACTION_sendEmptyUpdate = IBinder.FIRST_CALL_TRANSACTION + 1005;
	private static final int TRANSACTION_toggleUseOfHwComposer = IBinder.FIRST_CALL_TRANSACTION + 1007;
	private static final int TRANSACTION_toggleUseOfTransformHint = IBinder.FIRST_CALL_TRANSACTION + 1008;
	private static final int TRANSACTION_interrogate = IBinder.FIRST_CALL_TRANSACTION + 1009;
	private static final int TRANSACTION_getPageFlipCount = IBinder.FIRST_CALL_TRANSACTION + 1012;
	
	private static SurfaceFlingerProxy mInstance = null;
	
	private IBinder mSurfaceFlinger = null;
	
	/***
	 * Private class constructor; only the singleton object can be called
	 * 
	 * @since		1.0.1.0
	 */
	private SurfaceFlingerProxy() {
		CreateProxy();
	}
	
	/***
	 * Gets the singleton instance of the class
	 * 
	 * @return		The singleton instance of the class
	 * 
	 * @since		1.0.1.0
	 */
	public static SurfaceFlingerProxy getInstance() {
		
		if (mInstance == null) {
			mInstance = new SurfaceFlingerProxy();
		}
		return mInstance;
	}
	
	/***
	 * Creates the proxy binder to the native SurfaceFlinger
	 * 
	 * @since		1.0.1.0
	 */
	private void CreateProxy() {
		
		try {
			//Use reflection to get handle to the hidden ServiceManager
			Class<?> cServiceManager = Class.forName("android.os.ServiceManager");
			//Create the binding to the surface flinger by calling the getService from the hidden ServiceManager
			mSurfaceFlinger = (IBinder)cServiceManager.getMethod("getService", String.class).invoke(null, SERVICE_NAME);
		} catch (Exception e) {
			mSurfaceFlinger = null;
			Trace.writeLine(e);
		}
	}
	
	/***
	 * Checks if the SurfaceFlinger service is available
	 * 
	 * @return		True if available; false otherwise
	 * 
	 * @since		1.0.1.0
	 */
	public boolean serviceAvailable() {
		return mSurfaceFlinger != null;
	}
	
	/***
	 * Interrogates
	 * 
	 * @return		Result from surfaceManager; null if the service was not successfully called
	 * 
	 * @since		1.0.1.0
	 */
	public int[] interrogate() {
		
		if (!serviceAvailable()) {
			return null;
		}
		
		Parcel data = Parcel.obtain();
		Parcel reply = Parcel.obtain();
		
		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			if (mSurfaceFlinger.transact(TRANSACTION_interrogate, data, reply, 0) &&
					reply.dataAvail() == 5 * 4/*sizeof(int)*/) {
				int[] response = new int[5];
				for(int i = 0; i < 5; i++) {
					response[i] = reply.readInt();
				}
				return response;
			}
			return null;
		}
		catch (RemoteException re)  {
			return null;
		}
		finally {
			data.recycle();
			reply.recycle();
		}
	}
	
	/***
	 * Enables or disables use of transform hint
	 * 
	 * @param enable		Value indicating whether to enable or disable use of transform hint
	 * 
	 * @return		True if available; false otherwise
	 * 
	 * @since		1.0.1.0			
	 */
	public boolean useTransformHint(boolean enable) {
		
		if (!serviceAvailable()) {
			return false;
		}
		
		Parcel data = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			data.writeInt(enable ? 1 : 0);
			return mSurfaceFlinger.transact(TRANSACTION_toggleUseOfTransformHint, data, null, 0);
		}
		catch (RemoteException re)  {
			return false;
		}
		finally {
			data.recycle();
		}
	}
	
	/***
	 * Enables or disables use of HW composer
	 * 
	 * @param enable		Value indicating whether to enable or disable use of HW composer
	 * 
	 * @return		True if available; false otherwise
	 * 
	 * @since		1.0.1.0			
	 */
	public boolean useHwComposer(boolean enable) {
		
		if (!serviceAvailable()) {
			return false;
		}
		
		Parcel data = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			data.writeInt(enable ? 1 : 0);
			return mSurfaceFlinger.transact(TRANSACTION_toggleUseOfHwComposer, data, null, 0);
		}
		catch (RemoteException re)  {
			return false;
		}
		finally {
			data.recycle();
		}
	}
	
	/***
	 * Forces a transaction
	 * 
	 * @return				True if the service was successfully called; false otherwise
	 * 
	 * @since				1.0.1.0
	 */
	public boolean forceTransaction() {
		
		if (!serviceAvailable()) {
			return false;
		}
		
		Parcel data = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			return mSurfaceFlinger.transact(TRANSACTION_forceTransaction, data, null, 0);
		}
		catch (RemoteException re)  {
			return false;
		}
		finally {
			data.recycle();
		}
	}
	
	/***
	 * Sends an empty update
	 * 
	 * @return				True if the service was successfully called; false otherwise
	 * 
	 * @since				1.0.1.0
	 */
	public boolean sendEmptyUpdate() {
		
		if (!serviceAvailable()) {
			return false;
		}
		
		Parcel data = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			return mSurfaceFlinger.transact(TRANSACTION_sendEmptyUpdate, data, null, 0);
		}
		catch (RemoteException re)  {
			return false;
		}
		finally {
			data.recycle();
		}	
	}
	
	/***
	 * Repaints everything on the screen
	 * 
	 * @return				True if the service was successfully called; false otherwise
	 * 
	 * @since				1.0.1.0
	 */
	public boolean repaintEverything() {
		
		if (!serviceAvailable()) {
			return false;
		}
		
		Parcel data = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			return mSurfaceFlinger.transact(TRANSACTION_repaintEverything, data, null, 0);
		}
		catch (RemoteException re)  {
			return false;
		}
		finally {
			data.recycle();
		}	
	}
	
	/***
	 * Enables or disable showing the display updates on the screen
	 * 
	 * @param 	enable		Whether to enable or disable the updates
	 * @return				True if the service was successfully called; false otherwise
	 * 
	 * @since				1.0.1.0
	 */
	public boolean showUpdates(boolean enable) {
		
		if (!serviceAvailable()) {
			return false;
		}
		
		Parcel data = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			data.writeInt(enable ? 1 : 0);
			return mSurfaceFlinger.transact(TRANSACTION_showUpdates, data, null, 0);
		}
		catch (RemoteException re)  {
			return false;
		}
		finally {
			data.recycle();
		}		
	}
	
	/***
	 * Gets the count of page flips in EGLDisplaySurface
	 * 
	 * @return		Count of page flips in EGLDisplaySurface; -1 if the service was not successfully called
	 * 
	 * @since		1.0.1.0
	 */
	public int getPageFlipCount() {
		
		if (!serviceAvailable()) {
			return -1;
		}
		
		Parcel data = Parcel.obtain();
		Parcel reply = Parcel.obtain();

		try
		{
			data.writeInterfaceToken(mSurfaceFlinger.getInterfaceDescriptor());
			if (mSurfaceFlinger.transact(TRANSACTION_getPageFlipCount, data, reply, 0) && 
					reply.dataAvail() == 4 /*sizeof(int)*/) {
				return reply.readInt();
			}
		}
		catch (RemoteException re)  {
			return -1;
		}
		finally {
			reply.recycle();
			data.recycle();
		}
		
		return -1;
	}
}
