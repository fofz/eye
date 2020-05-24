all: bin/graph

test: test.ppm

bin/graph: src/graph.c include/dither.h | bin
	cc -w -O2 src/graph.c -o bin/graph -lm -Iinclude

bin/julia: src/julia.c | bin
	cc -w -O2 src/julia.c -o bin/julia -lm -Iinclude
	
bin/mandelbrot: src/julia.c | bin
	cc -w -O2 -D MANDELBROT src/julia.c -o bin/mandelbrot -lm
	
test.ppm: bin/graph bin/julia
	echo "P6 1024 1024 255 " > test.ppm; bin/julia -r 1024x1024 -s 3x3 -t -1.5+-1.5i -n 384 -b 1024 -c -0.757730701301672+0.121160627920417i | bin/graph -r 1024x1024 -p palette/flowers -s 1408 >> test.ppm
	
bin:
	mkdir bin
	
clean:
	rm -rf bin test.ppm
