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
	             
	/* allocate memory, read input, transform, write output */
	ib = malloc(size.x * size.y); 
	if(ib == NULL) return 1; 
	if(read(0, ib, size.x * size.y) < 0) return 1;
	ob = malloc(3 * size.y * size.y); 
	if(ob == NULL) return 1;
	for(i = 0; i < size.x * size.y; ++i) {
		const uint8_t k = ib[i] + shift;
		ob[i * 3    ] = p[k * 3    ];
		ob[i * 3 + 1] = p[k * 3 + 1];
		ob[i * 3 + 2] = p[k * 3 + 2];
	}
	if(write(1, ob, 3 * size.x * size.y) < 0) return 1;
	return 0;
}
