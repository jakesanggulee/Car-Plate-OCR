#include <stdio.h>

#define width_bmp(bmp) ((bmp)->w)
#define height_bmp(bmp) ((bmp)->h)
#define depth_bmp(bmp) ((bmp)->bps)
#define Write_4BYTE(x,f) write(f,&x,4)
#define Write_2BYTE(x,f) write(f,&x,2)

#define Read_2BYTE(x,f)		do{  unsigned char tmp[2]; read(f,tmp, 2 ); *x = (tmp[1] << 8 | tmp[0]);} while(0)
#define Read_4BYTE(x,f)		do{  unsigned char tmp[4]; read(f,tmp, 4 ); *x = (tmp[3] << 24 | tmp[2] << 16 | tmp[1] << 8 | tmp[0]);} while(0)


typedef struct _BITMAP
{
	unsigned short			mg;				
	unsigned long int		size;		
	unsigned short			extra1;
	unsigned short			extra2;
	unsigned long int		offset;			
	unsigned long int		header_length;			
	unsigned long int		w;				
	unsigned long int		h;				
	unsigned short			plane;				
	unsigned short			bps;		
	unsigned long int		compression;	
	unsigned long int		image_size;		
	unsigned long int		ppm;	
	unsigned long int		vpm;	
	unsigned long int		used_color;			
	unsigned long int		required_color;	
	unsigned char*		palette;
	unsigned char*		image_data;
}BITMAP;

BITMAP*			create_bmp(unsigned int width, unsigned int height, unsigned short depth);
void			free_bmp(BITMAP* bmp);

BITMAP*			read_bmp(const char* filename);
void			write_bmp(BITMAP* bmp, const char* filename);

void			get_rgb(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char* r, unsigned char* g, unsigned char* b);
void			set_rgb(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
void			get_idx(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char* val);
void 			set_idx(BITMAP* bmp, unsigned int x, unsigned int y, unsigned char val);
void 			set_pal(BITMAP* bmp, unsigned char index, unsigned char r, unsigned char g, unsigned char b);

