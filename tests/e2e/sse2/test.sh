#!/bin/sh
gcc -msse2 movaps.c -o test_movaps
echo movaps
./test_movaps

echo movss
gcc -msse2 movss.c -o test_movss
./test_movss

