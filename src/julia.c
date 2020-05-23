#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/* #define MANDELBROT */
#define SMOOTH

int width, height, x, y, i, imax, opt;
double zr, zi, cr, ci, t1, t2, t3, bailout,
       xscale, yscale, xoffset, yoffset, *ob;
char *k1;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:s:t:n:b:c:")) {
	case 'r':
		k1 = strtok(optarg, "x");
		if(k1 != NULL) width = atoi(k1); else return 3;
		k1 = strtok(NULL, ""); 
		if(k1 != NULL) height = atoi(k1); else return 3; 
		break;
	case 's':
		k1 = strtok(optarg, "x");
		if(k1 != NULL) xscale = atof(k1); else return 3;
		k1 = strtok(NULL, ""); 
		if(k1 != NULL) yscale = atof(k1); else return 3; 
		break;
	case 't':
		k1 = strtok(optarg, "+");
		if(k1 != NULL) xoffset = atof(k1); else return 3;
		k1 = strtok(NULL, "i"); 
		if(k1 != NULL) yoffset = atof(k1); else return 3; 
		break;
	case 'n': imax = atoi(optarg); break;
	case 'b': bailout = atof(optarg); break;
	case 'c':
		k1 = strtok(optarg, "+");
		if(k1 != NULL) cr = atof(k1); else return 3;
		k1 = strtok(NULL, "i"); 
		if(k1 != NULL) ci = atof(k1); else return 3; 
		break;
	default: break;
	} while(opt != -1);
	
	/* size constants (for malloc, write, etc) */
	const size_t area = width * height, obsize = area * sizeof(double);
	
	/* create data */
	ob = malloc(obsize);
	for(y = 0; y < height; ++y) for(x = 0; x < width; ++x) {
		zr = (double)x / width * xscale + xoffset; 
		zi = (double)y / height * yscale + yoffset;
		#ifdef MANDELBROT
		cr = zr; ci = zi;
		#endif
		for(i = 0; i < imax && (zr * zr) + (zi * zi) < bailout; ++i) {
			t1 = zr * (zr + zi);
			t2 = zr * (zi - zr); 
			t3 = zi * (zr + zi); 
			zr = t1 - t3 + cr;
			zi = t1 + t2 + ci;
		}
		#ifdef SMOOTH
		ob[x + y * width] = fmin(
			(double)i 
		  - log(log(sqrt((zr * zr) + (zi * zi))) / log(bailout))
		  / log(2),
		  	imax
		) / imax;
		#else
		ob[x + y * width] = (double)i / imax;
		#endif
	}
	
	/* write output */
	write(1, ob, obsize);
	return 0;
}
