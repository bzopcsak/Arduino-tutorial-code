package com.man.boldi.smartwatch;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.BatteryManager;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Set;
import java.util.UUID;

/**
 * Created by boldi on 10-Jul-18.
 */

public class SecondActivity extends AppCompatActivity {

    private final String DEVICE_ADDRESS = "20:15:11:23:93:85"; //MAC Address of Bluetooth Module
    private final UUID PORT_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
    private BluetoothDevice device;
    private BluetoothSocket socket;
    private OutputStream outputStream;

    String command;

    Handler handler = new Handler();
    int delay = 1000; //milliseconds

    String sendStringBatLevel;
    int batLevel;
    int oldBatLevel = 0;
    String batLevelString;

    int whatsappState = 0;
    int viberState = 0;
    int emailState = 0;
    int phoneState = 0;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);


        if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.READ_PHONE_STATE)
                != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.READ_PHONE_STATE)) {
            } else {
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.READ_PHONE_STATE}, 1);
            }
        } else {

        }
    }

    public void second1(View view) {
        if (BTinit()) {
            BTconnect();

            //Only do this once
            SimpleDateFormat sdf = new SimpleDateFormat("EEEMMddHHmmss");
            String currentDateandTime = sdf.format(new Date());
            String[] timeStringArray = currentDateandTime.split("");


            for (int i = 1; i < 14; i++) {
                command = timeStringArray[i];
                sendCommand();
                //Toast.makeText(getApplicationContext(), timeStringArray[i], Toast.LENGTH_SHORT).show();
            }


            repetitiveCommands();
        }
    }



    public void repetitiveCommands() {
        handler.postDelayed(new Runnable() {
            public void run() {


                BatteryManager bm = (BatteryManager) getSystemService(BATTERY_SERVICE);
                batLevel = bm.getIntProperty(BatteryManager.BATTERY_PROPERTY_CAPACITY);
                batLevelString = String.valueOf(batLevel);

                whatsappState = PassNotifierValues.getWhatsappMessageState();
                viberState = PassNotifierValues.getViberMessageState();
                emailState = PassNotifierValues.getEmailMessageState();
                phoneState = PassNotifierValues.getPhoneMessageState();



                if (batLevel != oldBatLevel || whatsappState == 1 || viberState == 1 || emailState == 1 || phoneState == 1) {

                    //Repetitive Routine
                    command = "b";
                    sendCommand();

                    if (batLevel == 100) {

                        sendStringBatLevel = batLevelString.substring(0, 1);
                        command = sendStringBatLevel;
                        sendCommand();

                        sendStringBatLevel = batLevelString.substring(1, 2);
                        command = sendStringBatLevel;
                        sendCommand();

                        sendStringBatLevel = batLevelString.substring(2, 3);
                        command = sendStringBatLevel;
                        sendCommand();

                    } else if (batLevel < 100 && batLevel > 9) {

                        sendStringBatLevel = "0";
                        command = sendStringBatLevel;
                        sendCommand();

                        sendStringBatLevel = batLevelString.substring(0, 1);
                        command = sendStringBatLevel;
                        sendCommand();

                        sendStringBatLevel = batLevelString.substring(1, 2);
                        command = sendStringBatLevel;
                        sendCommand();

                    } else if (batLevel < 10) {

                        sendStringBatLevel = "0";
                        command = sendStringBatLevel;
                        sendCommand();

                        sendStringBatLevel = "0";
                        command = sendStringBatLevel;
                        sendCommand();

                        sendStringBatLevel = batLevelString;
                        command = sendStringBatLevel;
                        sendCommand();

                    }



                    //Send Message States
                    command = String.valueOf(whatsappState);
                    sendCommand();

                    command = String.valueOf(viberState);
                    sendCommand();

                    command = String.valueOf(emailState);
                    sendCommand();

                    command = String.valueOf(phoneState);
                    sendCommand();



                }
                oldBatLevel = batLevel;


                PassNotifierValues.setWhatsappMessageState(0);
                PassNotifierValues.setViberMessageState(0);
                PassNotifierValues.setEmailMessageState(0);
                PassNotifierValues.setPhoneMessageState(0);



                handler.postDelayed(this, delay);
            }
        }, delay);
    }





















    public void sendCommand() {
        try {
            outputStream.write(command.getBytes()); //transmits the value of command to the bluetooth module
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //Initializes bluetooth module
    public boolean BTinit() {
        boolean found = false;

        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        if (bluetoothAdapter == null) //Checks if the device supports bluetooth
        {
            //Toast.makeText(getApplicationContext(), "Device doesn't support bluetooth", Toast.LENGTH_SHORT).show();
        }

        if (!bluetoothAdapter.isEnabled()) //Checks if bluetooth is enabled. If not, the program will ask permission from the user to enable it
        {
            Intent enableAdapter = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableAdapter, 0);

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        Set<BluetoothDevice> bondedDevices = bluetoothAdapter.getBondedDevices();

        if (bondedDevices.isEmpty()) //Checks for paired bluetooth devices
        {
            //Toast.makeText(getApplicationContext(), "Please pair the device first", Toast.LENGTH_SHORT).show();
        } else {
            for (BluetoothDevice iterator : bondedDevices) {
                if (iterator.getAddress().equals(DEVICE_ADDRESS)) {
                    device = iterator;
                    found = true;
                    break;
                }
            }
        }

        return found;
    }

    public boolean BTconnect() {
        boolean connected = true;

        try {
            socket = device.createRfcommSocketToServiceRecord(PORT_UUID); //Creates a socket to handle the outgoing connection
            socket.connect();

            Toast.makeText(getApplicationContext(),
                    "Connection successful", Toast.LENGTH_LONG).show();
        } catch (IOException e) {
            e.printStackTrace();
            connected = false;
        }

        if (connected) {
            try {
                outputStream = socket.getOutputStream(); //gets the output stream of the socket
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return connected;
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

}
