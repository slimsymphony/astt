using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;

namespace Managed.Adb.MoreLinq
{
    /// <summary>
    /// 
    /// </summary>
    public partial class MoreEnumerable
    {
        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="argument"></param>
        /// <param name="func"></param>
        internal static void ThrowIfNegative<T>(this int argument, Expression<Func<T, string>> func)
        {
            if (argument < 0)
            {
                ThrowException(s => new ArgumentOutOfRangeException(s), func);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="argument"></param>
        /// <param name="func"></param>
        internal static void ThrowIfNonPositive<T>(this int argument, Expression<Func<T, string>> func)
        {
            if (argument <= 0)
            {
                ThrowException(s => new ArgumentOutOfRangeException(s), func);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="argument"></param>
        /// <param name="func"></param>
        public static void ThrowIfNull<T>(this T argument, Expression<Func<T, string>> func) where T : class
        {
            if (argument == null)
            {
                ThrowException(s => new ArgumentNullException(s), func);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="argument"></param>
        /// <param name="func"></param>
        public static void ThrowIfNullOrEmpty(this string argument, Expression<Func<String, string>> func)
        {
            if (string.IsNullOrEmpty(argument))
            {
                ThrowException(s => new ArgumentNullException(s), func);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="argument"></param>
        /// <param name="func"></param>
        public static void ThrowIfNullOrWhiteSpace(this string argument, Expression<Func<String, string>> func)
        {
            if (string.IsNullOrEmpty(argument) || string.IsNullOrEmpty(argument.Trim()))
            {
                ThrowException(s => new ArgumentNullException(s), func);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <typeparam name="E"></typeparam>
        /// <param name="e"></param>
        /// <param name="func"></param>
        private static void ThrowException<T, E>(Func<string, E> e, Expression<Func<T, string>> func) where E : Exception
        {
            string name = string.Empty;
            Expression body = func.Body;
            if (body is MemberExpression)
                name = ((MemberExpression)body).Member.Name;
            throw e(name);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="argument"></param>
        /// <param name="name"></param>
        internal static void ThrowIfNull<T>(this T argument, string name) where T : class
        {
            if (argument == null)
            {
                throw new ArgumentNullException(name);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="argument"></param>
        /// <param name="name"></param>
        internal static void ThrowIfNullOrEmpty(this string argument, string name)
        {
            if (string.IsNullOrEmpty(argument))
            {
                throw new ArgumentNullException(name);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="argument"></param>
        /// <param name="name"></param>
        internal static void ThrowIfNullOrWhiteSpace(this string argument, string name)
        {
            if (string.IsNullOrEmpty(argument) || string.IsNullOrEmpty(argument.Trim()))
            {
                throw new ArgumentNullException(name);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="argument"></param>
        /// <param name="name"></param>
        internal static void ThrowIfNegative(this int argument, string name)
        {
            if (argument < 0)
            {
                throw new ArgumentOutOfRangeException(name);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="argument"></param>
        /// <param name="name"></param>
        internal static void ThrowIfNonPositive(this int argument, string name)
        {
            if (argument <= 0)
            {
                throw new ArgumentOutOfRangeException(name);
            }
        }
    }
}
