/*
 * Copyright (C) 2014 SlimRoms Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.cyanogenmod.settings.device;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.SystemClock;
import android.util.Log;

import java.util.Iterator;

public class SensorService extends Service implements SensorEventListener {

    private static final boolean DEBUG = false;

    public static final String TAG = "SensorService";
    public static final String HTC_GESTURES = "hTC Gesture_Motion";

    // Gestures
    private static final int DOUBLE_TAP = 15;
    private static final int SWIPE_UP = 2;
    private static final int SWIPE_DOWN = 3;
    private static final int SWIPE_RIGHT = 4;
    private static final int SWIPE_LEFT = 5;
    private static final int CAMERA = 6;

    private PowerManager mPowerManager;
    private ScreenStateReceiver mScreenStateReceiver;
    private SensorManager mSensorManager;
    private Sensor mSensor = null;
    private SensorEventListener mSensorEventListener;

    @Override
    public void onCreate() {
        super.onCreate();

        mPowerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        mSensorEventListener = this;

        Iterator iterator = mSensorManager.getSensorList(-1).iterator();
        while (iterator.hasNext()) {
            Sensor sensor = (Sensor) iterator.next();
            if (sensor.getName().equals(HTC_GESTURES)) {
                if (DEBUG) Log.d(TAG, "found gesture sensor");
                mSensor = sensor;
            }
        }
        if (mSensor != null) {
            mSensorManager.registerListener(mSensorEventListener,
                    mSensor, SensorManager.SENSOR_DELAY_FASTEST);
            mScreenStateReceiver = new ScreenStateReceiver();
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(Intent.ACTION_SCREEN_ON);
            intentFilter.addAction(Intent.ACTION_SCREEN_OFF);
            registerReceiver(mScreenStateReceiver, intentFilter);
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        mSensorManager.unregisterListener(this);
        unregisterReceiver(mScreenStateReceiver);
    }

    public IBinder onBind(Intent intent) {
        return null;
    }

    public final void onAccuracyChanged(Sensor sensor, int i) {
    }

    public final void onSensorChanged(SensorEvent sensorEvent) {
        if (DEBUG) Log.d(TAG, "Sensor type=" + sensorEvent.sensor.getType()
                + "," + sensorEvent.values[0] + "," + sensorEvent.values[1]);

        switch ((int)sensorEvent.values[0]) {
            case DOUBLE_TAP:
                mPowerManager.wakeUp(SystemClock.uptimeMillis());
                break;
            // TODO
            case SWIPE_UP:
            case SWIPE_DOWN:
            case SWIPE_RIGHT:
            case SWIPE_LEFT:
            case CAMERA:
            default:
        }
    }
}
