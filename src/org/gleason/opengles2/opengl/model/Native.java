package org.gleason.opengles2.opengl.model;

public class Native {
	static 
	{
		System.loadLibrary("color-atttr");
	}

	public static native void init();
	public static native void resize(int width, int height);
	public static native void render();
	public static native void setCords(float y, float x);
	public static native void toggleColor();
}