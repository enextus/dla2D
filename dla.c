#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "paulslib.h"
#include "bitmaplib.h"

/*
	Very basic (brute force) 2D DLA code
	Seed in the center, random points added round the rim
	Written for simplicity not speed or elegance
	Paul Bourke

	The two usual ways of improving performance are
	- Keep an internal state (2D array of occupied sites) rather than checking the image each time.
	- Only introduce points at a radius just bigger than the current structure.
	- Don't let points wander too far away.
	All of the above will dramatically improve speed.

	Note this does not implement the so called "stickiness" algorithm.
*/

// Image size, radius of "world"
#define R 1000

// Number of points to introduce
#define N 1000

int main(int argc,char **argv)
{
	int i,j,n,ix,iy,ixnew,iynew;
	int found;
	int counter = 0;
	time_t secs;
	double theta;
	FILE *fptr;
	BITMAP4 *image = NULL,white = {255,255,255,0},black = {0,0,0,0};
	BITMAP4 v;
	char fname[64];

	// Create and initialise the final image
	image = Create_Bitmap(R,R);
	Erase_Bitmap(image,R,R,white);
	Draw_Pixel(image,R,R,R/2,R/2,black);

	// Set the random number seeds based upon the current time
	time(&secs);
	srand((int)secs);
	srand48((int)secs);

	for (n=0;n<N;n++) {
		theta = drand48() * TWOPI;
		ix = R/2 + 0.5 * (R-2) * cos(theta);
      iy = R/2 + 0.5 * (R-2) * sin(theta);
		fprintf(stderr,"Seed: %d %d %d\n",n,ix,iy);

		// Repeat until we hit another pixel
		for (;;) {

			// Move in a random direction
			ixnew = ix + (rand() % 3) - 1;
			if (ixnew > 0 && ixnew < R-1)
				ix = ixnew;
			iynew = iy + (rand() % 3) - 1;
         if (iynew > 0 && iynew < R-1)
            iy = iynew;

			// Have we struck an existing point?
			found = FALSE;
			for (i=-1;i<=1;i++) {
				for (j=-1;j<=1;j++) {
					v = Get_Pixel(image,R,R,ix+i,iy+j);
					if (v.r < 128) {
						found = TRUE;
						break;
					}
				}
				if (found)
					break;
			}
			if (found)
				break;
		}

		Draw_Pixel(image,R,R,ix,iy,black);

		// Save intermediate images
		if (n > 0 && n % (N/10) == 0) {
			sprintf(fname,"dla_%02d.tga",counter++);
   		if ((fptr = fopen(fname,"w")) == NULL) {
   		   fprintf(stderr,"Failed to open output file\n");
   		} else {
   			Write_Bitmap(fptr,image,R,R,12);
   			fclose(fptr);
			}
		}
	}

	// Write the image to a TGA file
	if ((fptr = fopen("dla.tga","w")) == NULL) {
		fprintf(stderr,"Failed to open output file\n");
	} else {
		Write_Bitmap(fptr,image,R,R,12);
		fclose(fptr);
	}

	exit(0);
}

