package org.gleason.opengles2.opengl;


import java.nio.FloatBuffer;
import java.nio.IntBuffer;


import org.gleason.opengles2.opengl.model.Sprite;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class OpenGlLineActivity extends Activity {
	Thread mGameThread;
	private GLSurfaceView view;
	GLSurfaceView.Renderer render;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

	    view = new GLSurfaceView(this);

	    // Tell EGL to use a ES 2.0 Context
	    view.setEGLContextClientVersion(2);
	    view.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);

	    // Set the renderer
	    render = new LineRenderer();
	    view.setRenderer(render);

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

}
