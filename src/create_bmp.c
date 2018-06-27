/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:01:36 by jostraye          #+#    #+#             */
/*   Updated: 2018/06/25 18:57:11 by jostraye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // create a file object that we will use to write our image
// FILE *image;
// // we want to know how many pixels to reserve
// int image_size = width * height;
// // a byte is 4 bits but we are creating a 24 bit image so we can represent a pixel with 3
// // our final file size of our image is the width * height * 4 + size of bitmap header
// int file_size = 54 + 4 * image_size;
// // pixels per meter https://www.wikiwand.com/en/Dots_per_inch
// int ppm = dpi * 39.375;
//
// // bitmap file header (14 bytes)
// // we could be savages and just create 2 array but since this is for learning lets
// // use structs so it can be parsed by someone without having to refer to the spec
//
// // since we have a non-natural set of bytes, we must explicitly tell the
// // compiler to not pad anything, on gcc the attribute alone doesn't work so
// // a nifty trick is if we declare the smallest data type last the compiler
// // *might* ignore padding, in some cases we can use a pragma or gcc's
// // __attribute__((__packed__)) when declaring the struct
// // we do this so we can have an accurate sizeof() which should be 14, however
// // this won't work here since we need to order the bytes as they are written
#include "rtv1.h"


struct bitmap_file_header {
    unsigned char   bitmap_type[2];     // 2 bytes
    int             file_size;          // 4 bytes
    short           reserved1;          // 2 bytes
    short           reserved2;          // 2 bytes
} bfh;

// bitmap image header (40 bytes)
struct bitmap_image_header {
    unsigned int    size_header;        // 4 bytes
    unsigned int    width;              // 4 bytes
    int    height;             // 4 bytes
    short int       planes;             // 2 bytes
    short int       bit_count;          // 2 bytes
    unsigned int    compression;        // 4 bytes
    unsigned int    image_size;         // 4 bytes
    unsigned int    ppm_x;              // 4 bytes
    unsigned int    ppm_y;              // 4 bytes
    unsigned int    clr_used;           // 4 bytes
    unsigned int    clr_important;      // 4 bytes
} bih;
// if you are on Windows you can include <windows.h>
// and make use of the BITMAPFILEHEADER and BITMAPINFOHEADER structs

t_vc			hextorgb(int hex)
{
	t_vc rgb;

	rgb.x = (double)((hex / (0X100 * 0X100)) % 0X100);
	rgb.y = (double)((hex / 0X100) % 0X100);
	rgb.z = (double)(hex % 0X100);
	return (rgb);
}

void create_bmp(int *data, unsigned int file_size, t_env *e)
{
	int fd;
	int i;

	t_vc rgb;
	file_size = 54 + 3 * (WINY * WINZ);
    // Pourquoi 18? et ou sont passes ces pixels?
	i = -1;
	memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size       = file_size;
	bfh.reserved1       = 0;
	bfh.reserved2       = 0;

	bih.size_header     = sizeof(bih);
	bih.width           = WINY;
	bih.height          = -WINZ;
	bih.planes          = 1;
	bih.bit_count       = 24;
	bih.compression     = 0;
	bih.image_size      = (WINY * WINZ);
	bih.ppm_x           = 2835;
	bih.ppm_y           = 2835;
	bih.clr_used        = 0;
	bih.clr_important   = 0;
	char *name;
	name = ft_strjoin(e->file_name, ".bmp");
	if ((fd = open(name,  O_EXCL| O_RDWR|O_CREAT| O_TRUNC| O_APPEND, 00700)) == -1)
		(fd = open(name,  O_EXCL| O_RDWR, 00700));
	printf("creating file fd %d \n",fd);
	free (name);
	write(fd, &bfh, 14);
	pwrite(fd, "0X36", 4, 10);
	pwrite(fd, &bih, sizeof(bih), 14);
	// while (++i <18)
	// printf("1%d %f %f %f\n", i,hextorgb(data[i]).x, hextorgb(data[i]).y, hextorgb(data[i]).z);
	while (++i < WINY * WINZ)
	{
		rgb = hextorgb(data[i]);
		char red   = (char)rgb.x;
		char green = (char)rgb.y;
		char blue  = (char)rgb.z;
		unsigned char color[3] = {blue, green, red};
	   write(fd, color, sizeof(color));
	}
	close(fd);
}
