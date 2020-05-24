#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "wdex.h"
#include "fire.h"

vec2i size; 
int i, opt;
uint8_t shift, *ib, *ob;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:s:")) {
	case 'r': size = atovec2i(optarg, "x"); break;
	case 's': shift = atoi(optarg); break;
	default: break;
	} while(opt != -1);
	
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
		const uint8_t k = ib[i] + shift;
		ob[i * 3    ] = p[k * 3    ];
		ob[i * 3 + 1] = p[k * 3 + 1];
		ob[i * 3 + 2] = p[k * 3 + 2];
	}
	write(1, ob, obsize);
	return 0;
}
