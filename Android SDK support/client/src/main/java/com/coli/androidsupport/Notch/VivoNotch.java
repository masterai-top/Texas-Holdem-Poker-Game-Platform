package com.coli.androidsupport.Notch;

import android.util.Log;
import android.util.TypedValue;

import java.lang.reflect.Method;

public class VivoNotch extends SDKClass implements DeviceNotch{
    public static final int VIVO_NOTCH = 0x00000020;//是否有刘海
    @Override
    public int getNotchHeight() {
        if (this.isSupportNotch())
        {
            return dp2px(27);
        }
        return 0;
    }

    @Override
    public int getNotchWidth() {
        if(this.isSupportNotch())
        {
            return dp2px(100);
        }
        return 0;
    }

    @Override
    public boolean isSupportNotch() {
        boolean ret = false;
        try {
             ClassLoader classLoader = context.getClassLoader();
             Class FtFeature = classLoader.loadClass("android.util.FtFeature");
             Method method = FtFeature.getMethod("isFeatureSupport", int.class);
             ret = (boolean) method.invoke(FtFeature, VIVO_NOTCH);
        } catch (ClassNotFoundException e) {
            Log.e("Notch", "hasNotchAtVivo ClassNotFoundException");
        } catch (NoSuchMethodException e) {
            Log.e(  "Vivo","hasNotchAtVivo NoSuchMethodException");
        } catch (Exception e) {
            Log.e(  "Vivo","hasNotchAtVivo Exception");
        } finally {
            return ret;
        }
    }
    private  int dp2px( int dp) {
        return (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp,
                context.getResources().getDisplayMetrics());
    }
}
