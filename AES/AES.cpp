#include <Windows.h>
#include "AES.h"
#include "AESInterns.h"

// block size,it is always 4 in AES
#define Nb 4

// Rotate a word from {a0,a1,a2,a3} => { a3,a0,a1,a2 }
inline uint32 RotWord_Right(uint32 iRotate)
{
	return ((iRotate & 0xff) << 24) | (iRotate >> 8);
}

// use S-Box to replace each uint8 of input uint32 to generate a new output uint32
uint32 SubWord(uint32 input)
{
	uint32 output;
	output = FSB[(byte) input];
	output |= FSB_8[((regs *) &input)->ah];
	input = input >> 16;
	output |= FSB_16[(byte) input];
	output |= FSB_24[((regs *) &input)->ah];
	return output;
}

void InvMixColumnsDecKey(uint32 * pInput, uint32 * pOutput)
{
	uint32 a1, state;

	state = pInput[0];
	a1 = RevRawTable1[(byte) state];
	a1 ^= RevRawTable2[((regs *) &state)->ah];
	state = state >> 16;
	a1 ^= RevRawTable3[(byte) state];
	a1 ^= RevRawTable4[((regs *) &state)->ah];
	pOutput[0] = a1;


	state = pInput[1];
	a1 = RevRawTable1[(byte) state];
	a1 ^= RevRawTable2[((regs *) &state)->ah];
	state = state >> 16;
	a1 ^= RevRawTable3[(byte) state];
	a1 ^= RevRawTable4[((regs *) &state)->ah];
	pOutput[1] = a1;


	state = pInput[2];
	a1 = RevRawTable1[(byte) state];
	a1 ^= RevRawTable2[((regs *) &state)->ah];
	state = state >> 16;
	a1 ^= RevRawTable3[(byte) state];
	a1 ^= RevRawTable4[((regs *) &state)->ah];
	pOutput[2] = a1;


	state = pInput[3];
	a1 = RevRawTable1[(byte) state];
	a1 ^= RevRawTable2[((regs *) &state)->ah];
	state = state >> 16;
	a1 ^= RevRawTable3[(byte) state];
	a1 ^= RevRawTable4[((regs *) &state)->ah];
	pOutput[3] = a1;
}

void AesSetKey(AESContext* pContext, void * key)
{
	uint8 * pKey = (uint8 *) key;

	for (int i = 0; i < 8; ++i)
	{
		pContext->AesEncKey[i] = (pKey[i * 4]) | (pKey[i * 4 + 1] << 8) | (pKey[i * 4 + 2] << 16) | (pKey[i * 4 + 3] << 24);
	}

	for (int i = 8; i < Nb * 15; ++i)
	{
		if (i % 8 == 0)
			pContext->AesEncKey[i] = pContext->AesEncKey[i - 8] ^ (SubWord(RotWord_Right(pContext->AesEncKey[i - 1])) ^ RCON[i / 8]);
		else if ((i % 8) == 4)
			pContext->AesEncKey[i] = pContext->AesEncKey[i - 8] ^ (SubWord(pContext->AesEncKey[i - 1]));
		else
			pContext->AesEncKey[i] = pContext->AesEncKey[i - 8] ^ pContext->AesEncKey[i - 1];
	}

	memcpy(&pContext->AesDecKey[14 * Nb], pContext->AesEncKey, Nb * sizeof(uint32));
	memcpy(pContext->AesDecKey, &pContext->AesEncKey[14 * Nb], Nb * sizeof(uint32));
	for (int i = 1; i < 14; i++)
		InvMixColumnsDecKey(&pContext->AesEncKey[i * Nb], &pContext->AesDecKey[(14 - i) * Nb]);
}