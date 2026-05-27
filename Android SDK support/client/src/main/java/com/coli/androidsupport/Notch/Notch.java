package com.coli.androidsupport.Notch;

import android.app.Activity;
import android.os.Build;
import android.util.Log;
import android.util.TypedValue;
import android.view.DisplayCutout;
import android.view.View;

public class Notch extends SDKClass {
    static  Notch instance;
    DeviceNotch deviceNotch;
    public static  Notch getInstance()
    {
        if (instance == null)
            instance = new Notch();
        return instance;
    }

    //获取刘海的宽度
    public String getWidth(Activity ctx)
    {
        init(ctx);
        String width = "0";
        try
        {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P)
            {
                View decorView = context.getWindow().getDecorView();
                DisplayCutout displayCutout = decorView.getRootWindowInsets().getDisplayCutout();
                if (displayCutout != null)
                    width = displayCutout.getBoundingRects().get(0).width()+"";
            }
            else
                width = getLowerVersionWidth();
        }
        catch (Exception ex)
        {
            width = getLowerVersionWidth();
        }
        Log.w("Unity Notch width", width);
        return  width;
    }

    // 获取刘海高度
    public  String  getHeight(Activity ctx)
    {
        init(ctx);
        String height = "0";
        try
        {
            height = getLowerVersionHeight();
            // 优先尝试从官方内容获取，没有再尝试从安卓原生部分获取
            if (height == "0")
            {
                View decorView = context.getWindow().getDecorView();
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P)
                {
                    Log.w("Unity", "为高版本sdk");
                    DisplayCutout displayCutout = decorView.getRootWindowInsets().getDisplayCutout();
                    if (displayCutout != null)
                        height = displayCutout.getSafeInsetTop()+"";
                }
            }
        }
        catch (Exception ex)
        {
            height = getLowerVersionHeight();
        }
        Log.w("Unity Notch height",height);
        return  height;
    }
    //    华为：Huawei
//    荣耀：HONOR
//    小米：Xiaomi
//    一加：
//    OPPO：
//    VIVO：
//    魅族：Meizu
//    三星：samsung
//    锤子：
//    联想：Lenovo
//    中兴：zte
//    手机模拟器：generic
    public void getDeviceNotch()
    {
        String brand = android.os.Build.BRAND;
        if (deviceNotch == null)
            switch (brand.toLowerCase())
            {
                case "huawei":
                case "honor":
                    deviceNotch = new HuaweiNotch();
                    break;
                case "lenovo":
                    deviceNotch = new LenovoNotch();
                    break;
                case "xiaomi":
                    deviceNotch = new XiaomiNotch();
                    break;
                case "meizu":
                    deviceNotch = new MeiZuNotch();
                    break;
                case "samsung":
                    deviceNotch = new  SamSungNotch();
                    break;
                case "vivo":
                    deviceNotch = new VivoNotch();
                    break;
                case "oppo":
                    deviceNotch = new  OppoNotch();
                    break;
            }
    }

    public String getLowerVersionHeight()
    {
        getDeviceNotch();
        if (deviceNotch != null)
            return  deviceNotch.getNotchHeight()+"";
        else
            return  0 + "";
    }
    public String getLowerVersionWidth()
    {
        getDeviceNotch();
        if (deviceNotch != null)
            return  deviceNotch.getNotchWidth()+"";
        else
            return  0 + "";
    }

}
