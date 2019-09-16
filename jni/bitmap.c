#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "bitmap.h"


BITMAP* create_bmp(unsigned int width, unsigned int height, unsigned short depth)
{
	BITMAP*	bmp = (BITMAP*) malloc(sizeof(BITMAP));

	if( depth == 8 )
		bmp->palette = (unsigned char*)calloc(1024, 1);
	else
		bmp->palette = NULL;
//Essential Data

	bmp->w = width;
	bmp->h = height;

	int width_pad = ( width*(depth >> 3) % 4 ? 4 - (width*(depth >> 3)%4) : 0 );

	bmp->image_size = (width +width_pad) * height;
	bmp->size = 54 +bmp->image_size + (depth == 8 ? 1024 : 0);
	bmp->offset = 54 + (depth == 8 ? 1024 : 0);
		

//Independant Constant

	bmp->mg = 0x4d42;
	bmp->header_length = 40;
	bmp->extra1 = 0;
	bmp->extra2 = 0;
	bmp->compression = 0;
	bmp->ppm = 0;
	bmp->vpm = 0;
	bmp->used_color = 0;
	bmp->required_color = 0;
	bmp->plane = 1;	
	bmp->bps = depth;
	
	bmp->image_data = (unsigned char*)malloc(bmp->image_size);
	return bmp;
}

void free_bmp(BITMAP* bmp)
{
	if (bmp == NULL)
		return;
	if (bmp->image_data != NULL)
		free(bmp->image_data);
	if (bmp->palette != NULL)
		free(bmp->palette);
	free(bmp);
}

BITMAP* read_bmp(const char* filename)
{
	BITMAP*	bmp;
	int f;
	bmp = (BITMAP*) malloc(sizeof(BITMAP));
	f = open(filename,O_RDONLY);

	Read_2BYTE(&(bmp->mg), f);
	Read_4BYTE(&(bmp->size), f);
	Read_2BYTE(&(bmp->extra1), f);
	Read_2BYTE(&(bmp->extra2), f);
	Read_4BYTE(&(bmp->offset), f);
	Read_4BYTE(&(bmp->header_length), f);
	Read_4BYTE(&(bmp->w), f);
	Read_4BYTE(&(bmp->h), f);
	Read_2BYTE(&(bmp->plane), f);
	Read_2BYTE(&(bmp->bps), f);
	Read_4BYTE(&(bmp->compression), f);
	Read_4BYTE(&(bmp->image_size), f);
	Read_4BYTE(&(bmp->ppm), f);
	Read_4BYTE(&(bmp->vpm), f);
	Read_4BYTE(&(bmp->used_color), f);
	Read_4BYTE(&(bmp->required_color), f);

	bmp->palette = NULL;

	if (bmp->bps == 8){
		bmp->palette = (unsigned char*)calloc(1024,1);
		read(f,bmp->palette, 1024 ); 
	}


	bmp->image_data = (unsigned char*)malloc(bmp->image_size);
	read(f,bmp->image_data, bmp->image_size ); 
	close(f);

	return bmp;
}

void write_bmp(BITMAP* bmp, const char* filename)
{
	int	f = open(filename, O_WRONLY|O_CREAT|O_TRUNC,0666);

	Write_2BYTE(bmp->mg, f);
	Write_4BYTE(bmp->size, f);
	Write_2BYTE(bmp->extra1, f);
	Write_2BYTE(bmp->extra2, f);
	Write_4BYTE(bmp->offset, f);
	Write_4BYTE(bmp->header_length, f);
	Write_4BYTE(bmp->w, f);
	Write_4BYTE(bmp->h, f);
	Write_2BYTE(bmp->plane, f);
	Write_2BYTE(bmp->bps, f);
	Write_4BYTE(bmp->compression, f);
	Write_4BYTE(bmp->image_size, f);
	Write_4BYTE(bmp->ppm, f);
	Write_4BYTE(bmp->vpm, f);
	Write_4BYTE(bmp->used_color, f);
	Write_4BYTE(bmp->required_color, f);

	if (bmp->palette != NULL)
		write(f,bmp->palette,  1024);

	write(f,bmp->image_data, bmp->image_size);
	close(f);
}


void get_rgb(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char* r, unsigned char* g, unsigned char* b)
{
unsigned char*	start_pos =((bmp->h - 1 - y) * (bmp->image_size / bmp->h) + x * (bmp->bps >> 3))  + bmp->image_data ; 
	if (bmp->bps == 8)
		start_pos = bmp->palette + *start_pos * 4;
	if (r)	*r = start_pos[2];
	if (g)	*g = start_pos[1];
	if (b)	*b = start_pos[0];
	
}

void set_rgb(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
unsigned char*	start_pos =((bmp->h - 1 - y) * (bmp->image_size / bmp->h) + x * (bmp->bps >> 3))  + bmp->image_data;

		start_pos[2] = r;
		start_pos[1] = g;
		start_pos[0] = b;
	
}


void get_idx(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char* val)
{
	unsigned char*	pixel = bmp->image_data + ((bmp->h - y - 1) * (bmp->image_size / bmp->h) + x);
	if (val)	*val = *pixel;
	
}


void set_idx(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char val)
{
	unsigned char*	pixel = bmp->image_data + ((bmp->h - y - 1) * (bmp->image_size / bmp->h) + x);

		*pixel = val;
	
}

void set_pal(BITMAP* bmp, unsigned char index, unsigned char r, unsigned char g, unsigned char b)
{

		*(bmp->palette + index * 4 + 2) = r;
		*(bmp->palette + index * 4 + 1) = g;
		*(bmp->palette + index * 4 + 0) = b;

}




