using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using TestAutomation.Gui.Marble.IPC.Interfaces;
using log4net;

namespace TestAutomation.Gui.Marble.IPC.Clients
{
    public class MarbleFwBlackBoxClient : IDisposable
    {
        private readonly MarbleWcfClient<IBlackBoxService> client;
        private const int defaultRetriesOnError = 5;
        private readonly ILog log;

        public MarbleFwBlackBoxClient(int servicePort = -1)
        {
            this.log = LogManager.GetLogger("BlackBoxServiceLogger");

            BlackBoxClientSettings settings = new BlackBoxClientSettings();
            if (servicePort != -1)
                settings.ServiceUri.ServicePort = servicePort;

            this.client = new MarbleWcfClient<IBlackBoxService>(settings, ServiceDefinitions.BlackBoxServiceEndpoint);
            this.log.Debug("MarbleFwBlackBoxClient initialized");
        }

        public void InitIoWarrior(bool grayboxEnabled)
        {
            try
            {
                this.log.Debug("MarbleFwBlackBoxClient InitIoWarrior()");
                this.client.DelegateExecutor(proxy => proxy.InitIoWarrior(grayboxEnabled));
                return;
            }
            catch
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient InitIoWarrior() failed. --> ResetIoWarrior()");
                    this.ResetIoWarrior();
                    return;
                }
                catch
                {
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient InitIoWarrior() --> ResetIoWarrior() Failed --> ResetIoWarrior(true)");
                        this.ResetIoWarrior(true);
                        return;
                    }
                    catch (Exception ex)
                    {
                        this.log.Error("MarbleFwBlackBoxClient InitIoWarrior() --> ResetIoWarrior() --> ResetIoWarrior(true) Failed", ex);
                        throw new InvalidOperationException("InitIoWarrior failed: " + ex.Message);
                    }
                }
            }
        }

        /// <summary>
        /// Resets IoWarrior by closing/reopening the HW
        /// </summary>
        /// <param name="resetAndExit">If set to true, resets IoWarrior by exiting the IoWarrior service process</param>
        public void ResetIoWarrior(bool resetAndExit = false)
        {
            this.client.DelegateExecutor(proxy => proxy.ResetIoWarrior(resetAndExit));
        }

        public void PowerOnPhone(int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient PowerOnPhone()");
                    this.powerOnPhone();
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError -1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient PowerOnPhone() Failed", e);
                        throw new InvalidOperationException("PowerOnPhone failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient PowerOnPhone() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient PowerOnPhone() --> ResetIoWarrior() succeeded, Executing PowerOnPhone again...");
                        this.powerOnPhone();
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient PowerOnPhone() Failed", ee);
                            throw new InvalidOperationException("PowerOnPhone failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient PowerOnPhone() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient PowerOnPhone() --> ResetIoWarrior(true) succeeded, Executing PowerOnPhone again...");
                            this.powerOnPhone();
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient PowerOnPhone() Failed", eee);
                                throw new InvalidOperationException("PowerOnPhone failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient PowerOnPhone() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void ResetPhonePower(int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ResetPhonePower()");
                    this.resetPhonePower();
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ResetPhonePower() Failed", e);
                        throw new InvalidOperationException("ResetPhonePower failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ResetPhonePower() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ResetPhonePower() --> ResetIoWarrior() succeeded, Executing ResetPhonePower again...");
                        this.resetPhonePower();
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ResetPhonePower() Failed", ee);
                            throw new InvalidOperationException("ResetPhonePower failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ResetPhonePower() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ResetPhonePower() --> ResetIoWarrior(true) succeeded, Executing ResetPhonePower again...");
                            this.resetPhonePower();
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ResetPhonePower() Failed", eee);
                                throw new InvalidOperationException("ResetPhonePower failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ResetPhonePower() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void ConnectPower(int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ConnectPower()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectPower());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ConnectPower() Failed", e);
                        throw new InvalidOperationException("ConnectPower failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ConnectPower() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ConnectPower() --> ResetIoWarrior() succeeded, Executing ConnectPower again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectPower());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ConnectPower() Failed", ee);
                            throw new InvalidOperationException("ConnectPower failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ConnectPower() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ConnectPower() --> ResetIoWarrior(true) succeeded, Executing ConnectPower again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectPower());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ConnectPower() Failed", eee);
                                throw new InvalidOperationException("ConnectPower failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ConnectPower() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void DisconnectPower(int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient DisconnectPower()");
                    this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient DisconnectPower() Failed", e);
                        throw new InvalidOperationException("DisconnectPower failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient DisconnectPower() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient DisconnectPower() --> ResetIoWarrior() succeeded, Executing DisconnectPower again...");
                        this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient DisconnectPower() Failed", ee);
                            throw new InvalidOperationException("DisconnectPower failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient DisconnectPower() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient DisconnectPower() --> ResetIoWarrior(true) succeeded, Executing DisconnectPower again...");
                            this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient DisconnectPower() Failed", eee);
                                throw new InvalidOperationException("DisconnectPower failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient DisconnectPower() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void DisconnectUsb(int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient DisconnectUsb()");
                    this.client.DelegateExecutor(proxy => proxy.DisconnectUsb());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient DisconnectUsb() Failed", e);
                        throw new InvalidOperationException("DisconnectUsb failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient DisconnectUsb() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient DisconnectUsb() --> ResetIoWarrior() succeeded, Executing DisconnectUsb again...");
                        this.client.DelegateExecutor(proxy => proxy.DisconnectUsb());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient DisconnectUsb() Failed", ee);
                            throw new InvalidOperationException("DisconnectUsb failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient DisconnectUsb() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient DisconnectUsb() --> ResetIoWarrior(true) succeeded, Executing DisconnectUsb again...");
                            this.client.DelegateExecutor(proxy => proxy.DisconnectUsb());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient DisconnectUsb() Failed", eee);
                                throw new InvalidOperationException("DisconnectUsb failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient DisconnectUsb() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void InitTouch()
        {
            this.log.Debug("MarbleFwBlackBoxClient InitTouch");
            this.client.DelegateExecutor(proxy => proxy.InitTouch());
        }

        public void InitAccelerometer()
        {
            this.log.Debug("MarbleFwBlackBoxClient InitAccelerometer");
            this.client.DelegateExecutor(proxy => proxy.InitAccelerometer());
        }

        public void ExecuteHwOperation(string operation, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ExecuteHwOperation()");
                    this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(operation));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ExecuteHwOperation() Failed", e);
                        throw new InvalidOperationException("ExecuteHwOperation failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ExecuteHwOperation() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ExecuteHwOperation() --> ResetIoWarrior() succeeded, Executing ExecuteHwOperation again...");
                        this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(operation));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ExecuteHwOperation() Failed", ee);
                            throw new InvalidOperationException("ExecuteHwOperation failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ExecuteHwOperation() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ExecuteHwOperation() --> ResetIoWarrior(true) succeeded, Executing ExecuteHwOperation again...");
                            this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(operation));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ExecuteHwOperation() Failed", eee);
                                throw new InvalidOperationException("ExecuteHwOperation failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ExecuteHwOperation() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public TouchStateResponse TouchEvent(List<MarbleTouchData> marbleTouchData)
        {
            this.log.Debug("MarbleFwBlackBoxClient TouchEvent()");
            TouchStateResponse resp = new TouchStateResponse();
            this.client.DelegateExecutor(proxy => resp = proxy.TouchEvent(marbleTouchData));
            return resp;
        }

        public TouchStateResponse PressKey(string key, int delay, int retriesOnError = defaultRetriesOnError)
        {
            TouchStateResponse resp = new TouchStateResponse();
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient PressKey()");
                    this.client.DelegateExecutor(proxy => resp = proxy.PressKey(key, delay));
                    return resp;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient PressKey() Failed", e);
                        throw new InvalidOperationException("PressKey " + key + ":" + delay + " failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient PressKey() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient PressKey() --> ResetIoWarrior() succeeded, Executing PressKey again...");
                        this.client.DelegateExecutor(proxy => resp = proxy.PressKey(key, delay));
                        return resp;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient PressKey() Failed", ee);
                            throw new InvalidOperationException("PressKey " + key + ":" + delay + " failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient PressKey() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient PressKey() --> ResetIoWarrior(true) succeeded, Executing PressKey again...");
                            this.client.DelegateExecutor(proxy => resp = proxy.PressKey(key, delay));
                            return resp;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient PressKey " + key + ":" + delay + " failed", eee);
                                throw new InvalidOperationException("PressKey " + key + ":" + delay + " failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient PressKey() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }

            return resp;
        }

        public void CloseAll()
        {
            try
            {
                this.log.Debug("MarbleFwBlackBoxClient CloseAll()");
                this.client.DelegateExecutor(proxy => proxy.CloseAll());
            }
            catch {/* Not handling this since we are closing anyway */}
        }

        public void CheckIoWarriorCards()
        {
            try
            {
                this.log.Debug("MarbleFwBlackBoxClient CloseAll()");
                this.client.DelegateExecutor(proxy => proxy.CheckIoWarriorCards());
                return;
            }
            catch
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient CheckIoWarriorCards() Failed --> ResetIoWarrior()");
                    this.ResetIoWarrior();
                    this.log.Debug("MarbleFwBlackBoxClient CheckIoWarriorCards() --> ResetIoWarrior() succeeded, Executing CheckIoWarriorCards again...");
                    this.client.DelegateExecutor(proxy => proxy.CheckIoWarriorCards());
                    return;
                }
                catch
                {
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient CheckIoWarriorCards() Failed again --> ResetIoWarrior(true)");
                        this.ResetIoWarrior(true);
                        this.log.Debug("MarbleFwBlackBoxClient CheckIoWarriorCards() --> ResetIoWarrior(true) succeeded, Executing CheckIoWarriorCards again...");
                        this.client.DelegateExecutor(proxy => proxy.CheckIoWarriorCards());
                        return;
                    }
                    catch (Exception ex)
                    {
                        throw new InvalidOperationException("CheckIoWarriorCards failed: " + ex.Message);
                    }
                }
            }
        }

        public void ConfigureBlackBox(string phoneModel)
        {
            this.log.Debug("MarbleFwBlackBoxClient ConfigureBlackBox(" + phoneModel + ")");
            this.client.DelegateExecutor(proxy => proxy.PhoneModelSelected(phoneModel));
        }

        public bool ConnectDefaultUsbAccessoryConnector(int retriesOnError = defaultRetriesOnError)
        {
            bool ret = false;

            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector()");
                    this.client.DelegateExecutor(proxy => ret = proxy.ConnectDefaultUsbAccessoryConnector());
                    return ret;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed", e);
                        throw new InvalidOperationException("ConnectDefaultUsbAccessoryConnector failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() --> ResetIoWarrior() succeeded, Executing ConnectDefaultUsbAccessoryConnector again...");
                        this.client.DelegateExecutor(proxy => ret = proxy.ConnectDefaultUsbAccessoryConnector());
                        return ret;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed", ee);
                            throw new InvalidOperationException("ConnectDefaultUsbAccessoryConnector failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() --> ResetIoWarrior(true) succeeded, Executing ConnectDefaultUsbAccessoryConnector again...");
                            this.client.DelegateExecutor(proxy => ret = proxy.ConnectDefaultUsbAccessoryConnector());
                            return ret;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed", eee);
                                throw new InvalidOperationException("ConnectDefaultUsbAccessoryConnector failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
            return ret;
        }

        public void ConnectUsb(UsbPort usbPort, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ConnectUsb()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectUsb(usbPort));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ConnectUsb() Failed", e);
                        throw new InvalidOperationException("ConnectUsb "+ usbPort + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ConnectUsb() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ConnectUsb() --> ResetIoWarrior() succeeded, Executing ConnectUsb again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectUsb(usbPort));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ConnectUsb() Failed", ee);
                            throw new InvalidOperationException("ConnectUsb " + usbPort + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ConnectUsb() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ConnectUsb() --> ResetIoWarrior(true) succeeded, Executing ConnectUsb again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectUsb(usbPort));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ConnectUsb() Failed", eee);
                                throw new InvalidOperationException("ConnectUsb " + usbPort + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ConnectUsb() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void ConnectSim(SimCard sim, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ConnectSim()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectSim(sim));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ConnectSim() Failed", e);
                        throw new InvalidOperationException("ConnectSim " + sim + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ConnectSim() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ConnectSim() --> ResetIoWarrior() succeeded, Executing ConnectSim again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectSim(sim));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ConnectSim() Failed", ee);
                            throw new InvalidOperationException("ConnectSim " + sim + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ConnectSim() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ConnectSim() --> ResetIoWarrior(true) succeeded, Executing ConnectSim again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectSim(sim));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ConnectSim() Failed", eee);
                                throw new InvalidOperationException("ConnectSim " + sim + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ConnectSim() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void ConnectMemoryCard(MemoryCard memoryCard, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ConnectMemoryCard()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectMemoryCard(memoryCard));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ConnectMemoryCard() Failed", e);
                        throw new InvalidOperationException("ConnectMemoryCard " + memoryCard + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ConnectMemoryCard() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ConnectMemoryCard() --> ResetIoWarrior() succeeded, Executing ConnectMemoryCard again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectMemoryCard(memoryCard));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ConnectMemoryCard() Failed", ee);
                            throw new InvalidOperationException("ConnectMemoryCard " + memoryCard + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ConnectMemoryCard() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ConnectMemoryCard --> ResetIoWarrior(true) succeeded, Executing ConnectMemoryCard again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectMemoryCard(memoryCard));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ConnectMemoryCard() Failed", eee);
                                throw new InvalidOperationException("ConnectMemoryCard " + memoryCard + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ConnectMemoryCard() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void ConnectAvPlug(AvPlug avPlugPort, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("MarbleFwBlackBoxClient ConnectAvPlug())");
                    this.client.DelegateExecutor(proxy => proxy.ConnectAvPlug(avPlugPort));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("MarbleFwBlackBoxClient ConnectAvPlug() Failed", e);
                        throw new InvalidOperationException("ConnectAvPlug " + avPlugPort + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("MarbleFwBlackBoxClient ConnectAvPlug() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("MarbleFwBlackBoxClient ConnectAvPlug() --> ResetIoWarrior() succeeded, Executing ConnectAvPlug again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectAvPlug(avPlugPort));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("MarbleFwBlackBoxClient ConnectAvPlug() Failed", ee);
                            throw new InvalidOperationException("ConnectAvPlug " + avPlugPort + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("MarbleFwBlackBoxClient ConnectAvPlug(() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("MarbleFwBlackBoxClient ConnectAvPlug( --> ResetIoWarrior(true) succeeded, Executing ConnectAvPlug( again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectAvPlug(avPlugPort));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("MarbleFwBlackBoxClient ConnectAvPlug() Failed", eee);
                                throw new InvalidOperationException("ConnectAvPlug " + avPlugPort + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("MarbleFwBlackBoxClient ConnectAvPlug() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void SetOrientation(string orientation)
        {
            this.log.Debug("MarbleFwBlackBoxClient SetOrientation: " + orientation);
            this.client.DelegateExecutor(proxy => proxy.SetOrientation(orientation));
        }

        public bool IsTouchEmulationEnabled
        {
            get
            {
                BlackBoxServiceSettings settings = null;
                this.client.DelegateExecutor(proxy => settings = proxy.Settings);
                return settings.General.TouchCard.EmulationEnabled;
            }
        }

        public bool IsAccelerometerEmulationEnabled
        {
            get
            {
                BlackBoxServiceSettings settings = null;
                this.client.DelegateExecutor(proxy => settings = proxy.Settings);
                return settings.General.AccelerometerCard.EmulationEnabled;
            }
        }

        public bool IsTouchReady
        {
            get
            {
                bool ret = false;
                this.client.DelegateExecutor(proxy => ret = proxy.IsTouchReady);
                return ret;
            }
        }

        public bool IsAccelerometerReady
        {
            get
            {
                bool ret = false;
                this.client.DelegateExecutor(proxy => ret = proxy.IsAccelerometerReady);
                return ret;
            }
        }

        public bool IsRequiredIoWCardsFound
        {
            get
            {
                bool ret = false;
                this.client.DelegateExecutor(proxy => ret = proxy.IsRequiredIoWCardsFound);
                return ret;
            }
        }

        public string CurrentConfiguredPhoneModel
        {
            get
            {
                BlackBoxServiceSettings settings = null;
                this.client.DelegateExecutor(proxy => settings = proxy.Settings);
                return settings.General.PhoneModel;
            }
        }

        public string DefaultUsbAccessoryConnector
        {
            get
            {
                BlackBoxServiceSettings settings = null;
                this.client.DelegateExecutor(proxy => settings = proxy.Settings);
                return settings.General.DefaultUsbAccessoryConnector.ToString();
            }
        }

        public string CurrentUsbAccessoryConnector
        {
            get
            {
                BlackBoxServiceSettings settings = null;
                this.client.DelegateExecutor(proxy => settings = proxy.Settings);
                return settings.General.CurrentUsbAccessoryConnector;
            }
        }

        public void Dispose()
        {
            this.log.Info("MarbleFwBlackBoxClient Dispose called. Calling Dispose() on WCF client");
            this.client.Dispose();
            this.log.Info("MarbleFwBlackBoxClient Dispose succeeded...");
        }

        public static void CloseBlackBoxServices()
        {
            closeServiceProcess("IOWarriorUI");
            closeServiceProcess("BlackBoxService");
            closeServiceProcess("IoWarriorService");
            closeServiceProcess("VideoRecorder");
        }

        private void powerOnPhone()
        {
            List<CommandSequenceItem> powerOnPhoneSequence = new List<CommandSequenceItem>();
            this.client.DelegateExecutor(proxy => powerOnPhoneSequence = proxy.PowerOnPhoneSequence);
            foreach (CommandSequenceItem seqItem in powerOnPhoneSequence)
            {
                mapBlackBoxCommand(seqItem);
            }

            this.client.DelegateExecutor(proxy => proxy.ConnectDefaultUsbAccessoryConnector());
        }

        private void resetPhonePower()
        {
            List<CommandSequenceItem> resetPhonePowerSequence = new List<CommandSequenceItem>();
            this.client.DelegateExecutor(proxy => resetPhonePowerSequence = proxy.ResetPhonePowerSequence);
            foreach (CommandSequenceItem seqItem in resetPhonePowerSequence)
            {
                mapBlackBoxCommand(seqItem);
            }

            this.client.DelegateExecutor(proxy => proxy.ConnectDefaultUsbAccessoryConnector());
        }

        private void mapBlackBoxCommand(CommandSequenceItem sequenceItem)
        {
            if (sequenceItem.BlackBoxCommand.StartsWith("KEYCODE"))
            {
                if (!string.IsNullOrEmpty(sequenceItem.Attribute))
                {
                    this.client.DelegateExecutor(proxy => proxy.PressKey(sequenceItem.BlackBoxCommand, int.Parse(sequenceItem.Attribute)));
                }
                else
                {
                    this.client.DelegateExecutor(proxy => proxy.PressKey(sequenceItem.BlackBoxCommand, 100));
                }
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.ConnectUsbCommand)
            {
                this.client.DelegateExecutor(proxy => proxy.ConnectUsb((UsbPort)Enum.Parse(typeof(UsbPort), sequenceItem.Attribute)));
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.SleepCommand)
            {
                Thread.Sleep(int.Parse(sequenceItem.Attribute));
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.ConnectPowerCommand)
            {
                this.client.DelegateExecutor(proxy => proxy.ConnectPower());
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.DisconnectPowerCommand)
            {
                this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
            }
            else if (sequenceItem.BlackBoxCommand == BlackBoxServiceSettings.ResetTouchCommand)
            {
                this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(BlackBoxServiceSettings.ResetTouchCommand));
            }
        }

        private static void closeServiceProcess(string serviceProcess)
        {
            var processes = Process.GetProcessesByName(serviceProcess);
            if (processes.Length > 0)
            {
                foreach (var process in processes)
                {
                    try
                    {
                        // Hack: set process priority so that in the BlackBoxService process we can identify that the process is closed by calling Process.CloseMainWindow instead of
                        // pressing the "Close Service" button in the BlackBoxService GUI.
                        if (serviceProcess == "BlackBoxService")
                            process.PriorityClass = ProcessPriorityClass.RealTime;
                    }
                    catch (Exception ex)
                    {
                        writeEventLog("Set PriorityClass of BlackBoxService failed: " + ex.Message);
                    }

                    try
                    {
                        if (!process.CloseMainWindow())
                        {
                            process.Kill();
                        }
                        else
                        {
                            if (!process.WaitForExit(5000))
                            {
                                process.Kill();
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        writeEventLog("closeServiceProcess failed: " + ex.Message);
                    }
                }
            }
        }

        private static void writeEventLog(string error)
        {
            string sSource = "MarbleFwBlackBoxClient";
            string sLog = "Application";

            if (!EventLog.SourceExists(sSource))
                EventLog.CreateEventSource(sSource, sLog);

            EventLog.WriteEntry(sSource, error, EventLogEntryType.Error);
        }
    }
}
