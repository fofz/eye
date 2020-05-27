#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#ifdef BENCHMARK
#include <time.h>
#endif

#define WIDTH  240
#define HEIGHT 240
#define FRAMES 256
#define PSIZE  256

uint8_t p[PSIZE * 3], in[WIDTH * HEIGHT], out[WIDTH * HEIGHT * 3 * 256];
int i, x, y;

int main() {
	if(read(0, p, PSIZE * 3) < 0) return 1;
	if(read(0, in, WIDTH * HEIGHT) < 0) return 1;

	#ifdef BENCHMARK
	clock_t start = clock(), stop;
	#endif

	for(i = 0; i < FRAMES; ++i)
		for(y = 0; y < HEIGHT; ++y) 
			for(x = 0; x < WIDTH; ++x) { 
				const size_t k = ((size_t)in[y * WIDTH + x] + i) % PSIZE * 3, 
					         l = (i * WIDTH * HEIGHT + y * WIDTH + x) * 3;
				out[l] = p[k];
				out[l + 1] = p[k + 1];
				out[l + 2] = p[k + 2];		
			}
			
	#ifdef BENCHMARK
	stop = clock();
	fprintf(stderr, "t: %f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	#endif
				
	for(i = 0; i < FRAMES; ++i) {
		char str[32]; sprintf(str, "%03d.ppm", i);
		FILE *fout = fopen(str, "wb");
		fprintf(fout, "P6 240 240 255 ");
		fwrite(out + (i * WIDTH * HEIGHT * 3), 1, WIDTH * HEIGHT * 3, fout);
		fclose(fout);
	}

	return 0;
}
