package com.coli.androidsupport.Notch;

import com.coli.androidsupport.Notch.DeviceNotch;

public class LenovoNotch extends SDKClass implements DeviceNotch {
    public boolean isSupportNotch() {
        boolean result = false;
        int resourceId = context.getResources().getIdentifier("config_screen_has_notch", "bool", "android");
        if (resourceId > 0) {
            result = context.getResources().getBoolean(resourceId);
        }
        return result;
    }

    @Override
    public int getNotchHeight() {
        if (!isSupportNotch() ) {
            return 0;
        }

        int result = 0;
        int resourceId = context.getResources().getIdentifier("notch_h", "integer", "android");
        if (resourceId > 0) {
            result = context.getResources().getInteger(resourceId);
        }
        return result;
    }

    @Override
    public int getNotchWidth() {
        if (!isSupportNotch() ) {
            return 0;
        }

        int result = 0;
        int resourceId = context.getResources().getIdentifier("notch_w", "integer", "android");
        if (resourceId > 0) {
            result = context.getResources().getInteger(resourceId);
        }
        return result;
    }
}
