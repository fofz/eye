#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include "wdex.h"

vec2i size;
int i, opt;
double *in; uint16_t *out;

int main(int argc, char **argv) {
	/* parse arguments */
	while((opt = getopt(argc, argv, "r:")) != -1)
		if(opt == 'r') size = atovec2i(optarg, "x");
	
	in = malloc(sizeof(double) * size.x * size.y); if(in == NULL) return 1;
	out = malloc(2 * size.x * size.y); if(out == NULL) return 2;
	if(read(0, in, sizeof(double) * size.x * size.y) < 0) return 3;
	for(i = 0; i < size.x * size.y; ++i) out[i] = in[i] * 0xffff;
	if(write(1, out, 2 * size.x * size.y) < 0) return 4;
	return 0;
}
