all: bin/graph

test: test.ppm

bin/graph: src/graph.c include/wdex.h include/fire.h | bin
	cc -O2 src/graph.c -o bin/graph -lm -Iinclude
	
bin/dither: src/dither.c include/wdex.h | bin
	cc -O2 src/dither.c -o bin/dither -Iinclude

bin/julia: src/julia.c include/wdex.h | bin
	cc -O2 src/julia.c -o bin/julia -lm -Iinclude
	
test.ppm: bin/graph bin/julia bin/dither
	echo "P6 1024 1024 255" > test.ppm; bin/julia -r 1024x1024 -s 3x3 -t -1.5+-1.5i -n 384 -b 1024 -c -0.757730701301672+0.121160627920417i | bin/dither -r 1024x1024 | bin/graph -r 1024x1024 -s 107 >> test.ppm
	
bin:
	mkdir bin
	
clean:
	rm -rf bin test.ppm
