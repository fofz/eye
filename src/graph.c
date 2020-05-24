#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "wdex.h"
#include "dither.h"

#define PSIZE 0x1000
vec2i size; 
int i, shift, opt;
char pfname[32]; 
FILE *pf;
uint8_t *ib;
rgb24 p[PSIZE], *ob;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:p:s:")) {
	case 'r': size = atovec2i(optarg, "x"); break;
	case 'p': strcpy(pfname, optarg); break;
	case 's': shift = atof(optarg); break;
	default: break;
	} while(opt != -1);
	
	/* load palette from file */
	if(strlen(pfname) == 0) return 2;
	pf = fopen(pfname, "rb"); 
	if(pf == NULL) return 2; 
	fread(p, 3, PSIZE, pf); 
	fclose(pf);
	
	/* size constants (for malloc, read, write, etc) */
	const size_t area = size.x * size.y, 
	             ibsize = area, 
	             obsize = area * 3;
	             
	/* allocate memory, read input, transform, write output */
	ib = malloc(ibsize); 
	if(ib == NULL) return 1; 
	read(0, ib, ibsize);
	ob = malloc(obsize); 
	if(ob == NULL) return 1;
	for(i = 0; i < area; ++i) {
		const int j = (int)ib[i] + shift % PSIZE;
		ob[i] = p[(j < 0 ? j + PSIZE : j)];
	}
	write(1, ob, obsize);
	return 0;
}
