/*
 * Copyright (C) 2009 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you ay not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package com.googlecode.android_scripting.activity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Binder;
import android.os.IBinder;
import android.preference.PreferenceManager;

import com.googlecode.android_scripting.AndroidProxy;
import com.googlecode.android_scripting.BaseApplication;
import com.googlecode.android_scripting.Constants;
import com.googlecode.android_scripting.ForegroundService;
import com.googlecode.android_scripting.Log;
import com.googlecode.android_scripting.ScriptLauncher;
import com.googlecode.android_scripting.ScriptProcess;
import com.googlecode.android_scripting.interpreter.InterpreterConfiguration;
import com.googlecode.android_scripting.interpreter.InterpreterProcess;
import com.googlecode.android_scripting.interpreter.shell.ShellInterpreter;

import java.io.File;
import java.lang.ref.WeakReference;
import java.net.InetSocketAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.connectbot.ConsoleActivity;
import org.connectbot.service.TerminalManager;

/**
 * A service that allows scripts and the RPC server to run in the background.
 * 
 * @author Damon Kohler (damonkohler@gmail.com)
 */
public class ScriptingLayerService extends ForegroundService {

  private final IBinder mBinder;
  private final Map<Integer, InterpreterProcess> mProcessMap;
  private volatile int mModCount = 0;

  private InterpreterConfiguration mInterpreterConfiguration;
  static final public String SERVICE_CREATED = "com.test_automation.service_created";
  static final public String SERVICE_CREATED_MESSAGE = "com.test_automation.MESSAGE";

  private volatile WeakReference<InterpreterProcess> mRecentlyKilledProcess;

  private TerminalManager mTerminalManager;

  private SharedPreferences mPreferences = null;
  private boolean mHide;

  public class LocalBinder extends Binder {
    public ScriptingLayerService getService() {
      return ScriptingLayerService.this;
    }
  }

  @Override
  public IBinder onBind(Intent intent) {
    return mBinder;
  }

  public ScriptingLayerService() {
    super();
    mProcessMap = new ConcurrentHashMap<Integer, InterpreterProcess>();
    mBinder = new LocalBinder();
  }

  @Override
  public void onCreate() {
    super.onCreate();

    mInterpreterConfiguration = ((BaseApplication) getApplication()).getInterpreterConfiguration();
    mRecentlyKilledProcess = new WeakReference<InterpreterProcess>(null);
    mTerminalManager = new TerminalManager(this);
    mPreferences = PreferenceManager.getDefaultSharedPreferences(this);
    mHide = mPreferences.getBoolean(Constants.HIDE_NOTIFY, false);
  }

  private void sendInfoMessageToMain() {
    if (mProcessMap.size() > 0) {
      Intent intent = new Intent(SERVICE_CREATED);

      intent.putExtra(SERVICE_CREATED_MESSAGE,
          "on port: " + mProcessMap.keySet().toArray()[0].toString());

      sendBroadcast(intent);
    }
  }

  private void updateNotification(String tickerText) {
    // sendInfoMessageToMain();
  }

  @Override
  public void onStart(Intent intent, int startId) {
    if (intent == null) {
      Log.v("warning: SL4A started with NULL intent");
      return;
    }

    super.onStart(intent, startId);
    String errmsg = null;
    if (intent.getAction().equals(Constants.ACTION_KILL_ALL)) {
      killAll();
      stopSelf(startId);
      return;
    }

    if (intent.getAction().equals(Constants.ACTION_UPDATE_SERVER)) {
      sendInfoMessageToMain();
      return;
    }

    if (intent.getAction().equals(Constants.ACTION_KILL_PROCESS)) {
      killProcess(intent);
      if (mProcessMap.isEmpty()) {
        stopSelf(startId);
      }
      return;
    }

    AndroidProxy proxy = null;
    InterpreterProcess interpreterProcess = null;
    if (intent.getAction().equals(Constants.ACTION_LAUNCH_SERVER)) {
      proxy = launchServer(intent, false);
      // TODO(damonkohler): This is just to make things easier. Really, we shouldn't need to start
      // an interpreter when all we want is a server.
      interpreterProcess = new InterpreterProcess(new ShellInterpreter(), proxy);
      interpreterProcess.setName("Server");
    } else {
      proxy = launchServer(intent, true);
      if (intent.getAction().equals(Constants.ACTION_LAUNCH_FOREGROUND_SCRIPT)) {
        launchTerminal(proxy.getAddress());
        try {
          interpreterProcess = launchScript(intent, proxy);
        } catch (RuntimeException e) {
          errmsg =
              "Unable to run " + intent.getStringExtra(Constants.EXTRA_SCRIPT_PATH) + "\n"
                  + e.getMessage();
          interpreterProcess = null;
        }
      }
    }
    if (errmsg != null) {
      Log.v("RPC error msg, " + errmsg);
      // updateNotification(errmsg);

    } else if (interpreterProcess == null) {
      Log.v("Action not implemented: " + intent.getAction());
      // updateNotification("Action not implemented: " + intent.getAction());
    } else {
      addProcess(interpreterProcess);
    }
  }

  private boolean tryPort(AndroidProxy androidProxy, boolean usePublicIp, int usePort) {
    if (usePublicIp) {
      return (androidProxy.startPublic(usePort) != null);
    } else {
      return (androidProxy.startLocal(usePort) != null);
    }
  }

  private AndroidProxy launchServer(Intent intent, boolean requiresHandshake) {
    AndroidProxy androidProxy = new AndroidProxy(this, intent, requiresHandshake);
    boolean usePublicIp = intent.getBooleanExtra(Constants.EXTRA_USE_EXTERNAL_IP, false);
    int usePort = intent.getIntExtra(Constants.EXTRA_USE_SERVICE_PORT, 0);
    // If port is in use, fall back to defaut behaviour
    if (!tryPort(androidProxy, usePublicIp, usePort)) {
      if (usePort != 0) {
        tryPort(androidProxy, usePublicIp, 0);
      }
    }
    return androidProxy;
  }

  private void launchHtmlScript(Intent intent) {
    File script = new File(intent.getStringExtra(Constants.EXTRA_SCRIPT_PATH));
    ScriptLauncher.launchHtmlScript(script, this, intent, mInterpreterConfiguration);
  }

  private ScriptProcess launchScript(Intent intent, AndroidProxy proxy) {
    final int port = proxy.getAddress().getPort();
    File script = new File(intent.getStringExtra(Constants.EXTRA_SCRIPT_PATH));
    return ScriptLauncher.launchScript(script, mInterpreterConfiguration, proxy, new Runnable() {
      @Override
      public void run() {
        // TODO(damonkohler): This action actually kills the script rather than notifying the
        // service that script exited on its own. We should distinguish between these two cases.
        Intent intent = new Intent(ScriptingLayerService.this, ScriptingLayerService.class);
        intent.setAction(Constants.ACTION_KILL_PROCESS);
        intent.putExtra(Constants.EXTRA_PROXY_PORT, port);
        startService(intent);
      }
    });
  }

  private InterpreterProcess launchInterpreter(Intent intent, AndroidProxy proxy) {
    InterpreterConfiguration config =
        ((BaseApplication) getApplication()).getInterpreterConfiguration();
    final int port = proxy.getAddress().getPort();
    return ScriptLauncher.launchInterpreter(proxy, intent, config, new Runnable() {
      @Override
      public void run() {
        // TODO(damonkohler): This action actually kills the script rather than notifying the
        // service that script exited on its own. We should distinguish between these two cases.
        Intent intent = new Intent(ScriptingLayerService.this, ScriptingLayerService.class);
        intent.setAction(Constants.ACTION_KILL_PROCESS);
        intent.putExtra(Constants.EXTRA_PROXY_PORT, port);
        startService(intent);
      }
    });
  }

  private void launchTerminal(InetSocketAddress address) {
    Intent i = new Intent(this, ConsoleActivity.class);
    i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
    i.putExtra(Constants.EXTRA_PROXY_PORT, address.getPort());
    startActivity(i);
  }

  private void showRunningScripts() {
    Intent i = new Intent(this, ScriptProcessMonitor.class);
    i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
    startActivity(i);
  }

  private void addProcess(InterpreterProcess process) {
    mProcessMap.put(process.getPort(), process);
    mModCount++;
    if (!mHide) {

      Log.v(process.getName() + " started on port:  " + String.valueOf(process.getPort()));
      // updateNotification(process.getName() + " started.");
    }
  }

  private InterpreterProcess removeProcess(int port) {
    InterpreterProcess process = mProcessMap.remove(port);
    if (process == null) {
      return null;
    }
    mModCount++;
    if (!mHide) {
      Log.v(process.getName() + " exited.");
      // updateNotification(process.getName() + " exited.");
    }
    return process;
  }

  private void killProcess(Intent intent) {
    int processId = intent.getIntExtra(Constants.EXTRA_PROXY_PORT, 0);
    InterpreterProcess process = removeProcess(processId);
    if (process != null) {
      process.kill();
      mRecentlyKilledProcess = new WeakReference<InterpreterProcess>(process);
    }
  }

  public int getModCount() {
    return mModCount;
  }

  private void killAll() {
    for (InterpreterProcess process : getScriptProcessesList()) {
      process = removeProcess(process.getPort());
      if (process != null) {
        process.kill();
      }
    }
  }

  public List<InterpreterProcess> getScriptProcessesList() {
    ArrayList<InterpreterProcess> result = new ArrayList<InterpreterProcess>();
    result.addAll(mProcessMap.values());
    return result;
  }

  public InterpreterProcess getProcess(int port) {
    InterpreterProcess p = mProcessMap.get(port);
    if (p == null) {
      return mRecentlyKilledProcess.get();
    }
    return p;
  }

  public TerminalManager getTerminalManager() {
    return mTerminalManager;
  }
}
