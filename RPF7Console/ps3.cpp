#include <Windows.h>
#include <stdio.h>
#include <deflate.h>

#include "platforms.h"

extern unsigned char ps3key[32];

unsigned char* ps3::getAESkey()
{
	return ps3key;
}

void ps3::decompressBuffer(unsigned char* in, unsigned char* out, int insize, int outsize)
{
	inflate(in, out, insize, outsize);
}