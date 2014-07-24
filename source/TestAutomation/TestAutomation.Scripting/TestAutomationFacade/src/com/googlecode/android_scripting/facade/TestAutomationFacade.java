package com.googlecode.android_scripting.facade;

import Server.ServiceManagerProxy;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;

import com.googlecode.android_scripting.jsonrpc.RpcReceiver;
import com.googlecode.android_scripting.rpc.Rpc;
import com.googlecode.android_scripting.rpc.RpcMinSdk;
import com.googlecode.android_scripting.rpc.RpcParameter;

import java.lang.reflect.InvocationTargetException;

/**
 * Provides Test Automation features
 */

@RpcMinSdk(14)
public class TestAutomationFacade extends RpcReceiver {
  private final Service mService;

  private Object mSmsProxy;
  private static final String MESSAGE_SENT_ACTION = "com.android.cts.permission.sms.MESSAGE_SENT";

  public TestAutomationFacade(FacadeManager manager) {
    super(manager);

    mService = manager.getService();
    mSmsProxy =
        ServiceManagerProxy.getInstance().createProxy("isms_msim",
            "com.android.internal.telephony.msim.ISmsMSim");
  }

  @Override
  public void shutdown() {

  }

  @Rpc(description = "Return status of on going call")
  public Boolean isCalling() {

    return true;
  }

  @Rpc(description = "Generated text of selected size. This is for debug purposes")
  public String generateText(@RpcParameter(name = "text character count") Integer size) {
    String output = new String("");
    for (int i = 0; i < size; i++) {
      output += (char) (i % 26 + 65);
    }
    return output;
  }

  @Rpc(description = "Sends an SMS.")
  public void smsSendMultisim(
      @RpcParameter(name = "destinationAddress", description = "typically a phone number") String destinationAddress,
      @RpcParameter(name = "text") String text, Integer simNumber) {
    PendingIntent sentIntent =
        PendingIntent.getBroadcast(mService, 0, new Intent(MESSAGE_SENT_ACTION), 0);
    try {
      mSmsProxy
          .getClass()
          .getMethod("sendText", String.class, String.class, String.class, String.class,
              PendingIntent.class, PendingIntent.class, int.class)
          .invoke(mSmsProxy, "com.googlecode.android_scripting", destinationAddress, null, text,
              sentIntent, null, simNumber - 1);

    } catch (IllegalArgumentException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (SecurityException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (IllegalAccessException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (InvocationTargetException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (NoSuchMethodException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }
}
