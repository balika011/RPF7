#include <Windows.h>
#include <stdio.h>
#include <lzx.h>

#include "platforms.h"

extern unsigned char xbox360key[32];

unsigned char* xbox360::getAESkey()
{
	return xbox360key;
}

void xbox360::decompressBuffer(unsigned char* in, unsigned char* out, int insize, int outsize)
{
	struct LZXstate* lzx_state = LZXinit(16);

	int outputSize = 0;

	int offset = 0;

	while (outputSize != outsize)
	{
		int tmpoutputSize = 0;
		int tmpinputSize = 0;

		if (*(byte*) (in + offset) == 0xff)
		{
			tmpoutputSize = *(byte*) (in + offset + 1) << 8;
			tmpoutputSize |= *(byte*) (in + offset + 2);
			tmpinputSize = *(byte*) (in + offset + 3) << 8;
			tmpinputSize |= *(byte*) (in + offset + 4);

			offset += 5;
		}
		else
		{
			tmpoutputSize = 0x8000;
			tmpinputSize = (*(byte*) (in + offset) << 8) | *(byte*) (in + offset + 1);
			if (tmpinputSize == 0)
				break;
			offset += 2;
		}

		int res = LZXdecompress(lzx_state, in + offset, out + outputSize, tmpinputSize, tmpoutputSize);
		if (res != 0)
		{
			printf("LZXdecompress returned with: %i\n", res);
			memset(out, 0, outsize);
			break;
		}

		offset += tmpinputSize;
		outputSize += tmpoutputSize;
	}

	LZXteardown(lzx_state);
}