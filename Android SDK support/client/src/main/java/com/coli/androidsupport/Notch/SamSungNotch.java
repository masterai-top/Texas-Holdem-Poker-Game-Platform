package com.coli.androidsupport.Notch;

import android.content.res.Configuration;
import android.content.res.Resources;
import android.text.TextUtils;
import android.util.Log;

import com.coli.androidsupport.Notch.DeviceNotch;

public class SamSungNotch extends SDKClass implements DeviceNotch {
    private String TAG = "BTSamsung";

    @Override
    public boolean isSupportNotch() {
        try {
            final Resources res = context.getResources();
            final int resId = res.getIdentifier("config_mainBuiltInDisplayCutout", "string", "android");
            final String spec = resId > 0 ? res.getString(resId) : null;
            return spec != null && !TextUtils.isEmpty(spec);
        } catch (Exception e) {
            Log.e(TAG, "getFeature Exception");
        }
        return false;
    }


    public int getStatusBarHeight() {
        int result = 0;
        int resourceId = context.getResources().getIdentifier("status_bar_height",
                "dimen", "android");
        if (resourceId > 0) {
            result = context.getResources().getDimensionPixelSize(resourceId);
        }
        Log.d(TAG, "statusBarHeight : " + result);
        return result;
    }

    @Override
    public int getNotchHeight() {
    if (isSupportNotch())
        return getStatusBarHeight();
    else
        return  0;
    }

    @Override
    public int getNotchWidth() {
        return 0;
    }
}
