package com.googlecode.android_scripting.activity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.googlecode.android_scripting.Constants;
import com.googlecode.android_scripting.Log;
import com.googlecode.android_scripting.R;

import org.connectbot.service.TerminalBridge;
import org.connectbot.service.TerminalManager;

public class TestAutomation extends Activity {

  protected ScriptingLayerService mService = null;
  protected TerminalManager manager = null;
  protected Integer processID;
  protected Button button;
  protected BroadcastReceiver receiver;
  protected boolean serviceAlive;

  @SuppressLint("NewApi")
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    serviceAlive = false;

    setContentView(R.layout.test_automation);
    addListenerOnButton();

    receiver = new BroadcastReceiver() {
      @Override
      public void onReceive(Context context, Intent intent) {
        String responseText = intent.getStringExtra(ScriptingLayerService.SERVICE_CREATED_MESSAGE);
        ((TextView) findViewById(R.id.statusText)).setText(responseText);
        ((Button) findViewById(R.id.button1)).setText("Close");
        serviceAlive = true;
      }
    };
  }

  @Override
  protected void onStart() {
    super.onStart();
    this.registerReceiver(receiver, new IntentFilter(ScriptingLayerService.SERVICE_CREATED));
    updateServices();
  }

  @Override
  protected void onStop() {
    unregisterReceiver(receiver);
    super.onStop();
  }

  private void launchService(boolean usePublicIp) {
    Intent intent = new Intent(this, ScriptingLayerService.class);
    intent.setAction(Constants.ACTION_LAUNCH_SERVER);
    intent.putExtra(Constants.EXTRA_USE_EXTERNAL_IP, usePublicIp);
    intent.putExtra(Constants.EXTRA_USE_SERVICE_PORT, 0); // getPrefInt("use_service_port", 0));
    startService(intent);
  }

  private void killServices() {
    Intent intent = new Intent(this, ScriptingLayerService.class);
    intent.setAction(Constants.ACTION_KILL_ALL);
    startService(intent);
  }

  private void updateServices() {
    Intent intent = new Intent(this, ScriptingLayerService.class);
    intent.setAction(Constants.ACTION_UPDATE_SERVER);
    startService(intent);
  }

  public void addListenerOnButton() {

    button = (Button) findViewById(R.id.button1);

    button.setOnClickListener(new OnClickListener() {

      @Override
      public void onClick(View arg0) {
        if (serviceAlive == false) {
          serviceAlive = true;
          launchService(false);
          ((TextView) findViewById(R.id.statusText)).setText("Started");
        } else {
          killServices();
          serviceAlive = false;
          ((TextView) findViewById(R.id.statusText)).setText("not started");
          ((Button) findViewById(R.id.button1)).setText("Start");
        }
      }

    });

  }

  private void closeBridge(final TerminalBridge bridge) {
    finish();
  }

  protected Handler disconnectHandler = new Handler() {
    @Override
    public void handleMessage(Message msg) {
      TerminalBridge bridge = (TerminalBridge) msg.obj;
      closeBridge(bridge);
    }
  };

  private final ServiceConnection mConnection = new ServiceConnection() {
    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {
      mService = ((ScriptingLayerService.LocalBinder) service).getService();
      manager = mService.getTerminalManager();
      // let manager know about our event handling services
      manager.setDisconnectHandler(disconnectHandler);

      manager.setResizeAllowed(true);

      // clear out any existing bridges and record requested index

      TerminalBridge requestedBridge = manager.getConnectedBridge(processID);

      // If we didn't find the requested connection, try opening it
      if (processID != null && requestedBridge == null) {
        try {
          Log.d(String.format(
              "We couldnt find an existing bridge with id = %d, so creating one now", processID));
          requestedBridge = manager.openConnection(processID);
        } catch (Exception e) {
          Log.d("Problem while trying to create new requested bridge", e);
        }
      }

    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
      manager = null;
      mService = null;
    }
  };

  @Override
  public boolean onOptionsItemSelected(MenuItem item) {

    return super.onOptionsItemSelected(item);
  }

}
