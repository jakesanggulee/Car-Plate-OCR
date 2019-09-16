/*
 * debug.h
 *
 *  Created on: 2019. 5. 10.
 *      Author: LEE SANG GU
 */
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#ifndef DEBUG_H_
#define DEBUG_H_

#define __DEBUG__
#define DEBUG_PATH	"/sdcard/im2char/logcat.txt"
#define __DEBUG_WRITE__(STR,VAL)	do{	sprintf(debug_mseg,STR,VAL);			\
						write(debug_fd,debug_mseg,strlen(debug_mseg));	\
					}while(0)

#define __TIME_WRITE__(STR)			do{		time ( &rawtime );						\
										timeinfo = localtime ( &rawtime );		\
										sprintf (debug_mseg,"\nTime %s"STR, asctime (timeinfo) );	\
										write(debug_fd,debug_mseg,strlen(debug_mseg));				\
								}while(0)


#ifndef __MAIN__
extern time_t rawtime;
extern struct tm * timeinfo;
extern int debug_fd;
extern char debug_mseg[200];
#endif

#ifdef __MAIN__
int debug_fd;
char debug_mseg[150];
time_t rawtime;
struct tm * timeinfo;
#endif


#endif /* DEBUG_H_ */
