package com.man.boldi.smartwatch;

import android.accessibilityservice.AccessibilityService;
import android.accessibilityservice.AccessibilityServiceInfo;
import android.content.Intent;
import android.view.accessibility.AccessibilityEvent;


public class Notifier extends AccessibilityService {


    @Override
    public void onCreate(){

    }

    @Override
    protected void onServiceConnected() {
        // Set the type of events that this service wants to listen to.  Others
        // won't be passed to this service.

        startActivity(new Intent(Notifier.this, SecondActivity.class));


        //Toast.makeText(this,"Service connected", Toast.LENGTH_LONG).show();

        AccessibilityServiceInfo info = new AccessibilityServiceInfo();
        info.feedbackType = AccessibilityServiceInfo.FEEDBACK_ALL_MASK;
        info.eventTypes = AccessibilityEvent.TYPE_NOTIFICATION_STATE_CHANGED;
        info.packageNames = new String[] {"com.whatsapp", "com.viber.voip", "com.google.android.gm"};
        info.notificationTimeout = 100;
        setServiceInfo(info);
    }


    @Override
    public void onAccessibilityEvent(AccessibilityEvent event) {


        if(event.getEventType() == AccessibilityEvent.TYPE_NOTIFICATION_STATE_CHANGED) {
            CharSequence currentPackageName = event.getPackageName();
            String currentPackageNameString = String.valueOf(currentPackageName);

            if (currentPackageNameString.equals("com.whatsapp")) {
                PassNotifierValues.setWhatsappMessageState(1);
                //Toast.makeText(this,"Whatsapp Message", Toast.LENGTH_LONG).show();
            }

            if (currentPackageNameString.equals("com.viber.voip")) {
                PassNotifierValues.setViberMessageState(1);
                //Toast.makeText(this,"Viber Message", Toast.LENGTH_LONG).show();
            }

            if (currentPackageNameString.equals("com.google.android.gm")) {
                PassNotifierValues.setEmailMessageState(1);
                //Toast.makeText(this,"Email", Toast.LENGTH_LONG).show();
            }
        }
    }

    @Override
    public void onInterrupt() {

        //Toast.makeText(this,"Exited", Toast.LENGTH_LONG).show();

    }
}
