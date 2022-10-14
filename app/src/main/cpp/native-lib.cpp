#include <jni.h>
#include <string>
#include <cstring>
#include <cstdio>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cppnativeapplication_MainActivity_getInternalPath(JNIEnv *env, jobject activity) {
    jclass cls_Env = env->FindClass("android/app/NativeActivity");
    jmethodID mid_getExtStorage = env->GetMethodID(cls_Env, "getFilesDir", "()Ljava/io/File;");
    jobject obj_File = env->CallObjectMethod(activity, mid_getExtStorage);
    jclass cls_File = env->FindClass("java/io/File");
    jmethodID mid_getPath = env->GetMethodID(cls_File, "getPath", "()Ljava/lang/String;");
    jstring obj_Path = (jstring) env->CallObjectMethod(obj_File, mid_getPath);
    const char *path = env->GetStringUTFChars(obj_Path, nullptr);

    env->ReleaseStringUTFChars(obj_Path, path);
    FILE *file = fopen(path, "w+");

    if (file != nullptr) {
        fputs("HELLO WORLD!\n", file);
        fflush(file);
        fclose(file);
    }

    return env->NewStringUTF(path);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cppnativeapplication_MainActivity_writeToFile(JNIEnv *env, jobject,
                                                               jstring path, jstring text) {

    const char *nativePath = env->GetStringUTFChars(path, nullptr);
    const char *textChar = env->GetStringUTFChars(text, nullptr);
    FILE *p;
    p = fopen(nativePath, "w");
    if (p == nullptr) {
        return env->NewStringUTF("Error writing file");
    }
    size_t len = strlen(textChar);
    fwrite(textChar, len, 1, p);
    fclose(p);
    return env->NewStringUTF("File written successfully!");

}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_cppnativeapplication_MainActivity_readFile(JNIEnv *env, jobject,
                                                            jstring path) {
    const char *nativePath = env->GetStringUTFChars(path, nullptr);
    char buffer[1000];
    FILE *stream;
    stream = fopen(nativePath, "r");
    fread(&buffer, sizeof(char), 20, stream);
    fclose(stream);
    return env->NewStringUTF(buffer);
}

