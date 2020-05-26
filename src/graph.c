#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

vec2i size; 
int i, opt; 
size_t psize, pshift; 
uint8_t *p, *in, *out;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:n:s:")) {
	case 'r': size = atovec2i(optarg, "x"); break;
	case 'n': psize = atoi(optarg); break;
	case 's': pshift = atoi(optarg); break;
	default: break;
	} while(opt != -1);
	             
	/* allocate memory, read palette, read input, transform, write output */
	p = malloc(3 * psize); if(p == NULL) return 2;
	if(read(0, p, 3 * psize) < 0) return 3;
	in = malloc(size.x * size.y); 
	if(in == NULL) return 4; 
	if(read(0, in, size.x * size.y) < 0) return 5;
	out = malloc(3 * size.y * size.y); 
	if(out == NULL) return 6;
	for(i = 0; i < size.x * size.y; ++i) {
		const size_t k = ((size_t)in[i] + pshift) % psize;
		out[i * 3    ] = p[k * 3    ];
		out[i * 3 + 1] = p[k * 3 + 1];
		out[i * 3 + 2] = p[k * 3 + 2];
	}
	if(write(1, out, 3 * size.x * size.y) < 0) return 7;
	return 0;
}
