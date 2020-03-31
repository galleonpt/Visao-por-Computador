//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//           INSTITUTO POLIT�CNICO DO C�VADO E DO AVE
//                          2011/2012
//             ENGENHARIA DE SISTEMAS INFORM�TICOS
//                    VIS�O POR COMPUTADOR
//
//             [  DUARTE DUQUE - dduque@ipca.pt  ]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Desabilita (no MSVC++) warnings de fun��es n�o seguras (fopen, sscanf, etc...)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "vc.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            FUN��ES: ALOCAR E LIBERTAR UMA IMAGEM
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Alocar mem�ria para uma imagem
IVC *vc_image_new(int width, int height, int channels, int levels)
{
	IVC *image = (IVC *)malloc(sizeof(IVC));

	if (image == NULL)
		return NULL;
	if ((levels <= 0) || (levels > 255))
		return NULL;

	image->width = width;
	image->height = height;
	image->channels = channels;
	image->levels = levels;
	image->bytesperline = image->width * image->channels;
	image->data = (unsigned char *)malloc(image->width * image->height * image->channels * sizeof(char));

	if (image->data == NULL)
	{
		return vc_image_free(image);
	}

	return image;
}

// Libertar mem�ria de uma imagem
IVC *vc_image_free(IVC *image)
{
	if (image != NULL)
	{
		if (image->data != NULL)
		{
			free(image->data);
			image->data = NULL;
		}

		free(image);
		image = NULL;
	}

	return image;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    FUN��ES: LEITURA E ESCRITA DE IMAGENS (PBM, PGM E PPM)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

char *netpbm_get_token(FILE *file, char *tok, int len)
{
	char *t;
	int c;

	for (;;)
	{
		while (isspace(c = getc(file)))
			;
		if (c != '#')
			break;
		do
			c = getc(file);
		while ((c != '\n') && (c != EOF));
		if (c == EOF)
			break;
	}

	t = tok;

	if (c != EOF)
	{
		do
		{
			*t++ = c;
			c = getc(file);
		} while ((!isspace(c)) && (c != '#') && (c != EOF) && (t - tok < len - 1));

		if (c == '#')
			ungetc(c, file);
	}

	*t = 0;

	return tok;
}

long int unsigned_char_to_bit(unsigned char *datauchar, unsigned char *databit, int width, int height)
{
	int x, y;
	int countbits;
	long int pos, counttotalbytes;
	unsigned char *p = databit;

	*p = 0;
	countbits = 1;
	counttotalbytes = 0;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = width * y + x;

			if (countbits <= 8)
			{
				// Numa imagem PBM:
				// 1 = Preto
				// 0 = Branco
				//*p |= (datauchar[pos] != 0) << (8 - countbits);

				// Na nossa imagem:
				// 1 = Branco
				// 0 = Preto
				*p |= (datauchar[pos] == 0) << (8 - countbits);

				countbits++;
			}
			if ((countbits > 8) || (x == width - 1))
			{
				p++;
				*p = 0;
				countbits = 1;
				counttotalbytes++;
			}
		}
	}

	return counttotalbytes;
}

void bit_to_unsigned_char(unsigned char *databit, unsigned char *datauchar, int width, int height)
{
	int x, y;
	int countbits;
	long int pos;
	unsigned char *p = databit;

	countbits = 1;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = width * y + x;

			if (countbits <= 8)
			{
				// Numa imagem PBM:
				// 1 = Preto
				// 0 = Branco
				//datauchar[pos] = (*p & (1 << (8 - countbits))) ? 1 : 0;

				// Na nossa imagem:
				// 1 = Branco
				// 0 = Preto
				datauchar[pos] = (*p & (1 << (8 - countbits))) ? 0 : 1;

				countbits++;
			}
			if ((countbits > 8) || (x == width - 1))
			{
				p++;
				countbits = 1;
			}
		}
	}
}

IVC *vc_read_image(char *filename)
{
	FILE *file = NULL;
	IVC *image = NULL;
	unsigned char *tmp;
	char tok[20];
	long int size, sizeofbinarydata;
	int width, height, channels;
	int levels = 255;
	int v;

	// Abre o ficheiro
	if ((file = fopen(filename, "rb")) != NULL)
	{
		// Efectua a leitura do header
		netpbm_get_token(file, tok, sizeof(tok));

		if (strcmp(tok, "P4") == 0)
		{
			channels = 1;
			levels = 1;
		} // Se PBM (Binary [0,1])
		else if (strcmp(tok, "P5") == 0)
			channels = 1; // Se PGM (Gray [0,MAX(level,255)])
		else if (strcmp(tok, "P6") == 0)
			channels = 3; // Se PPM (RGB [0,MAX(level,255)])
		else
		{
#ifdef VC_DEBUG
			printf("ERROR -> vc_read_image():\n\tFile is not a valid PBM, PGM or PPM file.\n\tBad magic number!\n");
#endif

			fclose(file);
			return NULL;
		}

		if (levels == 1) // PBM
		{
			if (sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 ||
					sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tFile is not a valid PBM file.\n\tBad size!\n");
#endif

				fclose(file);
				return NULL;
			}

			// Aloca mem�ria para imagem
			image = vc_image_new(width, height, channels, levels);
			if (image == NULL)
				return NULL;

			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height;
			tmp = (unsigned char *)malloc(sizeofbinarydata);
			if (tmp == NULL)
				return 0;

#ifdef VC_DEBUG
			printf("\nchannels=%d w=%d h=%d levels=%d\n", image->channels, image->width, image->height, levels);
#endif

			if ((v = fread(tmp, sizeof(unsigned char), sizeofbinarydata, file)) != sizeofbinarydata)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tPremature EOF on file.\n");
#endif

				vc_image_free(image);
				fclose(file);
				free(tmp);
				return NULL;
			}

			bit_to_unsigned_char(tmp, image->data, image->width, image->height);

			free(tmp);
		}
		else // PGM ou PPM
		{
			if (sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 ||
					sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1 ||
					sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &levels) != 1 || levels <= 0 || levels > 255)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tFile is not a valid PGM or PPM file.\n\tBad size!\n");
#endif

				fclose(file);
				return NULL;
			}

			// Aloca mem�ria para imagem
			image = vc_image_new(width, height, channels, levels);
			if (image == NULL)
				return NULL;

#ifdef VC_DEBUG
			printf("\nchannels=%d w=%d h=%d levels=%d\n", image->channels, image->width, image->height, levels);
#endif

			size = image->width * image->height * image->channels;

			if ((v = fread(image->data, sizeof(unsigned char), size, file)) != size)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tPremature EOF on file.\n");
#endif

				vc_image_free(image);
				fclose(file);
				return NULL;
			}
		}

		fclose(file);
	}
	else
	{
#ifdef VC_DEBUG
		printf("ERROR -> vc_read_image():\n\tFile not found.\n");
#endif
	}

	return image;
}

int vc_write_image(char *filename, IVC *image)
{
	FILE *file = NULL;
	unsigned char *tmp;
	long int totalbytes, sizeofbinarydata;

	if (image == NULL)
		return 0;

	if ((file = fopen(filename, "wb")) != NULL)
	{
		if (image->levels == 1)
		{
			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height + 1;
			tmp = (unsigned char *)malloc(sizeofbinarydata);
			if (tmp == NULL)
				return 0;

			fprintf(file, "%s %d %d\n", "P4", image->width, image->height);

			totalbytes = unsigned_char_to_bit(image->data, tmp, image->width, image->height);
			printf("Total = %ld\n", totalbytes);
			if (fwrite(tmp, sizeof(unsigned char), totalbytes, file) != totalbytes)
			{
#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
#endif

				fclose(file);
				free(tmp);
				return 0;
			}

			free(tmp);
		}
		else
		{
			fprintf(file, "%s %d %d 255\n", (image->channels == 1) ? "P5" : "P6", image->width, image->height);

			if (fwrite(image->data, image->bytesperline, image->height, file) != image->height)
			{
#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
#endif

				fclose(file);
				return 0;
			}
		}

		fclose(file);

		return 1;
	}

	return 0;
}

//FUNCOES PARA DESENHAR AS IMAGENS
IVC *GradienteDE(IVC *image)
{
	long int pos;
	for (int x = 0; x < image->width; x++) //correr as linhas da imagem
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = 255 - x;
		}
	}
}

IVC *DiagonalBC(IVC *image)
{
	long int pos;
	for (int x = 0; x < image->width; x++) //correr as linhas da imagem
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = 255 - ((x + y) / 2);
		}
	}
}

IVC *DiagonalCB(IVC *image)
{
	long int pos;
	for (int x = 0; x < image->width; x++) //correr as linhas da imagem
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = (x + y) / 2;
		}
	}
}

IVC *GradienteBC(IVC *image)
{
	long int pos;
	for (int x = 0; x < image->width; x++) //correr as linhas da imagem
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = 255 - y;
		}
	}
}

IVC *GradienteCB(IVC *image)
{
	long int pos;
	for (int x = 0; x < image->width; x++) //correr as linhas da imagem
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = y;
		}
	}
}

IVC *GradienteED(IVC *image)
{
	long int pos;
	for (int x = 0; x < image->width; x++) //correr as linhas da imagem
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = x;
		}
	}
}

int vc_gray_negative(IVC *imagem)
{
	int pos;
	int x, y;

	for (x = 0; x < imagem->width; x++)
	{
		for (y = 0; y < imagem->height; y++)
		{
			pos = y * imagem->bytesperline + x * imagem->channels;
			imagem->data[pos] = 255 - imagem->data[pos];
		}
	}
	return 0;
}

int vc_rgb_negative(IVC *image)
{
	int pos;
	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = 255 - image->data[pos];
			image->data[pos + 1] = 255 - image->data[pos + 1];
			image->data[pos + 2] = 255 - image->data[pos + 2];
		}
	}
	return 1;
}

//Extrair componentes de uma imagem RGB para Gray
int vc_rgb_get_red_gray(IVC *image)
{
	int pos;
	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos + 1] = image->data[pos];
			image->data[pos + 2] = image->data[pos];
		}
	}
	return 1;
}

int vc_rgb_get_green_gray(IVC *image)
{
	int pos;
	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = image->data[pos + 1];
			image->data[pos + 2] = image->data[pos + 1];
		}
	}
	return 1;
}

int vc_rgb_get_blue_gray(IVC *image)
{
	int pos;
	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			image->data[pos] = image->data[pos + 2];
			image->data[pos + 1] = image->data[pos + 2];
		}
	}
	return 1;
}

//Converter de RGB para Gray
int vc_rgb_to_gray(IVC *image, IVC *result)
{
	int bytesperline_image = image->width * image->channels;
	int bytesperline_result = result->width * result->channels;
	long int pos_image, pos_result;
	float red, green, blue;

	if (image->width <= 0 || image->height <= 0 || image->data == NULL)
		return 0;
	if (image->width != result->width || image->height != result->height)
		return 0;
	if (image->channels != 3 || result->channels != 1)
		return 0;

	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			pos_image = y * bytesperline_image + x * image->channels;
			pos_result = y * bytesperline_result + x * result->channels;

			red = (float)image->data[pos_image];
			green = (float)image->data[pos_image + 1];
			blue = (float)image->data[pos_image + 2];

			result->data[pos_result] = (unsigned char)((red * 0.299) + (green * 0.587) + (blue * 0.114));
		}
	}
	return 1;
}

// Converter RGB para HSV
int vc_rgb_to_hsv(IVC *image)
{
	unsigned char *data = (unsigned char *)image->data;
	int width = image->width;
	int height = image->height;
	int bytesperline = image->bytesperline;
	int channels = image->channels;
	float r, g, b, hue, saturation, value;
	float rgb_max, rgb_min;
	int i, size;

	// Verificação de erros
	if ((width <= 0) || (height <= 0) || (data == NULL))
		return 0;
	if (channels != 3)
		return 0;

	size = width * height * channels;

	for (i = 0; i < size; i = i + channels)
	{
		r = (float)data[i];
		g = (float)data[i + 1];
		b = (float)data[i + 2];

		// Calcula valores máximo e mínimo dos canais de cor R, G e B
		rgb_max = (r > g ? (r > b ? r : b) : (g > b ? g : b));
		rgb_min = (r < g ? (r < b ? r : b) : (g < b ? g : b));

		// Value toma valores entre [0,255]
		value = rgb_max;
		if (value == 0.0f)
		{
			hue = 0.0f;
			saturation = 0.0f;
		}
		else
		{
			// Saturation toma valores entre [0,255]
			saturation = ((rgb_max - rgb_min) / rgb_max) * 255.0f;

			if (saturation == 0.0f)
			{
				hue = 0.0f;
			}
			else
			{
				// Hue toma valores entre [0,360]
				if ((rgb_max == r) && (g >= b))
				{
					hue = 60.0f * (g - b) / (rgb_max - rgb_min);
				}
				else if ((rgb_max == r) && (b > g))
				{
					hue = 360.0f + 60.0f * (g - b) / (rgb_max - rgb_min);
				}
				else if (rgb_max == g)
				{
					hue = 120.0f + 60.0f * (b - r) / (rgb_max - rgb_min);
				}
				else /* rgb_max == b*/
				{
					hue = 240.0f + 60.0f * (r - g) / (rgb_max - rgb_min);
				}
			}
		}

		// Atribui valores entre [0,255]
		data[i] = (unsigned char)(hue / 360.0f * 255.0f);
		data[i + 1] = (unsigned char)(saturation);
		data[i + 2] = (unsigned char)(value);
	}

	return 1;
}

// hmin,hmax = [0, 360]; smin,smax = [0, 100]; vmin,vmax = [0, 100]
int vc_hsv_segmentation(IVC *image, int hmin, int hmax, int smin, int smax, int vmin, int vmax)
{
	unsigned char *data = (unsigned char *)image->data;
	int width = image->width;
	int height = image->height;
	int bytesperline = image->bytesperline;
	int channels = image->channels;
	int hue, saturation, value;
	int h, s, v; // h=[0, 360] s=[0, 100] v=[0, 100]
	int i, size;

	// Verificação de erros
	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if (channels != 3)
		return 0;

	size = width * height * channels;

	for (i = 0; i < size; i = i + channels)
	{
		h = ((float)data[i]) / 255.0f * 360.0f;
		s = ((float)data[i + 1]) / 255.0f * 100.0f;
		v = ((float)data[i + 2]) / 255.0f * 100.0f;

		if ((h > hmin) && (h <= hmax) && (s >= smin) && (s <= smax) && (v >= vmin) && (v <= vmax))
		{
			data[i] = 255;
			data[i + 1] = 255;
			data[i + 2] = 255;
		}
		else
		{
			data[i] = 0;
			data[i + 1] = 0;
			data[i + 2] = 0;
		}
	}

	return 1;
}

int vc_scale_gray_to_rgb(IVC *original, IVC *converted)
{
	int pos, posAux, x, y;
	float value;
	unsigned char *_original = (unsigned char *)original->data;
	unsigned char *_converted = (unsigned char *)converted->data;

	if (original->width <= 0 || original->height <= 0 || original->data == NULL)
		return 0;
	if (original->width != converted->width || original->height != converted->height)
		return 0;
	if (original->channels != 1 || converted->channels != 3)
		return 0;

	for (x = 0; x < original->width; x++)
	{
		for (y = 0; y < original->height; y++)
		{
			pos = y * original->bytesperline + x * original->channels;
			posAux = y * converted->bytesperline + x * converted->channels;

			if (_original[pos] < 64)
			{
				_converted[posAux] = (unsigned char)0;
				_converted[posAux + 1] = (unsigned char)(4.047619048 * _original[pos]);
				_converted[posAux + 2] = (unsigned char)255;
			}
			else if (_original[pos] >= 64 && _original[pos] < 128)
			{
				_converted[posAux] = 0;
				_converted[posAux + 1] = 255;
				_converted[posAux + 2] = (int)(((129 - _original[pos]) * 255) / 64);
			}
			else if (_original[pos] >= 128 && _original[pos] < 192)
			{
				_converted[posAux] = ceil(((_original[pos] - 128.0) / 63.0) * 255);
				_converted[posAux + 1] = 255;
				_converted[posAux + 2] = 0;
			}
			else
			{
				_converted[posAux] = 255;
				_converted[posAux + 1] = (int)(((255 - _original[pos]) * 255) / 64);
				_converted[posAux + 2] = 0;
			}
		}
	}
	return 1;
}

int vc_gray_to_binary(IVC *image, IVC *result, int threshold)
{
	int bytesperline_image = image->width * image->channels;
	long int pos;
	long int pos_res;

	if (image->width <= 0 || image->height <= 0 || image->data == NULL)
		return 0;
	if (image->width != result->width || image->height != result->height)
		return 0;
	else
	{
		for (int x = 0; x < image->width; x++)
		{
			for (int y = 0; y < image->height; y++)
			{
				pos = y * bytesperline_image + x * image->channels;
				pos_res = y * result->bytesperline + x * result->channels;

				if (image->data[pos] > threshold)
					result->data[pos_res] = 1;
				else if (image->data[pos] <= threshold)
					result->data[pos_res] = 0;
			}
		}
		return 1;
	}
}

int vc_gray_to_binary_global_mean(IVC *image, IVC *result)
{
	long int pos;
	long int pos_res;
	long int soma = 0;
	float media;

	if (image->width <= 0 || image->height <= 0 || image->data == NULL)
		return 0;
	if (image->width != result->width || image->height != result->height)
		return 0;

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			soma += image->data[pos];
		}
	}

	media = soma / (image->height * image->width);

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
		{
			pos = y * image->bytesperline + x * image->channels;
			pos_res = y * result->bytesperline + x * result->channels;
			if (image->data[pos] <= media)
				result->data[pos_res] = 0;
			else if (image->data[pos] > media)
				result->data[pos_res] = 1;
		}
	}
	return 1;
}

// Converter de Gray para Binário (threshold automático Midpoint)
int vc_gray_to_binary_midpoint(IVC *src, IVC *dst, int kernel)
{
	unsigned char *datasrc = (unsigned char *)src->data;
	unsigned char *datadst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->bytesperline;
	int channels = src->channels;
	int x, y, kx, ky;
	int offset = (kernel - 1) / 2; //(int) floor(((double) kernel) / 2.0);
	int max, min;
	long int pos, posk;
	unsigned char threshold;

	// Verificação de erros
	if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL))
		return 0;
	if ((src->width != dst->width) || (src->height != dst->height) || (src->channels != dst->channels))
		return 0;
	if (channels != 1)
		return 0;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = y * bytesperline + x * channels;

			max = 0;
			min = 255;

			// NxM Vizinhos
			for (ky = -offset; ky <= offset; ky++)
			{
				for (kx = -offset; kx <= offset; kx++)
				{
					if ((y + ky >= 0) && (y + ky < height) && (x + kx >= 0) && (x + kx < width))
					{
						posk = (y + ky) * bytesperline + (x + kx) * channels;

						if (datasrc[posk] > max)
							max = datasrc[posk];
						if (datasrc[posk] < min)
							min = datasrc[posk];
					}
				}
			}

			threshold = (unsigned char)((float)(max + min) / (float)2);

			if (datasrc[pos] > threshold)
				datadst[pos] = 255;
			else
				datadst[pos] = 0;
		}
	}

	return 1;
}

int vc_gray_to_binary_bernsen(IVC *src, IVC *dst, int kernel, int Cmin)
{
	unsigned char *datasrc = (unsigned char *)src->data;
	unsigned char *datadst = (unsigned char *)dst->data;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->bytesperline;
	int channels = src->channels;
	int x, y, kx, ky;
	int offset = (kernel - 1) / 2; //(int) floor(((double) kernel) / 2.0);
	int max, min;
	long int pos, posk;
	unsigned char threshold;

	// Verificação de erros
	if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL))
		return 0;
	if ((src->width != dst->width) || (src->height != dst->height) || (src->channels != dst->channels))
		return 0;
	if (channels != 1)
		return 0;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = y * bytesperline + x * channels;

			max = 0;
			min = 255;

			// NxM Vizinhos
			for (ky = -offset; ky <= offset; ky++)
			{
				for (kx = -offset; kx <= offset; kx++)
				{
					if ((y + ky >= 0) && (y + ky < height) && (x + kx >= 0) && (x + kx < width))
					{
						posk = (y + ky) * bytesperline + (x + kx) * channels;

						if (datasrc[posk] > max)
							max = datasrc[posk];
						if (datasrc[posk] < min)
							min = datasrc[posk];
					}
				}
			}

			if ((max - min) < Cmin)
				threshold = 255 / 2;
			else
				threshold = 0.5 * (max + min);

			if (datasrc[pos] > threshold)
				datadst[pos] = 255;
			else
				datadst[pos] = 0;
		}
	}

	return 1;
}

int vc_gray_to_binary_niBlack(IVC *original, IVC *converted, int kernel, float k)
{
	long int pos, posk;
	float meanAux;
	int channels = original->channels, bytesperline = original->bytesperline;
	int offset = (kernel - 1) / 2;
	int x, kx, y, ky;
	int width = original->width, height = original->height;
	float mean, dv;
	int count;
	float threshold;

	if ((original->width <= 0) || (original->height <= 0) || (original->data == NULL))
		return 0;
	if ((original->width != converted->width) || (original->height != converted->height) || (original->channels != converted->channels))
		return 0;
	if (channels != 1)
		return 0;

	for (y = 0; y < original->height; y++)
		for (x = 0; x < original->width; x++)
		{
			pos = y * original->bytesperline + x * original->channels;
			mean = 0.0;
			dv = 0;
			count = 0;
			//
			for (ky = -offset; ky <= offset; ky++)
				for (kx = -offset; kx <= offset; kx++)
				{
					if ((y + ky >= 0) && (y + ky < height) && (x + kx >= 0) && (x + kx < width))
					{
						posk = (y + ky) * bytesperline + (x + kx) * channels;
						//
						mean += original->data[posk];
						count++;
					}
				}

			//Mean
			mean /= count;

			for (ky = -offset; ky <= offset; ky++)
				for (kx = -offset; kx <= offset; kx++)
				{
					if ((y + ky >= 0) && (y + ky < height) && (x + kx >= 0) && (x + kx < width))
					{
						posk = (y + ky) * bytesperline + (x + kx) * channels;
						//
						dv += pow((original->data[posk] - mean), 2);
					}
				}

			//calculo final
			threshold = mean + k * sqrt(dv / count);

			//aplica o thresholding
			if (original->data[pos] > threshold)
				converted->data[pos] = 255;
			else
				converted->data[pos] = 0;
		}

	return 1;
}

int vc_binary_dilate(IVC *image, IVC *converted, int kernel)
{
	long int pos, posAux;
	int x, y, kx, ky;
	int offset = (kernel - 1) / 2;
	unsigned char threshold;
	int count;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if ((image->width != converted->width) || (image->height != converted->height) || (image->channels != converted->channels))
		return 0;
	if (image->channels != 1)
		return 0;

	for (y = 0; y < image->height; y++)
	{
		for (x = 0; x < image->width; x++)
		{
			pos = y * image->bytesperline + x * image->channels;
			count = 0;
			for (ky = -offset; ky <= offset; ky++)
			{
				for (kx = -offset; kx <= offset; kx++)
				{
					if ((y + ky >= 0) && (y + ky < image->height) && (x + kx >= 0) && (x + kx < image->width))
					{
						posAux = (y + ky) * image->bytesperline + (x + kx) * image->channels;
						if (image->data[posAux] == 0)
							count++;
					}
				}
			}
			if (count > 0)
				converted->data[pos] = 1;
			else
				converted->data[pos] = 0;
		}
	}
	return 1;
}

int vc_binary_erode(IVC *image, IVC *converted, int kernel)
{
	long int pos, posAux;
	int x, y, kx, ky;
	int offset = (kernel - 1) / 2;
	unsigned char threshold;
	int count;

	if ((image->width <= 0) || (image->height <= 0) || (image->data == NULL))
		return 0;
	if ((image->width != converted->width) || (image->height != converted->height) || (image->channels != converted->channels))
		return 0;
	if (image->channels != 1)
		return 0;

	for (y = 0; y < image->height; y++)
	{
		for (x = 0; x < image->width; x++)
		{
			pos = y * image->bytesperline + x * image->channels;
			count = 0;
			for (ky = -offset; ky <= offset; ky++)
			{
				for (kx = -offset; kx <= offset; kx++)
				{
					if ((y + ky >= 0) && (y + ky < image->height) && (x + kx >= 0) && (x + kx < image->width))
					{
						posAux = (y + ky) * image->bytesperline + (x + kx) * image->channels;
						if (image->data[posAux] == 1)
							count++;
					}
				}
			}
			if (count > 0)
				converted->data[pos] = 0;
			else
				converted->data[pos] = 1;
		}
	}
	return 1;
}
