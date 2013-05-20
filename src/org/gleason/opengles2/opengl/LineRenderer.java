package org.gleason.opengles2.opengl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import org.gleason.opengles2.opengl.model.Sprite;

import android.opengl.GLSurfaceView;

public class LineRenderer implements GLSurfaceView.Renderer {
	@Override
	public void onDrawFrame(GL10 arg0) {
		// TODO Auto-generated method stub
//		Sprite.loop();
		Sprite.renderline();
	}

	@Override
	public void onSurfaceChanged(GL10 arg0, int width, int height) {
		// TODO Auto-generated method stub
		Sprite.resize(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 arg0, EGLConfig arg1) {
		// TODO Auto-generated method stub
		Sprite.init();
	}

}