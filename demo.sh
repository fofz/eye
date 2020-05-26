bin/palette -n 256 > palette.data; 
bin/julia -r 240x240 -s 3x3 -t -1.5+-1.5i -n 256 -b 256 -c -0.757730701301672+0.121160627920417i | bin/normalize -r 240x240 | bin/dtou16 -r 240x240 | bin/dither -r 240x240 > julia.data;
mkdir frames;
for i in {0..31}; 
do (echo "P6 240 240 255" > frames/$(printf "%03d" $i).ppm; cat palette.data julia.data | bin/graph -r 240x240 -n 256 -s $((i * 8)) >> frames/$(printf "%03d" $i).ppm); 
done; 
montage frames/*.ppm -tile 8x4 -geometry 80x80+0+0 banner.jpg;
convert -delay 4 frames/*.ppm animation.gif;
