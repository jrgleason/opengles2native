package org.gleason.opengles2.opengl.model;

public class Sprite {
	static 
	{
		System.loadLibrary("game-gl");
	}

	public static native void init();
	public static native void resize(int width, int height);
	public static native void setWidth(int width);
	public static native void setHeight(int height);
	public static native void render();
	public static native void renderline();
	public static native void eglinfo();
	public static native void loop();
	public static native void rendercircle();
//	public static native void setLocationWidth(int w, int tw);
	public static native void setMoveX(float x);
	public static native void setMoveY(float y);
	public static native void setCords(float y, float x);
}