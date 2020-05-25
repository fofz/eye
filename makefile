all: bin/palette bin/graph bin/dither bin/dtou16 bin/normalize bin/julia

test: res/test.data res/test.ppm

bin/palette: src/palette.c include/wdex.h | bin
	cc -O2 src/palette.c -o bin/palette -lm -Iinclude

bin/graph: src/graph.c include/wdex.h include/fire.h | bin
	cc -O2 src/graph.c -o bin/graph -lm -Iinclude
	
bin/dither: src/dither.c include/wdex.h | bin
	cc -O2 src/dither.c -o bin/dither -Iinclude
	
bin/dtou16: src/dtou16.c include/wdex.h | bin
	cc -O2 src/dtou16.c -o bin/dtou16 -Iinclude
	
bin/normalize: src/normalize.c include/wdex.h | bin
	cc -O2 src/normalize.c -o bin/normalize -Iinclude

bin/julia: src/julia.c include/wdex.h | bin
	cc -O2 src/julia.c -o bin/julia -lm -Iinclude
	
res/test.data: bin/dither bin/dtou16 bin/normalize bin/julia bin/palette | res
	bin/palette -n 256 > res/test.data; bin/julia -r 1024x1024 -s 3x3 -t -1.5+-1.5i -n 256 -b 256 -c -0.757730701301672+0.121160627920417i | bin/normalize -r 1024x1024 | bin/dtou16 -r 1024x1024 | bin/dither -r 1024x1024 >> res/test.data
	
res/test.ppm: bin/graph res/test.data | res
	echo "P6 1024 1024 255" > res/test.ppm; bin/graph -r 1024x1024 -n 256 -s 107 < res/test.data >> res/test.ppm
	
bin:
	mkdir bin
	
res:
	mkdir res
	
clean:
	rm -rf bin res test.ppm
