package org.gleason.opengles2.opengl;


import org.gleason.opengles2.opengl.model.Sprite;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Intent;
import android.graphics.Point;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends ListActivity implements OnItemClickListener {
	
	static final String[] EXAMPLES = new String[] { "OpenGL Triangle", "OpenGL Lines", "OpenGL Circle", "EGL Info" };
	
	private enum Examples{
		TRIANGLE("OpenGL Triangle"),
		LINES("OpenGL Lines"),
		CIRCLE("OpenGL Circle"),
		EGL_INFO("EGL Info");
		private String text;
		private Examples(String text){
			this.text = text;
		}
		@Override public String toString() {
		    return text;
		}
		public static Examples getByText(String text){
			for(Examples e : Examples.values()){
				if(e.toString().equalsIgnoreCase(text)){
					return e;
				}
			}
			return null;
		}
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setListAdapter(new ArrayAdapter<Examples>(this, R.layout.activity_mainl, Examples.values()));
		ListView listView = getListView();
		listView.setTextFilterEnabled(true);
		listView.setOnItemClickListener(this);
	}
	public void onItemClick(AdapterView<?> parent, View view,
			int position, long id) {
	    // When clicked, show a toast with the TextView text
		Examples e = Examples.getByText(((TextView) view).getText().toString());
	    switch(e){
	    case CIRCLE:
	    	startGLCircle();
	    	break;
	    case EGL_INFO:
	    	Sprite.eglinfo();
	    	break;
	    case LINES:
	    	startGLLine();
	    	break;
	    case TRIANGLE:
	    	startGL();
	    	break;
	    }
	}
//	public void onClick(View v) {
//		switch(v.getId()){
//		case(R.id.button1):
//			startGL();
//			break;
//		case(R.id.button2):
//			Sprite.eglinfo();
//			break;
//		case(R.id.button3):
//			startGLLine();
//		    break;
//		}
    
	private void startGL(){
		Intent intent = new Intent(this, OpenGlActivity.class);
		startActivity(intent);
	}
	private void startGLLine(){
		Intent intent = new Intent(this, OpenGlLineActivity.class);
		startActivity(intent);
	}
	private void startGLCircle(){
		Intent intent = new Intent(this, OpenGlCircleActivity.class);
		startActivity(intent);
	}
}
