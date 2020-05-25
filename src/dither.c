#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include "wdex.h"

vec2i size;
int i, opt;
uint16_t *in; uint8_t *out;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "r:")) {
	case 'r': size = atovec2i(optarg, "x"); break;
	default: break;
	} while(opt != -1);
	
	in = malloc(2 * size.x * size.y); if(in == NULL) return 1;
	out = malloc(2 * size.x * size.y); if(out == NULL) return 2;
	if(read(0, in, 2 * size.x * size.y) < 0) return 3;
	for(i = 0; i < size.x * size.y; ++i)
		out[i] = (in[i] / 0x100 + (rand() % 0x100 < in[i] % 0x100 ? 1 : 0));
	if(write(1, out, size.x * size.y) < 0) return 4;
	return 0;
}
