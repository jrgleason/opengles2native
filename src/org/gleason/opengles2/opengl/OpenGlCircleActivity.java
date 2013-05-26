package org.gleason.opengles2.opengl;

import org.gleason.opengles2.opengl.model.Sprite;
import org.gleason.opengles2.opengl.renderer.CircleRenderer;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.graphics.Point;
import android.util.Log;
import android.view.Display;
import android.view.DragEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

public class OpenGlCircleActivity extends Activity implements View.OnTouchListener, View.OnDragListener {
	Thread mGameThread;
	private GLSurfaceView view;
	GLSurfaceView.Renderer render;
	Point size;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Display display = getWindowManager().getDefaultDisplay();
    	size = new Point();
    	display.getSize(size);
    	Sprite.setHeight(size.y);
    	Sprite.setWidth(size.x);
	    view = new GLSurfaceView(this);
	    view.setOnTouchListener(this);
	    // Tell EGL to use a ES 2.0 Context
	    view.setEGLContextClientVersion(2);
	    view.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);

	    // Set the renderer
	    render = new CircleRenderer();
	    view.setRenderer(render);
	    
	    Log.d("Debug", "Trying to set ortho");
	    Sprite.setCords(size.y, size.x);
	    Log.d("Debug", "Done set ortho");

	    setContentView(view);
	    Thread mGameThread = new Thread(new Runnable() {
			public void run() {
				Sprite.loop();
			}
		});
		mGameThread.start();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		view.requestRender();
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_open_gl, menu);
		return true;
	}

	int currentTouchX = 0;
	
	@Override
	public boolean onTouch(View view, MotionEvent event) {
		if(event.getAction() == MotionEvent.ACTION_DOWN){
			Sprite.toggleColor();
		}
		if(event.getAction() == MotionEvent.ACTION_UP){
			Sprite.toggleColor();
		}
		moveCircle(event.getX(), event.getY());
		return true;
	}
	
	private void moveCircle(float x, float y){
		Sprite.setMoveX(x);
		Sprite.setMoveY(y);
	}

	@Override
	public boolean onDrag(View v, DragEvent event) {
		moveCircle(event.getX(),event.getY());
		return true;
	}
}
