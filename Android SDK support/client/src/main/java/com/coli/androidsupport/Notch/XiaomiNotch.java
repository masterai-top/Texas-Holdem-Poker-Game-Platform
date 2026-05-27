package com.coli.androidsupport.Notch;


import java.lang.reflect.Method;
import android.annotation.SuppressLint;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.provider.Settings;
import android.view.Window;

public class XiaomiNotch  extends SDKClass implements DeviceNotch {
    @Override
    public boolean isSupportNotch() {
        try {
            Class<?> mClassType = Class.forName("android.os.SystemProperties");
            Method mGetIntMethod = mClassType.getDeclaredMethod("getInt", String.class, int.class);
            Integer v = (Integer) mGetIntMethod.invoke(mClassType, "ro.miui.notch", 0);
            return v.intValue() == 1;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public boolean isHideNotch() {
        return Settings.Secure.getInt(context.getContentResolver(), "force_black", 0) == 1;
    }

    @Override
    public int getNotchWidth() {
        // 如果不具备特性，则返回0
        if (!isSupportNotch()) {
            return 0;
        }

        // 如果隐藏了刘海，则设置不使用耳朵区
        if (isHideNotch()) {
            Message msg = new Message();
            msg.obj = "clearExtraFlags";
            mHandler.sendMessage(msg);
            return 0;
        }

        // 如果显示刘海，则设置使用耳朵区
        Message msg = new Message();
        msg.obj = "addExtraFlags";
        mHandler.sendMessage(msg);

        String model = Build.MODEL;
        if (model.contains("MI8Lite")) {
            return 296;
        }
        if (model.contains("Redmi 6 Pro")) {
            return 352;
        }
        if (model.contains("MI 8 SE")) {
            return 540;
        }
        if (model.contains("MI 8") || model.contains("MI 8 Explorer Edition") || model.contains("MI 8 UD")) {
            return 560;
        }
        if (model.contains("POCO F1")) {
            return 588;
        }

        int result = 0;
        int resourceId = context.getResources().getIdentifier("notch_width", "dimen", "android");
        if (resourceId > 0) {
            result = context.getResources().getDimensionPixelSize(resourceId);
        }
        return result;
    }

    @Override
    public int getNotchHeight() {
        // 如果不具备特性，则返回0
        if (!isSupportNotch()) {
            return 0;
        }

        // 如果隐藏了刘海，则设置不使用耳朵区
        if (isHideNotch()) {
            Message msg = new Message();
            msg.obj = "clearExtraFlags";
            mHandler.sendMessage(msg);
            return 0;
        }

        // 如果显示刘海，则设置使用耳朵区
        Message msg = new Message();
        msg.obj = "addExtraFlags";
        mHandler.sendMessage(msg);

        String model = Build.MODEL;
        if (model.contains("MI8Lite")) {
            return 82;
        }
        if (model.contains("MI 8 SE")) {
            return 85;
        }
        if (model.contains("POCO F1")) {
            return 86;
        }
        if (model.contains("MI 8") || model.contains("MI 8 Explorer Edition") || model.contains("MI 8 UD") || model.contains("Redmi 6 Pro")) {
            return 89;
        }
        if (model.contains("MI 9")) {
            return 89;
        }

        int result = 0;
        int resourceId = context.getResources().getIdentifier("notch_height", "dimen", "android");
        if (resourceId > 0) {
            result = context.getResources().getDimensionPixelSize(resourceId);
        }
        return result;
    }

    @SuppressLint("HandlerLeak")
    private Handler mHandler = new Handler() {

        @Override
        public void dispatchMessage(Message msg) {
            String cmd = (String) msg.obj;
            try {
                // 此方法需要在主线程上调用，否则会崩溃。
                Method method = Window.class.getMethod(cmd, int.class);
                method.invoke(context.getWindow(), 0x00000100 | 0x00000200 | 0x00000400);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    };
}
