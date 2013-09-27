#ifndef __EF_AES__
#define __EF_AES__

#define BLOCKBUFSZ  60

#ifndef uint8
typedef unsigned char uint8;
#endif

#ifndef uint16
typedef unsigned short uint16;
#endif 

#ifndef uint32
typedef unsigned int uint32;
#endif

#ifndef uint64
typedef unsigned __int64 uint64;
#endif

#ifdef _WIN64
#define ALIGN  __declspec(align(64))
#else
#define ALIGN  __declspec(align(32))
#endif

typedef struct _AESContext_
{
	uint32 AesEncKey[BLOCKBUFSZ];
	uint32 AesDecKey[BLOCKBUFSZ];
} AESContext;

//_AES_KEY_LENGTH_
#define AES_KEY_128BIT  0
#define AES_KEY_192BIT  1 
#define AES_KEY_256BIT  2

// set key and initial vector
extern void AesSetKey(AESContext* pContext, void * key);

// encrypt APIs
extern void AesEncrypt(AESContext* pContext, void * pOutput, void * pInput, int iSize);

extern void AesDecrypt(AESContext* pContext, void * pOutput, void * pInput, int iSize);
#endif //__EF_AES__

