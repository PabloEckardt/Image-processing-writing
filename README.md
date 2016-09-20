##-Pablo Eckardt

##PPM Image generator.

This repo is a sort of a thought experiment gone too far, and my introduction to image processing.
I learned a lot about how C++ data structures behave when they hold unconventionally large amounts of data. And also the mysterious errors that arise from not knowing that. 


##How to run it:
- Compile using Makefile provided by calling make on the directory of the project.

- Run using ./generatepic and your ppm file should be in the folder.

- Inside the main function you can select between two different images you can create.

Here is the output image you get when you build the spiral:

![alt tag](https://github.com/PabloEckardt/Image-processing-writing/blob/master/spiralDemoCropped.png)


  

##A brief exaplanation of how PPM images work:


.ppm images are images that are very easy to understand, and code for.

ppm, pgm, and pbm are all are encoded in this standard:


- [Magic number indicating subclass of format] \n

- [Bit color configuration ] \n

- [#Tags with comments starting with #] \n

- [Image dimensions] \n

- image in binary . . . .



Wikipedia makes a perfectly clear example:


This is an example bitmap of the letter "J"
''''
-P1

-6 10

0 0 0 0 1 0

0 0 0 0 1 0

0 0 0 0 1 0

0 0 0 0 1 0

0 0 0 0 1 0

0 0 0 0 1 0

1 0 0 0 1 0

0 1 1 1 0 0

0 0 0 0 0 0

0 0 0 0 0 0
''''

more information here:

https://en.wikipedia.org/wiki/Netpbm_format


NOTE: PPM is a dated format solution. Its just programatically straightforward and simple.

I do not recommend using this extremely inneficient format unless you want to start learning about image
processing. PPM files by default have no compression.
