# 7seg
Control one-digit 7-segment display with a Raspberry Pi Pico

## Build
_Prerequisites: Cmake_

Install `pico-sdk` as a submodule
```sh
git submodule init
git submodule update
```

Generate .uf2 binary for Pico
```sh
mkdir build && cd build && cmake ..
make
```
