#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "dither.h"

#define PSIZE 0x1000
int width, height, i, opt; double iscale, ishift, *ib;
struct { uint8_t r, g, b; } p[PSIZE], *ob;
char pfname[32], h[32], *k1; FILE *pf;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:p:s:t:")) {
	case 'r':
		k1 = strtok(optarg, "x");
		if(k1 != NULL) width = atoi(k1); else return 3;
		k1 = strtok(NULL, ""); 
		if(k1 != NULL) height = atoi(k1); else return 3; 
		break;
	case 'p': strcpy(pfname, optarg); break;
	case 's': iscale = atof(optarg); break;
	case 't': ishift = atof(optarg); break;
	default: break;
	} while(opt != -1);
	
	/* load palette from file */
	if(strlen(pfname) == 0) return 2;
	pf = fopen(pfname, "rb"); 
	if(pf == NULL) return 2; 
	fread(p, 3, PSIZE, pf); 
	fclose(pf);
	
	/* size constants (for malloc, read, write, etc) */
	const size_t area = width * height, 
	             ibsize = area * sizeof(double), 
	             obsize = area * 3;
	             
	/* read input */
	ib = malloc(ibsize); if(ib == NULL) return 1; read(0, ib, ibsize);
	
	/* transform input */
	ob = malloc(obsize); if(ob == NULL) return 1;
	for(i = 0; i < area; ++i)
		ob[i] = p[
			(size_t)(ib[i] * iscale + ishift + dv[(i % 17 + i / 23) % DVSIZE])
		  % PSIZE
		];
		
	/* write ppm file header followed by output */
	sprintf(h, "P6 %d %d 255 ", width, height);
	write(1, h, strlen(h));	write(1, ob, obsize);
}
