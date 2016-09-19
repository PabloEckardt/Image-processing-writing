#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <sys/resource.h>

//Project by Pablo Eckardt.
//No licenses are associated with this code.

using namespace std;

/*
This is the resolution of a piece of paper at 300pixels per inch.
The actual size of the image can be calculated by dividing width of height
by the solution you are printing with. 300 being very common.
*/
int const width = 1250;
int const height = 1650;

// draws a grid, given a margin, and the dimensions of each square as well
// as the file pointer that will become the image.
void drawGrid(int marginPixels, int sqHeight, int sqWidth, FILE ** file_pointer);

//same idea but it draws a spiral given a number of rotations.
void drawSpiral(FILE ** file_pointer, int rotations);
//Draw spire function.

int main(void)
{
  // Instantiate a file  in binary mode. you will make one of these:
  // FILE *fp = fopen("grid.ppm", "wb"); /* b - binary mode */
  FILE *fp = fopen("spiral.ppm", "wb"); /* b - binary mode */

  // we write the header of the image that allows it to be decoded as a .ppm file
  // p6 is the magic number for the format. And 255 is the maximum understood value of the RGB pixels.
  //the dimensions of the file are specified here as well.

  (void) fprintf(fp, "P6\n%d %d\n255\n", width, height);

  // uncomment this if you want to make the grid.
  // int square_height = 25;
  // int square_width = 25;
  // int marginSize = 100; // image margin

  //chose one of the functions below. (spiral is set by default)
  // drawGrid(marginSize,square_height,square_width,&fp);
  // 10 rotations.
  drawSpiral( &fp,150);
  (void) fclose(fp);
  return EXIT_SUCCESS;
}
void drawGrid(int marginPixels, int sqHeight, int sqWidth, FILE ** file_pointer){
  int colsEnd = width - marginPixels;
  int rowsEnd = height - marginPixels;
  int i, j =0;
  // every pixel is an array with its RGB values.
  static unsigned char color[3];
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
  //radius distance where next pixel will be drawn.
  double r = 0;
  //cartesian representation of the pixel.
  int y,x;
  // a pixel with RGB

  unsigned char color[3];

  //iterators
  int i,j;
  // the current degree minus the rotations.
  int modDegrees = 0;
  // two dimensional array containing matrix of flags
  // indicating where pixels will be written. separating the process of
  //calculating locations and writting to the file.
  // flag matrix is a vector for two reasons. It will hold a very large
  // amount of data so its a requiredment for this data to be on the heap.

  vector<vector<int > > flagMatrix;
  flagMatrix.resize(height);
  for (size_t i = 0; i < flagMatrix.size(); i++) {
    flagMatrix[i].resize(width);
  }
  //constant degree delta
  float degreeRate = .005;
  // current degree of the writter.
  float currentDegree= 0;
  // populate flags inside the matrix.
  for (currentDegree ; currentDegree < 360 * rotations; currentDegree += degreeRate){
      // slowly increase the radious after printing every pixel to generate the spiral
      r=r+.00005;
      modDegrees = (int)currentDegree % 360;
      // convert from degrees to radians.
      double radian = (modDegrees / 180.0) * pi;
      // generate a cartesian x and y coordinates from a polar point made with
      // an angle and a radious.
      x = (r * (cos(radian))) + height/2;
      y = r * (sin(radian)) + width/2 ;
      // the spiral will try to get out of bounds and we need to filter out
      // all the points that are not within the bounds of the image.
      if ((x>0 && y>0) && (x<height && y<width)){
          flagMatrix[x][y] = 1;
      }
  }
    // once we have a matrix indicating where pixels should be
    // we start writting them on the file.
    // if the matrix finds a flag, write a black pixel otherwise a white one.
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++){
      if (flagMatrix[i][j] == 1) {
        color[0] = (150 + i + j)%255;  /* red */
        color[1] = (150 + i)%255;  /* green */
        color[2] = (150 + j)%255;  /* blue */
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
