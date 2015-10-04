#!/bin/sh

TROKKO_PATH=$HOME/Projects/trokko
TROKKO_BUILD=$TROKKO_PATH/build
TROKKO_TOOLS=$TROKKO_PATH/tools

echo "binutils"
cd $TROKKO_BUILD
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.19.1.tar.bz2
tar jxvf binutils-2.19.1.tar.bz2
cd $TROKKO_BUILD/binutils-2.19.1
./configure --target=h8300-elf \
            --disable-nls \
            --disable-werror \
            --prefix=$TROKKO_TOOLS
make
make install

echo "gcc"
cd $TROKKO_BUILD
curl -O http://ftp.gnu.org/gnu/gcc/gcc-3.4.6/gcc-3.4.6.tar.gz
tar xvzf gcc-3.4.6.tar.gz
cd $TROKKO_BUILDa/gcc-3.4.6
./configure --target=h8300-elf \
            --disable-nls \
            --disable-threads \
            --disable-shared \
            --disable-werror \
            --enable-languages=c \
            --prefix=$TROKKO_TOOLS
cd $TROKKO_BUILD/gcc-3.4.6/gcc/config/h8300
mv $TROKKO_BUILD/gcc_for_64bit.patch $TROKKO_BUILD/gcc-3.4.6/gcc/config/h8300
patch < 64bit.patch
cd $TROKKO_BUILD/gcc-3.4.6
make
make install

