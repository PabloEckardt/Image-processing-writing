#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <array>
#include <sys/resource.h>


using namespace std;

// This is the resolution of a piece of paper at 300pixels per inch. Actual size is this values / print resolution.
// All functions will adjust to these parameters
int const width = 2500;
int const height = 3300;
void drawGrid(int marginPixels, int sqHeight, int sqWidth, FILE ** file_pointer);
void drawSpiral(FILE ** file_pointer, int rotations);
//Draw spire function.

int main(void)
{

  //#################Initiate all necessary variables to create a ppm file from scratch.############
  //dimx and dimy are pixels. To find the actual size of the image in scalars. Then
  // its dimx pixels / print resolution. Ex: 2500/500pixelsperinch = 5 inches. Most laser printers
  // print at 300 Pixels per inch.
  FILE *fp = fopen("grid.ppm", "wb"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", width, height); //this is part of the ppm format initialize.
  // p6 is the magic number for the format. And 255 is the maximum understood value of the RGB pixels.
  //the dimensions of the file are specified in the file header too.

  //#################                   End of initializations              ############


  // fourth argument is the pixels from the margins to the grid.
  int square_height = 25;
  int square_width = 25;
  int marginSize = 100;
  // drawGrid(marginSize,square_height,square_width,&fp);
  printf("hello1\n");
  drawSpiral( &fp,10);

  (void) fclose(fp);
  return EXIT_SUCCESS;
}
void drawGrid(int marginPixels, int sqHeight, int sqWidth, FILE ** file_pointer){
  int colsEnd = width - marginPixels;
  int rowsEnd = height - marginPixels;
  int i, j =0;
  printf("margin pixels = %d and rowsEnd =  %d and colsEnd = %d\n",marginPixels,rowsEnd,colsEnd );
  static unsigned char color[3]; // a pixel with RGB
  for (i = 0; i < height*3; i+=3)
  {
    for (j = 0; j < width*3; j+=3)
    {
        if ( i/3 < marginPixels || j/3 < marginPixels || j/3 > colsEnd || i/3 > rowsEnd){
          color[0] = 255;  /* red */
          color[1] = 255;  /* green */
          color[2] = 255;  /* blue */
          (void) fwrite(color, 1, 3, *file_pointer);
        }
        else{

          if ((j/3)%sqHeight != 0 && (i/3)%sqWidth != 0){
            color[0] = 255;  /* red */
            color[1] = 255;  /* green */
            color[2] = 255;  /* blue */
            (void) fwrite(color, 1, 3, *file_pointer);
          }
            else {
              color[0] = 0;  /* red */
              color[1] = 0;  /* green */
              color[2] = 0;  /* blue */
              (void) fwrite(color, 1, 3, *file_pointer);
            }

        }

    }
  }
}

void drawSpiral(FILE ** file_pointer, int rotations){
  float pi = 3.14159265359;
  double r = 0;
  int y,x;
  static unsigned char color[3]; // a pixel with RGB
  int i,j;

  std::array<std::array<int,height >,width > arrayFlags;
  printf("hello3\n");

  for (double degree = 0; degree < 360 * rotations; degree = degree + .15){
      r=r+.01;
      double radian = (degree / 180.0) * pi;
      x = (r * (cos(radian))) + height/2;
      y = r * (sin(radian)) + width/2 ;
      if ((  x>0 && y>0 ) && (x<height && y<width  ))
        arrayFlags[x][y] = 1;
  }

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++){
      if (arrayFlags[i][j] == 1) {
        color[0] = 255;  /* red */
        color[1] = 255;  /* green */
        color[2] = 255;  /* blue */
        (void) fwrite(color, 1, 3, *file_pointer);
      }
      else{
        color[0] = 0;  /* red */
        color[1] = 0;  /* green */
        color[2] = 0;  /* blue */
        (void) fwrite(color, 1, 3, *file_pointer);
      }
    }
  }

}
