package com.coli.androidsupport.Notch;

import android.app.Activity;
import android.view.View;


public class  SDKClass {

   protected static View view = null;
   protected static Activity context; // Unity的Active
    public void init(Activity act)
    {
        context = act;
        view = context.getWindow().getCurrentFocus();
    }
}
