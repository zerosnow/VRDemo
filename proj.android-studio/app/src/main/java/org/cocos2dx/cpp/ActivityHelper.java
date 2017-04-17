package org.cocos2dx.cpp;

import android.app.Activity;

/**
 * Created by archerlei on 2017/4/17.
 */

public class ActivityHelper {
    private static Activity mVrActivity = null;
    public static void setVrActivity(Activity vrActivity) {
        mVrActivity = vrActivity;
    }

    public static Activity getVrActivity() {
        return mVrActivity;
    }

    public static void finishVrActivity() {
        mVrActivity.finish();
    }

    public static void VrActivityOnBackPressed() {
        mVrActivity.onBackPressed();
    }

}
