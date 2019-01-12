package test.zml.com.myndk;

public class JNITest {

    static {
        System.loadLibrary("NDKTest");
    }

    public native static String getVersion();

    public native static String sendMessage(String msg);


}
