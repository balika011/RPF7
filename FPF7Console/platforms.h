#ifndef platforms_h
#define platforms_h
class platforms
{
public:
	virtual unsigned char* getAESkey() = 0;
	virtual void decompressBuffer(unsigned char* in, unsigned char* out, int insize, int outsize) = 0;
};

class ps3 : public platforms
{
public:
	unsigned char* getAESkey();
	void decompressBuffer(unsigned char* in, unsigned char* out, int insize, int outsize);
};

class xbox360 : public platforms
{
public:
	unsigned char* getAESkey();
	void decompressBuffer(unsigned char* in, unsigned char* out, int insize, int outsize);
};
#endif