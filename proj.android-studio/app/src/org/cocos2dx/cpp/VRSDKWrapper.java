/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;
//VR_SDK_WRAPPER_IMPORTS_BEGIN
import android.view.View;
import android.view.WindowManager;
import com.google.vr.ndk.base.AndroidCompat;
import com.google.vr.ndk.base.GvrLayout;
import org.cocos2dx.lib.ResizeLayout;
//VR_SDK_WRAPPER_IMPORTS_END

public class VRSDKWrapper {
//VR_SDK_WRAPPER_MEMBERS_BEGIN
    private GvrLayout gvrLayout;
    private AppActivity appActivity;
//VR_SDK_WRAPPER_MEMBERS_END
    public void onCreate(AppActivity activity){
//VR_SDK_WRAPPER_ON_CREATE_BEGIN
        appActivity = activity;
        gvrLayout = new GvrLayout(appActivity);
        setImmersiveSticky();
        appActivity.getWindow()
                  .getDecorView()
                  .setOnSystemUiVisibilityChangeListener(
                                                      new View.OnSystemUiVisibilityChangeListener() {
                                                           @Override
                                                           public void onSystemUiVisibilityChange(int visibility) {
                                                               if ((visibility & View.SYSTEM_UI_FLAG_FULLSCREEN) == 0) {
                                                                   setImmersiveSticky();
                                                               }
                                                           }
                                                       });
        ResizeLayout parent = (ResizeLayout)appActivity.getGLSurfaceView().getParent();
        parent.removeView(appActivity.getGLSurfaceView());
        appActivity.getGLSurfaceView().setPreserveEGLContextOnPause(true);
        gvrLayout.setPresentationView(appActivity.getGLSurfaceView());
        AndroidCompat.setVrModeEnabled(appActivity, true);
        nativeCreate(gvrLayout.getGvrApi().getNativeGvrContext());
        appActivity.setContentView(gvrLayout);
        appActivity.getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
//VR_SDK_WRAPPER_ON_CREATE_END
    }

    public void onDestroy(){
//VR_SDK_WRAPPER_ON_DESTROY_BEGIN
        gvrLayout.shutdown();
//VR_SDK_WRAPPER_ON_DESTROY_END
    }

    public void onResume(){
//VR_SDK_WRAPPER_ON_RESUME_BEGIN
        gvrLayout.onResume();
//VR_SDK_WRAPPER_ON_RESUME_END
    }

    public void onPause(){
//VR_SDK_WRAPPER_ON_PAUSE_BEGIN
        gvrLayout.onPause();
//VR_SDK_WRAPPER_ON_PAUSE_END
    }

    public void onRestart(){
//VR_SDK_WRAPPER_ON_RESTART_BEGIN
//VR_SDK_WRAPPER_ON_RESTART_END
    }

    public void onStop(){
//VR_SDK_WRAPPER_ON_STOP_BEGIN
//VR_SDK_WRAPPER_ON_STOP_END
    }
//VR_SDK_WRAPPER_FUNCTIONS_BEGIN
    private void setImmersiveSticky() {
        appActivity.getWindow()
                .getDecorView()
                .setSystemUiVisibility(
                        View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                      | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                      | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                      | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                      | View.SYSTEM_UI_FLAG_FULLSCREEN
                      | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
    }
    private native long nativeCreate(long gvrContext);
//VR_SDK_WRAPPER_FUNCTIONS_END
}
