package com.coli.androidsupport;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.Service;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Build;
import android.os.LocaleList;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.Log;

import java.net.NetworkInterface;
import java.util.Collections;
import java.util.List;
import java.util.Locale;

import static android.content.Context.TELEPHONY_SERVICE;

public class ConvenientUtils {
    public static void downloadAndInstallApk(Context ctx, String url) {
        new ApkInstaller(ctx, url);
    }

    public static void copyToClippingBoard(Context ctx, String text) {
        ClipboardManager clipboardManager=(ClipboardManager)ctx.getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData data = ClipData.newPlainText("simple text copy", text);
        clipboardManager.setPrimaryClip(data);
    }

    public static void showAlertDialogOK(Context ctx, String title, String content, String buttonTitle, DialogInterface.OnClickListener clicker) {
        AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(ctx);
        dlgAlert.setMessage(content);
        dlgAlert.setTitle(title);
        dlgAlert.setPositiveButton(buttonTitle, clicker);
        dlgAlert.setCancelable(false);
        dlgAlert.create().show();
    }

    public static  void vibratePhone(Context ctx ,int power, int time)
    {
        Vibrator vibrator = (Vibrator) ctx.getSystemService(Service.VIBRATOR_SERVICE);

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            VibrationEffect vibrationEffect = VibrationEffect.createOneShot(time, power);
            vibrator.vibrate(vibrationEffect);
        }
        else
        {
            vibrator.vibrate(time);
        }
    }

    public static String getLanguage()
    {
        Locale locale;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            LocaleList lsit = LocaleList.getDefault();
            locale = lsit.get(0);
        } else {
            locale = Locale.getDefault();
        }
        String lang = locale.toString();
        return  lang;
    }

    public static String getCountry() {
        Locale defaultLocale = Locale.getDefault();
        return defaultLocale.getCountry();
    }

    public static void showAlertDialogOKAndCancel(Context ctx, String title, String content, String okButtonTitle, DialogInterface.OnClickListener okClicker, String cancelButtonTitle, DialogInterface.OnClickListener cancelClicker) {
        AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(ctx);
        dlgAlert.setMessage(content);
        dlgAlert.setTitle(title);
        dlgAlert.setPositiveButton(okButtonTitle, okClicker);
        dlgAlert.setNegativeButton(cancelButtonTitle, cancelClicker);
        dlgAlert.setCancelable(false);
        dlgAlert.create().show();
    }

    public static String getDeviceIdentifier(Context ctx) {
        if (getDeviceId(ctx) ==  "")
        {
            return getAndroidId(ctx);
        }
        else
        {
            return  getDeviceId(ctx);
        }
    }

    public static String getMac() {
        try {
            List<NetworkInterface> all = Collections.list(NetworkInterface.getNetworkInterfaces());
            for (NetworkInterface nif : all) {
                if (!nif.getName().equalsIgnoreCase("wlan0")) continue;

                byte[] macBytes = nif.getHardwareAddress();
                if (macBytes == null) {
                    return "";
                }
                StringBuilder res1 = new StringBuilder();
                for (byte b : macBytes) {
                    res1.append(String.format("%02X:",b));
                }
                if (res1.length() > 0) {
                    res1.deleteCharAt(res1.length() - 1);
                }
                return res1.toString();
            }
        } catch (Exception ex) {
        }
        return "02:00:00:00:00:00";
    }

    public static String getDeviceId(Context ctx) {
        String str = "";
        try
        {
            TelephonyManager TelephonyMgr = (TelephonyManager)ctx.getSystemService(TELEPHONY_SERVICE);
            @SuppressLint("MissingPermission") String szImei = TelephonyMgr.getDeviceId();
            str =szImei;
        }
        catch (Exception e)
        {
          Log.w("error","没有权限");
        }
        return str;
    }

    public static String getAndroidId(Context ctx) {
        if (Build.VERSION.SDK_INT <= 14) {
            return Settings.System.getString(ctx.getContentResolver(), Settings.System.ANDROID_ID);
        } else {
            return Settings.System.getString(ctx.getContentResolver(), Settings.Secure.ANDROID_ID);
        }
    }

    public  static String getAndroidVersion()
    {
        return  Build.VERSION.SDK_INT  + "";
    }

    public static  String getBrand()
    {
        return android.os.Build.BRAND;
    }
}
