// -----------------------------------------------------------------------
// <copyright file="SplashScreen.cs" company="NOKIA">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace MarbleLibrary.CustomControls
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Threading;
    using System.Windows;
    using System.Windows.Media.Animation;
    using System.Windows.Threading;

    /// <summary>
    /// TODO: Update summary.
    /// </summary>
    public static class SplashScreenUtility
    {
        /// <summary>
        /// 
        /// </summary>
        private static Window splashScreen;

        /// <summary>
        /// Get or set the splash screen window
        /// </summary>
        public static Window SplashScreen
        {
            get
            {
                return splashScreen;
            }
            set
            {
                splashScreen = value;
            }
        }

        /// <summary>
        /// Show splash screen
        /// </summary>
        public static void ShowSplashScreen()
        {
            if (splashScreen == null) return;

            splashScreen.Show();
        }

        /// <summary>
        /// Close splash screen
        /// </summary>
        public static void CloseSplashScreen()
        {
            if (splashScreen == null) return;

            splashScreen.Close();

            if (splashScreen is IDisposable)
                (splashScreen as IDisposable).Dispose();

            splashScreen = null;
        }
    }
}
