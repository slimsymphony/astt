using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Marble.Views.Dialogs
{
    using System.ComponentModel;
    using System.Threading;
    using System.Windows.Media.Animation;
    using System.Windows.Media.Effects;
    using System.Windows.Threading;

    /// <summary>
    /// Interaction logic for MarbleSplashScreen.xaml
    /// </summary>
    public partial class MarbleSplashScreen : Window
    {
        private Storyboard closeStoryBoard { get; set; }

        public MarbleSplashScreen()
        {
            InitializeComponent();

            this.createFadeOutAnimation();
        }

        private bool closeStoryBoardCompleted = false;

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            if (!this.closeStoryBoardCompleted)
            {
                this.closeStoryBoard.Begin();
                e.Cancel = true;
            }
        }

        private void createFadeOutAnimation()
        {
            closeStoryBoard = new Storyboard();

            DoubleAnimation fadeOut = new DoubleAnimation(1.0, 0.0, TimeSpan.FromSeconds(2), FillBehavior.HoldEnd);
            fadeOut.BeginTime = TimeSpan.FromSeconds(0);

            closeStoryBoard = new Storyboard();
            Storyboard.SetTarget(fadeOut, this);
            Storyboard.SetTargetProperty(fadeOut, new PropertyPath("(Opacity)"));
            closeStoryBoard.Children.Add(fadeOut);
            this.Resources.Clear();
            this.Resources.Add("FadeOutEffect", closeStoryBoard);

            this.closeStoryBoard.Completed += delegate
                {
                    this.closeStoryBoardCompleted = true;
                    this.Close();
                };
        }
    }
}
