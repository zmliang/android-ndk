package test.zml.com.myndk;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Author: zml
 * Date  : 2019/1/11 - 17:51
 **/
public class BitmapPlayerActivity extends AbstractPlayerActivity {
    private final AtomicBoolean isPlaying = new AtomicBoolean();

    private SurfaceHolder surfaceHolder;
    private Thread thread;

    public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bitmap_player);
        SurfaceView surfaceView = findViewById(R.id.surface_view);
        surfaceHolder = surfaceView.getHolder();
        surfaceHolder.addCallback(surfaceHolderCallback);
    }

    private final SurfaceHolder.Callback surfaceHolderCallback = new SurfaceHolder.Callback() {
        @Override
        public void surfaceCreated(SurfaceHolder surfaceHolder) {
            isPlaying.set(true);
            if (thread == null){
                thread = new Thread(renderer);
            }
            thread.start();
        }

        @Override
        public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

        }

        @Override
        public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
            isPlaying.set(false);
        }
    };

    private final Runnable renderer = new Runnable() {
        @Override
        public void run() {
            Bitmap bitmap = Bitmap.createBitmap(getWidth(avi),getHeight(avi),Bitmap.Config.ARGB_8888);
            long frameDelay = (long) (getFrameRate(avi));
            Log.i("zmliang","frameDelay:"+frameDelay);
            while (isPlaying.get()){
                render(avi,bitmap);
                Canvas canvas = surfaceHolder.lockCanvas();
                canvas.drawBitmap(bitmap,0,0,null);
                surfaceHolder.unlockCanvasAndPost(canvas);
                try{
                    Thread.sleep(frameDelay);
                }catch (InterruptedException e){
                    break;
                }
            }
        }
    };

    public native static boolean render(long avi,Bitmap bitmap);

}
