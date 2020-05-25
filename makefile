all: bin/palette bin/graph bin/dither bin/dtou16 bin/normalize bin/julia

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
	
bin:
	mkdir bin
	
clean:
	rm -rf bin
