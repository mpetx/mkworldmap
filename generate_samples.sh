#!/bin/zsh

cd $(dirname "$0")

WIDTH=3072
SAMPLE_DIR=samples

mkdir -p $SAMPLE_DIR

for projection in equirectangular mercator miller central-cylindrical sinusoidal mollweide azimuthal-equidistant aitoff orthographic orthographic-aitoff lambert-azimuthal-equal-area hammer gall-stereographic eckert-1 eckert-2 eckert-3 eckert-4 eckert-5 eckert-6 collignon
do
    echo "Generating $projection.jpg"
    ./bin/mkworldmap -p "$projection" -o "$SAMPLE_DIR/$projection.jpg" -w "$WIDTH"
done

for tuple in "lambert-cylindrical-equal-area 0" "behrmann 30" "hobo-dyer 37.5" "gall-peters 45" "tobler-square 55.653966546055335747516929098917204661637573065118"
do
    projection=$(echo $tuple | awk '{print $1}')
    latitude=$(echo $tuple | awk '{print $2}')
    echo "Generating $projection.jpg"
    ./bin/mkworldmap -p cylindrical-equal-area -o "$SAMPLE_DIR/$projection.jpg" --standard-latitude "$latitude" -w "$WIDTH"
done
