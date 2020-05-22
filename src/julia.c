#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

/* #define MANDELBROT */
#define SMOOTH

int width, height, x, y, i, imax, opt;
double zr, zi, cr, ci, t1, t2, t3, bailout,
       xscale, yscale, xoffset, yoffset, *ob;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "w:h:x:y:u:v:n:b:r:i:")) {
	case 'w': width = atoi(optarg); break;
	case 'h': height = atoi(optarg); break;
	case 'x': xscale = atof(optarg); break;
	case 'y': yscale = atof(optarg); break;
	case 'u': xoffset = atof(optarg); break;
	case 'v': yoffset = atof(optarg); break;
	case 'n': imax = atoi(optarg); break;
	case 'b': bailout = atof(optarg); break;
	case 'r': cr = atof(optarg); break;
	case 'i': ci = atof(optarg); break;
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
