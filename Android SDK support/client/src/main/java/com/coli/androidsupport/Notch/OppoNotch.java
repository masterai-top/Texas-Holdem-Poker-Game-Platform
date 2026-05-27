package com.coli.androidsupport.Notch;

public class OppoNotch extends SDKClass implements DeviceNotch {

    @Override
    public int getNotchHeight() {
        if (this.isSupportNotch())
        {
            return 80;
        }
        return  0;
    }

    @Override
    public int getNotchWidth() {
      if (this.isSupportNotch())
      {
          return 324;
      }
      return  0;
    }

    @Override
    public boolean isSupportNotch() {
        return context.getPackageManager().hasSystemFeature("com.oppo.feature.screen.heteromorphism");
    }
}
