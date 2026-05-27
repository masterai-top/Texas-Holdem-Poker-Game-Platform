package com.coli.androidsupport.Notch;

import android.content.Context;
import android.graphics.Point;
import android.provider.Settings;
import android.util.Log;

import com.coli.androidsupport.Notch.DeviceNotch;

import java.lang.reflect.Method;
public class HuaweiNotch extends SDKClass implements DeviceNotch {

    private String TAG = "BTHuawei";

    public boolean isSupportNotch() {
        try {
            ClassLoader cl = context.getClassLoader();
            Class<?> HwNotchSizeUtil = cl.loadClass("com.huawei.android.util.HwNotchSizeUtil");
            Method get = HwNotchSizeUtil.getMethod("hasNotchInScreen");
            return (Boolean) get.invoke(HwNotchSizeUtil);
        } catch (ClassNotFoundException e) {
            Log.e(TAG, "isFeatureSupport ClassNotFoundException");
        } catch (NoSuchMethodException e) {
            Log.e(TAG, "isFeatureSupport NoSuchMethodException");
        } catch (Exception e) {
            Log.e(TAG, "isFeatureSupport Exception");
        }
        return false;
    }

    public boolean isHideNotch() {
        boolean isHide = Settings.Secure.getInt(context.getContentResolver(), "display_notch_status", 0) == 1;
        if (!isHide) {
            return false;
        }
        return true;
    }
    public int getNotchWidth() {
        // 如果不具备特性或者隐藏了刘海，则返回0
        if (!isSupportNotch()||isHideNotch()) {
            return 0;
        }
        return getNotchSize()[0];
    }

    public int getNotchHeight() {
        // 如果不具备特性或者隐藏了刘海，则返回0
        if (!isSupportNotch()||isHideNotch()) {
            return 0;
        }
        return getNotchSize()[1];
    }

    /**
     * 获取刘海屏凹槽尺寸
     *
     * @param
     * @return
     */
    private int[] getNotchSize() {
        int[] ret = new int[] { 0, 0 };
        try {
            ClassLoader cl = context.getClassLoader();
            Class<?> HwNotchSizeUtil = cl.loadClass("com.huawei.android.util.HwNotchSizeUtil");
            Method get = HwNotchSizeUtil.getMethod("getNotchSize");
            ret = (int[]) get.invoke(HwNotchSizeUtil);
        } catch (ClassNotFoundException e) {
            Log.e(TAG, "getNotcSize ClassNotFoundException");
        } catch (NoSuchMethodException e) {
            Log.e(TAG, "getNotcSize NoSuchMethodException");
        } catch (Exception e) {
            Log.e(TAG, "getNotcSize Exception");
        }
        return ret;
    }
}
