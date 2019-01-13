#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/spoomy.png
ICON_DST=../../src/qt/res/icons/spoomy.ico
convert ${ICON_SRC} -resize 16x16 spoomy-16.png
convert ${ICON_SRC} -resize 32x32 spoomy-32.png
convert ${ICON_SRC} -resize 48x48 spoomy-48.png
convert spoomy-16.png spoomy-32.png spoomy-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/zumy_testnet.png
ICON_DST=../../src/qt/res/icons/zumy_testnet.ico
convert ${ICON_SRC} -resize 16x16 spoomy-16.png
convert ${ICON_SRC} -resize 32x32 spoomy-32.png
convert ${ICON_SRC} -resize 48x48 spoomy-48.png
convert spoomy-16.png spoomy-32.png spoomy-48.png ${ICON_DST}
rm spoomy-16.png spoomy-32.png spoomy-48.png
