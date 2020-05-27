mkdir frames;
for i in {0..31}; 
do (echo "P6 240 240 255" > frames/$(printf "%03d" $i).ppm; cat palette.data res/image/lenna.data | bin/graph -r 240x240 -n 256 -s $((i * 8)) >> frames/$(printf "%03d" $i).ppm); 
done; 
montage frames/*.ppm -tile 8x4 -geometry 160x160+0+0 banner.jpg;
convert -delay 4 frames/*.ppm animation.gif;
