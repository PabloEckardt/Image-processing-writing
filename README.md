-Pablo Eckardt

PPM Image generator.

In this repo I will just play with this idea and generate
a few images for fun.

NOTE: PPM is a dated format solution. Its just programatically straightforward and simple.

I do not recommend using this extremely inneficient format unless you want to start learning about image
processing. PPM files by default have no compression.

A brief exaplanation of how they work:

.ppm images are images that are very easy to understand, and code for.

ppm, pgm, and pbm are all are encoded in this standard:


-[magic number indicating subclass of format] \n
-[Bit color configuration ] \n
-[#Tags with comments starting with #] \n
-[image dimensions] \n

- image in binary . . . .



Wikipedia makes a perfectly clear example:
This is an example bitmap of the letter "J"

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


more information here:

https://en.wikipedia.org/wiki/Netpbm_format