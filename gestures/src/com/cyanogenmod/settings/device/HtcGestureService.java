/*
 * Copyright (C) 2016 The CyanogenMod Project
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
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.hardware.SensorEvent;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.SystemClock;
import android.preference.PreferenceManager;
import android.provider.Settings;
import android.util.Log;

public class HtcGestureService extends Service {

    private static final boolean DEBUG = false;

    public static final String TAG = "GestureService";

    private static final String HTC_GESTURES = "hTC Gesture_Motion";

    private static final String KEY_SWIPE_UP = "swipe_up_action_key";
    private static final String KEY_SWIPE_DOWN = "swipe_down_action_key";
    private static final String KEY_SWIPE_LEFT = "swipe_left_action_key";
    private static final String KEY_SWIPE_RIGHT = "swipe_right_action_key";

    private static final int ACTION_NONE = 0;
    private static final int ACTION_CAMERA = 1;
    private static final int ACTION_TORCH = 2;

    private Context mContext;
    private GestureMotionSensor mDoubleTapSensor;
    private GestureMotionSensor mSwipeUpSensor;
    private GestureMotionSensor mSwipeDownSensor;
    private GestureMotionSensor mSwipeLeftSensor;
    private GestureMotionSensor mSwipeRightSensor;
    private PowerManager mPowerManager;

    private int mSwipeUpAction;
    private int mSwipeDownAction;
    private int mSwipeLeftAction;
    private int mSwipeRightAction;

    private GestureMotionSensor.GestureMotionSensorListener mListener =
        new GestureMotionSensor.GestureMotionSensorListener() {
        @Override
        public void onEvent(int type, SensorEvent event) {
            switch (type) {
                case GestureMotionSensor.SENSOR_TYPE_DOUBLE_TAP:
                    mPowerManager.wakeUp(SystemClock.uptimeMillis());
                    break;
                case GestureMotionSensor.SENSOR_TYPE_SWIPE_UP:
                case GestureMotionSensor.SENSOR_TYPE_SWIPE_DOWN:
                case GestureMotionSensor.SENSOR_TYPE_SWIPE_LEFT:
                case GestureMotionSensor.SENSOR_TYPE_SWIPE_RIGHT:
                case GestureMotionSensor.SENSOR_TYPE_CAMERA:
                    /* TODO: Handle these */
                    break;
            }
        }
    };

    @Override
    public void onCreate() {
        if (DEBUG) Log.d(TAG, "Creating service");
        super.onCreate();

        mContext = this;
        mDoubleTapSensor = new GestureMotionSensor(mContext, GestureMotionSensor.SENSOR_TYPE_DOUBLE_TAP);
        mDoubleTapSensor.registerListener(mListener);
        SharedPreferences sharedPrefs = PreferenceManager.getDefaultSharedPreferences(mContext);
        loadPreferences(sharedPrefs);
        sharedPrefs.registerOnSharedPreferenceChangeListener(mPrefListener);
        mPowerManager = (PowerManager) getSystemService(Context.POWER_SERVICE);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (DEBUG) Log.d(TAG, "Starting service");
        IntentFilter screenStateFilter = new IntentFilter(Intent.ACTION_SCREEN_ON);
        screenStateFilter.addAction(Intent.ACTION_SCREEN_OFF);
        mContext.registerReceiver(mScreenStateReceiver, screenStateFilter);
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        if (DEBUG) Log.d(TAG, "Destroying service");
        super.onDestroy();
        unregisterReceiver(mScreenStateReceiver);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private void onDisplayOn() {
        if (DEBUG) Log.d(TAG, "Display on");
        if (isDoubleTapEnabled()) {
            mDoubleTapSensor.disable();
        }
    }

    private void onDisplayOff() {
        if (DEBUG) Log.d(TAG, "Display off");
        if (isDoubleTapEnabled()) {
            mDoubleTapSensor.enable();
        }
    }

    private boolean isDoubleTapEnabled() {
        return (Settings.Secure.getInt(mContext.getContentResolver(),
                    Settings.Secure.DOUBLE_TAP_TO_WAKE, 0) != 0);
    }

    private BroadcastReceiver mScreenStateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals(Intent.ACTION_SCREEN_OFF)) {
                onDisplayOff();
            } else if (intent.getAction().equals(Intent.ACTION_SCREEN_ON)) {
                onDisplayOn();
            }
        }
    };

    private void loadPreferences(SharedPreferences sharedPreferences) {
        mSwipeUpAction = sharedPreferences.getInt(KEY_SWIPE_UP, ACTION_NONE);
        mSwipeDownAction = sharedPreferences.getInt(KEY_SWIPE_DOWN, ACTION_NONE);
        mSwipeLeftAction = sharedPreferences.getInt(KEY_SWIPE_LEFT, ACTION_NONE);
        mSwipeRightAction = sharedPreferences.getInt(KEY_SWIPE_RIGHT, ACTION_NONE);
    }

    private SharedPreferences.OnSharedPreferenceChangeListener mPrefListener =
            new SharedPreferences.OnSharedPreferenceChangeListener() {
        @Override
        public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
            /* TODO: Enable corresponding GestureSensor member variable also */
            if (KEY_SWIPE_UP.equals(key)) {
                mSwipeUpAction = sharedPreferences.getInt(KEY_SWIPE_UP, ACTION_NONE);
            } else if (KEY_SWIPE_DOWN.equals(key)) {
                mSwipeDownAction = sharedPreferences.getInt(KEY_SWIPE_DOWN, ACTION_NONE);
            } else if (KEY_SWIPE_LEFT.equals(key)) {
                mSwipeLeftAction = sharedPreferences.getInt(KEY_SWIPE_LEFT, ACTION_NONE);
            } else if (KEY_SWIPE_RIGHT.equals(key)) {
                mSwipeRightAction = sharedPreferences.getInt(KEY_SWIPE_RIGHT, ACTION_NONE);
            }
        }
    };
}
