package org.gleason.opengles2.opengl;


import org.gleason.opengles2.opengl.model.Sprite;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity implements View.OnClickListener {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_mainl);
		final Button button = (Button) findViewById(R.id.button1);
        button.setOnClickListener(this);
        final Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(this);
        final Button button3 = (Button) findViewById(R.id.button3);
        button3.setOnClickListener(this);
	}
	public void onClick(View v) {
		switch(v.getId()){
		case(R.id.button1):
			startGL();
			break;
		case(R.id.button2):
			Sprite.eglinfo();
			break;
		case(R.id.button3):
			startGLLine();
		    break;
		}
    }
	private void startGL(){
		Intent intent = new Intent(this, OpenGlActivity.class);
		startActivity(intent);
	}
	private void startGLLine(){
		Intent intent = new Intent(this, OpenGlLineActivity.class);
		startActivity(intent);
	}
}
