using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestAutomation.Client
{
    /// <summary>
    /// Delegate for overcoming the IronPython's bug of not distinguishing dynamic methods and dynamic property calls
    /// In case of dynamic property call, an instance of this handler is returned for further invoking.
    /// </summary>
    /// <param name="args">Method parameters</param>
    /// <returns></returns>
    public delegate object DynamicInvoker(params object[] args);

    /// <summary>
    /// Handler delegate for Accessibility events sent by the remote device
    /// </summary>
    /// <param name="args">Accessibility event</param>
    public delegate void AccessibilityEventHandler(AccessibilityEvent args);

    /// <summary>
    /// Handler delegate for Test server trace messages
    /// </summary>
    /// <param name="args">Test server trace message</param>
    public delegate void TestAutomationServerTraceHandler(string args);

    /// <summary>
    /// Handler delegate for notifying that the test server has been started
    /// </summary>
    public delegate void TestAutomationServerStartedHandler();

    /// <summary>
    /// Handler delegate for notifying that the test server has been stopped/terminated
    /// </summary>
    public delegate void TestAutomationServerExitHandler();

    /// <summary>
    /// Handler delegate for receiving the progress of pushing the server archive to the remote device
    /// </summary>
    /// <param name="percentage">Percentage of push done.</param>
    /// <param name="transferred">Bytes transferred</param>
    /// <param name="total">Bytes total</param>
    public delegate void TestAutomationServerPushProgressHandler(int percentage, long transferred, long total);
}
