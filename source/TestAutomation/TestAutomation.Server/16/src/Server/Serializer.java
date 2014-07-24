package Server;

import java.lang.reflect.Type;
import com.google.gson.*;
import com.google.gson.internal.Primitives;

/**
 * A singleton class for serializin and deserializing objects
 * 
 * @author 		Sami Utriainen
 * @version 	1.0.0.0
 */
public class Serializer {
	
	private Gson m_serializer = null;
	private static Serializer m_instance;
	
	/**
	 * Private class constructor as we provide only a singleton instance
	 * 
	 * @since		1.0.0.0
	 */
	private Serializer() {
		m_serializer = new Gson();
	}
	
	/**
	 * Gets the singleton instance of the class
	 * 
	 * @return		The singleton instance of the class
	 * @since		1.0.0.0
	 */
	public static synchronized Serializer getInstance() {
		
		if (m_instance == null) {
			m_instance = new Serializer();
		}
		return m_instance;
	}
	
	/**
	 * Serializes an object into a Json string
	 * 
	 * @param 		obj		An object to serialize
	 * @return		Json presentation of an object
	 * @since		1.0.0.0
	 */
	public String serialize(Object obj) {
		return m_serializer.toJson(obj, obj.getClass());
	}
	
	/**
	 * Deserializes a Json string into a corresponding object
	 * 
	 * @param 		json			A Json string to deserialize
	 * @param 		targetClass		Class type into which to deserialize
	 * @return		Actual object	
	 * @since		1.0.0.0
	 */
	public <T> T deserialize(String json, Class<T> classOfT) {
	    Object object = m_serializer.fromJson(json, (Type) classOfT);
	    return Primitives.wrap(classOfT).cast(object);
	}
}
