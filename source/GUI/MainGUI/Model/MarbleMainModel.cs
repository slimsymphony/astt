using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace Marble.Model
{
    /// <summary>
    /// Model holding general UI properties.
    /// </summary>
    internal class MarbleMainModel : INotifyPropertyChanged
    {
        private int totalTestCases;
        
        /// <summary>
        /// Property to hold number of cases in current testset.
        /// </summary>
        public int TotalTestCases
        {
            get { return this.totalTestCases; }
            set
            {
                this.totalTestCases = value;
                this.OnPropertyChanged("TotalTestCases");
            }
        }

        private int passedTestCases;
        
        /// <summary>
        /// Property to hold number of passed tests on current/previous run.
        /// </summary>
        public int PassedTestCases
        {
            get { return this.passedTestCases; }
            set
            {
                this.passedTestCases = value;
                this.OnPropertyChanged("PassedTestCases");
            }
        }

        private int failedTestCases;

        /// <summary>
        /// Property to hold number of failed tests on current/previous run.
        /// </summary>
        public int FailedTestCases
        {
            get { return this.failedTestCases; }
            set
            {
                this.failedTestCases = value;
                this.OnPropertyChanged("FailedTestCases");
            }
        }

        private int noResultTestCases;
        
        /// <summary>
        /// Property to hold number of tests that were not run on current/previous run.
        /// </summary>
        public int NoResultTestCases
        {
            get { return this.noResultTestCases; }
            set
            {
                this.noResultTestCases = value;
                this.OnPropertyChanged("NoResultTestCases");
            }
        }

        private double checkedTestCases;

        /// <summary>
        /// Property to hold number of checked test cases.
        /// </summary>
        public double CheckedTestCases
        {
            get { return this.checkedTestCases; }
            set
            {
                this.checkedTestCases = value;
                this.OnPropertyChanged("CheckedTestCases");
            }
        }

        private double testRunProgressValue;

        /// <summary>
        /// Property for storing current test case run total progress.
        /// </summary>
        public double TestRunProgressValue
        {
            get { return this.testRunProgressValue; }
            set
            {
                this.testRunProgressValue = value;
                this.OnPropertyChanged("TestRunProgressValue");
            }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        private void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        #endregion
    }
}
