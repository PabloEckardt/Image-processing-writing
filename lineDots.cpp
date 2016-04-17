#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <array>
#include <sys/resource.h>

//to do make a header and functions file and update the makefile
// upgrade make spiral to make it round numbers properly and make it user friendlu
// upgrade grid by delimiting possible inputs. It should only take the margin and width of individual squares
// in milimiters or inches
// implement scan function.That finds a black square, measures its diameter. creates a new array with only
// information of the new picture the size of the black square where the new object is in the center and there
// are no borders for the object.
// for the future, implement a rotate function that rotates an image.
// for the future implement a generate image based off variations of a single image an a user input (or simulated user input)


using namespace std;

int const width = 2500;
int const height = 3300;

void drawSpiral( array<array< int, width>, height> & arrayFlag,int mod1, int mod2){
  float pi = 3.14159265359;
  double r = 0;
  int y,x;
  float multiplier = 2; // number of complete rotations

  for (double degree = 0; degree < 32000; degree = degree + .15){
      r=r+.01;
     double radian = (degree / 180.0) * pi;
     //there needs to be smarter rounding in this case to fix the jittery stuff
     x = (r * (cos(radian))) + height/2 +mod1;
     y = r * (sin(radian)) + width/2 +mod2;
    //if arrays function wrap correctly from center then add the point to the array.
    if ((x>0 && y > 0 ) && (x < height && y < width)){
      // printf("angle is %d x is %d y is %d \n",radian, x, y);
    arrayFlag[x][y] = 1;
    // printf( " is   %d \n",arrayFlag[x][y]);
    }
  }
}
void drawGrid(array<array< int, width>, height> &arrayflag, int mod1, int mod2,int mod3){
//mod1 here is the number of rows
//mod2 is the number of columns.
//mod3 is the margin for all the sides
int cols = height - mod3;
int rows = width - mod3;

  int fill =1;
    for (size_t y = mod3; y < cols; y++) {
        if(y%30==0){
          fill=1;
        }
        else{fill = 0;}
      arrayflag[y][mod3] = 1;
      for (size_t x = mod3; x < rows; x++) {
          if(!fill){
            x += 30;
            arrayflag[y][x] = 1;
        }
        else if (x <= width-mod3/2){arrayflag[y][x] = 1;}

      }
  }

}

int main(void)
{
  // printf("memorytest\n" );
  const int dimx = 2500, dimy = 3300;
  int i, j;
  FILE *fp = fopen("grid.ppm", "wb"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);

  array<array< int, width>, height> *arrayFlag = new array<array< int, width>, height>; // allocate the vector on the heap.

  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      (*arrayFlag)[i][j] =0;
    }
  }

  (drawGrid(*arrayFlag,1,2,90)); //mod3 has to be a multiple of the pixel width and size of the squares.
  // (drawSpiral( *arrayFlag,1,1));
  // (drawSpiral( *arrayFlag,-1,1));
  // (drawSpiral( *arrayFlag,-1,-1));
  // (drawSpiral( *arrayFlag,1,-1));

  for (j = 0; j < dimy; ++j)
  {
    for (i = 0; i < dimx; ++i)
    {
      // printf("[%d]",pixels[i][j]);
      static unsigned char color[3];
      if ((*arrayFlag)[j][i]){
        color[0] = 0;  /* red */
        color[1] = 0;  /* green */
        color[2] = 0;  /* blue */
      (void) fwrite(color, 1, 3, fp);}
      else {
        color[0] = 255;  /* red */
        color[1] = 255;  /* green */
        color[2] = 255;  /* blue */
      (void) fwrite(color, 1, 3, fp);
      }
    }
    // printf("\n");
  }
  (void) fclose(fp);
  return EXIT_SUCCESS;
}
