package com.example.myapplication;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);

        TestJNIBean testJNIBean = new TestJNIBean();
        String testCallMethod = testJNIBean.testCallMethod();
        String testStaticCallMethod = TestJNIBean.testStaticCallMethod();
//        tv.setText(stringFromJNI() + "-------testCallMethod-----" + testCallMethod + "******testStaticCallMethod*******" + testStaticCallMethod);

        String testStaticCallStaticMethod = TestJNIBean.testStaticCallStaticMethod();
//        tv.setText("--------"+testStaticCallStaticMethod);

        String callFatherMethod = testJNIBean.testCallFatherMethod();
        String callChildMethod = testJNIBean.testCallChildMethod();
        tv.setText("------callFatherMethod---"+callFatherMethod+"------callChildMethod---"+callChildMethod);


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
