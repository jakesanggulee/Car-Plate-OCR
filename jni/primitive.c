#define COLS	652
#define ROWS	488
#define MAX_LABEL	5000
#define BI_TH		100
#define CHAR_MAX_WIDTH	(COLS/7)
#define CHAR_MAX_HEIGHT	(ROWS*0.8)
#define CHAR_LEN	20
#define CHAR_X_OFFSET	2
#define CHAR_Y_OFFSET	2
#define CHAR_Y_DIFF_TOL	0
#define CHAR_MAX_SEARCH	15
#define IMG_TH		0.005
#define IMG_TH_DELTA	0.0001
#define IMG_MIN_TH	0.0001

#define CHAR_Y_MIN	(ROWS/25)
#define CHAR_X_MIN   (COLS/40)
#define THRESH_HOLD_TOO_LOW	-2
#define THRESH_HOLD_TOO_HIGH	-3

#define SKEWRATE	23
#define SKWTOL		10

#define PATH	"/sdcard/im2char/"
#define BINARIZED_FILE_NAME	"log/step1.bmp"
#define LABELED_FILE_NAME   "log/step3.bmp"
#define FIRST_PRED			"log/step4.bmp"
#define SECOND_PRED			"log/step5.bmp"
#define OUTPUT_PREFIX	"O"

//#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bitmap.h"



void java_binarized_update_screen(void);


struct _tobj {
	unsigned int pixels;
	unsigned int l, r, u, d;
	unsigned int w, h;
	unsigned int label;

};

struct img_status {

	unsigned int nobjs;
	struct _tobj obj[MAX_LABEL];
};

int compare(const void* a, const void* b) {

	struct _tobj* aa = (struct _tobj*) a;
	struct _tobj* bb = (struct _tobj*) b;

	if (aa->l < bb->l)
		return -1;

	if (aa->l > bb->l)
		return 1;

	return 0;


}


unsigned int img[ROWS][COLS];

static int loc(int search[], int x)
{
	int r = x;
	while (search[r] != r)
		r = search[r];
	return r;
}

int imgseg(char path[], double thresh, int bi_thresh) {

	struct img_status is;
	BITMAP*    bmp;
	unsigned int    width, height;
	unsigned int    x, y;
	is.nobjs =0;


#ifdef __DEBUG__
	__TIME_WRITE__("Image Segfunction Called!");
	__DEBUG_WRITE__("Area Thresh %lf, Bi Thresh\n",thresh);
	__DEBUG_WRITE__(" %d\n",bi_thresh);


#endif




	// 0.2989 * R + 0.5870 * G + 0.1140 * B
	unsigned char   rr, gg, bb;
	bmp = read_bmp(path);
	//////////////////////////////////////// Ãß°¡///////////////////////////
	if (bmp == NULL) {
#ifdef __DEBUG__
		__TIME_WRITE__("Original File Fetch Failed!");
#endif

		return -1;
	}
#ifdef __DEBUG__
	__TIME_WRITE__("File Fetch Success! ");
#endif

	//////////////////////////////////////////////////////////////////////

	width = width_bmp(bmp);
	height = height_bmp(bmp);

#ifdef __DEBUG__
	__DEBUG_WRITE__("\nBMP Width %d", width);
	__DEBUG_WRITE__(" BMP Height %d", height);
#endif



	int i, r, c;

	for (x = 0; x < width; ++x) {
		for (y = 0; y < height; ++y) {
			get_rgb(bmp, x, y, &rr, &gg, &bb);
			if (0.2989*rr + 0.5870*gg + 0.1140*bb < bi_thresh)
		        img[y][x] = 1;
		    else
		        img[y][x] = 0;
		}
	}
	/*
	int thre = 0;
	double sum = 0;  //½Âº¸
	double avg = 0; //½Âº¸
	double gray = 0;   //½Âº¸
	double all_sum = 0; //½Âº¸
	double tmp_T = 0;  //½Âº¸
	double low_sum = 0;
	double high_sum = 0;
	double low_cnt = 0;
	double high_cnt = 0;
	double tar_his[256] = { 0 }; //½Âº¸
	double out_his[256] = { 0 };  //½Âº¸


	for (x = 0; x < width; ++x) {
		for (y = 0; y < height; ++y) {
			//BMP_GetPixelIndex( bmp, x, y, &(img[y][x]) );
			get_rgb(bmp, x, y, &rr, &gg, &bb);
			gray = (rr + gg + bb) / 3;  //½Âº¸
			all_sum = all_sum + gray;   //½Âº¸
			tar_his[(int)gray] = tar_his[(int)gray] + 1; //½Âº¸
			//if (0.2989*rr + 0.5870*gg + 0.1140*bb < BI_TH)
		 //       img[y][x] = 1;
		 //   else
		 //       img[y][x] = 0;
		}
	}

	tmp_T = all_sum / (x * y);  //½Âº¸
	for (i = 0; i < 256; i++)
	{
		sum = sum + tar_his[i];
		out_his[i] = sum;
	} ////////////////////½Âº¸
	int k = 0;
	do
	{
		avg = tmp_T;
		for (i = 0; i < 256; i++)
		{
			if (i <= tmp_T)
			{
				low_cnt = low_cnt + tar_his[i];
				low_sum = low_sum + tar_his[i] * i;
			}
			else
			{
				high_cnt = high_cnt + tar_his[i];
				high_sum = high_sum + tar_his[i] * i;
			}
		}
		tmp_T = ((low_sum / (double)low_cnt) + (high_sum / (double)high_cnt)) / 2.0;
		k++;
	} while ((tmp_T != avg) && (k <= 10000));
	thre = (int)tmp_T;/////////////////////////////////½Âº¸
	for (x = 0; x < width; ++x) {
		for (y = 0; y < height; ++y) {
			//BMP_GetPixelIndex( bmp, x, y, &(img[y][x]) );
			get_rgb(bmp, x, y, &rr, &gg, &bb);
			gray = (rr + gg + bb) / 3;  //½Âº¸

			if (gray < thre + bi_thresh)
				img[y][x] = 1;
			else
				img[y][x] = 0;
		}
	}






#ifdef __DEBUG__
	__DEBUG_WRITE__("\nTh %d ", thre);
#endif

*/
	free_bmp(bmp);
	bmp = create_bmp(width, height, 8);

	for (x = 0; x < 256; x++)
		set_pal(bmp, x, x, x, x);

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			if (img[y][x] == 1)
				set_idx(bmp, x, y, 255);
			else
				set_idx(bmp, x, y, 0);
		}
	}
#ifdef __DEBUG__
	__TIME_WRITE__("Binarized Completed!");
#endif
	write_bmp(bmp, PATH BINARIZED_FILE_NAME);
	java_binarized_update_screen();
#ifdef __DEBUG__
	__TIME_WRITE__("Saving File To: "BINARIZED_FILE_NAME);

#endif

	//int th = ROWS * COLS*IMG_TH;
	int nth_label = 0;
	int lset[MAX_LABEL] = { 0, };
	int nobj = 0;
	int pred_idx[CHAR_LEN];
	char buf[100];
	int row, col;
	i = 0;
	r = 0;
	c = 0;

	for (row = 0; row < ROWS; row++) {
		for (col = 0; col < COLS; col++) {
			if (img[row][col] != 0) { //when cell is on
				int lu, mu, ru, l;
				if (col == 0)
					l = 0;
				else
					l = loc(lset, (int)img[row][col - 1]);

				if (row == 0)
					mu = 0;
				else
					mu = loc(lset, (int)img[row - 1][col]);

				if ((row == 0) || (col == 0))
					lu = 0;
				else
					lu = loc(lset, (int)img[row - 1][col - 1]);

				if ((row == 0) || (col == COLS - 1))
					ru = 0;
				else
					ru = loc(lset, (int)img[row - 1][col + 1]);

				if (l || mu || lu || ru) {  //  at least one cell is connected

					int temp_label = l;
					if (l)
						temp_label = l;
					else if (mu)
						temp_label = mu;
					else if (lu)
						temp_label = lu;
					else if (ru)
						temp_label = ru;

					img[row][col] = temp_label;

					if (l  && l != temp_label)
						lset[l] = temp_label;
					if (mu && mu != temp_label)
						lset[mu] = temp_label;
					if (lu && lu != temp_label)
						lset[lu] = temp_label;
					if (ru && ru != temp_label)
						lset[ru] = temp_label;
				} //if l mu lu ru

				else {
					nth_label++;
					img[row][col] = lset[nth_label] = nth_label;
				}

			} //if A is not zero
		} //end for(rows)
	} //end for(cols)

	for (i = 0; i <= nth_label; i++)
		lset[i] = loc(lset, i);

	for (r = 0; r < ROWS; r++)
		for (c = 0; c < COLS; c++)
			img[r][c] = lset[(int)img[r][c]];


	// count up the objects in the image
	for (i = 0; i <= nth_label; i++)
		lset[i] = 0;

	for (r = 0; r < ROWS; r++) {
		for (c = 0; c < COLS; c++) {
			lset[(int)img[r][c]]++;
		}
	}
	// number the objects from 1 through n objects

	nobj = 0;
	lset[0] = 0;
	int cnt[MAX_LABEL];

	memcpy(cnt, lset, MAX_LABEL * sizeof(int));

	for (i = 1; i <= nth_label; i++) {
		if (lset[i] > thresh) {
			is.nobjs++;
			is.obj[is.nobjs - 1].pixels = lset[i];
			lset[i] = ++nobj;
		}
	}

	for (i = 0; i < is.nobjs; i++) {
		is.obj[i].l = COLS - 1;
		is.obj[i].r = 0;
		is.obj[i].u = ROWS - 1;
		is.obj[i].d = 0;
		is.obj[i].label = i + 1;

	}
	// run through the look-up table again
	for (r = 0; r < ROWS; r++)
		for (c = 0; c < COLS; c++) {
			unsigned int idx = img[r][c];
			unsigned int label = lset[idx];

			if (cnt[idx] > thresh) {
				img[r][c] = lset[idx];

				if (is.obj[label - 1].l > c)
					is.obj[label - 1].l = c;
				if (is.obj[label - 1].r < c)
					is.obj[label - 1].r = c;
				if (is.obj[label - 1].u > r)
					is.obj[label - 1].u = r;
				if (is.obj[label - 1].d < r)
					is.obj[label - 1].d = r;
			}
			else
				img[r][c] = 0;
		}






	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			if(img[y][x]*10 <= 255)
				set_idx(bmp, x, y, img[y][x]*10 );
			else
				set_idx(bmp, x, y, 255);
		}
	}
	write_bmp(bmp, PATH "log/step2.bmp");
	java_labeled_update_screen();


	for (i = 0; i < is.nobjs; i++) {
		is.obj[i].w = is.obj[i].r - is.obj[i].l;
		is.obj[i].h = is.obj[i].d - is.obj[i].u;

	}


	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
				set_idx(bmp, x, y, 0);
		}
	}

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			if (img[y][x] > 0)
				set_idx(bmp, x, y, 255);
			else
				set_idx(bmp, x, y, 0);
		}
	}

	write_bmp(bmp, PATH LABELED_FILE_NAME);


	// average char_height det

	if (is.nobjs < 7) {
#ifdef __DEBUG__
		__DEBUG_WRITE__("[ERROR %d]\n", 1);
		__DEBUG_WRITE__("[Return]Detected Objs  %d\n", is.nobjs);
#endif
		free_bmp(bmp);
		return THRESH_HOLD_TOO_HIGH;
	}


	int max_idx = 0;
	int max_count = 0;
	int flg = 0;

	//	while (th > IMG_MIN_TH && flg != 1) {

	//		max_idx = 0;
	//		max_count = 0;










	for (r = 0; r < CHAR_MAX_SEARCH; r++) {  // change h ++
#ifdef __DEBUG__
		__DEBUG_WRITE__("Y tol is : %d\n", r);
#endif
		for (i = 0; i < is.nobjs; i++) {
			int test_pt = is.obj[i].h;
			int count = 0;
			////
			if ((test_pt < CHAR_Y_MIN) || (test_pt - CHAR_Y_DIFF_TOL - r < 0))
				continue;
			////
			for (c = 0; c < is.nobjs; c++) {
				if ((test_pt <= CHAR_Y_DIFF_TOL + r + is.obj[c].h) && (is.obj[c].h - CHAR_Y_DIFF_TOL - r <= test_pt)) {
					count++;
				}
			}
			if (max_count < count) {
				max_idx = i;
				max_count = count;
			}
		}




#ifdef __DEBUG__
		__DEBUG_WRITE__("Max Count : %d\n", max_count);
#endif
		//return optimal ref object probably number object
		if (max_count < 6)
			continue;

		if (max_count >= 6) {
			nobj = 0;

			for (i = 0; i < is.nobjs; i++) {
				if ((is.obj[i].h <= CHAR_Y_DIFF_TOL + r + is.obj[max_idx].h) && (is.obj[max_idx].h - CHAR_Y_DIFF_TOL - r <= is.obj[i].h)) {
					if (nobj < CHAR_LEN){
						pred_idx[nobj++] = i;
					}
					else { //³Ê¹« ¸¹Àº°æ¿ì
#ifdef __DEBUG__
						__DEBUG_WRITE__("[ERROR 2]\n", max_count);
#endif
						free_bmp(bmp);
						return THRESH_HOLD_TOO_LOW;
					}
				}

			}

#ifdef __DEBUG__
			__DEBUG_WRITE__("First Selected Objects: %d\n", max_count);
#endif


			for (x = 0; x < width; x++)
				for (y = 0; y < height; y++)
					set_idx(bmp, x, y, 0);

			for (i = 0; i < nobj; i++) {
				for (x = 0; x < width; x++) {
					for (y = 0; y < height; y++) {
						int tmp = img[y][x];
						for (c = 0; c < nobj; c++) {
							if (tmp == is.obj[pred_idx[c]].label) {
								set_idx(bmp, x, y, 255);
								break;
							}

						}


					}
				}
			}

			write_bmp(bmp, PATH FIRST_PRED);


			/*
			ÇÑ¹ø´õ ÇÊÅÍ¸µ
			*/




			int q;
			int u_max_idx;
			int u_max_count;
			int u_count;


			for (q = 0; q < SKEWRATE; q++) {

				u_max_count = 0;
				u_max_idx = 0;

				for (i = 0; i < nobj; i++) { //pred idx ³»¿¡¼­ ¼­Ä¡

					int u_test_pt = is.obj[pred_idx[i]].u; //Å×½ºÆ® Æ÷ÀÎÆ®

					u_count = 0;

					if (u_test_pt == 0 ||  is.obj[pred_idx[i]].h < CHAR_Y_MIN || is.obj[pred_idx[i]].w < CHAR_X_MIN)
						continue;
					////
					for (c = 0; c < nobj; c++) {
						if ((u_test_pt <=   q + is.obj[pred_idx[c]].u) && (is.obj[pred_idx[c]].u  - q <= u_test_pt)) {
							u_count++;
						}
					}
					if (u_max_count < u_count) {
						u_max_idx = i;
						u_max_count = u_count;
					}
				}

				if (u_max_count >= 6)
					break;

			}

			if (u_max_count < 6) {
				free_bmp(bmp);
				return THRESH_HOLD_TOO_LOW;
			}

			int u_nobj = 0;
			int spred_idx[CHAR_LEN];

			for (i = 0; i < nobj; i++) {
				if ((is.obj[pred_idx[i]].u <=  q + is.obj[pred_idx[u_max_idx]].u) && (is.obj[pred_idx[u_max_idx]].u - q <= is.obj[pred_idx[i]].u)) {
					if (u_nobj < 8) {
						spred_idx[u_nobj++] = pred_idx[i];
					}
					else { //³Ê¹« ¸¹Àº°æ¿ì
						free_bmp(bmp);
						return THRESH_HOLD_TOO_LOW;
					}
				}

			}

			nobj = u_nobj;
			memcpy(pred_idx, spred_idx, sizeof(int)*CHAR_LEN);



			int pix =0;
			unsigned int left_y_up, right_y_up, left_y_down, right_y_down;
			unsigned int first_x = width, first_y = height, last_x = 0, last_y = 0;
			for (i = 0; i < nobj; i++) {
						if (is.obj[pred_idx[i]].l != 0 && first_x > is.obj[pred_idx[i]].l){
							first_x = is.obj[pred_idx[i]].l;
							left_y_up = is.obj[pred_idx[i]].u;
							left_y_down = is.obj[pred_idx[i]].d;
						}
						if (is.obj[pred_idx[i]].u != 0 && first_y > is.obj[pred_idx[i]].u){
							first_y = is.obj[pred_idx[i]].u;
						}
						if ((is.obj[pred_idx[i]].r != COLS - 1) && last_x < is.obj[pred_idx[i]].r){
							last_x = is.obj[pred_idx[i]].r;
							right_y_up = is.obj[pred_idx[i]].u;
							right_y_down = is.obj[pred_idx[i]].d;
						}
						if ((is.obj[pred_idx[i]].d != ROWS - 1) && last_y < is.obj[pred_idx[i]].d){
							last_y = is.obj[pred_idx[i]].d;
						}
						if(pix < is.obj[pred_idx[i]].pixels)
							pix = is.obj[pred_idx[i]].pixels;
					}

			double skw = (double)(left_y_up - right_y_up)/(last_x - first_x );

#ifdef __DEBUG__
			__DEBUG_WRITE__("\nFirst x %d ", first_x);
			__DEBUG_WRITE__("First y %d ", first_y);
			__DEBUG_WRITE__("Last x %d", last_x);
			__DEBUG_WRITE__("\nLast y %d", last_y);
			__DEBUG_WRITE__("\nLeft_y_up %d, Left_y_down", left_y_up);
			__DEBUG_WRITE__("%d ", left_y_down);
			__DEBUG_WRITE__("\nRight_y_up %d, Right_y_down", right_y_up);
			__DEBUG_WRITE__("%d \n", right_y_down);
			__DEBUG_WRITE__("%SKEW Rate %lf \n", (double)(left_y_up - right_y_up)/(last_x - first_x ));

#endif


			for (x = 0; x < width; x++) {
				for (y = 0; y < height; y++) {
					if (x == first_x)
						set_idx(bmp, x, y, 255);
					if( y == first_y)
						set_idx(bmp, x, y, 255);
					if( x == last_x)
						set_idx(bmp, x, y, 255);
					if (y == last_y)
						set_idx(bmp, x, y, 255);
		}
					}

			write_bmp(bmp, PATH"log/Det_Square.bmp");
			java_deq_sqr_update_screen();


			qsort(is.obj, is.nobjs, sizeof(is.obj[0]), compare); // left char first search
			nobj = 0;
			int det=0;
			for (i = 0; i < is.nobjs; i++) {
				if ((is.obj[i].r <= last_x) && (first_x <= is.obj[i].l) && (is.obj[i].d <= last_y) && (first_y <= is.obj[i].u) && is.obj[i].pixels > pix/5) {


#ifdef __DEBUG__

					__DEBUG_WRITE__("\nPixels %d\n", is.obj[i].pixels);
#endif

						pred_idx[nobj++] = i;
						det++;
#ifdef __DEBUG__

					for (x = 0; x < width; x++) {
							for (y = 0; y < height; y++) {
								if(img[y][x]==is.obj[i].label)
									set_idx(bmp, x, y, 255);
								else
									set_idx(bmp, x, y, 0);
							}
						}


					sprintf(buf, PATH "log/PRED%d.bmp", det);
					write_bmp(bmp, buf);

#endif

				}

				if (nobj > 8) {
#ifdef __DEBUG__
					__DEBUG_WRITE__("[ERROR 3] %d \n", nobj);
#endif
					free_bmp(bmp);
					return THRESH_HOLD_TOO_LOW;

				}
			}










#ifdef __DEBUG__
			__DEBUG_WRITE__("\Second Selected Objects: %d\n", max_count);
			for (x = 0; x < width; x++)
				for (y = 0; y < height; y++)
					set_idx(bmp, x, y, 0);

			for (i = 0; i < nobj; i++) {
				for (x = 0; x < width; x++) {
					for (y = 0; y < height; y++) {
						int tmp = img[y][x];
						for (c = 0; c < nobj; c++) {
							if (tmp == is.obj[pred_idx[c]].label) {
								set_idx(bmp, x, y, 255);
								break;
							}

						}
					}
				}
			}

			write_bmp(bmp, PATH SECOND_PRED);

#endif

#ifdef __DEBUG__
			__DEBUG_WRITE__("Detected Number+korean OBJS %d\n", nobj);
#endif
			//uncertain
			if ((nobj == 8) || (nobj == 7)) {
				flg = 1;
				break;
			}
		} //if maxcount > 6 < 8

#ifdef __DEBUG__
		__DEBUG_WRITE__("OJBS %d\n", nobj);
#endif

	} //max search



	if (flg == 0) {
#ifdef __DEBUG__
		__TIME_WRITE__("Number Plate Detection Failed!");
		__DEBUG_WRITE__("\nDetected Number OBJS %d", nobj);
#endif

		free_bmp(bmp);
		return -1;
	}

#ifdef __DEBUG__
	__TIME_WRITE__("Number Plate Detection Failed!");
	__DEBUG_WRITE__("\nDetected Number OBJS %d", nobj);
#endif


	// after removing unnecessary objs
	free_bmp(bmp);


if( nobj == 8){
#ifdef __DEBUG__
		__DEBUG_WRITE__("\nChecking for swap %d", 1);
		__DEBUG_WRITE__("\n is.obj[2].u %d",is.obj[pred_idx[2]].u  );
		__DEBUG_WRITE__("\n is.obj[3].d %d",is.obj[pred_idx[3]].d  );

#endif
if(is.obj[pred_idx[2]].u > is.obj[pred_idx[3]].d){
#ifdef __DEBUG__
		__DEBUG_WRITE__("\n swaping %d", 1);
#endif
	struct _tobj temp;
	temp = is.obj[pred_idx[3]];
	is.obj[pred_idx[3]] = is.obj[pred_idx[2]];
	is.obj[pred_idx[2]] = temp;

}


}



	for (i = 0; i < nobj; i++) {
#ifdef __DEBUG__
		__DEBUG_WRITE__("\nWriting Detected OBJS to file %d", i + 1);
#endif

		width = is.obj[pred_idx[i]].w + 1;
		height = is.obj[pred_idx[i]].h + 1;
		int xsp = is.obj[pred_idx[i]].l;
		int ysp = is.obj[pred_idx[i]].u;


#ifdef __DEBUG__
		__DEBUG_WRITE__("Width %d", (int)width);
		__DEBUG_WRITE__("Height %d", (int)height);
#endif
		bmp = create_bmp(width + CHAR_X_OFFSET, height + CHAR_Y_OFFSET, 8);

		for (c = 0; c < 256; c++)
			set_pal(bmp, c, c, c, c);


		for (x = 0; x < CHAR_X_OFFSET / 2; x++) {
			for (y = 0; y < height + CHAR_Y_OFFSET; y++) {
				set_idx(bmp, x, y, 255);
			}
		}

		for (x = width + CHAR_X_OFFSET / 2; x < width + CHAR_X_OFFSET; x++) {
			for (y = 0; y < height + CHAR_Y_OFFSET; y++) {
				set_idx(bmp, x, y, 255);
			}
		}

		for (y = 0; y < CHAR_Y_OFFSET / 2; y++) {
			for (x = CHAR_X_OFFSET / 2; x < width + CHAR_X_OFFSET / 2; x++) {
				set_idx(bmp, x, y, 255);
			}
		}

		for (y = height + CHAR_Y_OFFSET / 2; y < height + CHAR_Y_OFFSET; y++) {
			for (x = CHAR_X_OFFSET / 2; x < width + CHAR_X_OFFSET / 2; x++) {
				set_idx(bmp, x, y, 255);
			}
		}



		for (x = xsp; x < xsp + width; x++) {
			for (y = ysp; y < ysp + height; y++) {
				if (img[y][x] == is.obj[pred_idx[i]].label)
					set_idx(bmp, x - xsp + CHAR_X_OFFSET / 2, y - ysp + CHAR_Y_OFFSET / 2, 0);
				else
					set_idx(bmp, x - xsp + CHAR_X_OFFSET / 2, y - ysp + CHAR_Y_OFFSET / 2, 255);
			}
		}
		sprintf(buf, PATH OUTPUT_PREFIX "%d.bmp", i + 1);
		write_bmp(bmp, buf);
		free_bmp(bmp);

	}

	return nobj;
}//end function

