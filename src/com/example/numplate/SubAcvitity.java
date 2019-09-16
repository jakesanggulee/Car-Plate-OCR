package com.example.numplate;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

public class SubAcvitity extends Activity {
	
	TextView txtRead;
    
	final static String filePath = "/sdcard/im2char/logcat.txt";


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_sub_acvitity);
		txtRead = (TextView)findViewById(R.id.logcats);
		
		String read = ReadTextFile(filePath);
        txtRead.setText(read);


		
	}
	
	
	 public String ReadTextFile(String path){
	        StringBuffer strBuffer = new StringBuffer();
	        try{
	            InputStream is = new FileInputStream(path);
	            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
	            String line="";
	            while((line=reader.readLine())!=null){
	                strBuffer.append(line+"\n");
	            }
	 
	            reader.close();
	            is.close();
	        }catch (IOException e){
	            e.printStackTrace();
	            return "";
	        }
	        return strBuffer.toString();
	    }

}
