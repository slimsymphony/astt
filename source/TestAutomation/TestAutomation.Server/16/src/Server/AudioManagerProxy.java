package Server;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.HashMap;

import android.content.Context;
import android.media.AudioManager;
import android.os.Binder;
import android.os.IBinder;


/***
 * Class for communicating with the IAudioService
 * 
 * @author 		Sami Utriainen
 * @since		1.0.1.0
 */
public class AudioManagerProxy {

	private static final String PACKAGE_NAME = "TAServer";
	
	private static final String AUDIO_SERVICE_STUB = "android.media.IAudioService$Stub";
		
	private static final String GET_MASTER_MAX_VOLUME = "getMasterMaxVolume";
	private static final String GET_MASTER_STREAM_TYPE = "getMasterStreamType";
	private static final String GET_MASTER_VOLUME = "getMasterVolume";
	private static final String GET_STREAM_MAX_VOLUME = "getStreamMaxVolume";
	private static final String GET_STREAM_VOLUME = "getStreamVolume";
	private static final String IS_MASTER_MUTE = "isMasterMute";
	private static final String IS_SPEAKERPHONE_ON = "isSpeakerphoneOn";
	private static final String SET_MASTER_MUTE = "setMasterMute";
	private static final String SET_MASTER_VOLUME = "setMasterVolume";
	private static final String SET_STREAM_VOLUME = "setStreamVolume";
	private static final String SET_SPEAKERPHONE_ON = "setSpeakerphoneOn";
	
	private static final int FLAG_SHOW_UI = 1 << 0;
	
	private Object mAudioProxy;
	
	private HashMap<String, Integer> mStreams = new HashMap<String, Integer>();
	
	private final IBinder mICallBack = new Binder();
		
	private static AudioManagerProxy mInstance;
	
	
	/***
	 * Private class constructor: only the singleton instance is available
	 * 
	 * @since		1.0.1.0
	 */
	private AudioManagerProxy() {
		mAudioProxy = ServiceManagerProxy.getInstance().createProxy(
				Context.AUDIO_SERVICE, AUDIO_SERVICE_STUB);
		reflectStreams();
	}
	
	
	/***
	 * Gets the singleton instance of the class
	 * 
	 * @return		The singleton instance of the class
	 * @since		1.0.1.0
	 */
	public static AudioManagerProxy getInstance() {
		
		if (mInstance == null) {
			mInstance = new AudioManagerProxy();
		}
		return mInstance;
	}
	
	
	/***
	 * Reflects the stream names into a hash map
	 * 
	 * @since		1.0.1.0
	 */
	private void reflectStreams() {
		
		try
		{
			for (Field f : AudioManager.class.getFields()) {
				if (f.getName().startsWith("STREAM_")) {
					mStreams.put(f.getName(), (Integer)f.get(null));
				}
			}
		} catch (Exception e) { }
	}
	
	
	/***
	 * Gets a stream by its name
	 * 
	 * @param 		name		The name of the stream
	 * @return		A stream by its name
	 * @since		1.0.1.0
	 */
	private int getStream(String name) {
		if (mStreams.containsKey(name)) {
			return mStreams.get(name);
		}
		return -1;
	}
	
	
	/***
	 * Gets a name of the stream
	 * 
	 * @param 		stream		The stream
	 * @return		A name of the stream
	 * @since		1.0.1.0
	 */
	private String getStreamName(int stream) {
		for(String key : mStreams.keySet()) {
			if (mStreams.get(key).equals(stream)) {
				return key;
			}
		}
		return null;
	}
		
	
	/***
	 * Gets the names of the supported audio streams
	 * 
	 * @return		The names of the supported audio streams
	 * @since		1.0.1.0
	 */
	public String[] getAudioStreamNames() {
		return mStreams.keySet().toArray(new String[mStreams.size()]);
	}
	
	/***
	 * Gets the current ringer volume index
	 * 
	 * @return		The current ringer volume; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	public int getRingerVolume() {
		return getStreamVolume(getStreamName(AudioManager.STREAM_RING));
	}
	
	
	/***
	 * Sets the ringer volume index
	 * 
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	public boolean setRingerVolume(int index) {
		return setStreamVolume(getStreamName(AudioManager.STREAM_RING), index);
	}
	
	
	/***
	 * Gets the current media volume index
	 * 
	 * @return		The current media volume; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	public int getMediaVolume() {
		return getStreamVolume(getStreamName(AudioManager.STREAM_MUSIC));
	}
	
	
	/***
	 * Sets the media volume index
	 * 
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	public boolean setMediaVolume(int index) {
		return setStreamVolume(getStreamName(AudioManager.STREAM_MUSIC), index);
	}
	

	/***
	 * Gets the maximum volume index of the master stream
	 * 
	 * @return		The maximum volume index of the master stream; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	public int getMasterMaxVolume() {
		
		try {
			if (mAudioProxy != null) {
				return (Integer)mAudioProxy.getClass().getMethod(GET_MASTER_MAX_VOLUME).invoke(mAudioProxy);
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		return -1;
	}
	
	
	/***
	 * Gets the name of the master stream
	 * 
	 * @return		The name of the master stream; null in case of service unreachable
	 * @since		1.0.1.0
	 */
	public String getMasterStreamName() {
		
		try {
			if (mAudioProxy != null) {
				int type = (Integer)mAudioProxy.getClass().getMethod(GET_MASTER_STREAM_TYPE).invoke(mAudioProxy);
				return getStreamName(type);
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		return null;
	}
	
	
	/***
	 * Gets the current volume index of the master stream
	 * 
	 * @return		The current volume index of the master stream; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	public int getMasterVolume() {
		
		try {
			if (mAudioProxy != null) {
				return (Integer)mAudioProxy.getClass().getMethod(GET_MASTER_VOLUME).invoke(mAudioProxy);
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		return -1;
	}
	

	/***
	 * Gets the maximum volume of a stream by its name
	 * 
	 * @param 		streamName		Name of the stream
	 * @return		The maximum volume of a stream by it's name; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	public int getStreamMaxVolume(String streamName) {
		
		try {
			int stream = getStream(streamName);
			if (stream != -1 && mAudioProxy != null) {
				return (Integer)mAudioProxy.getClass().getMethod(GET_STREAM_MAX_VOLUME, int.class).invoke(mAudioProxy, stream);
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		return -1;
	}
	
	
	/***
	 * Gets the current volume index of a stream by its name
	 * 
	 * @param 		streamName		Name of the stream
	 * @return		The current volume index of a stream by its name; -1 in case of service unreachable
	 * @since		1.0.1.0
	 */
	public int getStreamVolume(String streamName) {
		
		try {
			int stream = getStream(streamName);
			if (stream != -1 && mAudioProxy != null) {
				return (Integer)mAudioProxy.getClass().getMethod(GET_STREAM_VOLUME, int.class).invoke(mAudioProxy, stream);
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		return -1;
	}
	

	/***
	 * Gets a value indicating whether the master stream is muted
	 * 
	 * @return		True if muted; otherwise, false. Also, false in case of service unreachable
	 * @since		1.0.1.0
	 */
	public boolean isMasterMute() {
		
		try {
			if (mAudioProxy != null) {
				return (Boolean)mAudioProxy.getClass().getMethod(IS_MASTER_MUTE).invoke(mAudioProxy);
			}
		} 
		catch(Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}
	

	/***
	 * Gets a value indicating whether the speaker phone is on
	 * 
	 * @return		True if on; otherwise, false. Also, false in case of service unreachable
	 * @since		1.0.1.0
	 */
	public boolean isSpeakerphoneOn() {
		
		try {
			if (mAudioProxy != null) {
				return (Boolean)mAudioProxy.getClass().getMethod(IS_SPEAKERPHONE_ON).invoke(mAudioProxy);
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}
	
	
	/***
	 * Toggles the master stream's mute state
	 * 
	 * @param 		state		True to mute; false to unmute		
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	public boolean setMasterMute(boolean state) {
		
		try {
			if (mAudioProxy != null) {
				mAudioProxy.getClass().getMethod(SET_MASTER_MUTE, boolean.class, int.class, IBinder.class).
					invoke(mAudioProxy, state, FLAG_SHOW_UI, mICallBack);
				return isMasterMute() == state;
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		return false;
	}
	

	/***
	 * Sets the master stream's volume level index
	 * 
	 * @param 		index		The volume level index to set
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0	
	 */
	public boolean setMasterVolume(int index) {
		
		try {
			
			if (index < 0) index = 0;
			
			int max = getMasterMaxVolume();
			
			if (index > max) index = max;
								
			if (mAudioProxy != null) {
				
				Method method = android.os.Build.VERSION.SDK_INT < 19 ? mAudioProxy.getClass().getMethod(SET_MASTER_VOLUME, int.class, int.class) :
					mAudioProxy.getClass().getMethod(SET_MASTER_VOLUME, int.class, int.class, String.class);
				
				if (android.os.Build.VERSION.SDK_INT < 19) {
					method.invoke(mAudioProxy,index, FLAG_SHOW_UI);
				} else {
					method.invoke(mAudioProxy,index, FLAG_SHOW_UI, PACKAGE_NAME);
				}
				
				return getMasterVolume() == index;
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
		
	}

	
	/***
	 * Sets a stream's volume level index
	 * 
	 * @param 		streamName	Name of the audio stream
	 * @param 		index		The volume level index to set
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	public boolean setStreamVolume(String streamName, int index) {
		
		try {
			
			if (index < 0) index = 0;
			
			int max = getStreamMaxVolume(streamName);
			
			if (max != -1 && index > max) index = max;
						
			int stream = getStream(streamName);
			
			if (stream != -1 && mAudioProxy != null) {
				
				Method method = android.os.Build.VERSION.SDK_INT < 19 ? mAudioProxy.getClass().getMethod(SET_STREAM_VOLUME, int.class, int.class, int.class) :
					mAudioProxy.getClass().getMethod(SET_STREAM_VOLUME, int.class, int.class, int.class, String.class);
				
				if (android.os.Build.VERSION.SDK_INT < 19) {
					method.invoke(mAudioProxy, stream, index, FLAG_SHOW_UI);
				} else {
					method.invoke(mAudioProxy, stream, index, FLAG_SHOW_UI, PACKAGE_NAME);
				}
								
				return getStreamVolume(streamName) == index;
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}

	
	/***
	 * Toggles the speaker phone state 
	 * 
	 * @param 		on		True to enable; false to disable
	 * @return		True if the operation was successfully performed; otherwise, false
	 * @since		1.0.1.0
	 */
	public boolean setSpeakerphoneOn(boolean on) {
	
		try {
			if (mAudioProxy != null) {
				mAudioProxy.getClass().getMethod(SET_SPEAKERPHONE_ON, boolean.class).
					invoke(mAudioProxy, on);
				return isSpeakerphoneOn() == on;
			}
		} catch(Exception e) {
			Trace.writeLine(e);
		}
		
		return false;
	}
}
