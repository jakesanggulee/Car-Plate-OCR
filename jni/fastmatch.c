#include "bitmap.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "debug.h"
#define MAX_LABEL   500

struct _tobj {
	unsigned int pixels;
	unsigned int l, r, u, d;
	unsigned int w, h;
	unsigned int label;

};

struct img_status {

	int nobjs;
	struct _tobj obj[MAX_LABEL];
};

int compare_l(const void* a, const void* b) {

	struct _tobj* aa = (struct _tobj*) a;
	struct _tobj* bb = (struct _tobj*) b;

	if (aa->l < bb->l)
		return -1;

	if (aa->l > bb->l)
		return 1;

	return 0;


}

static int find(int set[], int x)
{
	int r = x;
	while (set[r] != r)
		r = set[r];
	return r;
}

int fast_match(char path[]) {


#ifdef __DEBUG__
	__DEBUG_WRITE__("Fast match started %c", '!');
#endif

	struct img_status is;
	BITMAP*    bmp;
	unsigned int    width, height;
	unsigned int    x, y;
	is.nobjs = 0;

	bmp = read_bmp(path);


	width = width_bmp(bmp)+2;
	height = height_bmp(bmp)+2;
	unsigned char   r1, g1, b1;
	unsigned char **img;

	img = (unsigned char**)malloc(sizeof(unsigned char*) * (height));

	for (x = 0; x < height; x++) {
		img[x] = (unsigned char*)malloc(sizeof(unsigned char) * (width));
	}

	for (x = 0; x < width; ++x) {
		for (y = 0; y < height; ++y) {
				img[y][x] = 1;
	}
}





	for (x = 0; x < width-2; ++x) {
		for (y = 0; y < height-2; ++y) {
			get_rgb(bmp, x, y, &r1, &g1, &b1);
			if (0.2989*r1 + 0.5870*g1 + 0.1140*b1 < 128)
				img[y+1][x+1] = 0;
			else
				img[y+1][x+1] = 1;
		}
	}





	int nth_label = 0;
	int lset[MAX_LABEL] = { 0, };
	int nobj = 0;
	int i, r, c;
	int row, col;

	for (row = 0; row < height; row++) {
		for (col = 0; col < width; col++) {
			if (img[row][col] != 0) { //when cell is on
				int lu, mu, ru, l;
				if (col == 0)
					l = 0;
				else
					l = find(lset, (int)img[row][col - 1]);

				if (row == 0)
					mu = 0;
				else
					mu = find(lset, (int)img[row - 1][col]);

				if ((row == 0) || (col == 0))
					lu = 0;
				else
					lu = find(lset, (int)img[row - 1][col - 1]);

				if ((row == 0) || (col == width - 1))
					ru = 0;
				else
					ru = find(lset, (int)img[row - 1][col + 1]);

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
		lset[i] = find(lset, i);

	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
			img[r][c] = lset[(int)img[r][c]];

	// count up the objects in the image
	for (i = 0; i <= nth_label; i++)
		lset[i] = 0;

	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++)
			lset[(int)img[r][c]]++;

	// number the objects from 1 through n objects

	nobj = 0;
	lset[0] = 0;
	int cnt[MAX_LABEL];

	memcpy(cnt, lset, MAX_LABEL * sizeof(int));

	for (i = 1; i <= nth_label; i++) {
		if (lset[i] > 0) {
			is.nobjs++;
			is.obj[is.nobjs - 1].pixels = lset[i];
			lset[i] = ++nobj;
		}
	}




	for (i = 0; i < is.nobjs; i++) {
		is.obj[i].l = width - 1;
		is.obj[i].r = 0;
		is.obj[i].u = height - 1;
		is.obj[i].d = 0;
		is.obj[i].label = i + 1;

	}
	// run through the look-up table again
	for (r = 0; r < height; r++)
		for (c = 0; c < width; c++) {
			int idx = (int)img[r][c];
			int label = lset[idx];

			if (cnt[idx] > 0) {
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


	for (i = 0; i < is.nobjs; i++) {
		is.obj[i].w = is.obj[i].r - is.obj[i].l;
		is.obj[i].h = is.obj[i].d - is.obj[i].u;

	}




	qsort(is.obj, is.nobjs, sizeof(is.obj[0]), compare_l);

	int pred = -1;


#ifdef __DEBUG__
	__DEBUG_WRITE__("Fast Match obj Type %d\n", is.nobjs);
#endif

	if (is.nobjs == 3) {
		pred = 8;
	}


	if (is.nobjs == 2)
	{ // 6 9 0 4

		double xexp = 0, yexp = 0;
		int pix = is.obj[1].pixels;
		//calculate expectation
		for (x = 0; x < width; ++x) {
			for (y = 0; y < height; ++y) {
				if (img[y][x] == is.obj[1].label) {
					xexp += (double)x / pix;
					yexp += (double)y / pix;
				}
			}
		}

		if ((height - 2) > 1.6 * is.obj[1].h)
		{
#ifdef __DEBUG__
	__DEBUG_WRITE__("Fast match: Not zero %d\n", pred);
#endif

			if ((xexp / (width - 1) > 0.4) && (xexp / (width - 1) < 0.6))
			{
#ifdef __DEBUG__
	__DEBUG_WRITE__("Fast match: 4 6 9 det:  %lf\n", (yexp / (height - 1)));
#endif

				if ((yexp / (height - 1) < 0.4)) {

					pred = 9;
				}
				else if ((yexp / (height - 1) > 0.65)) {

					pred = 6;
				}
				else if ((yexp / (height - 1) > 0.45) && (yexp / (height - 1) < 0.6))
					pred = 4;
			}
		}
		else {

			pred = 0;
		}


	}

	for (x = 0; x < height; x++) {
		free(img[x]);
	}
	free(img);
	free(bmp);

#ifdef __DEBUG__
	__DEBUG_WRITE__("Fast match  return %d\n", pred);
#endif

	return pred;
}

