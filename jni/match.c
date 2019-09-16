#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "match.h"
#include "debug.h"


extern int TMP_NUM_VAL;
extern int TEMP_CHR_VAL;
extern int TEMP_MOR_VAL;
extern int TEMP_JAR_VAL;

TP predict(int what, char something[], char something2[])
{
	TP c;
	c.error = 1;
	if (what == NTYPE)  //숫자일때
	{
#ifdef __DEBUG__
		__DEBUG_WRITE__("N type matching %c\n", '!');
#endif
		c = num_match(something);  //숫자 템플릿 실행
		return c;
	}
	else if (what == CTYPE)  //1개 문자일때
	{
#ifdef __DEBUG__
		__DEBUG_WRITE__("C type matching %c\n", '!');
#endif
		c = ch_match(something); //문자템플릿 실행
		return c;
	}
	else if (what == C2TYPE)  //자음모음 나뉠때
	{
#ifdef __DEBUG__
		__DEBUG_WRITE__("C2 type matching %c\n", '!');
#endif
		c = ch_match2(something, something2); //문자템플릿2 실행
		return c;
	}
	else
	{
		c.error = -1;   //잘못된 모드 입력시
		return c;
	}

}

TP num_match(char something[])
{
	int i, j;
	double percent[10] = { 0 };
	int cost[10] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,100000, 100000 }; //추가
	char buffer[100];
	value result, output;
	for (i = 0; i < 10; i++)
	{
		if ((i == 0) || (i == 4) || (i == 6) || (i == 8) || (i == 9)) continue;  //04689 검색 안하게 추가
		cost[i] -= -100000; //추가
		for (j = 1; j < TMP_NUM_VAL + 1; j++)
		{
			sprintf(buffer, PATH_NUM_TEMPLATE, i, j);  //템플릿 경로
			result = template(something, buffer);  // template(입력 파일 경로, 템플릿경로)




			percent[i] += result.percent;
			cost[i] += result.cost;
		}
		percent[i] = percent[i] / TMP_NUM_VAL;
		cost[i] = cost[i] / TMP_NUM_VAL;
#ifdef __DEBUG__
		__DEBUG_WRITE__("%d average percent: ", i);
		__DEBUG_WRITE__("%lf, cost:", percent[i]);
		__DEBUG_WRITE__("%d \n", cost[i]);
#endif
		// printf("%d의 평균 percent:%lf, cost:%d\n", i, percent[i], cost[i]);
	}
	int max, min;
	int maxflag = 0;
	int minflag = 0;
	max = percent[0];
	min = cost[0];
	for (i = 0; i < 10; i++) {
		if (percent[i] > max) {
			max = percent[i];
			maxflag = i;
		}
		if (cost[i] < min) {
			min = cost[i];
			minflag = i;
		}
	}
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d best prob \n", maxflag);
	__DEBUG_WRITE__("%d lowest cost \n", minflag);
#endif
	// printf("%d가 확률높음 %d가 코스트낮음\n", maxflag, minflag);
	int end;
	int judge;
	if (minflag == maxflag)
		end = maxflag;
	else
	{
		judge = (percent[minflag] / (cost[minflag] + 1) > percent[maxflag] / (cost[maxflag] + 1)) ? minflag : maxflag;
		//printf("percent랑 cost가 매칭된게 다름%d, %d\n그래서 판별식 쓰면 얘일 확률이 높음: %d\n", maxflag, minflag, judge);
		end = judge;
		__DEBUG_WRITE__("percent and cost is different, so it use equation%c\n ", ".");
		__DEBUG_WRITE__("finally %d is number\n", judge);
	}

	TP fin;
	fin.first = end;
	fin.second = 1000;

	return fin;
}


TP ch_match(char something[])
{
	int i, j;
	double percent[15] = { 0 };
	int cost[15] = { 0 };
	char buffer[100];
	value result, output;
	for (i = 0; i < 15; i++)
	{
		for (j = 1; j < TEMP_CHR_VAL + 1; j++)
		{
			sprintf(buffer, PATH_CHAR_TEMPLATE, i, j);  //템플릿 경로

			result = Ctemplate(something, buffer);  // template(입력 파일 경로, 템플릿경로, 템플릿타입)
												   //printf("%d폴더 %d번째와 비교\n", i,j);
			percent[i] += result.percent;
			cost[i] += result.cost;
		}
		percent[i] = percent[i] / TEMP_CHR_VAL;
		cost[i] = cost[i] / TEMP_CHR_VAL;
		// printf("%d의 평균 percent:%lf, cost:%d\n", i, percent[i], cost[i]);
#ifdef __DEBUG__
		__DEBUG_WRITE__("%d average percent: ", i);
		__DEBUG_WRITE__("%lf, cost:", percent[i]);
		__DEBUG_WRITE__("%d \n", cost[i]);
#endif
	}
	int max, min;
	int maxflag = 0;
	int minflag = 0;
	max = percent[0];
	min = cost[0];
	for (i = 0; i < 15; i++) {
		if (percent[i] > max) {
			max = percent[i];
			maxflag = i;
		}
		if (cost[i] < min) {
			min = cost[i];
			minflag = i;
		}
	}
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d best prob \n", maxflag);
	__DEBUG_WRITE__("%d lowest cost \n", minflag);
#endif
	// printf("%d가 확률높음 %d가 코스트낮음\n", maxflag, minflag);
	int judge, end;
	if (minflag == maxflag)
	{
		// printf("한글:%d\n", maxflag);
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d is hangle\n", maxflag);
#endif
		end = maxflag;
	}
	else
	{
		judge = (percent[minflag] / (cost[minflag] + 1) > percent[maxflag] / (cost[maxflag] + 1)) ? minflag : maxflag;
		// printf("percent랑 cost가 매칭된게 다름%d, %d\n그래서 판별식 쓰면 얘일 확률이 높음: %d\n", maxflag, minflag, judge);
		end = judge;
		__DEBUG_WRITE__("percent and cost is different, so it use equation%c\n ", ".");
		__DEBUG_WRITE__("finally %d is hangle\n", judge);
	}
	TP fin;
	fin.first = end;
	fin.second = 1000;
	return fin;

}

TP ch_match2(char something[], char something2[])
{
	int i, j;
	double percent[5] = { 0 };
	int cost[5] = { 0 };
	char buffer[100];
	value result, output;
	for (i = 0; i < 5; i++)
	{
		for (j = 1; j < TEMP_MOR_VAL + 1; j++)
		{
			sprintf(buffer, PATH_MOR_TEMPLATE, i, j);  //모음 템플릿 경로

			result = Ctemplate_mor(something, buffer);  // template(모음 입력 파일 경로, 모음 템플릿경로)
		  //printf("%d폴더 %d번째와 비교\n", i,j);
			percent[i] += result.percent;
			cost[i] += result.cost;
		}
		percent[i] = percent[i] / TEMP_MOR_VAL;
		cost[i] = cost[i] / TEMP_MOR_VAL;
		//printf("%d의 평균 percent:%lf, cost:%d\n", i, percent[i], cost[i]);
#ifdef __DEBUG__
		__DEBUG_WRITE__("%d average percent: ", i);
		__DEBUG_WRITE__("%lf, cost:", percent[i]);
		__DEBUG_WRITE__("%d \n", cost[i]);
#endif
	}
	int max, min;
	int maxflag = 0;
	int minflag = 0;
	max = percent[0];
	min = cost[0];
	for (i = 0; i < 5; i++) {
		if (percent[i] > max) {
			max = percent[i];
			maxflag = i;
		}
		if (cost[i] < min) {
			min = cost[i];
			minflag = i;
		}
	}
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d best prob \n", maxflag);
	__DEBUG_WRITE__("%d lowest cost \n", minflag);
#endif
	//  printf("%d가 확률높음 %d가 코스트낮음\n", maxflag, minflag);
	char mor, end;
	int judge, jar;
	if (minflag == maxflag)
	{
		// printf("모음이녀석:%d\n", maxflag);
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d is moum\n", maxflag);
#endif
		mor = maxflag;
	}
	else
	{
		judge = (percent[minflag] / (cost[minflag] + 1) > percent[maxflag] / (cost[maxflag] + 1)) ? minflag : maxflag;
		// printf("percent랑 cost가 매칭된게 다름%d, %d\n그래서 판별식 쓰면 얘일 확률이 높음: %d\n", maxflag, minflag, judge);
		mor = judge;
#ifdef __DEBUG__
	__DEBUG_WRITE__("percent and cost is different, so it use equation%c\n ", ".");
	__DEBUG_WRITE__("finally %d is moum\n", judge);
#endif
	}
	switch (mor) {
	case aa: jar = ch_match2_jar(something2, aa); break;
	case uu: jar = ch_match2_jar(something2, uu); break;
	case oo: jar = ch_match2_jar(something2, oo); break;
	case wo: jar = ch_match2_jar(something2, wo); break;
	case ae: jar = 5; break;
	}
	TP fin;
	fin.first = mor;
	fin.second = jar;

	return fin;

}
int ch_match2_jar(char something[], int mor_type)
{
	int i, j;
	double percent[10] = { 0 };
	int cost[10] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,100000, 100000 };
	char buffer[100];
	value result, output;
	for (i = 0; i < 10; i++)
	{
		if (mor_type == aa) { if ((i == 1) || (i == 2) || (i == 3)) continue; }
		else if (mor_type == uu) { if ((i == 0) || (i == 1) || (i == 2) || (i == 3) || (i == 4) || (i == 5) || (i == 7) || (i == 9)) continue; }
		else if (mor_type == oo) { if ((i == 0) || (i == 7) || (i == 9)) continue; }
		else if (mor_type == wo) { if ((i == 0) || (i == 9)) continue; }

		cost[i] -= 100000;
		for (j = 1; j < TEMP_JAR_VAL + 1; j++)
		{

			sprintf(buffer, PATH_JAR_TEMPLATE, i, j);  //자음 템플릿 경로

			result = Ctemplate_jar(something, buffer);  // template(자음 입력 파일 경로, 모음 템플릿경로)
			//printf("%d폴더 %d번째와 비교\n", i, j);
			percent[i] += result.percent;
			cost[i] += result.cost;
		}
		percent[i] = percent[i] / TEMP_JAR_VAL;
		cost[i] = cost[i] / TEMP_JAR_VAL;
		//printf("%d의 평균 percent:%lf, cost:%d\n", i, percent[i], cost[i]);
#ifdef __DEBUG__
		__DEBUG_WRITE__("%d average percent: ", i);
		__DEBUG_WRITE__("%lf, cost:", percent[i]);
		__DEBUG_WRITE__("%d \n", cost[i]);
#endif
	}

	int max, min;
	int maxflag = 0;
	int minflag = 0;
	max = percent[0];
	min = cost[0];
	for (i = 0; i < 10; i++) {
		if (percent[i] > max) {
			max = percent[i];
			maxflag = i;
		}
		if (cost[i] < min) {
			min = cost[i];
			minflag = i;
		}
	}

	int end;
	int judge;
	if (minflag == maxflag)
	{
		//printf("자음은이녀석:%d\n", maxflag);
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d is jaum\n", maxflag);
#endif
		end = maxflag;
	}
	else
	{
		judge = (percent[minflag] / (cost[minflag] + 10000) > percent[maxflag] / (cost[maxflag] + 10000)) ? minflag : maxflag;
		//printf("자음이 percent랑 cost가 매칭된게 다름%d, %d\n그래서 판별식 쓰면 얘일 확률이 높음: %d\n", maxflag, minflag, judge);
		end = judge;
#ifdef __DEBUG__
	__DEBUG_WRITE__("%d is jaum\n", end);
#endif
	}
	return end;
}

value template(char path1[], char path2[])
{

	int i, j;
	BITMAP* bmp1 = read_bmp(path1);
	BITMAP* bmp2 = read_bmp(path2);
	unsigned char   r1, r2, g1, g2, b1, b2;
	unsigned int x, y;
	unsigned int width_1 = width_bmp(bmp1);
	unsigned int height_1 = height_bmp(bmp1);
	unsigned int width_2 = width_bmp(bmp2);
	unsigned int height_2 = height_bmp(bmp2);
	unsigned char img_1[ROWS][COLS];
	unsigned char img_2[ROWS][COLS];





	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			//BMP_GetPixelIndex(bmp1, x, y, &(img_1[y][x]));
			//BMP_GetPixelIndex(bmp2, x, y, &(img_2[y][x]));

			get_rgb(bmp1, x, y, &r1, &g1, &b1);
			get_rgb(bmp2, x, y, &r2, &g2, &b2);
			if (0.2989*r1 + 0.5870*g1 + 0.1140*b1 < 128)
			img_1[y][x] = 255;
			else
			img_1[y][x] = 0;
			if (0.2989*r2 + 0.5870*g2 + 0.1140*b2 < 128)
			img_2[y][x] = 255;
			else
			img_2[y][x] = 0;

		}
	}

	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			if (img_1[y][x] > 128)
				img_1[y][x] = 255;
			else
				img_1[y][x] = 0;
			if (img_2[y][x] > 128)
				img_2[y][x] = 255;
			else
				img_2[y][x] = 0;
		}
	}

	double per = 0;

	int perx_1[ROWS] = { 0, };
	int pery_1[COLS] = { 0, };

	int perx_2[ROWS] = { 0, };
	int pery_2[COLS] = { 0, };


	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if (img_1[i][j] == img_2[i][j])
				per += 1;
			if (img_1[i][j] == 255)
				perx_1[i] += 1;
			if (img_2[i][j] == 255)
				perx_2[i] += 1;
		}
	}
	for (j = 0; j < COLS; j++)
	{
		for (i = 0; i < ROWS; i++)
		{
			if (img_1[i][j] == 255)
				pery_1[j] += 1;
			if (img_2[i][j] == 255)
				pery_2[j] += 1;

		}
	}


	int costx = 0;
	int costy = 0;
	int cost = 0;
	for (i = 0; i < ROWS; i++)
	{
		costx += pow((perx_1[i] - perx_2[i]), 2);
	}

	for (j = 0; j < COLS; j++)
	{
		costy += pow((perx_1[j] - perx_2[j]), 2);
	}

	cost = costx + costy;
	double reper = (per /= ROWS * COLS) * 100;
	//printf("\nxor 일치율:%lf%%\n", reper);
	// printf("가로세로 cost:%d\n", cost);

	value p;
	p.percent = reper;
	p.cost = cost;




	free_bmp(bmp1); //상구추가
	free_bmp(bmp2); //상구추가
	return p;

}
value Ctemplate(char path1[], char path2[])
{

	int i, j;
	BITMAP* bmp1 = read_bmp(path1);
	BITMAP* bmp2 = read_bmp(path2);
	unsigned char   r1, r2, g1, g2, b1, b2;
	unsigned int x, y;
	unsigned int width_1 = width_bmp(bmp1);
	unsigned int height_1 = height_bmp(bmp1);
	unsigned int width_2 = width_bmp(bmp2);
	unsigned int height_2 = height_bmp(bmp2);
	unsigned char img_1[C_ROWS][C_COLS];
	unsigned char img_2[C_ROWS][C_COLS];




	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			//BMP_GetPixelIndex(bmp1, x, y, &(img_1[y][x]));
			//BMP_GetPixelIndex(bmp2, x, y, &(img_2[y][x]));

						get_rgb(bmp1, x, y, &r1, &g1, &b1);
						get_rgb(bmp2, x, y, &r2, &g2, &b2);
						if (0.2989*r1 + 0.5870*g1 + 0.1140*b1 > 128)
						img_1[y][x] = 255;
						else
						img_1[y][x] = 0;
						if (0.2989*r2 + 0.5870*g2 + 0.1140*b2 > 128)
						img_2[y][x] = 255;
						else
						img_2[y][x] = 0;


		}
	}

	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			if (img_1[y][x] > 128)
				img_1[y][x] = 255;
			else
				img_1[y][x] = 0;
			if (img_2[y][x] > 128)
				img_2[y][x] = 255;
			else
				img_2[y][x] = 0;
		}
	}

	double per = 0;

	int perx_1[C_ROWS] = { 0, };
	int pery_1[C_COLS] = { 0, };

	int perx_2[C_ROWS] = { 0, };
	int pery_2[C_COLS] = { 0, };


	for (i = 0; i < C_ROWS; i++)
	{
		for (j = 0; j < C_COLS; j++)
		{
			if (img_1[i][j] == img_2[i][j])
				per += 1;
			if (img_1[i][j] == 255)
				perx_1[i] += 1;
			if (img_2[i][j] == 255)
				perx_2[i] += 1;
		}
	}
	for (j = 0; j < C_COLS; j++)
	{
		for (i = 0; i < C_ROWS; i++)
		{
			if (img_1[i][j] == 255)
				pery_1[j] += 1;
			if (img_2[i][j] == 255)
				pery_2[j] += 1;

		}
	}


	int costx = 0;
	int costy = 0;
	int cost = 0;
	for (i = 0; i < C_ROWS; i++)
	{
		costx += pow((perx_1[i] - perx_2[i]), 2);
	}

	for (j = 0; j < C_COLS; j++)
	{
		costy += pow((perx_1[j] - perx_2[j]), 2);
	}

	cost = costx + costy;
	double reper = (per /= C_ROWS * C_COLS) * 100;
	//printf("\nxor 일치율:%lf%%\n", reper);
	// printf("가로세로 cost:%d\n", cost);

	value p;
	p.percent = reper;
	p.cost = cost;


	free_bmp(bmp1); //상구추가
	free_bmp(bmp2); //상구추가

	return p;

}
value Ctemplate_mor(char path1[], char path2[])
{

	int i, j;
	BITMAP* bmp1 = read_bmp(path1);
	BITMAP* bmp2 = read_bmp(path2);
	unsigned char   r1, r2, g1, g2, b1, b2;
	unsigned int x, y;
	unsigned int width_1 = width_bmp(bmp1);
	unsigned int height_1 = height_bmp(bmp1);
	unsigned int width_2 = width_bmp(bmp2);
	unsigned int height_2 = height_bmp(bmp2);



	unsigned char img_1[C2_ROWS][C2_COLS];
	unsigned char img_2[C2_ROWS][C2_COLS];

	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			//BMP_GetPixelIndex(bmp1, x, y, &(img_1[y][x]));
			//BMP_GetPixelIndex(bmp2, x, y, &(img_2[y][x]));

						get_rgb(bmp1, x, y, &r1, &g1, &b1);
						get_rgb(bmp2, x, y, &r2, &g2, &b2);
						if (0.2989*r1 + 0.5870*g1 + 0.1140*b1 < 128)
						img_1[y][x] = 255;
						else
						img_1[y][x] = 0;
						if (0.2989*r2 + 0.5870*g2 + 0.1140*b2 < 128)
						img_2[y][x] = 255;
						else
						img_2[y][x] = 0;


		}
	}

	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			if (img_1[y][x] > 128)
				img_1[y][x] = 255;
			else
				img_1[y][x] = 0;
			if (img_2[y][x] > 128)
				img_2[y][x] = 255;
			else
				img_2[y][x] = 0;
		}
	}

	double per = 0;

	int perx_1[C2_ROWS] = { 0, };
	int pery_1[C2_COLS] = { 0, };

	int perx_2[C2_ROWS] = { 0, };
	int pery_2[C2_COLS] = { 0, };


	for (i = 0; i < C2_ROWS; i++)
	{
		for (j = 0; j < C2_COLS; j++)
		{
			if (img_1[i][j] == img_2[i][j])
				per += 1;
			if (img_1[i][j] == 255)
				perx_1[i] += 1;
			if (img_2[i][j] == 255)
				perx_2[i] += 1;
		}
	}
	for (j = 0; j < C2_COLS; j++)
	{
		for (i = 0; i < C2_ROWS; i++)
		{
			if (img_1[i][j] == 255)
				pery_1[j] += 1;
			if (img_2[i][j] == 255)
				pery_2[j] += 1;

		}
	}


	int costx = 0;
	int costy = 0;
	int cost = 0;
	for (i = 0; i < C2_ROWS; i++)
	{
		costx += pow((perx_1[i] - perx_2[i]), 2);
	}

	for (j = 0; j < C2_COLS; j++)
	{
		costy += pow((perx_1[j] - perx_2[j]), 2);
	}

	cost = costx + costy;
	double reper = (per /= C2_ROWS * C2_COLS) * 100;
	//printf("\nxor 일치율:%lf%%\n", reper);
	// printf("가로세로 cost:%d\n", cost);

	value p;
	p.percent = reper;
	p.cost = cost;



	free_bmp(bmp1); //상구추가
	free_bmp(bmp2); //상구추가

	return p;

}
value Ctemplate_jar(char path1[], char path2[])
{
	int i, j;
	BITMAP* bmp1 = read_bmp(path1);
	BITMAP* bmp2 = read_bmp(path2);
	unsigned char   r1, r2, g1, g2, b1, b2;
	unsigned int x, y;
	unsigned int width_1 = width_bmp(bmp1);
	unsigned int height_1 = height_bmp(bmp1);
	unsigned int width_2 = width_bmp(bmp2);
	unsigned int height_2 = height_bmp(bmp2);
	unsigned char img_1[C2_ROWS][CJ_COLS];
	unsigned char img_2[C2_ROWS][CJ_COLS];



	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {

						get_rgb(bmp1, x, y, &r1, &g1, &b1);
						get_rgb(bmp2, x, y, &r2, &g2, &b2);
						if (0.2989*r1 + 0.5870*g1 + 0.1140*b1 < 128)
							img_1[y][x] = 255;
						else
							img_1[y][x] = 0;
						if (0.2989*r2 + 0.5870*g2 + 0.1140*b2 < 128)
							img_2[y][x] = 255;
						else
							img_2[y][x] = 0;


		}
	}

	for (x = 0; x < width_1; x++) {
		for (y = 0; y < height_1; y++) {
			if (img_1[y][x] > 128)
				img_1[y][x] = 255;
			else
				img_1[y][x] = 0;
			if (img_2[y][x] > 128)
				img_2[y][x] = 255;
			else
				img_2[y][x] = 0;
		}
	}

	double per = 0;

	int perx_1[CJ_ROWS] = { 0, };
	int pery_1[CJ_COLS] = { 0, };

	int perx_2[CJ_ROWS] = { 0, };
	int pery_2[CJ_COLS] = { 0, };


	for (i = 0; i < CJ_ROWS; i++)
	{
		for (j = 0; j < CJ_COLS; j++)
		{
			if (img_1[i][j] == img_2[i][j])
				per += 1;
			if (img_1[i][j] == 255)
				perx_1[i] += 1;
			if (img_2[i][j] == 255)
				perx_2[i] += 1;
		}
	}
	for (j = 0; j < CJ_COLS; j++)
	{
		for (i = 0; i < CJ_ROWS; i++)
		{
			if (img_1[i][j] == 255)
				pery_1[j] += 1;
			if (img_2[i][j] == 255)
				pery_2[j] += 1;

		}
	}


	int costx = 0;
	int costy = 0;
	int cost = 0;
	for (i = 0; i < CJ_ROWS; i++)
	{
		costx += pow((perx_1[i] - perx_2[i]), 2);
	}

	for (j = 0; j < CJ_COLS; j++)
	{
		costy += pow((perx_1[j] - perx_2[j]), 2);
	}

	cost = costx + costy;
	double reper = (per /= CJ_ROWS * CJ_COLS) * 100;
	//printf("\nxor 일치율:%lf%%\n", reper);
	// printf("가로세로 cost:%d\n", cost);

	value p;
	p.percent = reper;
	p.cost = cost;


	free_bmp(bmp1); //상구추가
	free_bmp(bmp2); //상구추가

	return p;
}

int pow(int a, int b)
{
	int i, pow = 1;
	for (i = 0; i < b; i++)
		pow *= a;
	return pow;

}
