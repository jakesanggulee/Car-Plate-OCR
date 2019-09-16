#define __MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <jni.h>
#include <stdlib.h>
#include <pthread.h>
#include "debug.h"

#include "match.h"

#define  BUFF_SIZE   1024

JavaVM* javaVM = NULL;
jobject OBJ;
jclass CLS;


int TMP_NUM_VAL;
int TEMP_CHR_VAL;
int TEMP_MOR_VAL;
int TEMP_JAR_VAL;



int serv_bi_tha;
double serv_area_tha;
int serv_det;

JNIEXPORT void JNICALL
Java_com_example_numplate_MainActivity_Methodadd(JNIEnv *env, jobject obj,int nv,int cv,int mv, int jv){

	(*env)->GetJavaVM(env,&javaVM);
	jclass cls = (*env)->GetObjectClass(env,obj);
	CLS = (jclass)(*env)->NewGlobalRef(env,cls);
	OBJ = (*env)->NewGlobalRef(env,obj);
	 TMP_NUM_VAL = nv;
	 TEMP_CHR_VAL = cv;
	 TEMP_MOR_VAL = mv;
	 TEMP_JAR_VAL = jv;


}



JNIEXPORT jint JNICALL Java_com_example_numplate_MainActivity_downloaddb(JNIEnv *env, jobject obj){


   int   client_socket;
   int save_fd = open("/sdcard/im2char/download.zip",O_CREAT |O_WRONLY| O_TRUNC);


   struct sockaddr_in   server_addr;

   char   buff[BUFF_SIZE+5];

   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == client_socket)
      return -1;

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons(1982);
   server_addr.sin_addr.s_addr= inet_addr("202.30.20.187");

   if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
      return -1;

int len;

while(  (len = read ( client_socket, buff, BUFF_SIZE) ) > 0){
write(save_fd,buff,len);
}

   close( client_socket);
close(save_fd);
   return 0;



}


JNIEXPORT jint JNICALL Java_com_example_numplate_MainActivity_uploaddb(JNIEnv *env, jobject obj){


   int   client_socket;
   int send_fd = open("/sdcard/im2char/upload.zip",O_RDONLY|O_CREAT);


   struct sockaddr_in   server_addr;

   char   buff[BUFF_SIZE+5];

   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == client_socket)
      return -1;

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons(1983);
   server_addr.sin_addr.s_addr= inet_addr("202.30.20.187");

   if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
      return -1;

int len;

while(  (len = read ( send_fd, buff, BUFF_SIZE) ) > 0){
write(client_socket,buff,len);
}

   close( client_socket);
close(send_fd);
   return 0;



}



void* outsourcing(void* arg)
{
	 int   client_socket;
	   int send_fd = open("/sdcard/im2char/test.bmp",O_RDONLY|O_CREAT);
	   char carplatenumber[10];
	   struct sockaddr_in   server_addr;

	   char   buff[BUFF_SIZE+5];

	   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
	   if( -1 == client_socket)
	      return -1;

	   memset( &server_addr, 0, sizeof( server_addr));
	   server_addr.sin_family     = AF_INET;
	   server_addr.sin_port       = htons(1988);
	   server_addr.sin_addr.s_addr= inet_addr("202.30.20.187");

	   if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
	      return -1;

	int len;

	while(  (len = read ( send_fd, buff, BUFF_SIZE) ) > 0){
	write(client_socket,buff,len);
	}
	write(client_socket,buff,0);


	read(client_socket,carplatenumber,10);
	serv_det  = atoi(carplatenumber);
	read(client_socket,carplatenumber,10);
	serv_bi_tha = atoi(carplatenumber);
	read(client_socket,carplatenumber,10);
	serv_area_tha = atof(carplatenumber);

	close( client_socket);
	close(send_fd);


}



int outsource(){


	pthread_t  pt;
	pthread_create(&pt,NULL,outsourcing,(void*)NULL);

	return 0;
}





void java_selection_upate_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"selection_update_screen","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}

void java_match_upate_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"match_update_screen","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}


void java_labeled_update_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"labeled_update_screen","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}


void java_binarized_update_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"binarized_update_screen","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}


void java_progress_update_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"progress_update_screen","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}





void java_deq_sqr_update_screen(){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"deq_sqr_update_screen","()V");
	(*env)->CallVoidMethod(env,OBJ,method);

}




JNIEXPORT jint JNICALL Java_com_example_numplate_MainActivity_img2char(JNIEnv * env, jobject obj, jstring jstr){

#ifdef __DEBUG__
debug_fd = open(DEBUG_PATH, O_WRONLY|O_TRUNC);
__TIME_WRITE__("Logger Started!\n");
#endif


char *path_to_file = (*env)->GetStringUTFChars(env, jstr, NULL);

int ret;
int cont =1;

double area_tha = 40.0;
int bi_tha = 128;
int up =1;
int up_val = 3;


serv_det =1;
outsource();
	while(area_tha <= 60 && cont){
		bi_tha = 125;
		up_val = 5;
		while( bi_tha > 50 && bi_tha < 200 && cont){
			java_progress_update_screen();

			if( serv_det ==0){
#ifdef __DEBUG__
		__DEBUG_WRITE__("\nServer has Detected values %d", serv_bi_tha);
		__DEBUG_WRITE__("and %lf \n",serv_area_tha);
#endif
		serv_det =1;
		if((ret= imgseg(path_to_file,serv_area_tha,serv_bi_tha)) > 0){
						cont = 0;
					}

			}

			if(cont != 0 && (ret= imgseg(path_to_file,area_tha,bi_tha)) > 0){
#ifdef __DEBUG__
		__DEBUG_WRITE__("\nDetected By ANdroid %c\n",'!');
		__DEBUG_WRITE__("\nValues %d ",bi_tha);
		__DEBUG_WRITE__("%lf \n",area_tha);
#endif
				cont = 0;
			}
			if(up == 1){
				bi_tha += up_val;
				up_val += 5;
				up = 0;
			}
			else{
				bi_tha -= up_val;
				up_val += 5;
				up = 1;
			}
		}
		area_tha += 5.0;
	}
	if(cont == 1)
			return 0;
	else{
#ifdef __DEBUG__
__TIME_WRITE__("Segmentation Complete!\n");
#endif

java_update_str("Segmentation Complete!");
//java_selection_upate_screen();
			return ret;
	}


}

void java_update_str(char str[]){
	JNIEnv * env;
	(*javaVM)->AttachCurrentThread(javaVM,&env,NULL);
	jmethodID  method = (*env)->GetMethodID(env,CLS,"ocr_string","(Ljava/lang/String;)V");
	jstring name = (*env)->NewStringUTF(env,str);
	(*env)->CallVoidMethod(env,OBJ,method,name);
}


JNIEXPORT jint JNICALL Java_com_example_numplate_MainActivity_startocr(JNIEnv * env, jobject obj,jint mode){

char buf[50]="OCR started!";

#ifdef __DEBUG__
__TIME_WRITE__("OCR Started!\n");
#endif

if(TMP_NUM_VAL ==0 ||TEMP_CHR_VAL ==0 ||  TEMP_MOR_VAL ==0 || TEMP_JAR_VAL ==0 )
	return -1;



	if(mode == 0){

		 TP an1,an2,an3,an4,an5,an6,an7;
		 if( (an1.first = fast_match("/sdcard/im2char/N1.bmp")) == -1 )
			 an1 = predict(NTYPE, "/sdcard/im2char/N1.bmp",NULL);

		 if( (an2.first = fast_match("/sdcard/im2char/N2.bmp")) == -1 )
		 			 an2 = predict(NTYPE, "/sdcard/im2char/N2.bmp",NULL);

		 an3 = predict(CTYPE, "/sdcard/im2char/C1.bmp",NULL);

		 if( (an4.first = fast_match("/sdcard/im2char/N3.bmp")) == -1 )
				 			 an4 = predict(NTYPE, "/sdcard/im2char/N3.bmp",NULL);


		 if( (an5.first = fast_match("/sdcard/im2char/N4.bmp")) == -1 )
				 			 an5 = predict(NTYPE, "/sdcard/im2char/N4.bmp",NULL);


		 if( (an6.first = fast_match("/sdcard/im2char/N5.bmp")) == -1 )
				 			 an6 = predict(NTYPE, "/sdcard/im2char/N5.bmp",NULL);


		 if( (an7.first = fast_match("/sdcard/im2char/N6.bmp")) == -1 )
				 			 an7 = predict(NTYPE, "/sdcard/im2char/N6.bmp",NULL);


		// if(an1.error !=-1 &&  an2.error !=-1 && an3.error !=-1 && an4.error !=-1&& an5.error !=-1 && an6.error !=-1 && an7.error !=-1)
			 sprintf(buf,"%d %d %d %d %d %d %d",an1.first,an2.first,an3.first,an4.first,an5.first,an6.first,an7.first);

	}
	else if(mode ==1){

		 TP an1,an2,an3,an4,an5,an6,an7;
				 if( (an1.first = fast_match("/sdcard/im2char/N1.bmp")) == -1 ){


					 an1 = predict(NTYPE, "/sdcard/im2char/N1.bmp",NULL);
				 }

				 if( (an2.first = fast_match("/sdcard/im2char/N2.bmp")) == -1 ){


				 			 an2 = predict(NTYPE, "/sdcard/im2char/N2.bmp",NULL);

				 }

				 an3 = predict(C2TYPE, "/sdcard/im2char/C2.bmp","/sdcard/im2char/C1.bmp");

				 if( (an4.first = fast_match("/sdcard/im2char/N3.bmp")) == -1 ){


						 			 an4 = predict(NTYPE, "/sdcard/im2char/N3.bmp",NULL);
				 }

				 if( (an5.first = fast_match("/sdcard/im2char/N4.bmp")) == -1 ){


						 			 an5 = predict(NTYPE, "/sdcard/im2char/N4.bmp",NULL);
				 }

				 if( (an6.first = fast_match("/sdcard/im2char/N5.bmp")) == -1 ){

						 			 an6 = predict(NTYPE, "/sdcard/im2char/N5.bmp",NULL);
				 }

				 if( (an7.first = fast_match("/sdcard/im2char/N6.bmp")) == -1 ){

						 			 an7 = predict(NTYPE, "/sdcard/im2char/N6.bmp",NULL);
				 }

		 //if(an1.error !=-1 &&  an2.error !=-1 && an3.error !=-1 && an4.error !=-1&& an5.error !=-1 && an6.error !=-1 && an7.error !=-1)
			 sprintf(buf,"%d %d %d %d %d %d %d %d",an1.first,an2.first,an3.first,an3.second,an4.first,an5.first,an6.first,an7.first);

	}

	java_update_str(buf);
#ifdef __DEBUG__
__TIME_WRITE__("OCR end!\n");
#endif
return 0;
}


