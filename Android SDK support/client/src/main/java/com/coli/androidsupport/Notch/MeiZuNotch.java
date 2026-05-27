package com.coli.androidsupport.Notch;

import android.content.Context;
import android.provider.Settings;
import android.util.Log;


import java.lang.reflect.Field;

public class MeiZuNotch extends SDKClass implements DeviceNotch {
    private String TAG = "BTMeizu";

    @Override
    public boolean isSupportNotch() {
        boolean fringeDevice = false;
        try {
            Class<?> clazz = Class.forName("flyme.config.FlymeFeature");
            Field field = clazz.getDeclaredField("IS_FRINGE_DEVICE");
            fringeDevice = (Boolean) field.get(null);
        } catch (Exception e) {
            Log.e(TAG, "isSupportNotch:\n" + e.toString());
        }
        return fringeDevice;
    }

    public boolean isHideNotch() {
        // 判断隐藏刘海开关(默认关)
        return Settings.Secure.getInt(context.getContentResolver(), "mz_fringe_hide", 0) == 1;
    }

    @Override
    public int getNotchHeight() {
        if (!isSupportNotch() || isHideNotch()) {
            return 0;
        }

        // 获取刘海高度（51px）
        int fringeHeight = 0;
        int fhid = context.getResources().getIdentifier("fringe_height", "dimen", "android");
        if (fhid > 0) {
            fringeHeight = context.getResources().getDimensionPixelSize(fhid);
        }
        return fringeHeight;
    }

    @Override
    public int getNotchWidth() {
        return 0;
    }

}
