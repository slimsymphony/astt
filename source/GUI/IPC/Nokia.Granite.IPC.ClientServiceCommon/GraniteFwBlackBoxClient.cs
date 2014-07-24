using System;
using System.Collections.Generic;
using System.Diagnostics;
using Nokia.Granite.IPC.Interfaces;
using log4net;

namespace Nokia.Granite.IPC.Clients
{
    public class GraniteFwBlackBoxClient : IDisposable
    {
        private readonly GraniteWcfClient<IBlackBoxService> client;
        private const int defaultRetriesOnError = 5;
        private readonly ILog log;

        public GraniteFwBlackBoxClient(int servicePort = -1)
        {
            this.log = LogManager.GetLogger("BlackBoxServiceLogger");

            BlackBoxClientSettings settings = new BlackBoxClientSettings();
            if (servicePort != -1)
                settings.ServiceUri.ServicePort = servicePort;

            this.client = new GraniteWcfClient<IBlackBoxService>(settings, ServiceDefinitions.BlackBoxServiceEndpoint);
            this.log.Debug("GraniteFwBlackBoxClient initialized");
        }

        public void InitIoWarrior()
        {
            try
            {
                this.log.Debug("GraniteFwBlackBoxClient InitIoWarrior()");
                this.client.DelegateExecutor(proxy => proxy.InitIoWarrior());
                return;
            }
            catch
            {
                try
                {
                    this.log.Debug("GraniteFwBlackBoxClient InitIoWarrior() failed. --> ResetIoWarrior()");
                    this.ResetIoWarrior();
                    return;
                }
                catch
                {
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient InitIoWarrior() --> ResetIoWarrior() Failed --> ResetIoWarrior(true)");
                        this.ResetIoWarrior(true);
                        return;
                    }
                    catch (Exception ex)
                    {
                        this.log.Error("GraniteFwBlackBoxClient InitIoWarrior() --> ResetIoWarrior() --> ResetIoWarrior(true) Failed", ex);
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
                    this.log.Debug("GraniteFwBlackBoxClient PowerOnPhone()");
                    this.client.DelegateExecutor(proxy => proxy.PowerOnPhone());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError -1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient PowerOnPhone() Failed", e);
                        throw new InvalidOperationException("PowerOnPhone failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient PowerOnPhone() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient PowerOnPhone() --> ResetIoWarrior() succeeded, Executing PowerOnPhone again...");
                        this.client.DelegateExecutor(proxy => proxy.PowerOnPhone());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient PowerOnPhone() Failed", ee);
                            throw new InvalidOperationException("PowerOnPhone failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient PowerOnPhone() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient PowerOnPhone() --> ResetIoWarrior(true) succeeded, Executing PowerOnPhone again...");
                            this.client.DelegateExecutor(proxy => proxy.PowerOnPhone());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient PowerOnPhone() Failed", eee);
                                throw new InvalidOperationException("PowerOnPhone failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient PowerOnPhone() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient ResetPhonePower()");
                    this.client.DelegateExecutor(proxy => proxy.ResetPhonePower());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ResetPhonePower() Failed", e);
                        throw new InvalidOperationException("ResetPhonePower failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ResetPhonePower() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ResetPhonePower() --> ResetIoWarrior() succeeded, Executing ResetPhonePower again...");
                        this.client.DelegateExecutor(proxy => proxy.ResetPhonePower());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ResetPhonePower() Failed", ee);
                            throw new InvalidOperationException("ResetPhonePower failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ResetPhonePower() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ResetPhonePower() --> ResetIoWarrior(true) succeeded, Executing ResetPhonePower again...");
                            this.client.DelegateExecutor(proxy => proxy.ResetPhonePower());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ResetPhonePower() Failed", eee);
                                throw new InvalidOperationException("ResetPhonePower failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ResetPhonePower() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient ConnectPower()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectPower());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ConnectPower() Failed", e);
                        throw new InvalidOperationException("ConnectPower failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ConnectPower() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ConnectPower() --> ResetIoWarrior() succeeded, Executing ConnectPower again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectPower());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ConnectPower() Failed", ee);
                            throw new InvalidOperationException("ConnectPower failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ConnectPower() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ConnectPower() --> ResetIoWarrior(true) succeeded, Executing ConnectPower again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectPower());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ConnectPower() Failed", eee);
                                throw new InvalidOperationException("ConnectPower failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ConnectPower() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient DisconnectPower()");
                    this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient DisconnectPower() Failed", e);
                        throw new InvalidOperationException("DisconnectPower failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient DisconnectPower() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient DisconnectPower() --> ResetIoWarrior() succeeded, Executing DisconnectPower again...");
                        this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient DisconnectPower() Failed", ee);
                            throw new InvalidOperationException("DisconnectPower failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient DisconnectPower() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient DisconnectPower() --> ResetIoWarrior(true) succeeded, Executing DisconnectPower again...");
                            this.client.DelegateExecutor(proxy => proxy.DisconnectPower());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient DisconnectPower() Failed", eee);
                                throw new InvalidOperationException("DisconnectPower failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient DisconnectPower() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient DisconnectUsb()");
                    this.client.DelegateExecutor(proxy => proxy.DisconnectUsb());
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient DisconnectUsb() Failed", e);
                        throw new InvalidOperationException("DisconnectUsb failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient DisconnectUsb() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient DisconnectUsb() --> ResetIoWarrior() succeeded, Executing DisconnectUsb again...");
                        this.client.DelegateExecutor(proxy => proxy.DisconnectUsb());
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient DisconnectUsb() Failed", ee);
                            throw new InvalidOperationException("DisconnectUsb failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient DisconnectUsb() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient DisconnectUsb() --> ResetIoWarrior(true) succeeded, Executing DisconnectUsb again...");
                            this.client.DelegateExecutor(proxy => proxy.DisconnectUsb());
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient DisconnectUsb() Failed", eee);
                                throw new InvalidOperationException("DisconnectUsb failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient DisconnectUsb() Failed again --> ResetIoWarrior() one more time...");
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
            this.log.Debug("GraniteFwBlackBoxClient InitTouch");
            this.client.DelegateExecutor(proxy => proxy.InitTouch());
        }

        public void InitAccelerometer()
        {
            this.log.Debug("GraniteFwBlackBoxClient InitAccelerometer");
            this.client.DelegateExecutor(proxy => proxy.InitAccelerometer());
        }

        public void ExecuteHwOperation(string operation, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("GraniteFwBlackBoxClient ExecuteHwOperation()");
                    this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(operation));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ExecuteHwOperation() Failed", e);
                        throw new InvalidOperationException("ExecuteHwOperation failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ExecuteHwOperation() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ExecuteHwOperation() --> ResetIoWarrior() succeeded, Executing ExecuteHwOperation again...");
                        this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(operation));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ExecuteHwOperation() Failed", ee);
                            throw new InvalidOperationException("ExecuteHwOperation failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ExecuteHwOperation() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ExecuteHwOperation() --> ResetIoWarrior(true) succeeded, Executing ExecuteHwOperation again...");
                            this.client.DelegateExecutor(proxy => proxy.ExecuteHwOperation(operation));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ExecuteHwOperation() Failed", eee);
                                throw new InvalidOperationException("ExecuteHwOperation failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ExecuteHwOperation() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void TouchEvent(List<GraniteTouchData> graniteTouchData)
        {
            this.log.Debug("GraniteFwBlackBoxClient TouchEvent()");
            this.client.DelegateExecutor(proxy => proxy.TouchEvent(graniteTouchData));
        }

        public void PressKey(string key, int delay, int retriesOnError = defaultRetriesOnError)
        {
            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("GraniteFwBlackBoxClient PressKey()");
                    this.client.DelegateExecutor(proxy => proxy.PressKey(key, delay));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient PressKey() Failed", e);
                        throw new InvalidOperationException("PressKey " + key + ":" + delay + " failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient PressKey() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient PressKey() --> ResetIoWarrior() succeeded, Executing PressKey again...");
                        this.client.DelegateExecutor(proxy => proxy.PressKey(key, delay));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient PressKey() Failed", ee);
                            throw new InvalidOperationException("PressKey " + key + ":" + delay + " failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient PressKey() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient PressKey() --> ResetIoWarrior(true) succeeded, Executing PressKey again...");
                            this.client.DelegateExecutor(proxy => proxy.PressKey(key, delay));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient PressKey " + key + ":" + delay + " failed", eee);
                                throw new InvalidOperationException("PressKey " + key + ":" + delay + " failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient PressKey() Failed again --> ResetIoWarrior() one more time...");
                                this.ResetIoWarrior();
                            }
                            catch { /*Try to reset one more time */}
                        }
                    }
                }
            }
        }

        public void CloseAll()
        {
            try
            {
                this.log.Debug("GraniteFwBlackBoxClient CloseAll()");
                this.client.DelegateExecutor(proxy => proxy.CloseAll());
            }
            catch {/* Not handling this since we are closing anyway */}
        }

        public void CheckIoWarriorCards()
        {
            try
            {
                this.log.Debug("GraniteFwBlackBoxClient CloseAll()");
                this.client.DelegateExecutor(proxy => proxy.CheckIoWarriorCards());
                return;
            }
            catch
            {
                try
                {
                    this.log.Debug("GraniteFwBlackBoxClient CheckIoWarriorCards() Failed --> ResetIoWarrior()");
                    this.ResetIoWarrior();
                    this.log.Debug("GraniteFwBlackBoxClient CheckIoWarriorCards() --> ResetIoWarrior() succeeded, Executing CheckIoWarriorCards again...");
                    this.client.DelegateExecutor(proxy => proxy.CheckIoWarriorCards());
                    return;
                }
                catch
                {
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient CheckIoWarriorCards() Failed again --> ResetIoWarrior(true)");
                        this.ResetIoWarrior(true);
                        this.log.Debug("GraniteFwBlackBoxClient CheckIoWarriorCards() --> ResetIoWarrior(true) succeeded, Executing CheckIoWarriorCards again...");
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
            this.log.Debug("GraniteFwBlackBoxClient ConfigureBlackBox(" + phoneModel + ")");
            this.client.DelegateExecutor(proxy => proxy.PhoneModelSelected(phoneModel));
        }

        public bool ConnectDefaultUsbAccessoryConnector(int retriesOnError = defaultRetriesOnError)
        {
            bool ret = false;

            for (int i = 0; i < retriesOnError; i++)
            {
                try
                {
                    this.log.Debug("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector()");
                    this.client.DelegateExecutor(proxy => ret = proxy.ConnectDefaultUsbAccessoryConnector());
                    return ret;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed", e);
                        throw new InvalidOperationException("ConnectDefaultUsbAccessoryConnector failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() --> ResetIoWarrior() succeeded, Executing ConnectDefaultUsbAccessoryConnector again...");
                        this.client.DelegateExecutor(proxy => ret = proxy.ConnectDefaultUsbAccessoryConnector());
                        return ret;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed", ee);
                            throw new InvalidOperationException("ConnectDefaultUsbAccessoryConnector failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() --> ResetIoWarrior(true) succeeded, Executing ConnectDefaultUsbAccessoryConnector again...");
                            this.client.DelegateExecutor(proxy => ret = proxy.ConnectDefaultUsbAccessoryConnector());
                            return ret;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed", eee);
                                throw new InvalidOperationException("ConnectDefaultUsbAccessoryConnector failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ConnectDefaultUsbAccessoryConnector() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient ConnectUsb()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectUsb(usbPort));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ConnectUsb() Failed", e);
                        throw new InvalidOperationException("ConnectUsb "+ usbPort + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ConnectUsb() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ConnectUsb() --> ResetIoWarrior() succeeded, Executing ConnectUsb again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectUsb(usbPort));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ConnectUsb() Failed", ee);
                            throw new InvalidOperationException("ConnectUsb " + usbPort + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ConnectUsb() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ConnectUsb() --> ResetIoWarrior(true) succeeded, Executing ConnectUsb again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectUsb(usbPort));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ConnectUsb() Failed", eee);
                                throw new InvalidOperationException("ConnectUsb " + usbPort + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ConnectUsb() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient ConnectSim()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectSim(sim));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ConnectSim() Failed", e);
                        throw new InvalidOperationException("ConnectSim " + sim + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ConnectSim() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ConnectSim() --> ResetIoWarrior() succeeded, Executing ConnectSim again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectSim(sim));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ConnectSim() Failed", ee);
                            throw new InvalidOperationException("ConnectSim " + sim + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ConnectSim() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ConnectSim() --> ResetIoWarrior(true) succeeded, Executing ConnectSim again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectSim(sim));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ConnectSim() Failed", eee);
                                throw new InvalidOperationException("ConnectSim " + sim + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ConnectSim() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient ConnectMemoryCard()");
                    this.client.DelegateExecutor(proxy => proxy.ConnectMemoryCard(memoryCard));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ConnectMemoryCard() Failed", e);
                        throw new InvalidOperationException("ConnectMemoryCard " + memoryCard + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ConnectMemoryCard() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ConnectMemoryCard() --> ResetIoWarrior() succeeded, Executing ConnectMemoryCard again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectMemoryCard(memoryCard));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ConnectMemoryCard() Failed", ee);
                            throw new InvalidOperationException("ConnectMemoryCard " + memoryCard + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ConnectMemoryCard() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ConnectMemoryCard --> ResetIoWarrior(true) succeeded, Executing ConnectMemoryCard again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectMemoryCard(memoryCard));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ConnectMemoryCard() Failed", eee);
                                throw new InvalidOperationException("ConnectMemoryCard " + memoryCard + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ConnectMemoryCard() Failed again --> ResetIoWarrior() one more time...");
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
                    this.log.Debug("GraniteFwBlackBoxClient ConnectAvPlug())");
                    this.client.DelegateExecutor(proxy => proxy.ConnectAvPlug(avPlugPort));
                    return;
                }
                catch (Exception e)
                {
                    if (i == retriesOnError - 1)
                    {
                        this.log.Error("GraniteFwBlackBoxClient ConnectAvPlug() Failed", e);
                        throw new InvalidOperationException("ConnectAvPlug " + avPlugPort + "failed: " + e.Message);
                    }
                    try
                    {
                        this.log.Debug("GraniteFwBlackBoxClient ConnectAvPlug() Failed --> ResetIoWarrior()");
                        this.ResetIoWarrior();
                        this.log.Debug("GraniteFwBlackBoxClient ConnectAvPlug() --> ResetIoWarrior() succeeded, Executing ConnectAvPlug again...");
                        this.client.DelegateExecutor(proxy => proxy.ConnectAvPlug(avPlugPort));
                        return;
                    }
                    catch (Exception ee)
                    {
                        if (i == retriesOnError - 1)
                        {
                            this.log.Error("GraniteFwBlackBoxClient ConnectAvPlug() Failed", ee);
                            throw new InvalidOperationException("ConnectAvPlug " + avPlugPort + "failed: " + ee.Message);
                        }
                        try
                        {
                            this.log.Debug("GraniteFwBlackBoxClient ConnectAvPlug(() Failed again --> ResetIoWarrior(true)");
                            this.ResetIoWarrior(true);
                            this.log.Debug("GraniteFwBlackBoxClient ConnectAvPlug( --> ResetIoWarrior(true) succeeded, Executing ConnectAvPlug( again...");
                            this.client.DelegateExecutor(proxy => proxy.ConnectAvPlug(avPlugPort));
                            return;
                        }
                        catch (Exception eee)
                        {
                            if (i == retriesOnError - 1)
                            {
                                this.log.Error("GraniteFwBlackBoxClient ConnectAvPlug() Failed", eee);
                                throw new InvalidOperationException("ConnectAvPlug " + avPlugPort + "failed: " + eee.Message);
                            }
                            try
                            {
                                this.log.Debug("GraniteFwBlackBoxClient ConnectAvPlug() Failed again --> ResetIoWarrior() one more time...");
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
            this.log.Debug("GraniteFwBlackBoxClient SetOrientation: " + orientation);
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
            this.log.Info("GraniteFwBlackBoxClient Dispose called. Calling Dispose() on WCF client");
            this.client.Dispose();
            this.log.Info("GraniteFwBlackBoxClient Dispose succeeded...");
        }

        public static void CloseBlackBoxServices()
        {
            closeServiceProcess("IOWarriorUI");
            closeServiceProcess("BlackBoxService");
            closeServiceProcess("IoWarriorService");
            closeServiceProcess("VideoRecorder");
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
            string sSource = "GraniteFwBlackBoxClient";
            string sLog = "Application";

            if (!EventLog.SourceExists(sSource))
                EventLog.CreateEventSource(sSource, sLog);

            EventLog.WriteEntry(sSource, error, EventLogEntryType.Error);
        }
    }
}
