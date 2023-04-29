#! /bin/sh

cd libpngloader
./autogen.sh
cd ..
cd liblitejson
./autogen.sh
cd ..
mkdir -p "./build"
autoreconf --force --install
