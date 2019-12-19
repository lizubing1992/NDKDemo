package com.example.myapplication;

public class TestJNIBean {
    public static final String DEMO = "Test JNI Bean 9999";
    static {
        System.loadLibrary("native-lib");
    }

    //非静态方法
    public native String testCallMethod();

    //静态方法
    public static native String testStaticCallMethod();

    //静态方法调用静态方法

    public static native String testStaticCallStaticMethod();


    public Father father = new Child();
    //调用父类方法
    public native String testCallFatherMethod();
    //调用子类的方法
    public native String testCallChildMethod();


    //-------------C++ 调用Java------------------------





    public String describe(){
        return DEMO + "非静态方法";
    }

    public static String staticDescribe(){
        return DEMO + "静态方法";
    }


}
