#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


//普通方法调用native 之后回调普通方法 使用jobject
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_TestJNIBean_testCallMethod(JNIEnv *env, jobject instance) {
    //获取类 非静态类 需要通过GetObjectClass获取对象
    jclass test_class = env->GetObjectClass(instance);
    //获取方法
    jmethodID test_method = env->GetMethodID(test_class, "describe", "()Ljava/lang/String;");
    //实例化对象 相当于Java中的new
    jobject jobj = env->AllocObject(test_class);
    //调用方法获取返回值
    jstring res_string = (jstring) env->CallObjectMethod(jobj, test_method);
    //转化格式输出
    char *print = (char *) env->GetStringUTFChars(res_string, 0);
    return env->NewStringUTF(print);
}

//静态方法调用native 之后native调用普通方法 使用jclass
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_TestJNIBean_testStaticCallMethod(JNIEnv *env, jclass type) {
    //获取method
    jmethodID method_id = env->GetMethodID(type, "describe", "()Ljava/lang/String;");
    //实例化对象 相当于new
    jobject jobj = env->AllocObject(type);
    //调用方法
    jstring pring = (jstring) env->CallObjectMethod(jobj, method_id);
    //转化格式
    char *print = (char *) env->GetStringUTFChars(pring, 0);
    return env->NewStringUTF(print);
}


//静态调用native 之后调用java静态方法
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_TestJNIBean_testStaticCallStaticMethod(JNIEnv *env, jclass type) {
    jmethodID method_id = env->GetStaticMethodID(type, "staticDescribe", "()Ljava/lang/String;");
    jstring jni_string = (jstring) env->CallStaticObjectMethod(type, method_id);
    char *print = (char *) env->GetStringUTFChars(jni_string, 0);
    return env->NewStringUTF(print);
}

//多态调用父类的方法
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_TestJNIBean_testCallFatherMethod(JNIEnv *env, jobject instance) {
    jclass clazz = env->GetObjectClass(instance);
    //获取实例的字段
    jfieldID father_field = env->GetFieldID(clazz, "father", "Lcom/example/myapplication/Father;");
    //根据变量获取对象
    jobject father_obj = env->GetObjectField(instance, father_field);
    //获取类
    jclass clazz_father = env->FindClass("com/example/myapplication/Father");

    jmethodID father_method = env->GetMethodID(clazz_father, "toString", "()Ljava/lang/String;");
    //获取类的非虚方法
    jstring result = (jstring) env->CallNonvirtualObjectMethod(father_obj, clazz_father,father_method);

    return result;
}

//多态调用子类的方法
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_TestJNIBean_testCallChildMethod(JNIEnv *env,jobject instance){
    jclass clazz = env->GetObjectClass(instance);
    //获取实例的字段
    jfieldID father_field = env->GetFieldID(clazz, "father", "Lcom/example/myapplication/Father;");
    //根据变量获取对象
    jobject father_obj = env->GetObjectField(instance, father_field);
    //获取类
    jclass clazz_father = env->FindClass("com/example/myapplication/Father");

    jmethodID father_method = env->GetMethodID(clazz_father, "toString", "()Ljava/lang/String;");
    //获取类的非虚方法CallObjectMethod 则调用子类的toString
    jstring result = (jstring) env->CallObjectMethod(father_obj, father_method);

    return result;

}


