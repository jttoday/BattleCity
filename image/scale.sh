for img in `ls`; do convert -resize 50%x50% $img small/$img; done
