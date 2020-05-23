#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "wdex.h"

/* #define MANDELBROT */
#define SMOOTH

vec2i size; int x, y, i, imax, opt;
vec2d scale; compd z, c, offset; double t1, t2, t3, bailout, *ob;
char *k1;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:s:t:n:b:c:")) {
	case 'r': size = atovec2i(optarg, "x"); break;
	case 's': scale = atovec2d(optarg, "x"); break;
	case 't': offset = atocompd(optarg, "+"); break;
	case 'n': imax = atoi(optarg); break;
	case 'b': bailout = atof(optarg); break;
	case 'c': c = atocompd(optarg, "+"); break;
	default: break;
	} while(opt != -1);
	
	/* size constants (for malloc, write, etc) */
	const size_t area = size.x * size.y, obsize = area * sizeof(double);
	
	/* create data */
	ob = malloc(obsize);
	for(y = 0; y < size.y; ++y) for(x = 0; x < size.x; ++x) {
		z.re = (double)x / size.x * scale.x + offset.re; 
		z.im = (double)y / size.y * scale.y + offset.im;
		#ifdef MANDELBROT
		c = z;
		#endif
		for(i = 0; i < imax && (z.re * z.re) + (z.im * z.im) < bailout; ++i) {
			t1 = z.re * (z.re + z.im);
			t2 = z.re * (z.im - z.re); 
			t3 = z.im * (z.re + z.im); 
			z.re = t1 - t3 + c.re;
			z.im = t1 + t2 + c.im;
		}
		#ifdef SMOOTH
		ob[x + y * size.x] = fmin(
			(double)i 
		  - log(log(sqrt((z.re * z.re) + (z.im * z.im))) / log(bailout))
		  / log(2),
		  	imax
		) / imax;
		#else
		ob[x + y * size.x] = (double)i / imax;
		#endif
	}
	
	/* write output */
	write(1, ob, obsize);
	return 0;
}
