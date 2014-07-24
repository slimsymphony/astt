using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace Nokia.Iowarrior
{
    internal static class ObjectFactory<ObjectType>
    {
        /// <summary>
        /// Constructs a new object of given objectType using a constructor matching the constructorParameters.
        /// "objectType" must be a (sub-)class of type "ObjectType".
        /// </summary>
        /// <param name="objectType">Type of the object to be created.</param>
        /// <param name="constructorParameters">Parameters to the constructor.</param>
        /// <returns>New instance of objectType.</returns>
        /// <exception cref="ArgumentException">Raised, if objectType is no (sub-)class of ObjectType.</exception>
        internal static ObjectType New(Type objectType, Object[] constructorParameters)
        {
            if (objectType.IsSubclassOf(typeof(ObjectType)))
            {
                Type[] constructorParamTypes = new Type[constructorParameters.Length];
                for (int i = 0; i < constructorParameters.Length; i++)
                    constructorParamTypes[i] = constructorParameters[i].GetType();
                ConstructorInfo c = objectType.GetConstructor(constructorParamTypes);
                return (ObjectType)c.Invoke(constructorParameters);
            }
            else
            {
                throw new ArgumentException(String.Format("{0} is not subclass of {1}.", objectType.Name, typeof(ObjectType).Name ), "objectType");
            }
        }

        /// <summary>
        /// Constructs a new object of given objectType. See also: New(objectType, constructorParameters).
        /// </summary>
        /// <param name="objectType">Type of the object to be created.</param>
        /// <param name="constructorParameters">Parameters to the constructor.</param>
        /// <returns>New instance of objectType or null, if object creation failed.</returns>
        internal static ObjectType TryNew(Type objectType, Object[] constructorParameters)
        {
            ObjectType newObject = default(ObjectType);

            try
            {
                newObject = New(objectType, constructorParameters);
            }
            catch
            {
                // ignore any errors here
            }

            return newObject;
        }
    }
}
