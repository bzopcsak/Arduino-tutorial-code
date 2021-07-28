package com.man.boldi.smartwatch;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

/**
 * Created by boldi on 22-Jul-18.
 */

public class InterceptCall extends BroadcastReceiver{

    @Override
    public void onReceive(Context context, Intent intent) {
        PassNotifierValues.setPhoneMessageState(1);
    }
}
