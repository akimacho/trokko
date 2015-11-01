trokko
====

Embedded operating system based on KOZOS & uITRON

## Target board

* H8/3069F

## Requirement

* OS X 10.9+
* [binutils-2.19.1](http://www.gnu.org/software/binutils/)
* [gcc-3.4.6](https://gcc.gnu.org)
* [kz_h8write](https://osdn.jp/projects/kz-h8write/)

For serial communication

* cu or screen

For file-transmission on XMODEM protocol

* lrzsz

## Setup build-tools

Directory tree is following:

```
trokko
├── build # for building tools
├── etc   # utils
├── src   # source code of OS & bootstrap
└── tools # tools
```

```
$ git clone https://github.com/akimacho/hiyoko.git
$ cd trokko
$ mkdir build tools
```

export PATH

```
export PATH=to/your/tools/bin:$PATH
```

in `build` directory

```
$ curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.19.1.tar.bz2
$ tar jxvf binutils-2.19.1.tar.bz2
$ curl -O http://ftp.gnu.org/gnu/gcc/gcc-3.4.6/gcc-3.4.6.tar.gz
$ tar xvzf gcc-3.4.6.tar.gz
```

### Install binutils

in `build/binutils-2.19.1` directory

```
$ ./configure \ 
        --target=h8300-elf \ 
        --disable-nls \ 
        --disable-werror \
        --prefix=to/your/tools
$ make
$ make install
```

### Install gcc

in `build/gcc-3.4.6`

```
$ ./configure \
        --target=h8300-elf \
        --disable-nls \ 
        --disable-threads \ 
        --disable-shared \ 
        --disable-werror \ 
        --enable-languages=c \ 
        --prefix=to/your/tools
```

in `build/gcc-3.4.6/gcc/config/h8300` directory

```
$ curl -O https://raw.githubusercontent.com/akimacho/trokko/master/etc/gcc_for_64bit.patch
$ patch < gcc_for_64bit.patch
Hunk #1 succeeded at 52 (offset -31 lines).
Hunk #2 succeeded at 368 with fuzz 2 (offset -142 lines).
Hunk #3 succeeded at 397 with fuzz 1 (offset -149 lines). 
```

in `build/gcc-3.4.6`

```
$ make
$ make install
```

### Install kz_h8write

in `build`

```
$ git clone http://scm.osdn.jp/gitroot/kz-h8write/kz_h8write.git
$ cd kz_h8write/src
$ make
$ cp kz_h8write to/your/tools
```

Thas's all!

## Author

* [akimacho](https://github.com/akimacho)

