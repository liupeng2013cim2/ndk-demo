package com.andy.ndkdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private int mCount;

    private void throwException() {
        throw new IllegalStateException("state error");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        try {
            String hello = "hello from java";
            stringFromJava(hello);
            Log.i(TAG, "hello set null in java");
            String hello2 = new String("hello2");
            stringFromJava2(hello2);
            hello2 = null;
            System.gc();
//            Thread.sleep(2000);
            Log.i(TAG, "hello set null");
//            accessGlobal();

            startNativeThread();

//            crash();

            testClass();

        } catch (Exception e) {
            Log.i(TAG, e.getMessage());
        }
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.i(TAG, "onstart");
        accessWeakGlobal();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String stringFromJava(String string);

    public native void stringFromJava2(String string);

    public native void accessGlobal();

    public native void accessWeakGlobal();

    public native void startNativeThread();

    public native void crash();

    public native void testClass();

    public void updateUi(String text) {
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(text);
    }

    int[] mData;
    public void updateData(int[] array) {
        mData = array;
        for (int t:mData) {
            Log.i(TAG, "i:" + t);
        }
        Log.i(TAG, "count:" + mCount);
    }
}
