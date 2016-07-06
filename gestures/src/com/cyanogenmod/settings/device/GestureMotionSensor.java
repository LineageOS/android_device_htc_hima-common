/*
 * Copyright (C) 2016 The CyanogenMod Project
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
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class GestureMotionSensor {

    private static final boolean DEBUG = false;
    private static final String TAG = "GestureMotionSensor";

    public static final int SENSOR_TYPE_DOUBLE_TAP = 1337;
    public static final int SENSOR_TYPE_SWIPE_UP = 1338;
    public static final int SENSOR_TYPE_SWIPE_DOWN = 1339;
    public static final int SENSOR_TYPE_SWIPE_LEFT = 1340;
    public static final int SENSOR_TYPE_SWIPE_RIGHT = 1341;
    public static final int SENSOR_TYPE_CAMERA = 1342;

    /* Correspond to actual sensor ID, internal use only */
    private static final int SENSOR_TYPE_ANY_MOTION = 65537;
    private static final int SENSOR_TYPE_GESTURE_MOTION = 65538;

    /* Correspond to sensor event value, internal use only */
    private static final int SENSOR_EVENT_ID_DOUBLE_TAP = 15;
    private static final int SENSOR_EVENT_ID_SWIPE_UP = 2;
    private static final int SENSOR_EVENT_ID_SWIPE_DOWN = 3;
    private static final int SENSOR_EVENT_ID_SWIPE_LEFT = 4;
    private static final int SENSOR_EVENT_ID_SWIPE_RIGHT = 5;
    private static final int SENSOR_EVENT_ID_CAMERA = 6;

    protected static final int BATCH_LATENCY_IN_MS = 100;

    private Context mContext;
    private SensorManager mSensorManager;
    private Sensor mSensor;
    private int mType;
    private List<GestureMotionSensorListener> mListeners;

    private static int sensorTypeToSysfsType(int type) {
        switch (type) {
            /* TODO: determine whether these are hex values written to sysfs */
            case SENSOR_TYPE_DOUBLE_TAP:
                return 8000;
            case SENSOR_TYPE_SWIPE_UP:
                return 4;
            case SENSOR_TYPE_SWIPE_DOWN:
                return 8;
            case SENSOR_TYPE_SWIPE_LEFT:
                return 10;
            case SENSOR_TYPE_SWIPE_RIGHT:
                return 20;
            case SENSOR_TYPE_CAMERA:
                return 40;
            default:
                return -1;
        }
    }

    private static int sensorEventToSensorType(int type) {
        switch (type) {
            case SENSOR_EVENT_ID_DOUBLE_TAP:
                return SENSOR_TYPE_DOUBLE_TAP;
            case SENSOR_EVENT_ID_SWIPE_UP:
                return SENSOR_TYPE_SWIPE_UP;
            case SENSOR_EVENT_ID_SWIPE_DOWN:
                return SENSOR_TYPE_SWIPE_DOWN;
            case SENSOR_EVENT_ID_SWIPE_LEFT:
                return SENSOR_TYPE_SWIPE_LEFT;
            case SENSOR_EVENT_ID_SWIPE_RIGHT:
                return SENSOR_TYPE_SWIPE_RIGHT;
            default:
                return -1;
        }
    }

    public interface GestureMotionSensorListener {
        public void onEvent(int type, SensorEvent event);
    }

    public GestureMotionSensor(Context context, int type) {
        mContext = context;
        mSensorManager = (SensorManager) mContext.getSystemService(Context.SENSOR_SERVICE);
        /* TODO: investigate if opening multiple sensor listeners works OK */
        mSensor = mSensorManager.getDefaultSensor(SENSOR_TYPE_GESTURE_MOTION);
        mListeners = new ArrayList<GestureMotionSensorListener>();
    }

    public void enable() {
        if (DEBUG) Log.d(TAG, "Enabling");
        /* TODO: Handle writing to /sys/class/htc_sensorhub/sensor_hub/gesture_motion */
        mSensorManager.registerListener(mSensorEventListener, mSensor,
                SensorManager.SENSOR_DELAY_NORMAL, BATCH_LATENCY_IN_MS * 1000);
    }

    public void disable() {
        if (DEBUG) Log.d(TAG, "Disabling");
        /* TODO: Handle writing to /sys/class/htc_sensorhub/sensor_hub/gesture_motion */
        mSensorManager.unregisterListener(mSensorEventListener);
    }

    public void registerListener(GestureMotionSensorListener listener) {
        mListeners.add(listener);
    }

    private void onSensorEvent(int type, SensorEvent event) {
        for (GestureMotionSensorListener l : mListeners) {
            l.onEvent(mType, event);
        }
    }

    private SensorEventListener mSensorEventListener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            int sensorEventType = (int) event.values[0];
            if (sensorEventToSensorType(sensorEventType) == mType) {
                /* Only report events which match our type */
                onSensorEvent(mType, event);
            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            /* Empty */
        }
    };
}
