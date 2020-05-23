all: bin/julia bin/mandelbrot bin/graph

test: j.data j.ppm

bin/julia: src/julia.c | bin
	cc -w -O2 src/julia.c -o bin/julia -lm
	
bin/mandelbrot: src/julia.c | bin
	cc -w -O2 -D MANDELBROT src/julia.c -o bin/mandelbrot -lm
	
bin/graph: src/graph.c include/dither.h | bin
	cc -w -O2 src/graph.c -o bin/graph -lm -Iinclude

j.data: bin/julia
	bin/julia -w 1024 -h 1024 -n 384 -b 1024 -x 3 -y 3 -u -1.5 -v -1.5 -r -0.757730701301672 -i 0.121160627920417 > j.data
	
j.ppm: bin/graph j.data
	bin/graph -w 1024 -h 1024 -p palette/flowers -s 0 -r 8192 < j.data > j.ppm
	
bin:
	mkdir bin
	
clean:
	rm -rf bin