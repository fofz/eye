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
vec2i size; int i, opt; uint8_t *ib; size_t shift;
struct { uint8_t r, g, b; } p[PSIZE], *ob;
char pfname[32], h[32], *k1; FILE *pf;

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
	             
	ib = malloc(ibsize); if(ib == NULL) return 1; read(0, ib, ibsize);
	ob = malloc(obsize); if(ob == NULL) return 1;
	for(i = 0; i < area; ++i) ob[i] = p[((size_t)ib[i] + shift) % PSIZE];
	write(1, ob, obsize);
	return 0;
}
