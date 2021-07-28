package com.man.boldi.smartwatch;

import android.support.v7.app.AppCompatActivity;

/**
 * Created by boldi on 21-Jul-18.
 */

public class PassNotifierValues extends AppCompatActivity {

    static int whatsappMessageState = 0;
    static int viberMessageState = 0;
    static int emailMessageState = 0;
    static int phoneMessageState = 0;


    public static void setWhatsappMessageState(int newState) {
        whatsappMessageState = newState;
    }
    public static int getWhatsappMessageState() {
        return whatsappMessageState;
    }


    public static void setViberMessageState(int newState) {
        viberMessageState = newState;
    }
    public static int getViberMessageState() {
        return viberMessageState;
    }


    public static void setEmailMessageState(int newState) {
        emailMessageState = newState;
    }
    public static int getEmailMessageState() {
        return emailMessageState;
    }


    public static void setPhoneMessageState(int newState) {
        phoneMessageState = newState;
    }
    public static int getPhoneMessageState() {
        return phoneMessageState;
    }
}

