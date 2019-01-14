package test.zml.com.myndk;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import java.util.concurrent.atomic.AtomicBoolean;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Author: zml
 * Date  : 2019/1/14 - 09:35
 **/
public class OpenGLPlayerActivity extends AbstractPlayerActivity {
    private final AtomicBoolean isPlaying = new AtomicBoolean();

    /**
     * 原生渲染器
     */
    private long instance;

    private GLSurfaceView glSurfaceView;

    public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_open_gl_player);
        glSurfaceView = findViewById(R.id.gl_surface_view);
        glSurfaceView.setRenderer(renderer);
        glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    protected void onStart(){
        super.onStart();
        instance = init(avi);
        Log.i("zmliang","instance:"+instance);
    }

    protected void onResume(){
        super.onResume();
        glSurfaceView.onResume();
    }

    protected void onPause(){
        super.onPause();
        glSurfaceView.onPause();
    }

    protected void onStop(){
        super.onStop();
        free(instance);
        instance = 0;
    }

    private final Runnable player = new Runnable() {
        @Override
        public void run() {
            long frameDelay = (long)(1000/getFrameRate(avi));
            while (isPlaying.get()){
                glSurfaceView.requestRender();
                try{
                    Thread.sleep(frameDelay);
                }catch (InterruptedException e){
                    e.printStackTrace();
                    break;
                }
            }
        }
    };

    private final GLSurfaceView.Renderer renderer = new GLSurfaceView.Renderer() {
        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
            initSurface(instance,avi);

            isPlaying.set(true);
            new Thread(player).start();
        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int i, int i1) {

        }

        @Override
        public void onDrawFrame(GL10 gl10) {
            //渲染下一帧
            if (!render(instance,avi)){
                isPlaying.set(false);
            }
        }
    };


    private native static long init(long avi);

    private native static void initSurface(long instance,long avi);

    /**
     * 用给定文件进行帧渲染
     */
    private native static boolean render(long instance,long avi);

    private native static void free(long instance);



}
