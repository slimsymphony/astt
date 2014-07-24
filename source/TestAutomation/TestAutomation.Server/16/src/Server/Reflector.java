package Server;

import java.io.File;
import java.lang.reflect.*;
import java.net.URL;
import java.util.*;
import java.lang.annotation.Annotation;

/**
 * Class that provides a singleton instance from itself for for appending classes under reflection, and 
 * thus available for dynamic invocation
 * 
 * @author 		Sami Utriainen
 * @version		1.0.0.0
 *
 */
public class Reflector {
	
	private Map<Class<?>, Class<? extends Annotation>> m_classes = null;
	private static Reflector m_instance = null;
	
	/**
	 * Private constructor for the class, as we provide only a singleton instance
	 * 
	 * @since		1.0.0.0
	 */
	private Reflector() {
		
		m_classes = new HashMap<Class<?>, Class<? extends Annotation>>(); 
	}
	
	/**
	 * Gets the singleton instance of the class
	 * 
	 * @return		Singleton instance of the class
	 * @since		1.0.0.0
	 */
	public static Reflector getInstance() {
		
		if (m_instance == null) {
			m_instance = new Reflector();
		}
		return m_instance;
	}
	
	/**
	 * Adds a target class for reflection
	 * 
	 * @param 		targetClass		A target class for reflection
	 * @since		1.0.0.0
	 */
	public void AddTarget(Class<?> targetClass) {
		
		AddTarget(targetClass, null);
		
	}
	
	/**
	 * Adds a target class for reflection, with a limited visibility
	 * 
	 * @param 		targetClass		A target class for reflection
	 * @param 		visibility		Annotation which needs to defined by the methods in the target class
	 * @since		1.0.0.0
	 */
	public void AddTarget(Class<?> targetClass, Class<? extends Annotation> visibility) {
		
		if (targetClass != null) {
			m_classes.put(targetClass, visibility);
		}
		
	}
	
	/**
	 * Adds a target classes from a given package for reflection
	 * 
	 * @param 		targetPackage		Target classes from a given package for reflection
	 * @since		1.0.0.0		
	 */
	public void AddTarget(Package targetPackage) {
		
		AddTarget(targetPackage, null);
		
	}
	
	/**
	 * Adds a target classes from a given package for reflection, with a limited visibility
	 * 
	 * @param 		targetPackage		Target classes from a given package for reflection
	 * @param 		visibility			Annotation which needs to defined by the methods in the target class
	 * @since		1.0.0.0
	 */
	public void AddTarget(Package targetPackage, Class<? extends Annotation> visibility) {
		
		for(Class<?> cls : getClasses(targetPackage)) {
			AddTarget(cls, visibility);
		}
	}
		
	/**
	 * Invokes a given method by name, from a given class by name, with no parameters
	 *  
	 * @param 		className		Name of the class from which to call for a method
	 * @param 		methodName		Name of the method to call
	 * @return		Value returned by the method invocation; null in case of void methods
	 * @since		1.0.0.0
	 */
	public Object invoke(String className, String methodName) throws Exception {
		return invoke(className, methodName, null);
	}
	
	/**
	 * Invokes a given method by name, from a given class by name, with given parameters
	 * 
	 * @param 		className		Name of the class from which to call for a method
	 * @param 		methodName		Name of the method to call
	 * @param 		args			Parameters for a method as an array of objects 
	 * @return		Value returned by the method invocation; null in case of void methods
	 * @since		1.0.0.0
	 */
	public Object invoke(String className, String methodName, Object[] args) throws Exception {
		
		Class<?> toInvokeFrom = getClass(className);

		if (toInvokeFrom == null) {
			throw new ClassNotFoundException(className);
		}	
		
		Object targetObject = null;
		
		Method toInvoke = getPublicStaticMethod(toInvokeFrom, methodName);
		
		if (toInvoke == null) {
			throw new NoSuchMethodException(methodName);
		}
		
		if (args == null) {
			args = new Object[0];
		}
				
		return toInvoke.invoke(targetObject, args);
	}
	
	/***
	 * Lists names of the classes having visible methods
	 * 
	 * @return		List of names of the classes having visible methods
	 * @since		1.0.0.0
	 */
	public List<String> getAvailableClassNames() {
		
		List<String> classes = new ArrayList<String>();
		
		for (Class<?> cls : m_classes.keySet()) {
			classes.add(cls.getSimpleName());
		}
		
		return classes;
	}
	
	/***
	 * Lists the visible methods in a given class (name)
	 * 
	 * @param 		className		Simple name of the class from which to list the methods
	 * @return		List of visible methods
	 * @since		1.0.0.0
	 */
	public List<String> getAvailableMethodNames(String className) {
		
		List<String> methods = new ArrayList<String>();
		
		for(Class<?> cls : m_classes.keySet()) {

			if (cls.getSimpleName().equals(className)) {

				Class<? extends Annotation> visibility = m_classes.get(cls);
				
				for(Method method : cls.getDeclaredMethods()) {
					
					if ((visibility != null && method.isAnnotationPresent(visibility)) || visibility == null) {
						
						String methodName = method.getName();
						
						if (!methods.contains(methodName)) {
							methods.add(methodName);
						}
					}
				}
			}
		}
		
		return methods;
	}
	
	/**
	 * Generates a documentation from the visible methods in the classes under reflections
	 * 
	 * @return		Documentation		from the visible methods in the classes under reflections
	 * @since		1.0.0.0
	 */
	public String getDoc() {
		
		StringBuilder builder = new StringBuilder();
		
		String intent = "  ";
		
		for(Class<?> cls : m_classes.keySet()) {
			
			builder.append(cls.getSimpleName() + " Class" + Environment.getNewLine() + Environment.getNewLine());
			
			Class<? extends Annotation> visibility = m_classes.get(cls);
			
			List<String> labels = new ArrayList<String>();
			
			if (visibility != null) {
				for(Method m : visibility.getMethods()) {
					if (m.getDeclaringClass().equals(visibility)) {
						labels.add(m.getName());
					}
				}
			}
			
			builder.append("Methods" + Environment.getNewLine());
			
			for(Method method : cls.getDeclaredMethods()) {
				
				if ((visibility != null && method.isAnnotationPresent(visibility)) || visibility == null) {
					
					builder.append(intent);
					
					for (Annotation a : method.getAnnotations()) {
						try {		
							for (String label : labels) {
								Method m = a.getClass().getMethod(label, new Class<?>[] {});
								if (m != null) {
									Object value =  m.invoke(a, new Object[] { });
									if (value != null) {
										String sValue = value.toString();
										if (!sValue.isEmpty()) {
											builder.append("@" + label + ": " + sValue + "\n");
											builder.append(intent);
										}
									}
								}
							}
						} catch (Exception e) { }

					}
								
					if (Modifier.isPublic(method.getModifiers())) {
						builder.append("public ");
					}
					
					if (Modifier.isStatic(method.getModifiers())) {
						builder.append("static ");
					}
					
					builder.append(getName(method.getGenericReturnType()));
					builder.append(" " + method.getName() + "(");
					
					Type[] types = method.getGenericParameterTypes();
					
					if (types == null || types.length == 0) {
						builder.append(")");
					}
					else {
						for (int i = 0; i < types.length; i++) {
							builder.append(getName(types[i]) + " arg" + i);
							if (i < (types.length - 1)) {
								builder.append(", ");
							}
						}
						builder.append(")");
					}
					builder.append(Environment.getNewLine() + Environment.getNewLine());
				}
			}
			builder.append(Environment.getNewLine());
		}
		return builder.toString();
	}
	
	/**
	 * Gets classes out from a package
	 * 
	 * @param 		packageName		Name of the package from which the read the classes 		
	 * @param 		className		Name of the class of interest
	 * @return		Class if found; null otherwise
	 * @since		1.0.0.0
	 */
	private Class<?> getClassFromPackage(String packageName, String className) {
		
		Package p = getPackage(packageName);
		if (p == null) {
			return null;
		}
	
		for(Class<?> cls : getClasses(p)) {
			
			if (cls.getSimpleName().equals(className)) {
				return cls;
			}
		}
		return null;
	}
	
	/**
	 * Gets the friendly name of the value type, i,e, name without package -prefix
	 * 
	 * @param 		type		Type from which the get the friendly name
	 * @return		Friendly name of the value type
	 * @since		1.0.0.0
	 */
	private String getName(Type type) {
		
		String typeName = type.toString();
        String simpleName = "";
        
        boolean isGeneric = typeName.matches(".+<.+>.*");
        boolean isArray = typeName.matches(".*\\[[A-Z].+");
        
        if (isGeneric) {
			  
        	String generic = typeName.substring(0, typeName.indexOf("<"));
			  
        	int i = generic.lastIndexOf(".");
        	if (i > 0) {
        		simpleName = generic.substring(i + 1, generic.length()) + "<";
    		}
        }
        
        String elementType = isGeneric ? typeName.substring(typeName.indexOf("<") + 1, typeName.length() - 1) : typeName;
        
        int j = elementType.lastIndexOf(".");
        if (j > 0) {
        	elementType = elementType.substring(j + 1, isArray ? elementType.length() - 1 : elementType.length());
    	}
        
        simpleName += elementType + (isArray ? "[]" : "") + (isGeneric ? ">" : "");
        
        return simpleName;
	}
	
	/**
	 * Gets parameter types for a method
	 * 
	 * @param 		method		A method from which the look for the parameter types
	 * @return		List of parameter types for a method
	 * @since		1.0.0.0
	 */
	private List<Class<?>> getMethodParameterTypes(Method method) {
		
		List<Class<?>> argTypes = new ArrayList<Class<?>>();
		
		for (Class<?> cls : method.getParameterTypes()) {
			argTypes.add(cls);
		}
		
		return argTypes;
	}
	
	/**
	 * Validates that a method's parameter count and types matches to an array of parameters
	 * 
	 * @param 		method		Method whose parameters to check against
	 * @param 		args		Parameter array which to validate
	 * @return		True if match; false otherwise
	 * @since		1.0.0.0
	 */
	private boolean validateMethodParameters(Method method, Object[] args)
	{
		List<Class<?>> argTypes = getMethodParameterTypes(method);
	
		if (args.length != argTypes.size()) {
			return false;
		}

		for (int i = 0; i < argTypes.size(); i++) {
			
			Class<?> cls = args[i].getClass();
			
			if (argTypes.get(i).isPrimitive()) {
			
				try {
					cls = (Class<?>)cls.getField("TYPE").get(null);
				} catch (Exception e) {
				}
			}
			
			if (!cls.equals(argTypes.get(i))) {
				return false;
			}
		}
		
		return true;
	}
	
	/**
	 * Checks if a method by given name exists in a given class
	 * 
	 * @param 		inClass		Class from which to check
	 * @param 		methodName	Name of the method which to look for		
	 * @return		True if a method exists; false otherwise
	 * @since		1.0.0.0
	 */
	private boolean hasMethod(Class<?> inClass, String methodName) {
		
		for(Method method : inClass.getDeclaredMethods()) {
			if (Modifier.isPublic(method.getModifiers())) {
				if (method.getName().toLowerCase() == methodName.toLowerCase()) {
					return true;
				}
			}
		}
		
		return false;
	}
	
	/**
	 * Gets a public static method from a class by it's name.
	 * 
	 * @param 		fromClass		A class from which to look for the method	
	 * @param 		methodName		Name of the public static method
	 * @return		Method if found with given requirements; null otherwise
	 * @since		1.0.0.0
	 */
	private Method getPublicStaticMethod(Class<?> fromClass, String methodName) {
		
		Class<? extends Annotation> visibility = m_classes.get(fromClass);
		
		for(Method method : fromClass.getDeclaredMethods()) {
			if ((visibility != null && method.isAnnotationPresent(visibility)) || visibility == null) {
				int modifier = method.getModifiers();
				if (Modifier.isPublic(modifier) && Modifier.isStatic(modifier)) {
					if (method.getName().equals(methodName)) {
						return method;
					}
				}
			}
		}
		return null;
	}
	
	/**
	 * Gets a public method from a class by it's name.
	 * 
	 * @param 		fromClass		A class from which to look for the method	
	 * @param 		methodName		Name of the public method
	 * @return		Method if found with given requirements; null otherwise
	 * @since		1.0.0.0
	 */
	private Method getPublicMethod(Class<?> fromClass, String methodName) {
		
		Class<? extends Annotation> visibility = m_classes.get(fromClass);
		
		for(Method method : fromClass.getDeclaredMethods()) {
			if ((visibility != null && method.isAnnotationPresent(visibility)) || visibility == null) {
				int modifier = method.getModifiers();
				if (Modifier.isPublic(modifier)) {
					if (method.getName().equals(methodName)) {
						return method;
					}
				}
			}
		}
		return null;
	}
	
	/**
	 * Creates an instance of a class. Class needs to have a parametreles constructor
	 * 
	 * @param 		fromClass		A class from which to create an instance
	 * @return		An instance of the given class
	 * @since		1.0.0.0
	 */
	private Object createInstance(Class<?> fromClass) {
		
		for (Constructor<?> ctor : fromClass.getDeclaredConstructors()) {
			int modifier = ctor.getModifiers();
			if (Modifier.isPublic(modifier)) {
				if (ctor.getParameterTypes().length == 0) {
					try {
						return ctor.newInstance();
					} catch (Exception e) {
					}
				}
			}
		}

		return null;
	}
	
	/**
	 * Checks if the current package has a class corresponding the given simple class name
	 * 
	 * @param 		className		Simple name of the class
	 * @return		True if the current package has a class corresponding the given simple class name; False otherwise
	 * @since		1.0.0.0
	 */
	private boolean hasClass(String className) {
		
		for (Class<?> cls : m_classes.keySet()) {
			if (cls.getSimpleName().equals(className)) {
				return true;
			}
		}
		
		return false;
	}
	
	/**
	 * Gets a class by it's (simple) name
	 * 
	 * @param 		className		Simple name of the class
	 * @return		A class corresponding to given simple class name; null if not found 
	 */
	private Class<?> getClass(String className) {
		for (Class<?> cls : m_classes.keySet()) {
			if (cls.getSimpleName().equals(className)) {
				return cls;
			}
		}
		return null;
	}
	
	/**
	 * Gets a list of classes defined in a package
	 * 
	 * @param 		p		Package from which to look for the classes
	 * @return		A list of classes defined in a package
	 * @since		1.0.0.0
	 */
	private List<Class<?>> getClasses(Package p) {
		
	    List<Class<?>> classes = new ArrayList<Class<?>>();
			    
	    if (p == null) {
	    	return classes;
	    }
	    
	    try {
		    
			String packageName = p.getName();
			ClassLoader classLoader = Thread.currentThread().getContextClassLoader();
		    String path = packageName.replace('.', '/');
		    Enumeration<URL> resources = classLoader.getResources(path);
		    
		    if (resources == null) {
		    	return classes;
		    }
		    
		    List<File> dirs = new ArrayList<File>();
		    while (resources.hasMoreElements()) {
		        URL resource = resources.nextElement();
		        dirs.add(new File(resource.getFile()));
		    }
		    		    
		    for (File directory : dirs) {
		        classes.addAll(findClasses(directory, packageName));
		    }
		    return classes;
	    
	    } catch (Exception e) {
	    	return classes;
	    }
	}
	
	/**
	 * Gets a list of classes defined a directory 
	 * 
	 * @param 		directory		Directory from which to look for the classes
	 * @param 		packageName		Name of the package from which to look for the classes
	 * @return		A list of classes defined in a package in a directory
	 * @since		1.0.0.0
	 */
	private List<Class<?>> findClasses(File directory, String packageName) {
	    
		List<Class<?>> classes = new ArrayList<Class<?>>();
	    
		try
		{
			if (!directory.exists()) {
		        return classes;
		    }
		    File[] files = directory.listFiles();
		    for (File file : files) {
		        if (file.isDirectory()) {
		            assert !file.getName().contains(".");
		            classes.addAll(findClasses(file, packageName + "." + file.getName()));
		        } else if (file.getName().endsWith(".class")) {
		        	Class<?> cls = Class.forName(packageName + '.' + file.getName().substring(0, file.getName().length() - 6));
		            if (cls != null && !cls.getSimpleName().isEmpty()) {
		            	classes.add(cls);
		            }
		        }
		    }
		    return classes;
		
		} catch (Exception e) {
			return classes;
		}
	}
	
	/**
	 * Gets a package with given package name
	 * 
	 * @param 		packageName		Name of the package
	 * @return		Package with given package name
	 * @since		1.0.0.0
	 */
	private Package getPackage(String packageName) {
		return Package.getPackage(packageName);
	}
}