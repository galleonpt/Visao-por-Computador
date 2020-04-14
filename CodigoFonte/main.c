#include <stdio.h>
#include "vc.h"

#pragma region CriarAlterarGuardarImagem
//int main(void)
//{
//  IVC *image;
//  int i;
//
//  image = vc_read_image("../Images/FLIR/flir-01.pgm");
//  if (image == NULL)
//  {
//    printf("Erro!!! imagem nao encontrada!!!\n");
//    getchar();
//    return 0;
//  }
//
//  for (i = 0; i < image->bytesperline * image->height; i += image->channels)
//  {
//    image->data[i] = 255 - image->data[i];
//  }
//
//  vc_write_image("../Results/imagem1.pgm", image);
//  vc_image_free(image);
//
//  printf("Carregue numa tecla para sair...");
//
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region CriarImagemBinaria
//int main(void)
//{
//  IVC *image;
//  int x, y;
//  long int pos;
//
//  image = vc_image_new(280, 280, 1, 1);
//  if (image == NULL)
//  {
//    printf("out of memory!!!\n");
//    getchar();
//    return 0;
//  }
//
//  for (x = 0; x < image->width; x++)
//  {
//    for (y = 0; y < image->height; y++)
//    {
//      pos = y * image->bytesperline + x * image->channels;
//
//      if ((x <= image->width / 2) && (y <= image->height / 2))
//        image->data[pos] = 1;
//      else if ((x > image->width / 2) && (y > image->height / 2))
//        image->data[pos] = 1;
//      else
//        image->data[pos] = 0;
//    }
//  }
//  vc_write_image("../Results/binaria.pbm", image);
//  vc_image_free(image);
//  printf("Carregue numa tecla para sair...\n");
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region InverterBinaria
//int main(void)
//{
//  IVC *image;
//  int i;
//
//  image = vc_read_image("../Results/binaria.pbm");
//  if (image == NULL)
//  {
//    printf("File not found");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    for (i = 0; i < image->bytesperline * image->height; i += image->channels)
//    {
//      if (image->data[i] == 1)
//        image->data[i] = 0;
//      else
//        image->data[i] = 1;
//    }
//
//    vc_write_image("../Results/binairaInvertida.pbm", image);
//    vc_image_free(image);
//
//    printf("Press any key to continue\n");
//    getchar();
//  }
//}
#pragma endregion

#pragma region GradienteEsquerdaDireita
//int main(void)
//{
//  IVC *image;
//  long int pos;
//
//  image = vc_image_new(256, 256, 1, 255);
//  if (image == NULL)
//  {
//    printf("out of memory");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    GradienteED(image);
//    vc_write_image("../Results/gradienteED.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region GradienteCimaBaixo
//int main(void)
//{
//  IVC *image;
//  long int pos;
//
//  image = vc_image_new(256, 256, 1, 255);
//  if (image == NULL)
//  {
//    printf("out of memory");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    GradienteCB(image);
//    vc_write_image("../Results/gradienteCB.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region GradienteBaixoCima

//int main(void)
//{
//  IVC *image;
//  long int pos;
//
//  image = vc_image_new(256, 256, 1, 255);
//  if (image == NULL)
//  {
//    printf("out of memory");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    GradienteBC(image);
//    vc_write_image("../Results/gradienteBC.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region GradienteDireitaEsquerda
//int main(void)
//{
//  IVC *image;
//  long int pos;
//
//  image = vc_image_new(256, 256, 1, 255);
//  if (image == NULL)
//  {
//    printf("out of memory");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    GradienteDE(image);
//    vc_write_image("../Results/gradienteDE.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region DiagonalCimaBaixo
//int main(void)
//{
//  IVC *image;
//  long int pos;
//
//  image = vc_image_new(256, 256, 1, 255);
//  if (image == NULL)
//  {
//    printf("Out of memory!!!");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    DiagonalCB(image);
//    vc_write_image("../Results/gradienteDiagonalCB.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region DiagonalBaixoCima
//int main(void)
//{
//  IVC *image;
//
//  image = vc_image_new(256, 256, 1, 255);
//  if (image == NULL)
//  {
//    printf("out of memory");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    DiagonalBC(image);
//
//    vc_write_image("../Results/gradienteDiagonalBC.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region NegativeGray
//int main(void)
//{
//  IVC *image = vc_read_image("../Images/Other/gray-01.pgm");
//
//  if (image == NULL || image->channels != 1 || image->height <= 0 || image->width <= 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//
//  vc_gray_negative(image);
//  vc_write_image("../Results/grayNegative.pbm", image);
//
//  vc_image_free(image);
//
//  printf("Carregue numa tecla para sair...\n");
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region NegativeRGB
//int main(void)
//{
//  IVC *image = vc_read_image("../Images/Additional/girl.ppm");
//
//  if (image == NULL || image->channels != 3 || image->height <= 0 || image->width <= 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//
//  vc_rgb_negative(image);
//  vc_write_image("../Results/rbgNegative(girl).pbm", image);
//
//  vc_image_free(image);
//
//  printf("Carregue numa tecla para sair...\n");
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region RED_TO_GRAY
//int main(void)
//{
//  IVC *image = vc_read_image("../Images/Classic/baboon.ppm");
//
//  if (image == NULL || image->channels != 3 || image->height <= 0 || image->width <= 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//
//  vc_rgb_get_red_gray(image);
//  vc_write_image("../Results/red_to_gray.pbm", image);
//
//  vc_image_free(image);
//
//  printf("Carregue numa tecla para sair...\n");
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region Green_TO_GRAY
//int main(void)
//{
//  IVC *image = vc_read_image("../Images/Classic/baboon.ppm");
//
//  if (image == NULL || image->channels != 3 || image->height <= 0 || image->width <= 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//
//  vc_rgb_get_green_gray(image);
//  vc_write_image("../Results/green_to_gray.pbm", image);
//
//  vc_image_free(image);
//
//  printf("Carregue numa tecla para sair...\n");
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region Blue_TO_GRAY
//int main(void)
//{
//  IVC *image = vc_read_image("../Images/Classic/baboon.ppm");
//
//  if (image == NULL || image->channels != 3 || image->height <= 0 || image->width <= 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//
//  vc_rgb_get_blue_gray(image);
//  vc_write_image("../Results/blue_to_gray.pbm", image);
//
//  vc_image_free(image);
//
//  printf("Carregue numa tecla para sair...\n");
//  getchar();
//  return 0;
//}
#pragma endregion

#pragma region RGB_to_Gray
//int main(void)
//{
//  IVC *image = vc_read_image("../Images/Classic/baboon.ppm");
//  IVC *result = vc_image_new(image->width, image->height, 1, 255);
//
//  if (vc_rgb_to_gray(image, result) == 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    vc_write_image("../Results/rgb_to_gray.pbm", result);
//
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region RGB_to_HSV
//int main(void)
//{
//  IVC *image = vc_read_image("../HSV_ImagensTeste/HSVTestImage01.ppm");
//  // IVC *image = vc_read_image("../HSV_ImagensTeste/HSVTestImage02.ppm");
//
//  if (vc_rgb_to_hsv(image) == 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    // vc_write_image("../Results/rgb_to_hsv1.pbm", image);
//    vc_write_image("../Results/rgb_to_hsv1.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region HSV_Segmentation
// int main(void)
//{
//  IVC *image = vc_read_image("../Images/Additional/fruits.ppm");
//
//  if (vc_hsv_segmentation(image, 200, 360, 75, 100, 25, 75) == 0)
//  {
//    printf("ERRO!!!");
//    getchar();
//    return 0;
//  }
//  else
//  {
//    // vc_write_image("../Results/rgb_to_hsv1.pbm", image);
//    vc_write_image("../Results/segmentation1.pbm", image);
//    vc_image_free(image);
//
//    printf("Carregue numa tecla para sair...\n");
//    getchar();
//    return 0;
//  }
//}
#pragma endregion

#pragma region Scale_Gray_to_RGB
// int main(void)
// {
//   IVC *image = vc_read_image("../Images/Special/testpat.pgm");
//   IVC *result = vc_image_new(image->width, image->height, 3, 255);

//   if (vc_scale_gray_to_rgb(image, result) == 0)
//   {
//     printf("ERRO!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/GrayToRGB.pbm", result);
//     vc_image_free(image);
//     vc_image_free(result);

//     printf("Carregue numa tecla para sair...\n");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region Threshold(Gray_to_Binary)
// int main(void)
// {
//   IVC *image = vc_read_image("../ImagesTestSegmentation/grayscale_chart.pgm");
//   IVC *result = vc_image_new(image->width, image->height, 1, 1);
//   // IVC *image = vc_read_image("../ImagesTestSegmentation/cells.pgm");

//   if (vc_gray_to_binary(image, result, 100) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/rgb_to_binary(threshold).pbm", result);
//     vc_image_free(image);
//     puts("Carregue numa tecla para sair...");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region Global_Mean(Gray_to_Binary)
// int main(void)
// {
//   IVC *image = vc_read_image("../ImagesTestSegmentation/grayscale_chart.pgm");
//   IVC *result = vc_image_new(image->width, image->height, 1, 1);

//   if (vc_gray_to_binary_global_mean(image, result) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/rgb_to_binary(global_mean).pbm", result);
//     vc_image_free(image);
//     puts("Carregue numa tecla para sair...");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region MidPoint(Gray_to_Binary)
// int main(void)
// {
//   IVC *image = vc_read_image("../ImagesTestSegmentation/grayscale_chart.pgm");
//   IVC *result = vc_image_new(image->width, image->height, 1, 1);

//   if (vc_gray_to_binary_midpoint(image, result, 25) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/rgb_to_binary(midPoint).pbm", result);
//     vc_image_free(image);
//     puts("Carregue numa tecla para sair...");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region Bernsen(Gray_to_Binary)
// int main(void)
// {
//   IVC *image = vc_read_image("../ImagesTestSegmentation/grayscale_chart.pgm");
//   IVC *result = vc_image_new(image->width, image->height, 1, 1);

//   if (vc_gray_to_binary_bernsen(image, result, 25, 100) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/rgb_to_binary(bernsen).pbm", result);
//     vc_image_free(image);
//     puts("Carregue numa tecla para sair...");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region Bernsen(Gray_to_Binary)
// int main(void)
// {
//   IVC *image = vc_read_image("../ImagesTestSegmentation/grayscale_chart.pgm");
//   IVC *result = vc_image_new(image->width, image->height, 1, 1);

//   if (vc_gray_to_binary_niBlack(image, result, 15, -0.2) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/rgb_to_binary(niblack).pbm", result);
//     vc_image_free(image);
//     puts("Carregue numa tecla para sair...");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region Dilate
// int main(void)
// {
//   IVC *image = vc_read_image("../ImagesTestSegmentation/coins.pgm");
//   IVC *threshold = vc_image_new(image->width, image->height, 1, 1);
//   IVC *result = vc_image_new(image->width, image->height, 1, 1);

//   if (vc_gray_to_binary_global_man(image, threshold) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }

//   if (vc_binary_dilate1(threshold, result, 3) == 0)
//   {
//     puts("Erro!!!");
//     getchar();
//     return 0;
//   }
//   else
//   {
//     vc_write_image("../Results/binary(dilate).pbm", result);
//     vc_image_free(image);
//     puts("Carregue numa tecla para sair...");
//     getchar();
//     return 0;
//   }
// }
#pragma endregion

#pragma region Erode
int main(void)
{
  IVC *image = vc_read_image("../ImagesTestSegmentation/coins.pgm");
  IVC *threshold = vc_image_new(image->width, image->height, 1, 1);
  IVC *result = vc_image_new(image->width, image->height, 1, 1);

  if (vc_gray_to_binary_global_mean(image, threshold) == 0)
  {
    puts("Erro!!!");
    getchar();
    return 0;
  }

  if (vc_binary_erode(threshold, result, 3) == 0)
  {
    puts("Erro!!!");
    getchar();
    return 0;
  }
  else
  {
    vc_write_image("../Results/binary(erode).pbm", result);
    vc_image_free(image);
    puts("Carregue numa tecla para sair...");
    getchar();
    return 0;
  }
}
#pragma endregion