/*
 * match.h
 *
 *  Created on: 2019. 6. 3.
 *      Author: LEE SANG GU
 */

#ifndef MATCH_H_
#define MATCH_H_


typedef struct value {
    double percent;
    int cost;
}value;

typedef struct TP {
    int first;
    int second;
    int error;
}TP;

TP predict(int what, char something[], char something2[]);
TP ch_match(char something[]);
TP ch_match2(char something[], char something2[]);
int ch_match2_jar(char something[], int mor_type);
TP num_match(char something[]);
value template(char path1[], char path2[]);
value Ctemplate(char path1[], char path2[]);
value Ctemplate_mor(char path1[], char path2[]);
value Ctemplate_jar(char path1[], char path2[]);
int pow(int a, int b);


#define COLS   24   //숫자 픽셀 크기
#define ROWS   40

#define C_COLS   40   //한글자 픽셀 크기
#define C_ROWS   40

#define C2_COLS   40   //분리 모음 픽셀 크기
#define C2_ROWS   40

#define CJ_COLS   40   //분리 자음 픽셀 크기
#define CJ_ROWS   40


#define NTYPE 0    //숫자모드
#define CTYPE 1    //한글자모드
#define C2TYPE 2   //자음,모음 분리모드

#define gur 0  //거
#define gor 1  //고
#define gur 2  //구
#define nar 3  //나
#define nur 4  //너
#define dar 5  //다
#define dur 6  //더
#define rar 7  //라
#define rur 8  //러
#define mur 9  //머
#define bur 10 //버
#define our 11 //어
#define oor 12 //오
#define hur 13 //허
#define hor 14 //호

#define aa 0 //ㅏ
#define uu 1 //ㅓ
#define oo 2 //ㅗ
#define wo 3 //ㅜ
#define ae 4 //ㅐ

#define gi 0 //ㄱ
#define ni 1 //ㄴ
#define di 2 //ㄷ
#define ri 3 //ㄹ
#define mi 4 //ㅁ
#define bi 5 //ㅂ
#define si 6 //ㅅ
#define ei 7 //ㅇ
#define ji 8 //ㅈ
#define hi 9 //ㅎ




#define PATH_NUM_TEMPLATE "/sdcard/im2char/database/nums/%d/1 (%d).bmp"  //숫자 데이터베이스 경로
#define PATH_CHAR_TEMPLATE "/sdcard/im2char/database/chars/one/%d/1 (%d).bmp" // 한글자모드 데이터베이스 경로
#define PATH_MOR_TEMPLATE "/sdcard/im2char/database/chars/moum/%d/1 (%d).bmp" //분리모드 모음 데이터베이스경로
#define PATH_JAR_TEMPLATE "/sdcard/im2char/database/chars/jaum/%d/1 (%d).bmp" //분리모드 자음 데이터베이스 경로



#endif /* MATCH_H_ */
