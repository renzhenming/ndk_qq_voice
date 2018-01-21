package org.fmod.example;

import java.io.File;

import com.renzhenming.qq_voice.R;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;

public class QQActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		 org.fmod.FMOD.init(this);
		setContentView(R.layout.activity_main);
	}
	
	public void mFix(View view){
		String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "singing.wav";
		Log.d("renzhenming", path);
		
		switch (view.getId()) {
		case R.id.btn_record:
			EffectUtils.fix(path, EffectUtils.MODE_NORMAL);
		    Log.d("renzhenming", "MODE_NORMAL");
			break;
		case R.id.btn_luoli:
			EffectUtils.fix(path, EffectUtils.MODE_LUOLI);
		    Log.d("renzhenming", "MODE_LUOLI");
			break;
		case R.id.btn_dashu:
			EffectUtils.fix(path, EffectUtils.MODE_DASHU);
		    Log.d("renzhenming", "MODE_DASHU");
			break;
		case R.id.btn_jingsong:
			EffectUtils.fix(path, EffectUtils.MODE_JINGSONG);
			break;	
			
		case R.id.btn_gaoguai:
			EffectUtils.fix(path, EffectUtils.MODE_GAOGUAI);
			break;	
			
		case R.id.btn_kongling:
			EffectUtils.fix(path, EffectUtils.MODE_KONGLING);
			break;	
		default:
			break;
		}
		
		
	}
	
	@Override
    protected void onDestroy(){    
    	org.fmod.FMOD.close();    	
    	super.onDestroy();
    }
}
