#include <Windows.h>
#include "AES.h"
#include "AESInterns.h"

#define AES_DECRYPT_BLOCK_32\
	a1 = RevTable1[(byte) local_temp[0]]; \
	a2 = RevTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a3 = RevTable3[(byte) local_temp[0]]; \
	a4 = RevTable4[((regs *) &local_temp[0])->ah]; \
	\
	local_temp[0] = local_temp[1]; \
	a2 ^= RevTable1[(byte) local_temp[0]]; \
	a3 ^= RevTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a4 ^= RevTable3[(byte) local_temp[0]]; \
	a1 ^= RevTable4[((regs *) &local_temp[0])->ah]; \
	\
	local_temp[0] = local_temp[2]; \
	a3 ^= RevTable1[(byte) local_temp[0]]; \
	a4 ^= RevTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a1 ^= RevTable3[(byte) local_temp[0]]; \
	a2 ^= RevTable4[((regs *) &local_temp[0])->ah]; \
	\
	local_temp[0] = local_temp[3]; \
	a4 ^= RevTable1[(byte) local_temp[0]]; \
	a1 ^= RevTable2[((regs *) &local_temp[0])->ah]; \
	local_temp[0] = local_temp[0] >> 16; \
	a2 ^= RevTable3[(byte) local_temp[0]]; \
	a3 ^= RevTable4[((regs *) &local_temp[0])->ah];

void AES_DECRYPT(uint32 * _pInput, uint32 * _pOutput, uint32 * local_key)
{
	register uint32 a1, a2, a3, a4;
	ALIGN uint32 local_temp[4];

	local_temp[0] = _pInput[0] ^ local_key[0];
	local_temp[1] = _pInput[1] ^ local_key[1];
	local_temp[2] = _pInput[2] ^ local_key[2];
	local_temp[3] = _pInput[3] ^ local_key[3];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[4];
	local_temp[1] = a2^local_key[5];
	local_temp[2] = a3^local_key[6];
	local_temp[3] = a4^local_key[7];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[8];
	local_temp[1] = a2^local_key[9];
	local_temp[2] = a3^local_key[10];
	local_temp[3] = a4^local_key[11];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[12];
	local_temp[1] = a2^local_key[13];
	local_temp[2] = a3^local_key[14];
	local_temp[3] = a4^local_key[15];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[16];
	local_temp[1] = a2^local_key[17];
	local_temp[2] = a3^local_key[18];
	local_temp[3] = a4^local_key[19];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[20];
	local_temp[1] = a2^local_key[21];
	local_temp[2] = a3^local_key[22];
	local_temp[3] = a4^local_key[23];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[24];
	local_temp[1] = a2^local_key[25];
	local_temp[2] = a3^local_key[26];
	local_temp[3] = a4^local_key[27];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[28];
	local_temp[1] = a2^local_key[29];
	local_temp[2] = a3^local_key[30];
	local_temp[3] = a4^local_key[31];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[32];
	local_temp[1] = a2^local_key[33];
	local_temp[2] = a3^local_key[34];
	local_temp[3] = a4^local_key[35];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[36];
	local_temp[1] = a2^local_key[37];
	local_temp[2] = a3^local_key[38];
	local_temp[3] = a4^local_key[39];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[40];
	local_temp[1] = a2^local_key[41];
	local_temp[2] = a3^local_key[42];
	local_temp[3] = a4^local_key[43];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[44];
	local_temp[1] = a2^local_key[45];
	local_temp[2] = a3^local_key[46];
	local_temp[3] = a4^local_key[47];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[48];
	local_temp[1] = a2^local_key[49];
	local_temp[2] = a3^local_key[50];
	local_temp[3] = a4^local_key[51];

	AES_DECRYPT_BLOCK_32;

	local_temp[0] = a1^local_key[52];
	local_temp[1] = a2^local_key[53];
	local_temp[2] = a3^local_key[54];
	local_temp[3] = a4^local_key[55];

	a1 = RSB[(byte) local_temp[0]];
	a2 = RSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a3 = RSB_16[(byte) local_temp[0]];
	a4 = RSB_24[((regs *) &local_temp[0])->ah];

	local_temp[0] = local_temp[1];
	a2 |= RSB[(byte) local_temp[0]];
	a3 |= RSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a4 |= RSB_16[(byte) local_temp[0]];
	a1 |= RSB_24[((regs *) &local_temp[0])->ah];

	local_temp[0] = local_temp[2];
	a3 |= RSB[(byte) local_temp[0]];
	a4 |= RSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a1 |= RSB_16[(byte) local_temp[0]];
	a2 |= RSB_24[((regs *) &local_temp[0])->ah];

	local_temp[0] = local_temp[3];
	a4 |= RSB[(byte) local_temp[0]];
	a1 |= RSB_8[((regs *) &local_temp[0])->ah];
	local_temp[0] = local_temp[0] >> 16;
	a2 |= RSB_16[(byte) local_temp[0]];
	a3 |= RSB_24[((regs *) &local_temp[0])->ah];

	_pOutput[0] = a1 ^ local_key[56];
	_pOutput[1] = a2 ^ local_key[57];
	_pOutput[2] = a3 ^ local_key[58];
	_pOutput[3] = a4 ^ local_key[59];
}

void AesDecrypt(AESContext* pContext, void * pOutput, void * pInput, int iSize)
{
	while (iSize >= 16)
	{
		AES_DECRYPT(((uint32 *) pInput), ((uint32 *) pOutput), pContext->AesDecKey);
		pInput = (uint32 *) pInput + 4;
		pOutput = (uint32 *) pOutput + 4;
		iSize -= 16;
	}

	memcpy(pOutput, pInput, iSize);
}