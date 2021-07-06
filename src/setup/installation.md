# Installation

## Windows

TODO: Package everything in a nice to install zip file, else it's a big mess for your users.

## Linux

You'll need to install the following tools, everything can be newer then the specified versions, specified versions are minimal known working versions.
* python 3.6
* sdcc 4.1.0
* rgbds 0.5.1

Assuming a debian based system, you'll need the following steps:

```sh
# Install package from the package manager
apt-get install python3 build-essential bison libboost-dev libpng-dev

# Get and build sdcc
wget https://sourceforge.net/projects/sdcc/files/sdcc/4.1.0/sdcc-src-4.1.0.tar.bz2/download -O sdcc-src.tar.bz2
tar -xjvf sdcc-src.tar.bz2
cd sdcc
./configure --disable-pic14-port  --disable-pic16-port
make -j$(nproc)
sudo make install
cd ..

# Get and build rgbds
wget https://github.com/gbdev/rgbds/releases/download/v0.5.1/rgbds-0.5.1.tar.gz -O rgbds-src.tar.gz
tar -xzvf rgbds-src.tar.gz
cd rgbds-0.5.1
./configure
make
sudo make install
cd ..

```

## MacOS

Seriously. No clue, follow Linux installation mostly, I guess.