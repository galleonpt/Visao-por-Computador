//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//           INSTITUTO POLIT�CNICO DO C�VADO E DO AVE
//                          2011/2012
//             ENGENHARIA DE SISTEMAS INFORM�TICOS
//                    VIS�O POR COMPUTADOR
//
//             [  DUARTE DUQUE - dduque@ipca.pt  ]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define VC_DEBUG

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UMA IMAGEM
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct
{
	unsigned char *data;
	int width, height;
	int channels;			// Bin�rio/Cinzentos=1; RGB=3
	int levels;				// Bin�rio=1; Cinzentos [1,255]; RGB [1,255]
	int bytesperline; // width * channels
} IVC;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                    PROT�TIPOS DE FUN��ES
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// FUN��ES: ALOCAR E LIBERTAR UMA IMAGEM
IVC *vc_image_new(int width, int height, int channels, int levels);
IVC *vc_image_free(IVC *image);

// FUN��ES: LEITURA E ESCRITA DE IMAGENS (PBM, PGM E PPM)
IVC *vc_read_image(char *filename);
int vc_write_image(char *filename, IVC *image);

// Funcoes para desenhas as imagens
IVC *DiagonalCB(IVC *image);
IVC *DiagonalBC(IVC *image);
IVC *GradienteDE(IVC *image);
IVC *GradienteBC(IVC *image);
IVC *GradienteCB(IVC *image);
IVC *GradienteED(IVC *image);
int vc_gray_negative(IVC *imagem);
int vc_rgb_negative(IVC *image);

int vc_rgb_get_red_gray(IVC *image);
int vc_rgb_get_green_gray(IVC *image);
int vc_rgb_get_blue_gray(IVC *image);

int vc_rgb_to_gray(IVC *image, IVC *result);

float CalcValue(IVC image, int pos);
float CalcSaturation(IVC image, int pos);
int CalcHue(IVC image, int pos);
int vc_rgb_to_hsv(IVC *image);
int vc_hsv_segmentation(IVC *image, int hmin, int hmax, int smin, int smax, int vmin, int vmax);
int vc_scale_gray_to_rgb(IVC *original, IVC *converted);

int vc_gray_to_binary(IVC *image, IVC *result, int threshold);
int vc_gray_to_binary_global_mean(IVC *image, IVC *result);
int vc_gray_to_binary_midpoint(IVC *src, IVC *dst, int kernel);
int vc_gray_to_binary_bernsen(IVC *src, IVC *dst, int kernel, int Cmin);
int vc_gray_to_binary_niBlack(IVC *original, IVC *converted, int kernel, float k);
int vc_binary_dilate(IVC *src, IVC *dst, int kernel);
int vc_binary_dilate(IVC *original, IVC *converted, int kernel);
int vc_binary_erode(IVC *image, IVC *converted, int kernel);
int vc_binary_open(IVC *image, IVC *converted, int kernel);
int vc_binary_close(IVC *image, IVC *converted, int kernel);
