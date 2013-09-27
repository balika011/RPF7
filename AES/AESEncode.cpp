#include <Windows.h>
#include "AES.h"
#include "AESInterns.h"

// padding the input to 16bytes multiply
int padding(void * pToPad,int iSize)
{
	int iRest = iSize & 15;
	if( iRest )
	{
		int iCount = 16-iRest;

		while(iCount--)
		{
			((uint8*)pToPad)[iSize++]=0;
		}
	}
	return iSize;
}

#define AES_ENCRYPT_BLOCK_32	\
	a1 = TestTable1[(byte) local_temp[0]]; \
	a4 = TestTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a3 = TestTable3[(byte) local_temp[0]]; \
	a2 = TestTable4[((regs *) &local_temp[0])->ah]; \
	\
	local_temp[0] = local_temp[1]; \
	a2 ^= TestTable1[(byte) local_temp[0]]; \
	a1 ^= TestTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a4 ^= TestTable3[(byte) local_temp[0]]; \
	a3 ^= TestTable4[((regs *) &local_temp[0])->ah]; \
	\
	local_temp[0] = local_temp[2]; \
	a3 ^= TestTable1[(byte) local_temp[0]]; \
	a2 ^= TestTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a1 ^= TestTable3[(byte) local_temp[0]]; \
	a4 ^= TestTable4[((regs *) &local_temp[0])->ah]; \
	\
	local_temp[0] = local_temp[3]; \
	a4 ^= TestTable1[(byte) local_temp[0]]; \
	a3 ^= TestTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a2 ^= TestTable3[(byte) local_temp[0]]; \
	a1 ^= TestTable4[((regs *) &local_temp[0])->ah];

void AES_ENCRYPT(uint32 * pInput, uint32 * pOutput, uint32 * AesEncKey)
{
	register uint32 a1, a2, a3, a4;
	ALIGN uint32 local_temp[4];

	local_temp[0] = pInput[0] ^ AesEncKey[0];
	local_temp[1] = pInput[1] ^ AesEncKey[1];
	local_temp[2] = pInput[2] ^ AesEncKey[2];
	local_temp[3] = pInput[3] ^ AesEncKey[3];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[4];
	local_temp[1] = a2^AesEncKey[5];
	local_temp[2] = a3^AesEncKey[6];
	local_temp[3] = a4^AesEncKey[7];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[8];
	local_temp[1] = a2^AesEncKey[9];
	local_temp[2] = a3^AesEncKey[10];
	local_temp[3] = a4^AesEncKey[11];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[12];
	local_temp[1] = a2^AesEncKey[13];
	local_temp[2] = a3^AesEncKey[14];
	local_temp[3] = a4^AesEncKey[15];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[16];
	local_temp[1] = a2^AesEncKey[17];
	local_temp[2] = a3^AesEncKey[18];
	local_temp[3] = a4^AesEncKey[19];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[20];
	local_temp[1] = a2^AesEncKey[21];
	local_temp[2] = a3^AesEncKey[22];
	local_temp[3] = a4^AesEncKey[23];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[24];
	local_temp[1] = a2^AesEncKey[25];
	local_temp[2] = a3^AesEncKey[26];
	local_temp[3] = a4^AesEncKey[27];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[28];
	local_temp[1] = a2^AesEncKey[29];
	local_temp[2] = a3^AesEncKey[30];
	local_temp[3] = a4^AesEncKey[31];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[32];
	local_temp[1] = a2^AesEncKey[33];
	local_temp[2] = a3^AesEncKey[34];
	local_temp[3] = a4^AesEncKey[35];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[36];
	local_temp[1] = a2^AesEncKey[37];
	local_temp[2] = a3^AesEncKey[38];
	local_temp[3] = a4^AesEncKey[39];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[40];
	local_temp[1] = a2^AesEncKey[41];
	local_temp[2] = a3^AesEncKey[42];
	local_temp[3] = a4^AesEncKey[43];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[44];
	local_temp[1] = a2^AesEncKey[45];
	local_temp[2] = a3^AesEncKey[46];
	local_temp[3] = a4^AesEncKey[47];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[48];
	local_temp[1] = a2^AesEncKey[49];
	local_temp[2] = a3^AesEncKey[50];
	local_temp[3] = a4^AesEncKey[51];

	AES_ENCRYPT_BLOCK_32;

	local_temp[0] = a1^AesEncKey[52];
	local_temp[1] = a2^AesEncKey[53];
	local_temp[2] = a3^AesEncKey[54];
	local_temp[3] = a4^AesEncKey[55];

	a1 = FSB[(byte) local_temp[0]];
	a4 = FSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a3 = FSB_16[(byte) local_temp[0]];
	a2 = FSB_24[((regs *) &local_temp[0])->ah];

	local_temp[0] = local_temp[1];
	a2 |= FSB[(byte) local_temp[0]];
	a1 |= FSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a4 |= FSB_16[(byte) local_temp[0]];
	a3 |= FSB_24[((regs *) &local_temp[0])->ah];

	local_temp[0] = local_temp[2];
	a3 |= FSB[(byte) local_temp[0]];
	a2 |= FSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a1 |= FSB_16[(byte) local_temp[0]];
	a4 |= FSB_24[((regs *) &local_temp[0])->ah];

	local_temp[0] = local_temp[3];
	a4 |= FSB[(byte) local_temp[0]];
	a3 |= FSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a2 |= FSB_16[(byte) local_temp[0]];
	a1 |= FSB_24[((regs *) &local_temp[0])->ah];

	pOutput[0] = a1 ^ AesEncKey[56];
	pOutput[1] = a2 ^ AesEncKey[57];
	pOutput[2] = a3 ^ AesEncKey[58];
	pOutput[3] = a4 ^ AesEncKey[59];
}

void AesEncrypt(AESContext* pContext, void * pOutput, void * pInput, int iSize)
{
	iSize = padding( pInput , iSize );
	
	while(iSize >= 16)
	{
		AES_ENCRYPT(((uint32*) pInput), ((uint32 *) pOutput), pContext->AesEncKey);
		pInput = (uint32 *) pInput + 4;
		pOutput = (uint32 *) pOutput + 4;
		iSize -= 16;
	}

	memcpy(pOutput, pInput, iSize);
}