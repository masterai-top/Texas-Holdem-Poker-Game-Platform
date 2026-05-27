package com.coli.androidsupport;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {
    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();

        ApkInstaller.getInstance().downloadApk("http://10.10.10.44/Packs/Android/version.json", appContext.getCacheDir().getAbsolutePath(), "test.apk");
        // assertEquals("com.coli.androidsupport.test", appContext.getPackageName());
    }
}
