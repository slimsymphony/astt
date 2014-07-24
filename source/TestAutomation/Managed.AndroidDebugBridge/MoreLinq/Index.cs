using System.Collections.Generic;
using System.Linq;

namespace Managed.Adb.MoreLinq
{
    /// <summary>
    /// 
    /// </summary>
    public static partial class MoreEnumerable
    {
        /// <summary>
        /// Returns a sequence of <see cref="KeyValuePair{TKey,TValue}"/> 
        /// where the key is the zero-based index of the value in the source 
        /// sequence.
        /// </summary>
        /// <typeparam name="TSource">Type of elements in <paramref name="source"/> sequence.</typeparam>
        /// <param name="source">The source sequence.</param>
        /// <returns>A sequence of <see cref="KeyValuePair{TKey,TValue}"/>.</returns>
        /// <remarks>This operator uses deferred execution and streams its 
        /// results.</remarks>
        public static IEnumerable<KeyValuePair<int, TSource>> Index<TSource>(this IEnumerable<TSource> source)
        {
            return source.Index(0);
        }

        /// <summary>
        /// Returns a sequence of <see cref="KeyValuePair{TKey,TValue}"/> 
        /// where the key is the index of the value in the source sequence.
        /// An additional parameter specifies the starting index.
        /// </summary>
        /// <typeparam name="TSource">Type of elements in <paramref name="source"/> sequence.</typeparam>
        /// <param name="source">The source sequence.</param>
        /// <param name="startIndex"></param>
        /// <returns>A sequence of <see cref="KeyValuePair{TKey,TValue}"/>.</returns>
        /// <remarks>This operator uses deferred execution and streams its 
        /// results.</remarks>
        public static IEnumerable<KeyValuePair<int, TSource>> Index<TSource>(this IEnumerable<TSource> source, int startIndex)
        {
            return source.Select((item, index) => KeyValuePair.Create(startIndex + index, item));
        }
    }
}
