/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nozanne <nozanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:01:36 by jostraye          #+#    #+#             */
/*   Updated: 2018/08/13 13:54:33 by nozanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	unsigned char		*create_bmp_img(int *imgstr)
{
	unsigned char	*img;
	int				o;
	t_vc			rgb;

	if (!(img = (unsigned char*)malloc(sizeof(unsigned char)
	* 3 * 2 * WINY * WINZ)))
		return (0);
	ft_memset(img, 0, 3 * 2 * WINY * WINZ);
	o = 0;
	while (o < (WINY * WINZ))
	{
		rgb = hextorgb(imgstr[o]);
		img[o * 3 + 2] = (unsigned char)rgb.x;
		img[o * 3 + 1] = (unsigned char)rgb.y;
		img[o * 3 + 0] = (unsigned char)rgb.z;
		o++;
	}
	return (img);
}

static void					write_file_header(FILE *f)
{
	unsigned char	bmpfileheader[14];
	int				filesize;
	int				i;

	i = -1;
	while (++i < 14)
		bmpfileheader[i] = (unsigned char)0;
	filesize = 54 + 2 * WINY * WINZ;
	bmpfileheader[0] = (unsigned char)'B';
	bmpfileheader[1] = (unsigned char)'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpfileheader[10] = (unsigned char)54;
	fwrite(bmpfileheader, 1, 14, f);
}

static void					write_info_header(FILE *f)
{
	unsigned char	bmpinfoheader[40];
	int				i;

	i = -1;
	while (++i < 40)
		bmpinfoheader[i] = (unsigned char)0;
	bmpinfoheader[0] = (unsigned char)40;
	bmpinfoheader[12] = (unsigned char)1;
	bmpinfoheader[14] = (unsigned char)24;
	bmpinfoheader[4] = (unsigned char)(WINY);
	bmpinfoheader[5] = (unsigned char)(WINY >> 8);
	bmpinfoheader[6] = (unsigned char)(WINY >> 16);
	bmpinfoheader[7] = (unsigned char)(WINY >> 24);
	bmpinfoheader[8] = (unsigned char)(WINZ);
	bmpinfoheader[9] = (unsigned char)(WINZ >> 8);
	bmpinfoheader[10] = (unsigned char)(WINZ >> 16);
	bmpinfoheader[11] = (unsigned char)(WINZ >> 24);
	bmpinfoheader[12] = (unsigned char)1;
	fwrite(bmpinfoheader, 1, 40, f);
}

void						create_bmp_file(int *imgstr)
{
	FILE			*f;
	unsigned char	*img;
	unsigned char	bmppad[3];
	int				i;

	i = -1;
	img = create_bmp_img(imgstr);
	if (!img)
		return ;
	while (++i < 3)
		bmppad[i] = (unsigned char)0;
	f = fopen("img.bmp", "wb");
	i = -1;
	write_file_header(f);
	write_info_header(f);
	while (++i < WINZ)
	{
		fwrite(img + (WINY * (WINZ - i - 1) * 3), 3, WINY, f);
		fwrite(bmppad, 1, (4 - (WINY * 3) % 4) % 4, f);
	}
	free(img);
	fclose(f);
}
