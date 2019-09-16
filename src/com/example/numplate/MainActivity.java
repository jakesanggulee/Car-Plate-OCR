package com.example.numplate;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.channels.FileChannel;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipException;
import java.util.zip.ZipFile;
import java.util.zip.ZipOutputStream;

import com.example.numplate.MainActivity;
import com.example.numplate.SubAcvitity;
import com.example.numplate.BMPWriter;
import com.example.numplate.R;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

   public native void Methodadd(int nv, int cv, int mv, int jv);
   public native int img2char(String str);
   public native int startocr(int mode);
   public native int downloaddb();
   public native int uploaddb();
  
   
   static{
      System.loadLibrary("img");
      
   }
   
   ImageView n1,n2,n3,n4,n5,n6,n7,n8,m1,m2,m3,m4;
   Button button_pic, button_alb, button_go,button_save; 
   Button rotate, refresh;
   public Bitmap bitmap = null;  //// original image
   TextView tx,rx;
   public int suc = 2;
   public int n_det = 0;
   public File mFile,lFile;
   public int progress_bar = 1;
    ProgressBar mProgBar;
   public int db_valid = 0;
   int mDegree = 0;

    String str_result;
    
    public int a;
    private String[] items = {"다운로드", "업로드", "저장", "로그보기"};
    
    public void ocr_string(String str){
       String C1, C2, N1, N2;
       int strlength;
   
       if(n_det == 7){
          // 만약 7개의 글자가 감지되면
          //str이 입력으로 "N N C N N N N" 이렇게 들어옴   전부다 숫자값으로 들어옴
          strlength = str.length();
          
          if(strlength == 13){
             
             C1 = str.substring(4, 5);
             N1 = str.substring(0, 4);
             N2 = str.substring(5);
             
             if( C1.equals("0")) {
                str_result = N1.concat("거".concat(N2));
             }
             else if( C1.equals("1")) {
                str_result = N1.concat("고".concat(N2));
             }
             else if( C1.equals("2")) {
                str_result = N1.concat("구".concat(N2));
             }
             else if( C1.equals("3")) {
                str_result = N1.concat("나".concat(N2));
             }
             else if( C1.equals("4")) {
                str_result = N1.concat("너".concat(N2));
             }
             else if( C1.equals("5")) {
                str_result = N1.concat("다".concat(N2));
             }
             else if( C1.equals("6")) {
                str_result = N1.concat("더".concat(N2));
             }
             else if( C1.equals("7")) {
                str_result = N1.concat("라".concat(N2));
             }
             else if( C1.equals("8")) {
                str_result = N1.concat("러".concat(N2));
             }
             else if( C1.equals("9")) {
                str_result = N1.concat("머".concat(N2));
             }
          }
          else if(strlength == 14){
             C1 = str.substring(4, 6);
             N1 = str.substring(0, 4);
             N2 = str.substring(6);
             
             if( C1.equals("10")) {
                str_result = N1.concat("버".concat(N2));
             }
             else if( C1.equals("11")) {
                str_result = N1.concat("어".concat(N2));
             }
             else if( C1.equals("12")) {
                str_result = N1.concat("오".concat(N2));
             }
             else if( C1.equals("13")) {
                str_result = N1.concat("허".concat(N2));
             }
             else if( C1.equals("14")) {
                str_result = N1.concat("호".concat(N2));
             }
          }
        }
        
          
       
       
       if(n_det == 8){
          //만약 8개의 글자가 감지되면
          //str이 입력으로 "N N C C N N N N"이렇게 들어옴
          C1 = str.substring(4, 6);
          C2 = str.substring(6, 7);
          N1 = str.substring(0, 4);
          N2 = str.substring(7);
          
          if( C1.equals("0 ")) {
            if( C2.equals("0")){
               str_result = N1.concat("가".concat(N2));
            }
            else if( C2.equals("4")){
               str_result = N1.concat("마".concat(N2));
            }
            else if( C2.equals("5")){
               str_result = N1.concat("바".concat(N2));
            }
            else if( C2.equals("6")){
               str_result = N1.concat("사".concat(N2));
            }
            else if( C2.equals("7")){
               str_result = N1.concat("아".concat(N2));
            }
            else if( C2.equals("8")){
               str_result = N1.concat("자".concat(N2));
            }
            else if( C2.equals("9")){
               str_result = N1.concat("하".concat(N2));
            }
         }
         else if( C1.equals("1 ")) {
            if( C2.equals("6")){
               str_result = N1.concat("서".concat(N2));
            }
            else if( C2.equals("8")){
               str_result = N1.concat("저".concat(N2));
            }
         }
         else if( C1.equals("2 ")) {
            if( C2.equals("1")){
               str_result = N1.concat("노".concat(N2));
            }
            else if( C2.equals("2")){
               str_result = N1.concat("도".concat(N2));
            }
            else if( C2.equals("3")){
               str_result = N1.concat("로".concat(N2));
            }
            else if( C2.equals("4")){
               str_result = N1.concat("모".concat(N2));
            }
            else if( C2.equals("5")){
               str_result = N1.concat("보".concat(N2));
            }
            else if( C2.equals("6")){
               str_result = N1.concat("소".concat(N2));
            }
            else if( C2.equals("8")){
               str_result = N1.concat("조".concat(N2));
            }
         }
         else if( C1.equals("3 ")) {
            if( C2.equals("1")){
               str_result = N1.concat("누".concat(N2));
            }
            else if( C2.equals("2")){
               str_result = N1.concat("두".concat(N2));
            }
            else if( C2.equals("3")){
               str_result = N1.concat("루".concat(N2));
            }
            else if( C2.equals("4")){
               str_result = N1.concat("무".concat(N2));
            }
            else if( C2.equals("5")){
               str_result = N1.concat("부".concat(N2));
            }
            else if( C2.equals("6")){
               str_result = N1.concat("수".concat(N2));
            }
            else if( C2.equals("7")){
               str_result = N1.concat("우".concat(N2));
            }
            else if( C2.equals("8")){
               str_result = N1.concat("주".concat(N2));
            }
         }
         else if( C1.equals("4 ")) {
            str_result = N1.concat("배".concat(N2));
         }
       }
       // str_result = str;
       string_update_screen();
    }
    
    
    public void resize_img(int mode) throws IOException{
       if(mode == 0){
          
          Bitmap in,out ;  
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O1.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N1.bmp");

          in= BitmapFactory.decodeFile("/sdcard/im2char/O2.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N2.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O3.bmp");
          out = Bitmap.createScaledBitmap(in,40,40, true);
          BMPWriter.save(out,"/sdcard/im2char/C1.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O4.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N3.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O5.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N4.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O6.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N5.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O7.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N6.bmp");
          
          
       }
       
       else{
          
        Bitmap in,out ;  
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O1.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N1.bmp");

          in= BitmapFactory.decodeFile("/sdcard/im2char/O2.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N2.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O3.bmp");
          out = Bitmap.createScaledBitmap(in,40,40, true);
          BMPWriter.save(out,"/sdcard/im2char/C1.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O4.bmp");
          out = Bitmap.createScaledBitmap(in,40,40, true);
          BMPWriter.save(out,"/sdcard/im2char/C2.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O5.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N3.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O6.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N4.bmp");
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O7.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N5.bmp");
          
          
          in= BitmapFactory.decodeFile("/sdcard/im2char/O8.bmp");
          out = Bitmap.createScaledBitmap(in,24,40, true);
          BMPWriter.save(out,"/sdcard/im2char/N6.bmp");
          
          
       }
    }
    
    
   @Override
   protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
      setContentView(R.layout.activity_main);
      button_alb = (Button)findViewById(R.id.button_alb);
      button_go = (Button)findViewById(R.id.button_go);
      button_pic = (Button)findViewById(R.id.button_pic);
      button_save = (Button)findViewById(R.id.save);
      
      rotate = (Button)findViewById(R.id.rotate);
      
      refresh = (Button)findViewById(R.id.refresh);

      m1 = (ImageView)findViewById(R.id.image11); //main
      m2 = (ImageView)findViewById(R.id.image12); //main
      m3 = (ImageView)findViewById(R.id.image1); //main
      m4 = (ImageView)findViewById(R.id.image10); //main
      
      n1 = (ImageView)findViewById(R.id.image2); //dig1
      n2 = (ImageView)findViewById(R.id.image3); //dig2
   
      n3 = (ImageView)findViewById(R.id.image4); //char1
      n4 = (ImageView)findViewById(R.id.image5); //char2
   
      n5 = (ImageView)findViewById(R.id.image6); //dig3
      n6 = (ImageView)findViewById(R.id.image7); //dig4
      
      n7 = (ImageView)findViewById(R.id.image8); //dig3
      n8 = (ImageView)findViewById(R.id.image9); //dig4
      
      File sdcard = Environment.getExternalStorageDirectory();
      lFile  = new File(sdcard.getAbsolutePath() + "/im2char");
      lFile.mkdir();
      lFile  = new File(sdcard.getAbsolutePath() + "/im2char/log");
      lFile.mkdir();
      lFile  = new File(sdcard.getAbsolutePath() + "/im2char/logcat.txt");
      try {
         lFile.createNewFile();
         lFile.setWritable(true);
      } catch (IOException e1) {
         // TODO Auto-generated catch block
         e1.printStackTrace();
      }
      
      int min_nv = 10; //최대 탐색 파일 개수
      int min_cv = 10;
      int min_jv = 10;
      int min_mv = 10;
      
      lFile  = new File(sdcard.getAbsolutePath() + "/im2char/database");
      if ( lFile.exists() ){
    	  db_valid = 1;
       
    	  for(int j=0; j <= 9; j++){
    		  File dir = new File("/sdcard/im2char/database/nums/" + Integer.toString(j) );
    		  long totalNumFiles = dir.listFiles().length;
    		  
    		  if(min_nv > totalNumFiles)
    			  min_nv = (int) totalNumFiles;
    		  
    	  }
    	  
    	  for(int j=0; j <= 9; j++){
    		  File dir = new File("/sdcard/im2char/database/chars/jaum/" + Integer.toString(j) );
    		  long totalNumFiles = dir.listFiles().length;
    		  
    		  if(min_jv > totalNumFiles)
    			  min_jv = (int) totalNumFiles;
    		  
    	  }
    	  
    	  for(int j=0; j <= 4; j++){
    		  File dir = new File("/sdcard/im2char/database/chars/moum/" + Integer.toString(j) );
    		  long totalNumFiles = dir.listFiles().length;
    		  
    		  if(min_mv > totalNumFiles)
    			  min_mv = (int) totalNumFiles;
    		  
    	  }
    	  

    	  for(int j=0; j <= 14; j++){
    		  File dir = new File("/sdcard/im2char/database/chars/one/" + Integer.toString(j) );
    		  long totalNumFiles = dir.listFiles().length;
    		  
    		  if(min_cv > totalNumFiles)
    			  min_cv = (int) totalNumFiles;
    		  
    	  }
    	  
    	  
    	  
    	  Toast.makeText(getApplicationContext(), "DB 숫자" + Integer.toString(min_nv) + "자음" + Integer.toString(min_jv)+ "모음" + Integer.toString(min_mv) + "한글자" + Integer.toString(min_cv), Toast.LENGTH_LONG).show();
    	  Methodadd(min_nv,min_cv,min_mv,min_jv);
    	  
      }
      
      else{
    	  db_valid =0;
    	  Toast.makeText(getApplicationContext(), "DB가 존재하지 않습니다  업데이트를 해주세요!", Toast.LENGTH_LONG).show();
      Methodadd(0,0,0,0);
      }
     
     
      
      
      tx = (TextView) findViewById(R.id.textview);
      rx = (TextView) findViewById(R.id.result);
      ocr_string("여기에 결과가 표시됩니다");      
      
      
       mProgBar= (ProgressBar)findViewById(R.id.progressBar1);
      Button.OnClickListener listener = new Button.OnClickListener() {
         
         public void onClick(View v) {

            if(v==button_pic){
               File sdcard = Environment.getExternalStorageDirectory();
                  mFile = new File(sdcard.getAbsolutePath() + "/im2char/Original.jpeg");
               
                  //Toast.makeText(getApplicationContext(), sdcard.getAbsolutePath(), Toast.LENGTH_LONG).show();
                              
                  Intent intent_pic = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                  intent_pic.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(mFile));
                
                  sendBroadcast(new Intent( Intent.ACTION_MEDIA_SCANNER_SCAN_FILE, Uri.fromFile(mFile)));
                  startActivityForResult(intent_pic, 0);
                  
                  

            }
            
            if(v==button_alb){
               Intent intent_alb = new Intent();
               intent_alb.setType("image/*"); 
               intent_alb.setAction(Intent.ACTION_GET_CONTENT); 
               startActivityForResult(intent_alb, 1000);
               
            }
            if(v==button_go){
               suc = 2;
               progress_bar = 1;
               n_det = 0;
               tx.setText("잠시만 기다령~ㄱㄷㄱㄷ");
               new Thread(new Runnable() {
                   @Override public void run()
                   {
                      Bitmap resized = Bitmap.createScaledBitmap(bitmap, 326*2,244*2, true); 
                      try {
                        BMPWriter.save(resized,"/sdcard/im2char/test.bmp");
                     } catch (IOException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                     }
                      
                      if( db_valid == 1 && ((n_det =img2char("/sdcard/im2char/test.bmp")) > 0))
                         suc = 1;
                      else
                         suc = 0;
                      
                      selection_update_screen();
                      
         
                      
                      
                   } }).start();
            }
            
            
            
            if(v==refresh){
               Intent intent = getIntent();
               finish();
               startActivity(intent);
               if(bitmap != null)
                  {bitmap.recycle();}
            	//outsource();
            }
            
            if(v==rotate){
            mDegree = 90;
            bitmap = rotateImage(bitmap, mDegree);
            m1.setImageBitmap(bitmap);
            
            }
            
            
         
         }
      };
      
          refresh.setOnClickListener(listener);
          
          rotate.setOnClickListener(listener);
          button_alb.setOnClickListener(listener);
         button_go.setOnClickListener(listener);
         button_pic.setOnClickListener(listener);
         button_save.setOnClickListener(listener);
        
         button_save.setOnClickListener(new View.OnClickListener() {
        	 Intent intent_log = new Intent(MainActivity.this, SubAcvitity.class); 
             @Override
             
             public void onClick(View v) {
                 AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                 builder.setTitle("옵션");
                 builder.setItems(items, new DialogInterface.OnClickListener() {
                     @Override
                     public void onClick(DialogInterface dialogInterface, int i) {
                         Toast.makeText(getApplicationContext(), items[i], Toast.LENGTH_SHORT).show();
                         a = i;
                         if(a == 0){
                       	  Toast.makeText(getApplicationContext(), "DB다운로드중 ", Toast.LENGTH_SHORT).show();

                             if( downloaddb() == 0){
                             Toast.makeText(getApplicationContext(), "DB 압출을 푸는중 기다리세욥 ", Toast.LENGTH_SHORT).show();
                             lFile  = new File("/sdcard/im2char/");
                             File zfile  = new File("/sdcard/im2char/download.zip");         
                             try {
                                extractFolder(lFile,zfile);
                             } catch (ZipException e1) {
                                // TODO Auto-generated catch block
                                e1.printStackTrace();
                             } catch (IOException e1) {
                                // TODO Auto-generated catch block
                                e1.printStackTrace();
                             }
                             Toast.makeText(getApplicationContext(), "완료! 재시작해야 적용됩니다.", Toast.LENGTH_SHORT).show();
                             }
                             
                             else{
                                Toast.makeText(getApplicationContext(), "인터넷 연결상태 확인 / 서버 연결상태 확인", Toast.LENGTH_SHORT).show();
                             }
                         }
                         if(a == 1){
                        	 
                        	 Toast.makeText(getApplicationContext(), "업로드 시도중", Toast.LENGTH_SHORT).show();
                             zipFileAtPath("/sdcard/im2char/database/", "/sdcard/im2char/upload.zip");
                             if( uploaddb() != -1)
                                Toast.makeText(getApplicationContext(), "업로드 성공", Toast.LENGTH_SHORT).show();
                             else
                                Toast.makeText(getApplicationContext(), "업로드 실패/서버이상 ", Toast.LENGTH_SHORT).show();
                             
                         }
                         if(a == 2){
                       	  File sdcard = Environment.getExternalStorageDirectory();
                             
                             char n1 = str_result.charAt(0);
                             char n2 = str_result.charAt(2);
                             char c1 = str_result.charAt(4);
                             char n3 = str_result.charAt(6);
                             char n4 = str_result.charAt(8);
                             char n5 = str_result.charAt(10);
                             char n6 = str_result.charAt(12);
                             
                       
                             
                             if(n_det == 7 || n_det ==8){
                             
                                if(Character.toString(c1).equals("가")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/0" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                   
                                }
                                else if(Character.toString(c1).equals("마")){

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/4" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                }
                                else if(Character.toString(c1).equals("바")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/5");
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                }
                                else if(Character.toString(c1).equals("사")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/6" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                }
                                else if(Character.toString(c1).equals("아")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/7" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                }
                                else if(Character.toString(c1).equals("자")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/8" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                }
                                else if(Character.toString(c1).equals("하")){
                                   
                                   File dir = new File("/sdcard/im2char/database/chars/jaum/9" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/0" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                }
                                else if(Character.toString(c1).equals("서")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/6" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/1" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                }
                                else if(Character.toString(c1).equals("저")){
                                   

                                   File dir = new File("/sdcard/im2char/database/chars/jaum/8" );
                                   long totalNumFiles = dir.listFiles().length;
                                   File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                   File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                    dir = new File("/sdcard/im2char/database/chars/moum/1" );
                                    totalNumFiles = dir.listFiles().length;
                                    sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                    dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                   try {
                                      copy(sFile,dFile);
                                   } catch (IOException e) {
                                      // TODO Auto-generated catch block
                                      e.printStackTrace();
                                   }
                                   
                                }
                                
                                
                                
                                
                                
                                else if(Character.toString(c1).equals("노")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/1" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                }
                                else if(Character.toString(c1).equals("도")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/2" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("로")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/3" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("모")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/4" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("보")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/5" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("소")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/6" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("조")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/8" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/2" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                               
                                else if(Character.toString(c1).equals("누")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/1" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("두")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/2" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("루")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/3" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("무")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/4" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("부")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/5" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("수")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/6" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("우")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/7" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("주")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/8" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/3" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("배")){
                              	  File dir = new File("/sdcard/im2char/database/chars/jaum/5" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                    
                                     dir = new File("/sdcard/im2char/database/chars/moum/4" );
                                     totalNumFiles = dir.listFiles().length;
                                     sFile = new File(sdcard.getAbsolutePath() + "/im2char/C2.bmp");
                                     dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                
                                
                                
                                
                                
                                ///한글자
                                else if(Character.toString(c1).equals("거")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/0" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("고")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/1" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("구")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/2" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("나")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/3" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("너")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/4" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("다")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/5" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("더")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/6" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("라")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/7" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("러")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/8" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("머")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/9" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("버")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/10" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("어")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/11" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("오")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/12" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("허")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/13" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                                else if(Character.toString(c1).equals("호")){
                              	  File dir = new File("/sdcard/im2char/database/chars/one/14" );
                                    long totalNumFiles = dir.listFiles().length;
                                    File sFile = new File(sdcard.getAbsolutePath() + "/im2char/C1.bmp");
                                    File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                    try {
                                       copy(sFile,dFile);
                                    } catch (IOException e) {
                                       // TODO Auto-generated catch block
                                       e.printStackTrace();
                                    }
                                }
                          
                                
                                
                                
                                
                                
                                File dir = new File("/sdcard/im2char/database/nums/" + Character.toString(n1));
                                long totalNumFiles = dir.listFiles().length;
                                File sFile = new File(sdcard.getAbsolutePath() + "/im2char/N1.bmp");
                                File dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                try {
                                   copy(sFile,dFile);
                                } catch (IOException e) {
                                   // TODO Auto-generated catch block
                                   e.printStackTrace();
                                }
                                
                                
                                 dir = new File("/sdcard/im2char/database/nums/" + Character.toString(n2));
                                 totalNumFiles = dir.listFiles().length;
                                 sFile = new File(sdcard.getAbsolutePath() + "/im2char/N2.bmp");
                                 dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                try {
                                   copy(sFile,dFile);
                                } catch (IOException e) {
                                   // TODO Auto-generated catch block
                                   e.printStackTrace();
                                }
                                
                                 dir = new File("/sdcard/im2char/database/nums/" + Character.toString(n3));
                                 totalNumFiles = dir.listFiles().length;
                                 sFile = new File(sdcard.getAbsolutePath() + "/im2char/N3.bmp");
                                 dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                try {
                                   copy(sFile,dFile);
                                } catch (IOException e) {
                                   // TODO Auto-generated catch block
                                   e.printStackTrace();
                                }
                                
                                
                                 dir = new File("/sdcard/im2char/database/nums/" + Character.toString(n4));
                                 totalNumFiles = dir.listFiles().length;
                                 sFile = new File(sdcard.getAbsolutePath() + "/im2char/N4.bmp");
                                 dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                try {
                                   copy(sFile,dFile);
                                } catch (IOException e) {
                                   // TODO Auto-generated catch block
                                   e.printStackTrace();
                                }
                                
                                 dir = new File("/sdcard/im2char/database/nums/" + Character.toString(n5));
                                 totalNumFiles = dir.listFiles().length;
                                 sFile = new File(sdcard.getAbsolutePath() + "/im2char/N5.bmp");
                                 dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                try {
                                   copy(sFile,dFile);
                                } catch (IOException e) {
                                   // TODO Auto-generated catch block
                                   e.printStackTrace();
                                }
                                
                                
                                 dir = new File("/sdcard/im2char/database/nums/" + Character.toString(n6));
                                 totalNumFiles = dir.listFiles().length;
                                 sFile = new File(sdcard.getAbsolutePath() + "/im2char/N6.bmp");
                                 dFile = new File(dir.getAbsolutePath() + "/1 (" + Long.toString(totalNumFiles+1) + ").bmp");
                                try {
                                   copy(sFile,dFile);
                                } catch (IOException e) {
                                   // TODO Auto-generated catch block
                                   e.printStackTrace();
                                }
                                
                                
                             
                       
                             
                             
                             } 
                             
                             
                         }
                      if(a == 3){
                    	  startActivity(intent_log);
                      }
                     }
                 });
                 AlertDialog alertDialog = builder.create();
                 alertDialog.show();
             }
         });
         
      
   }

   @Override
   public boolean onCreateOptionsMenu(Menu menu) {
      // Inflate the menu; this adds items to the action bar if it is present.
      getMenuInflater().inflate(R.menu.main, menu);
      return true;
   }

   @Override
   public boolean onOptionsItemSelected(MenuItem item) {
      // Handle action bar item clicks here. The action bar will
      // automatically handle clicks on the Home/Up button, so long
      // as you specify a parent activity in AndroidManifest.xml.
      int id = item.getItemId();
      if (id == R.id.action_settings) {
         return true;
      }
      return super.onOptionsItemSelected(item);
   }
   
   


@Override protected void onActivityResult(int requestCode, int resultCode, Intent data) 
{ 
   if (requestCode == 1000) { 
      // Make sure the request was successful 
      if (resultCode == RESULT_OK) { 
         try { 
            // 선택한 이미지에서 비트맵 생성 
            InputStream in = getContentResolver().openInputStream(data.getData()); 

            bitmap = BitmapFactory.decodeStream(in); //// 이진화 함수에 넘겨주기 위함
            in.close(); 
            // 이미지 표시 
         
            m1.setImageBitmap(bitmap);
            
         } catch (Exception e) { 
            e.printStackTrace(); 
         } 
      } 
   } 

   
   
    if (requestCode == 0 && resultCode == RESULT_OK) {
         int width = m1.getWidth();
         int height = m1.getHeight();

         
     
         BitmapFactory.Options bmpFactoryOptions = new BitmapFactory.Options();
         bmpFactoryOptions.inJustDecodeBounds = true;
         BitmapFactory.decodeFile(mFile.getAbsolutePath(), bmpFactoryOptions);

         int widthRatio = (int) Math.ceil(bmpFactoryOptions.outWidth / (float) width);
         int heightRatio = (int) Math.ceil(bmpFactoryOptions.outHeight / (float) height);
         if (heightRatio > 1 || widthRatio > 1) {
             if (heightRatio > widthRatio) {
                 bmpFactoryOptions.inSampleSize = heightRatio;
             } else {
                 bmpFactoryOptions.inSampleSize = widthRatio;
             }
         }

         bmpFactoryOptions.inJustDecodeBounds = false;
         Bitmap bmp = BitmapFactory.decodeFile(mFile.getAbsolutePath(), bmpFactoryOptions);
         m1.setImageBitmap(bmp);
         
         bitmap = bmp;
     
    
    
    }
   
   
   
   
   
}



public void string_update_screen(){
   
   runOnUiThread(new Runnable() {
       @Override
       public void run() {          
       
       rx.setText(str_result);
       }
   });
   
   
}

public void labeled_update_screen(){
   
   runOnUiThread(new Runnable() {
       @Override
       public void run() {          
       
          Bitmap result = BitmapFactory.decodeFile("/sdcard/im2char/log/step2.bmp");
          m3.setImageBitmap(result);
       }
   });
   
   
}



public void binarized_update_screen(){
   
   runOnUiThread(new Runnable() {
       @Override
       public void run() {          
       
          Bitmap result = BitmapFactory.decodeFile("/sdcard/im2char/log/step1.bmp");
          m2.setImageBitmap(result);
       }
   });
   
   
}


public void progress_update_screen(){
   
   runOnUiThread(new Runnable() {
       @Override
       public void run() {          
       
         
            tx.setText("진행중"+ Integer.toString(progress_bar++));
            mProgBar.incrementProgressBy(1);
      
         
       }
   });
   
}
public void deq_sqr_update_screen(){
   
   runOnUiThread(new Runnable() {
       @Override
       public void run() {          
          Bitmap result = BitmapFactory.decodeFile("/sdcard/im2char/log/Det_Square.bmp");
          m4.setImageBitmap(result);
       }
   });
   
   
}



public void selection_update_screen(){
      
    runOnUiThread(new Runnable() {
       @Override
       public void run() {          
          if(suc ==0){
            tx.setText("망 ㅠㅠ");
            mProgBar.setProgress(0);
          }
         else if(suc == 1){
            tx.setText(Integer.toString(n_det)+"개 감지 성공ㅠㅠ");
            mProgBar.setProgress(0);
            
         
            
            if(n_det ==7){
               Bitmap result = BitmapFactory.decodeFile("/sdcard/im2char/O1.bmp");
                n1.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O2.bmp");
                n2.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O3.bmp");
                n3.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O4.bmp");
                n4.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O5.bmp");
                n5.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O6.bmp");
                n6.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O7.bmp");
                n7.setImageBitmap(result);
                try {
                  resize_img(0);
                  startocr(0);
                  
               } catch (IOException e) {
                  // TODO Auto-generated catch block
                  e.printStackTrace();
               }
                //startocr(0);
             
             }
   
            if(n_det ==8){
               Bitmap result = BitmapFactory.decodeFile("/sdcard/im2char/O1.bmp");
                n1.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O2.bmp");
                n2.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O3.bmp");
                n3.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O4.bmp");
                n4.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O5.bmp");
                n5.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O6.bmp");
                n6.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O7.bmp");
                n7.setImageBitmap(result);
                result = BitmapFactory.decodeFile("/sdcard/im2char/O8.bmp");
                n8.setImageBitmap(result);  
                try {
                  resize_img(1);
                  startocr(1);
               } catch (IOException e) {
                  // TODO Auto-generated catch block
                  e.printStackTrace();
               }
                //startocr(1);
             }
            
            
            
         }

       }
   });
      
}

public void copy(File src, File dst) throws IOException {
    FileInputStream inStream = new FileInputStream(src);
    FileOutputStream outStream = new FileOutputStream(dst);
    FileChannel inChannel = inStream.getChannel();
    FileChannel outChannel = outStream.getChannel();
    inChannel.transferTo(0, inChannel.size(), outChannel);
    inStream.close();
    outStream.close();
}


private boolean extractFolder(File destination, File zipFile) throws ZipException, IOException
{
   
     String newPath = destination.getAbsolutePath();
     new File(newPath).mkdir();
  
    int BUFFER = 8192;
    File file = zipFile;
    ZipFile zip = new ZipFile(file);
 
    
    Enumeration<? extends ZipEntry> zipFileEntries = zip.entries();
    while (zipFileEntries.hasMoreElements())
    {
       
        ZipEntry entry = (ZipEntry) zipFileEntries.nextElement();
        String currentEntry = entry.getName();
        File destFile = new File(newPath, currentEntry);
        File destinationParent = destFile.getParentFile();
        destinationParent.mkdirs();

        if (!entry.isDirectory())
        {
            BufferedInputStream is = new BufferedInputStream(zip
            .getInputStream(entry));
            int currentByte;
            byte data[] = new byte[BUFFER];
            //orthodox way of copying file data using streams
            FileOutputStream fos = new FileOutputStream(destFile);
            BufferedOutputStream dest = new BufferedOutputStream(fos, BUFFER);
            while ((currentByte = is.read(data, 0, BUFFER)) != -1) {
                dest.write(data, 0, currentByte);
            }
            dest.flush();
            dest.close();
            is.close();
        }
    }
    return true;//some error codes etc.
}

public boolean zipFileAtPath(String sourcePath, String toLocation) {
    final int BUFFER = 2048;

    File sourceFile = new File(sourcePath);
    try {
        BufferedInputStream origin = null;
        FileOutputStream dest = new FileOutputStream(toLocation);
        ZipOutputStream out = new ZipOutputStream(new BufferedOutputStream(
                dest));
        if (sourceFile.isDirectory()) {
            zipSubFolder(out, sourceFile, sourceFile.getParent().length());
        } else {
            byte data[] = new byte[BUFFER];
            FileInputStream fi = new FileInputStream(sourcePath);
            origin = new BufferedInputStream(fi, BUFFER);
            ZipEntry entry = new ZipEntry(getLastPathComponent(sourcePath));
            entry.setTime(sourceFile.lastModified()); // to keep modification time after unzipping
            out.putNextEntry(entry);
            int count;
            while ((count = origin.read(data, 0, BUFFER)) != -1) {
                out.write(data, 0, count);
            }
        }
        out.close();
    } catch (Exception e) {
        e.printStackTrace();
        return false;
    }
    return true;
}


private void zipSubFolder(ZipOutputStream out, File folder,
        int basePathLength) throws IOException {

    final int BUFFER = 2048;

    File[] fileList = folder.listFiles();
    BufferedInputStream origin = null;
    for (File file : fileList) {
        if (file.isDirectory()) {
            zipSubFolder(out, file, basePathLength);
        } else {
            byte data[] = new byte[BUFFER];
            String unmodifiedFilePath = file.getPath();
            String relativePath = unmodifiedFilePath
                    .substring(basePathLength);
            FileInputStream fi = new FileInputStream(unmodifiedFilePath);
            origin = new BufferedInputStream(fi, BUFFER);
            ZipEntry entry = new ZipEntry(relativePath);
            entry.setTime(file.lastModified()); // to keep modification time after unzipping
            out.putNextEntry(entry);
            int count;
            while ((count = origin.read(data, 0, BUFFER)) != -1) {
                out.write(data, 0, count);
            }
            origin.close();
        }
    }
}


public String getLastPathComponent(String filePath) {
    String[] segments = filePath.split("/");
    if (segments.length == 0)
        return "";
    String lastPathComponent = segments[segments.length - 1];
    return lastPathComponent;
}
   

public Bitmap rotateImage(Bitmap src, float degree) {
    
    // Matrix 객체 생성
    Matrix matrix = new Matrix();
    // 회전 각도 셋팅
    matrix.postRotate(degree);
    // 이미지와 Matrix 를 셋팅해서 Bitmap 객체 생성
    return Bitmap.createBitmap(src, 0, 0, src.getWidth(),
            src.getHeight(), matrix, true);
}




}
