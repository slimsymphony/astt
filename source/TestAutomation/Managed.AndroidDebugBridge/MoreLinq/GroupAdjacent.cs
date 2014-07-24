using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;

namespace Managed.Adb.MoreLinq
{
    /// <summary>
    /// 
    /// </summary>
    public static partial class MoreEnumerable
    {
        /// <summary>
        /// Groups the adjacent elements of a sequence according to a 
        /// specified key selector function.
        /// </summary>
        /// <typeparam name="TSource">The type of the elements of 
        /// <paramref name="source"/>.</typeparam>
        /// <typeparam name="TKey">The type of the key returned by 
        /// <paramref name="keySelector"/>.</typeparam>
        /// <param name="source">A sequence whose elements to group.</param>
        /// <param name="keySelector">A function to extract the key for each 
        /// element.</param>
        /// <returns>A sequence of groupings where each grouping
        /// (<see cref="IGrouping{TKey,TElement}"/>) contains the key
        /// and the adjacent elements in the same order as found in the 
        /// source sequence.</returns>
        /// <remarks>
        /// This method is implemented by using deferred execution and 
        /// streams the groupings. The grouping elements, however, are 
        /// buffered. Each grouping is therefore yielded as soon as it 
        /// is complete and before the next grouping occurs.
        /// </remarks>
        public static IEnumerable<IGrouping<TKey, TSource>> GroupAdjacent<TSource, TKey>(
                this IEnumerable<TSource> source,
                Func<TSource, TKey> keySelector)
        {
            return GroupAdjacent(source, keySelector, null);
        }

        /// <summary>
        /// Groups the adjacent elements of a sequence according to a 
        /// specified key selector function and compares the keys by using a 
        /// specified comparer.
        /// </summary>
        /// <typeparam name="TSource">The type of the elements of 
        /// <paramref name="source"/>.</typeparam>
        /// <typeparam name="TKey">The type of the key returned by 
        /// <paramref name="keySelector"/>.</typeparam>
        /// <param name="source">A sequence whose elements to group.</param>
        /// <param name="keySelector">A function to extract the key for each 
        /// element.</param>
        /// <param name="comparer">An <see cref="IEqualityComparer{T}"/> to 
        /// compare keys.</param>
        /// <returns>A sequence of groupings where each grouping
        /// (<see cref="IGrouping{TKey,TElement}"/>) contains the key
        /// and the adjacent elements in the same order as found in the 
        /// source sequence.</returns>
        /// <remarks>
        /// This method is implemented by using deferred execution and 
        /// streams the groupings. The grouping elements, however, are 
        /// buffered. Each grouping is therefore yielded as soon as it 
        /// is complete and before the next grouping occurs.
        /// </remarks>
        public static IEnumerable<IGrouping<TKey, TSource>> GroupAdjacent<TSource, TKey>(
                this IEnumerable<TSource> source,
                Func<TSource, TKey> keySelector,
                IEqualityComparer<TKey> comparer)
        {
            if (source == null) throw new ArgumentNullException("source");
            if (keySelector == null) throw new ArgumentNullException("keySelector");

            return GroupAdjacent(source, keySelector, e => e, comparer);
        }

        /// <summary>
        /// Groups the adjacent elements of a sequence according to a 
        /// specified key selector function and projects the elements for 
        /// each group by using a specified function.
        /// </summary>
        /// <typeparam name="TSource">The type of the elements of 
        /// <paramref name="source"/>.</typeparam>
        /// <typeparam name="TKey">The type of the key returned by 
        /// <paramref name="keySelector"/>.</typeparam>
        /// <typeparam name="TElement">The type of the elements in the
        /// resulting groupings.</typeparam>
        /// <param name="source">A sequence whose elements to group.</param>
        /// <param name="keySelector">A function to extract the key for each 
        /// element.</param>
        /// <param name="elementSelector">A function to map each source 
        /// element to an element in the resulting grouping.</param>
        /// <returns>A sequence of groupings where each grouping
        /// (<see cref="IGrouping{TKey,TElement}"/>) contains the key
        /// and the adjacent elements (of type <typeparamref name="TElement"/>) 
        /// in the same order as found in the source sequence.</returns>
        /// <remarks>
        /// This method is implemented by using deferred execution and 
        /// streams the groupings. The grouping elements, however, are 
        /// buffered. Each grouping is therefore yielded as soon as it 
        /// is complete and before the next grouping occurs.
        /// </remarks>
        public static IEnumerable<IGrouping<TKey, TElement>> GroupAdjacent<TSource, TKey, TElement>(
                this IEnumerable<TSource> source,
                Func<TSource, TKey> keySelector,
                Func<TSource, TElement> elementSelector)
        {
            return GroupAdjacent(source, keySelector, elementSelector, null);
        }

        /// <summary>
        /// Groups the adjacent elements of a sequence according to a 
        /// specified key selector function. The keys are compared by using 
        /// a comparer and each group's elements are projected by using a 
        /// specified function.
        /// </summary>
        /// <typeparam name="TSource">The type of the elements of 
        /// <paramref name="source"/>.</typeparam>
        /// <typeparam name="TKey">The type of the key returned by 
        /// <paramref name="keySelector"/>.</typeparam>
        /// <typeparam name="TElement">The type of the elements in the
        /// resulting groupings.</typeparam>
        /// <param name="source">A sequence whose elements to group.</param>
        /// <param name="keySelector">A function to extract the key for each 
        /// element.</param>
        /// <param name="elementSelector">A function to map each source 
        /// element to an element in the resulting grouping.</param>
        /// <param name="comparer">An <see cref="IEqualityComparer{T}"/> to 
        /// compare keys.</param>
        /// <returns>A sequence of groupings where each grouping
        /// (<see cref="IGrouping{TKey,TElement}"/>) contains the key
        /// and the adjacent elements (of type <typeparamref name="TElement"/>) 
        /// in the same order as found in the source sequence.</returns>
        /// <remarks>
        /// This method is implemented by using deferred execution and 
        /// streams the groupings. The grouping elements, however, are 
        /// buffered. Each grouping is therefore yielded as soon as it 
        /// is complete and before the next grouping occurs.
        /// </remarks>
        public static IEnumerable<IGrouping<TKey, TElement>> GroupAdjacent<TSource, TKey, TElement>(
                this IEnumerable<TSource> source,
                Func<TSource, TKey> keySelector,
                Func<TSource, TElement> elementSelector,
                IEqualityComparer<TKey> comparer)
        {
            source.ThrowIfNull("source");
            keySelector.ThrowIfNull("keySelector");
            elementSelector.ThrowIfNull("elementSelector");

            return GroupAdjacentImpl(source, keySelector, elementSelector,
                                                             comparer ?? EqualityComparer<TKey>.Default);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="TSource"></typeparam>
        /// <typeparam name="TKey"></typeparam>
        /// <typeparam name="TElement"></typeparam>
        /// <param name="source"></param>
        /// <param name="keySelector"></param>
        /// <param name="elementSelector"></param>
        /// <param name="comparer"></param>
        /// <returns></returns>
        private static IEnumerable<IGrouping<TKey, TElement>> GroupAdjacentImpl<TSource, TKey, TElement>(
                this IEnumerable<TSource> source,
                Func<TSource, TKey> keySelector,
                Func<TSource, TElement> elementSelector,
                IEqualityComparer<TKey> comparer)
        {
            Debug.Assert(source != null);
            Debug.Assert(keySelector != null);
            Debug.Assert(elementSelector != null);
            Debug.Assert(comparer != null);

            using (var iterator = source.Select(item => KeyValuePair.Create(keySelector(item), elementSelector(item)))
                                                                    .GetEnumerator())
            {
                var group = default(TKey);
                var members = (List<TElement>)null;

                while (iterator.MoveNext())
                {
                    var item = iterator.Current;
                    if (members != null && comparer.Equals(group, item.Key))
                    {
                        members.Add(item.Value);
                    }
                    else
                    {
                        if (members != null)
                            yield return CreateGroupAdjacentGrouping(group, members);
                        group = item.Key;
                        members = new List<TElement> { item.Value };
                    }
                }

                if (members != null)
                    yield return CreateGroupAdjacentGrouping(group, members);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="TKey"></typeparam>
        /// <typeparam name="TElement"></typeparam>
        /// <param name="key"></param>
        /// <param name="members"></param>
        /// <returns></returns>
        private static Grouping<TKey, TElement> CreateGroupAdjacentGrouping<TKey, TElement>(TKey key, IList<TElement> members)
        {
            Debug.Assert(members != null);
            return Grouping.Create(key, members.IsReadOnly ? members : new ReadOnlyCollection<TElement>(members));
        }

        /// <summary>
        /// 
        /// </summary>
        static class Grouping
        {
            public static Grouping<TKey, TElement> Create<TKey, TElement>(TKey key, IEnumerable<TElement> members)
            {
                return new Grouping<TKey, TElement>(key, members);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="TKey"></typeparam>
        /// <typeparam name="TElement"></typeparam>
#if !NO_SERIALIZATION_ATTRIBUTES
        [Serializable]
#endif
        private sealed class Grouping<TKey, TElement> : IGrouping<TKey, TElement>
        {
            private readonly IEnumerable<TElement> _members;

            /// <summary>
            /// 
            /// </summary>
            /// <param name="key"></param>
            /// <param name="members"></param>
            public Grouping(TKey key, IEnumerable<TElement> members)
            {
                Debug.Assert(members != null);
                Key = key;
                _members = members;
            }

            /// <summary>
            /// 
            /// </summary>
            public TKey Key { get; private set; }

            /// <summary>
            /// 
            /// </summary>
            /// <returns></returns>
            public IEnumerator<TElement> GetEnumerator()
            {
                return _members.GetEnumerator();
            }

            /// <summary>
            /// 
            /// </summary>
            /// <returns></returns>
            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }
    }
}
