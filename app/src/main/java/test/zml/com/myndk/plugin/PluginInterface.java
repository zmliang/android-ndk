package test.zml.com.myndk.plugin;

import android.os.Bundle;

import androidx.fragment.app.FragmentActivity;

/**
 * Author: zml
 * Date  : 2018/11/26 - 09:15
 **/
public interface PluginInterface {

    void onCreate(Bundle saveInstance);

    void attachContext(FragmentActivity context);

    void onStart();

    void onResume();

    void onRestart();

    void onDestroy();

    void onStop();

    void onPause();
}
